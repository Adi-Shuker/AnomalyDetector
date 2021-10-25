# Flight Anomaly Detector

# About The Project

Flight Detector is a server that allows the user to enter flight data and return his anomalys.<br>
Users are flight researchers or pilots or simply people who want to view anomalies in the flight.<br>
Flight data includes, among other things, the position of the rudders, the speed, the altitude, the direction, etc., and they are recorded into a csv file, which can be load
in our server. The server will receive the data and analyse it in order to find anomalies.<br>

To use the user has to load two data files to the server: 
1) learning csv file that contains the values of the attributes at each moment during the flight, from this file we learn the normal behaveor of every feature in the flight.
2) testing csv file - in this file we check according spcific algotirhm if during the flight the thete was anomaly to some feature and eport for it.

# Features

* Menu to select the desired action.<br>
* looks like this:<br>
    Welcome to the Anomaly Detection Server.
    Please choose an option:
    1. upload a time series csv file
    2. algorithm settings
    3. detect anomalies
    4. display results
    5. upload anomalies and analyze results
    6. exit
* the user also can chenge the algorithm setting and analyze the results<br>
* MainPage that contains:<br>
 • mediaBar to play the movie, change the speed, stop, go back to the beginning/end<br>
 • joystick and sliders that move according to the position of the airplane<br>
 • data display that contains altimeter, airspeed, heading, pitch, roll, yaw... <br>
 • a list of all the timestep in which there are anomalies<br>
 • graphs related to the flights attributes<br>

# Getting Started
# Download

Options to download the app: 
- Clone the repository https://github.com/Adi-Shuker/flight-detector.
- Download the zip.


