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



static char http_header[] = {
  			"HTTP/1.0 200 OK\r\nServer: ardrone\r\nContent-Type: text/html\r\n\r\n"
            "<HTML><HEAD><TITLE>libarpilot</TITLE>"};


static char css[] = {
		"<style type=\"text/css\">"
		  "body {"
		    "background-color: #444;"
		  "}"
		  "table {"
		    "border-collapse: collapse;"
		  "}"
		  "td {"
		   "padding: 4px;"
		  "}"
		  "td, th {"
		    "border: 0px solid #baf;"
		  "}"
		  "td#blank {"
		    "border: none;"
		  "}"
		  "a {"
		    "padding: 0.1em;"
		    "padding-bottom: 0;"
		    "color:            #000;"
		    "text-decoration:  none;"
		    "border:       1px solid gray;"
		    "border-left:  0;"
		    "border-right: 0;"
		    "font-size: 24px;"
		    "font-family: monospace;"
		  "}"
		  "h1 {"
		    "font-family: monospace;"
		    "font-size: 24px;"
		    "color: #000;"
		    "background-color: #aaaaaa;"
		  "}"
		  "a:link {"
		    "background-color: #99b440;"
		  "}"
		  "a:visited {"
		    "background: #99b440;"
		  "}"
		  "a:hover, a:focus {"
		    "background:    #ff5900;"
		    "outline-color: #ffc873"
		  "}"
  		  "a:active {"
		    "background:   #689ad3;"
		    "border-style: dotted;"
		  "}"
		  ".mtest {"
		    "color: #bada55"
		    "text-shadow: 0 0 20px black;"
		  "}"
		  "span#text {"
		    "background-color: #4488ee;"
		    "padding: 4px;"
		    "display: innline-table;;"
		    "transform: scaleX(2.5);"
		    "color: #112211;"
		    "text-shadow: "
		      "0 2px 2px rgba(255,255,255,0.7), "
		      "0 10px 4px rgba(0,0,0,0.5);"
		    "font-size: 22px;"
	  	  "}"
		  "span#text:hover {"
		    "transition: all 0.2s ease;"
		    "transform: scaleX(2.5) translateY(4px);"
		    "text-shadow:"
		      "0 1px 1px rgba(0,0,0,0.5);"
		  "}"
		  "span {"
		    "display: innline-table;;"
		    "padding: 8px; "
		    "transform: scaleX(2.5);"
		    "color: #4488ee;"
		    "text-shadow: "
		      "0 2px 2px rgba(255,255,255,0.7), "
		      "0 10px 4px rgba(0,0,0,0.5);"
		    "font-size: 48px;"
		  "}"
		  "span:hover {"
		    "transition: all 0.2s ease;"
		    "transform: scaleX(2.5) translateY(4px);"
		    "text-shadow:     "
		      "0 1px 1px rgba(0,0,0,0.5);"
		    "}"
		  "</style>"};

char doc_command[] = {
		"</HEAD>"
			"<BODY>"
		"<script type=\"application/javascript\">"
		  "function docom(command) {"
		    //"	alert(command);"
		    "var req = new XMLHttpRequest();"
		    "req.open('GET', 'cmd.html?cmd='+command, false);"
		    "req.send(command);"
		  "}"
		"</script>"
		"<H1>Control Panel:</H1><P>"
			  "<table summary=\"control panel\" >"
			    "<tr>"
			      "<td id=\"blank\"></td>"
			      "<td onclick=docom('fwd')>"
			        "<span class=\"mtest\">&#x25b2</span>"
			      "</td>"
			      "<td id=\"blank\"></td>"
			      "<td onclick=docom('start')>"
			        "<span class=\"mtest\" id=\"text\">START</span>"
			      "</td>"
			      "<td id=\"blank\"></td>"
			      "<td onclick=docom('up') >"
			        "<span class=\"mtest\">&#x25b2</span>"
			      "</td>"
			      "<td id=\"blank\"></td>"
			    "</tr>"
			    "<tr>"
			      "<td onclick=docom('left')>"
			        "<span class=\"mtest\">&#x25c4</span>"
			      "</td>"
			      "<td onclick=docom('stop')>"
			        "<span class=\"mtest\">&#x25cf</span>"
			      "</td>"
			      "<td onclick=docom('right')>"
			        "<span class=\"mtest\">&#x25ba</span>"
			      "</td>"
			      "<td onclick=docom('rec')>"
			        "<span class=\"mtest\" id=\"text\">VIDEO</span>"
			      "</td>"
			      "<td onclick=docom('rotl')>"
			        "<span class=\"mtest\">&#x25c4</span>"
			      "</td>"
			      "<td id=\"blank\"></td>"
			      "<td onclick=docom('rotr')>"
			        "<span class=\"mtest\">&#x25ba</span>"
			      "</td>"
			    "</tr>"
			    "<tr>"
			      "<td id=\"blank\"></td>"
			      "<td onclick=docom('rev')>"
			        "<span class=\"mtest\">&#x25bc</span>"
			      "</td>"
			      "<td id=\"blank\"></td>"
			      "<td onclick=docom('land')>"
			        "<span class=\"mtest\" id=\"text\">LAND</span>"
			      "</td>"
			      "<td id=\"blank\"></td>"
			      "<td onclick=docom('down')>"
			        "<span class=\"mtest\">&#x25bc</span>"
			      "</td>"
			      "<td id=\"blank\"></td>"
			    "</tr>"
			  "</table>"
			"</BODY>"
	      "</HTML>"};

