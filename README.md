SeniorDesign
============

Overview of Pathfinder Headers
------------------------------
This file includes 4.h files, and 3 implementation files
DEFINES.H requires no implementation because it is entirely #define statements to declare global constants
CriticalPath.h stores the critical path of the current maze as a list of numbers
grid.h interprets the numbers into coordinates and vice versa
RoboCtl.h uses the said coordinates and decides how the robot needs to turn or move to reach them. Alternatively, it translates the robot's movements into coordinates

Instructions for upload
-----------------------
Arduino needs to be instructed on where to find these header files. To use them, just go to [[Sketch>>Import Library...>>Add Library...]] and find the pathfinder folder containing these files. Open it to import to arduino.
Pathfinder will be added to the list of available libraries automatically.
Open the main function sketch, and click on [[Sketch>>Import Library...>>Pathfinder]] near the very bottom of the list.
This will put the relevant #includes at the top of the Arduino sketch. At this point, click verify & upload, and the code will be uploaded to the Arduino

Description of Testcode Folder
------------------------------
This folder contains code that was used for testing the code, but is not part of the final program (though parts of it will most likely be recycled)