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

#include <TinyGPS.h>
#include <SoftwareSerial.h>

SoftwareSerial GPS = SoftwareSerial(4,3);
TinyGPS        gps;
unsigned long fix_age = 0;

float lat_home, lon_home;
float lat_wp, lon_wp;
int flag_flying = 0;
float flat, flon;
unsigned long age;
int wp_reached = 0;

void setup()
{
  bool fixed = false;
  Serial.begin(115200);
  GPS.begin(9600);
  pilot_setup();
}

int gps_counter = 0;
int acquired = 0;
int i = 1;

void loop()
{ 
  if (GPS.available()) 
  {
    //Serial.println("HDOP");
    //Serial.println(gps.hdop());
     int byte = GPS.read();
     //Serial.write(byte); 
     if(gps.encode(byte) && gps.hdop() < 150) 
     {
       gps.f_get_position(&flat, &flon, &fix_age);
       acquired = 1;
     }
  }

  if(acquired)
  {
    drone_sendpos();
    
//    Serial.print("$ECHO,#Setting Home Position and Waypoint \n");
    while(i > 0)
    {
      drone_sethomepos();  // Set Home Position, set global variables lat_home, lon_home
//      drone_setwp(54.900700, 9.807400);   // Set Waypoint Position (longitude, latitude)
      //drone_setwp(54.913328, 9.779755);   // Set Waypoint Position (longitude, latitude)
//      drone_setwp(54.9060592651, 9.7946395874); 
      //drone_setwp(54.900500, 9.807990);  
      drone_setwp(54.89842, 9.81058);
//      Serial.print("Distance to wp:");
      Serial.println(calculate_distance(lat_home, lon_home, lat_wp, lon_wp));
      while(calculate_distance(lat_home, lon_home, lat_wp, lon_wp) > 500) //Stay in loop when distance>500m
      {
//        Serial.print("$ECHO,#Distance too great! Flight Aborted! \n");
//        Serial.print("Distance to wp:");
//        Serial.println(calculate_distance(lat_home, lon_home, lat_wp, lon_wp));
        delay(1000);
        while(1) delay(10000);  // Never fly, abort mission
      }
      drone_takeoff();
      Serial.print("$ECHO,#We Have Liftoff! \n");
      i--;
    }
    
    float angle = gps.course_to (flat, flon, lat_wp, lon_wp) * 1000; // $HEAD need 1/1000 of degree
    float distance_to_wp = gps.distance_between(flat, flon, lat_wp, lon_wp);
    
    head_to_target(angle);
    drone_move(distance_to_wp);
    
    if (distance_to_wp < 3) 
    {
      drone_hove();
      delay(15000);
      if (!wp_reached){
        drone_setwp(lat_home,lon_home);
        wp_reached = 1 ;
      }        
      else drone_land();
    }
    acquired = 0;
  } 
}



void pilot_setup()
{ // Executes the binary on AR.Drone 2.0, the arpilot code has to be compiled for arm architecture
  Serial.print("\n\n\n\n\n$QUIT\n\n");
  delay(1000);
  Serial.print("cat - | ./data/video/arpilot\n");      //no more USB, binary file in /data/video folder
  delay(4000);
  Serial.print("cat - | ./data/video/arpilot\n");      // Send it once more for safety
  delay(4000);

  /*Limits: max_yaw 2.50
             max_vz  700
          max_euler 0.30
           altitude 50000 (50m)*/
  Serial.print("$LIMI,250,700,30,50000\n"); /*Not sure that this works yet*/
  Serial.print("$TRIM\n");
  delay(1000);
}

void drone_sethomepos()
{
  lat_home = flat;
  lon_home = flon;
//  Serial.print("Home Coordinates: ");
//  Serial.print(flat);
//  Serial.print(", ");
//  Serial.println(flon);
}

void drone_sendpos()
{ // Update Drone executable, commands sent as SDTDIN.
  Serial.print("$PLON,");
  Serial.print(flon,10);
  Serial.print("\n");
  
  Serial.print("$PLAT,");
  Serial.print(flat,10);
  Serial.print("\n");

  //Serial.print("$PCOU,");
  //Serial.print(course_b,10); // Heading is calculated knowing current position and waypoint position
  //Serial.print("\n");
  
//  Serial.print("$HDOP,");
//  Serial.print(gps.hdop());
//  Serial.print("\n");
}

void drone_setwp(float latitude, float longitude)
{
  lat_wp = latitude;
  lon_wp = longitude;
}

float calculate_distance(float lat_home, float lon_home, float lat_wp, float lon_wp)
{
  return gps.distance_between(lat_home, lon_home, lat_wp, lon_wp);
}
 
void drone_takeoff()
{
  Serial.print("$STAT,1\n");
  delay(10000);
  Serial.print("$HOVE\n");
  delay(5000);
  Serial.print("$CALI\n");
  delay(6000);
  Serial.print("$ALTI,2000,1\n");
  delay(3000);
  flag_flying = 1;
}

void head_to_target(float angle)
{
   Serial.print("$HEAD,");
   Serial.print(angle,0);
   Serial.print("\n");
   //delay(500);
}

void drone_move(float dist_to_wp)
{
//  Serial.print("$ECHO,#");
//  Serial.println(dist_to_wp);
  int kp = (-10);
  float tpitch = dist_to_wp * kp;
//  Serial.print("$ECHO,#");
//  Serial.println(tpitch);
  if(tpitch > 0) tpitch = 0;
  if(tpitch < -200) tpitch = -200;
  
//  Serial.print("$ECHO,#");
//  Serial.println(tpitch);
  Serial.print("$MOVE,");
  Serial.print(0);
  Serial.print(",");
  Serial.print(tpitch,0);
  Serial.print(",");
  Serial.print(0);
  Serial.print(",");
  Serial.print(0);
  Serial.print("\n");
  delay(200);
  Serial.print("$ALTI,2000,1\n");
}

void drone_hove()
{
  Serial.print("$HOVE");
  Serial.print("\n");
}

void drone_land()
{
  Serial.print("$STAT,0");
  Serial.print("\n");
  flag_flying = 0;
}

