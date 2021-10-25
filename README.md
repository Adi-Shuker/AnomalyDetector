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

* Menu to select the desired action.
* looks like this:
    Welcome to the Anomaly Detection Server.
    Please choose an option:
    1. upload a time series csv file
    2. algorithm settings
    3. detect anomalies
    4. display results
    5. upload anomalies and analyze results
    6. exit
* MainPage that contains:<br>
 • mediaBar to play the movie, change the speed, stop, go back to the beginning/end<br>
 • joystick and sliders that move according to the position of the airplane<br>
 • data display that contains altimeter, airspeed, heading, pitch, roll, yaw... <br>
 • a list of all the timestep in which there are anomalies<br>
 • graphs related to the flights attributes<br>

   <br>
 ![alt tag](https://user-images.githubusercontent.com/81378726/114765868-5c927e80-9d6e-11eb-8d67-b622cb773e00.jpg)
   <br>

# Getting Started

# Prerequisites

1) Install the flight simulator - FlightGear(https://www.flightgear.org/) version 2020.3.6. (for all OS)
2) Put the XML file into the folder in which you have installed the FlightGear app, and inside /data/protocol (for example C:\Program Files\FlightGear 2020.3.6\data\Protocol).
3) Open the FlightGear and in the Additional Settings write the lignes below: <br>

--generic=socket,in,10,127.0.0.1,5400,tcp,playback_small <br>
--fdm=null <br>


# Download

Options to download the app: 
- Clone the repository https://github.com/Adi-Shuker/flight-detector.
- Download the zip.

# How to open FlightGear Application
FlightGear is an open source simulator that allows research.
To define what data is about we need to add XML file to the folder you download the FlightGear : 0/data/protocol. 
Example for windows user: C:\Program Files\FlightGear 2020.3.6\data\Protoco
Because we want to use him differently in the command line in the setting tab  we enter the next commands:
--generic=socket,in,10,127.0.0.1,5400,tcp,playback_small
 --fdm=null
and than press fly.

# Usage
Run the FlightGear and the Flight Detector app. <br>
In the HomePage load your csv, xml and dll files and choose an anomaly detector type. <br>
To start flying  press *Start Flying*.<br>
Good fly! <br>
<br>
 ![alt tag](https://user-images.githubusercontent.com/81378726/114764020-2227e200-9d6c-11eb-8b38-6225a6a9d2a0.jpg)
<br>

# Code Design and UML:
<br>


 ![alt tag](https://user-images.githubusercontent.com/81378726/114763777-dbd28300-9d6b-11eb-87f0-c4912a7c43ba.PNG)
<br>

The architecture of the app is based on the *MVVM* architectural pattern. <br>
Model–view–viewmodel (MVVM) is a software architectural pattern that facilitates the separation of the development of the graphical user interface (the view)<br>
The view is the appearance of what the user sees on the screen. It displays a representation of the model and receives the user's interaction with the view (mouse clicks,
keyboard input, screen tap gestures, etc.), and it forwards the handling of these to the view model via the data binding (properties, event callbacks) that is defined to link the view and view model.<br>
The view model is an abstraction of the view exposing public properties and commands. The view directly binds to properties on the view model to send and receive updates. <br>
The Model interacts with the FlightGear app via TCP connection like a client-server.

# Video Explanation 

https://youtu.be/230t_UPn8s0

# Contributors
This program was developed by Adi-Shuker, yairshp, Shana026