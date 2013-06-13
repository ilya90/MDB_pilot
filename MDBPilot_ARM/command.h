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


#include <stdint.h>

#ifndef COMMAND_H_
#define COMMAND_H_

void set_command_timestamp();

int command_set_lon(float lon);

int command_set_lat(float lat);

int command_set_alt(int lat);

int command_set_course(int course);

int command_set_hdop(int hdop);

int command_state(int state);

int command_move(int roll, int pitch, int gaz, int yaw);

int command_trim(void);

int command_hover(void);

int command_cali(void);

int command_print(void);

int command_record(int state);

int command_head(int angle);

int command_alti(int altitude, int monitor_state);

int command_turn(int delta_angle);

int command_rise(int delta_altitude);

int command_error(int my_alti, int my_phi);

int command_limit(int yaw, int vz, int angle, int altitude);

void command_idle();

void update_drone();

#endif /* COMMAND_H_ */
