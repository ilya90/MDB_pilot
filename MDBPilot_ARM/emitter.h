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


#ifndef EMITTER_H_
#define EMITTER_H_

void addATCTRL(char *buffer, int key, int val);

void addATCONFIGID(char *buffer, char *session, char *profile ,char *application);

void addATCONFIG(char *buffer, char* key, char* val);

void setSESSIONID(char *buffer, char *session);

void setPROFILEID(char *buffer, char *profile);

void setAPPLICATIONID(char *buffer, char *application);

void addATPCMD(char *buffer, int roll, int pitch, int gaz, int yaw );

void addATCWDG(char *buffer);

void addATREF(char *buffer, int val);

void addATFTRIM(char *buffer);

void addATCALIB(char *buffer);

#endif /* EMITTER_H_ */
