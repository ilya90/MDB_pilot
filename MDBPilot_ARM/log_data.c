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
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "log_data.h"
#include "states.h"

int i = 1;
double start_time;

void logdata(void){
	while( i > 0 ){ // Only do this once
		gettimeofday(&ts, NULL);
		start_time = ts.tv_sec+(ts.tv_usec/1000000.0);
		i--;
	}
	gettimeofday(&ts, NULL);
	double dTime1 = ts.tv_sec+(ts.tv_usec/1000000.0);
	fprintf(f, "%f; %f; %f; %d; %f; %f; %f; %f; %f; %f; %d\n",
						navdata_unpacked.navdata_demo.vx,
						navdata_unpacked.navdata_demo.vy,
						navdata_unpacked.navdata_demo.vz,
						navdata_unpacked.navdata_demo.altitude,
						navdata_unpacked.navdata_demo.psi,
						navdata_unpacked.navdata_demo.phi,
						navdata_unpacked.navdata_demo.theta,
						pos_lat,
						pos_lon,
						dTime1-start_time,
						navdata_unpacked.navdata_demo.vbat_flying_percentage );
} // vx, vy, vz, alt, psi, phi, theta, lat, lon, time, batt
