# Flight Anomaly Detector

# About The Project

Flight Detector is a server that allows the user to enter flight data and return his anomalies.<br>
Users are flight researchers or pilots or simply people who want to view anomalies in the flight.<br>
Flight data includes, among other things, the position of the rudders, the speed, the altitude, the direction, etc., and they are recorded into a csv file, which can be load
in our server. The server will receive the data and analyze it in order to find anomalies.<br>

To use the user has to load two data files to the server: 
1) learning csv file that contains the values of the attributes at each moment during the flight, from this file we learn the normal behavior of every feature in the flight.
2) testing csv file - in this file we check according to specific algorithm if during the flight an anomaly occurred in one of the features and report for it.

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
* The user also can change the algorithm setting and analyze the results<br>

# Getting Started
# Download

Options to download the app: 
- Clone the repository https://github.com/Adi-Shuker/AnomalyDetector
- Download the zip.


