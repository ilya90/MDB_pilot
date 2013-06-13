 # This file is part of mdbpilot.
 #
 # Copyright (C) 2013  University of Southern Denmark
 #
 #   mdbpilot is free software: you can redistribute it and/or modify
 #   it under the terms of the GNU General Public License as published by
 #   the Free Software Foundation, either version 3 of the License, or
 #   (at your option) any later version.
 #
 #   mdbpilot is distributed in the hope that it will be useful,
 #   but WITHOUT ANY WARRANTY; without even the implied warranty of
 #   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #   GNU General Public License for more details.
 #
 #   You should have received a copy of the GNU General Public License
 #   along with mdbpilot.  If not, see <http://www.gnu.org/licenses/>.

 # Note:
 # The origin of the contents are multiple.
 # Some of the Content was pulled from the AR.Drone programming documentation
 # available on Parrot's home page and several programming examples available
 # on the internet.
 # Also some code was modified and reused from the github repository
 # https://github.com/dherrendoerfer/ARPilot


 
CFLAGS = -O2 -Wall
CC = arm-linux-gnueabi-gcc
INSTALL = install
TARGET = /usr/sbin

LIB_OBJS=command.o controller.o emitter.o init.o log.o monitor.o navdata.o network.o pilot.o web.o log_data.o
PROG_OBJS=arpilot.o
LIB=arpilot.a
PROG=arpilot

all: lib arpilot 

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

lib: $(LIB_OBJS)
	ar r $(LIB) $(LIB_OBJS)

arpilot: $(PROG_OBJS) lib
	$(CC) $(CFLAGS) $(PROG_OBJS) $(LIB) -o $(PROG)

install: $(PROG)
	$(INSTALL) $(PROG) $(TARGET)/$(PROG)

clean:
	rm -f $(PROG_OBJS) $(LIB_OBJS) $(PROG) $(LIB)
