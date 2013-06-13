/*
 * This file is part of mdbpilot.
 *
 * Copyright (C) 2013  University of Southern Denmark
 *
 *   mdbpilot is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   mdbpilot is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with mdbpilot.  If not, see <http://www.gnu.org/licenses/>.
 
 * Note:
 * The origin of the contents are multiple.
 * Some of the Content was pulled from the AR.Drone programming documentation
 * available on Parrot's home page and several programming examples available
 * on the internet.
 * Also some code was modified and reused from the github repository
 * https://github.com/dherrendoerfer/ARPilot
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include "command.h"
#include "states.h"
#include "arpilot.h"

int emergency_timestamp = 0;
int emergency_active = 0;
float z_hat_old	= 0.0;
struct timeval ts;

int auto_monitor()
{
	int ret = 0;

    if (navdata_valid) {
        /* Low Battery helpers
         * 10% -> go to 5m altitude if above 6m
         *  5% -> Land                            */
         if (navdata_unpacked.navdata_demo.vbat_flying_percentage < 10){
        	 if (navdata_unpacked.navdata_demo.altitude + err_drone_altitude > 6000) {
        		 pilot_altitude = 5000;
        		 pilot_alti = 1;
        		 ret = 1;
        	 }
        }

        if (navdata_unpacked.navdata_demo.vbat_flying_percentage < 5){
            if (drone_fly == 1){
                drone_fly = 0;
                ret = 2;
            }
        }

        /* Flight height helpers
         * < 60cm -> go to 85cm altitude         */
        if (drone_fly && (navdata_unpacked.navdata_demo.altitude < 800)){
            pilot_altitude = 900;
            pilot_alti = 1;
            ret = 4;
        }

        /* Flight height helpers
         * try to hold the altitude exact to .5m          */
//        if (drone_fly && monitor_alti && !pilot_alti) {
//            if ( abs(navdata_unpacked.navdata_demo.altitude
//                 + err_drone_altitude - pilot_altitude) > 500) {
//                int alt = navdata_unpacked.navdata_demo.altitude
//                      + err_drone_altitude;
//
//                if(alt < pilot_altitude){
//                    drone_gaz = 200;
//                }
//                else {
//                    drone_gaz = -200;
//                }
//                ret = 8;
//            }
//        }
        float Kp_altitude 	= 3;

        // Stabilize altitude with a P-controller, call for example "#ALTI,3000,1" in Arduino
        // The Flag after the parameter has to be set to 1
        if (drone_fly && monitor_alti && !pilot_alti) {
        	drone_gaz = Kp_altitude*(pilot_altitude - navdata_unpacked.navdata_demo.altitude);
        	if (drone_gaz > 900) drone_gaz = 900;
        	if (drone_gaz < -900) drone_gaz = -900;
        }

        float Kp_roll 		= 0;
        float Kp_vy 		= 0.4;

        drone_roll = (-Kp_roll * navdata_unpacked.navdata_demo.phi) +
        			 (-Kp_vy * navdata_unpacked.navdata_demo.vy);   // Stabilize side disturbance

        /* Emergency detect
         * Switch off video recording after 20s  */
        if (navdata_unpacked.mykonos_state & MYKONOS_EMERGENCY_MASK) {
            struct timeval ts;

            ret = 16;

            gettimeofday(&ts, 0);

            if (!emergency_active) {
                emergency_timestamp=ts.tv_sec;
                emergency_active = 1;
                printf("!EMER\n");
            }
            else {
                if(is_recording && (emergency_active == 1)&& (ts.tv_sec == emergency_timestamp + 20)) {
                    // stop recording
                    command_record(0);
                    emergency_active = 2;
                    ret = 128;
                }
                else if((emergency_active == 2) && (ts.tv_sec == emergency_timestamp + 25)) {
                	// record till the end ....
                    command_record(1);
                    emergency_active = 3;
                    ret = 128;
                }
            }
        }
        else {
        	if (emergency_active)
        		emergency_active = 0; // reset emergency flag .... continue
        }
    }

    return ret;
}

//float altitude_observer(double L)
//{
//	float z_hat = 0.0;
//
//	if(drone_fly) // and something more I guess
//	{
//		T_old = Ts;
//
//		z_hat = z_hat_old + Ts*(navdata_unpacked.navdata_demo.vz + L*((float)navdata_unpacked.navdata_demo.altitude - z_hat_old));
//		z_hat_old = z_hat;
//	}
//	return z_hat;
//}
