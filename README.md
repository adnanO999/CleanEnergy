# CleanEnergy
![onsolarpanel](https://github.com/adnanO999/CleanEnergy/assets/88556508/d074ffef-ac9d-475f-83a0-5209ce02945e)

As it is obvious, the project is designed to clean solar panels. It might be an easy task however from simple observations, several problems might arise such as difficulties in covering the entire area, electrocution. Therefore I decided to build this project for the Mechatronics System design I. However I took one step further and used computer vision to detect the area of cleaning instead of relying only on sensors.



In this article I will be focusing on the implementation of each part and mainly the mechanical design wich was the core of the project and I was responsible of carrying out the design and implementation along with other tasks taht will be mentioned in what follows.

The project can be devided in several parts:
* Research 
* Mechanical design 
* assembling and wiring hardware 
* Code 
   * S shape path1 and path2 
   * Bluetooth communication/app 
   * MPU 6050 
* Report/presentaion
* Additional Improvements outside the course scope (personal work)

Each part will be expalined along

# Research and Motivation
## Dust and Efficiency Reduction
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/d8e749bf-2ea2-43f7-8b14-085d5ad663f0)

Solar energy is the most abundant of all energy resources and can be easily employed through the installation of solar panels constructed of photovoltaic cells (PV) that converts the sun radiation to electricity by a process of photon absorption and electrons excitation. 

However solar panels could experience efficiency reduction due to accumulated dust or unclean panels blocking solar radiation from interacting with PV cells. This is a major issue since the light obstruction materials (accumulation of dirt or particles like dust, sand, and moss) pose as external resistances that reduce solar photovoltaic performance. It was found that the external resistance could reduce the photovoltaic performance by up to 85% and the value of short circuit current, power decrease with respect the amount of dust on the solar panel.

## Modular Design and Angle Obstacle
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/74b90a17-df1c-4abd-b615-2ce17e84504f)

we can notice that the first obstacle is the issue related to the angle. If we need to build a robot, we need to overcome slope slippage. This is a main challenge since our target is to build modular cleaning mechanism capable of covering different solar panels installation rather than static mechanism such as conventional wipers available for large firms

# Mechanical Design: Caterpillar Model

The previous issue of slopes cannot be resolved using a standard wheel-based robot since these types of robots have small wheels providing reduced contact area with the surface. Any plastic wheel will fail to provide the necessary grip to overcome slopes.
For this purpose I started my research and opted for caterpillar design. However the available robots in the market were very small or made of plastic which will not help.
For this reason I started several design iterations listed below with a brief description:

## Fisrt Design: Use of Car Seat and Customized Belts
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/742e32e4-a113-4442-b2c0-ef9d522e570f)
As we can see the chassis is made of a car seat which was our initial starting point. We wanted to use the back of the seat as our cleaner since it had the ability to move up and down. Moreover we did not have appropriate belts thus we needed to cut one long belt and connect it. We discovered that the belts were not strongly bonded which will create slippage problems and malfunctioning when moving from one panel to the other

## Second Design: Customized Chassis Design and Use of car Window Motor
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/57960882-e7e5-4690-83eb-eafccccec29b)
As we can notice this time, we designed a new compact chassis that include polyamide wheels that will help us moving from one panel to the other easily. Moreover, we can notice that we added a gear and motors to make the caterpillar move. However, the gears were customized to fit the belt teeth which led to slippage once some teeth were jumped over. To solve this problem, we needed to maintain good contact with our gear. This will be done using pulleys that compress the belt to the gear. 

## Third Design: New Belts and Use of Wiper Motor 
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/794fa83b-c9c3-4a85-9460-ba0cca452181)
In this design we can see an enhancement of the previous design by adding fixed pulley to press the belt toward the gear. As such we avoid the case of belt’s teeth jumping more than one at a time. However, the problem is in the rigidity of the fixed pulley. When stress is coming from the bottom part, the belt will be in excessive tension around the gear which affects motion. To avoid this problem, we must use modular pulley to compress the belt toward the gear

## Fourth Design: Final Chassis Design 
### Tensioner Design: Unique Approach 
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/8c125d90-4842-4468-b797-0af537986d05)
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/fc110949-09e7-4d64-97cd-ae7c885e8a16)
To move from fixed to modular pulley we were inspired by the car mechanism “tensioner.” We tried to implement a similar behavior by allowing pulley to move by spring mean. This design allows us to reduce tension on the gear when moving from panel to another and in case the panels are not aligned at the same height this will insure a perfect transition. 

 By following the distinctive design procedure, we successfully designed a differential rover capable of defeating and climbing slops. Our final chassis model is in the adjacent picture. As we can see the robot is standing on the panels without any problem.  
The effort put in the mechanical design is a considerable effort since it is not a conventional design available in the market. The rover is a customized and assembled part by part from different components that include customized belts, car pulleys used as wheels, polyamide wheels, and copper tubes fixing the wheels to the chassis, springs to support the moving pulley. We can say that as first step which is the base of the project is achieved by producing a successful model able to climb slopes. 

## Cleaning Mechanism: Gears and Chains to Convert and Translate Motion
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/1a694d7b-37d5-4f1a-a967-b7a8e13a8670)
The cleaning mechanism can be considered as our second challenge. The main difficulty consists in ensuring a brush able to clean the distance traveled by the robot. This can be done using two separate disks rotating each having a diameter equal to half the width of the robot. This is technically realizable however it implies the need of two motors each for one brush or the use of gear assembly like the differential gear where two brushes will be rotated by one motor. The second solution is to use one a single brush able to cover the width of the robot and a motor attached at one end. The problem faced in this approach was the motor installation which was solved by adding chain and gears between the motor and brush.

# Motor Selection
We applied the concepts learned throught the course, and detailed calculation was carried out to find a suitable motor. Ater all calculation we selected wiper motors.

# Wiring and Connections
All connections and wires were organized to have the best wiring schematic. Clean wiring to avoid connections issues. This is shown below:
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/dba84c4c-55e3-4220-b804-15d6d1c0f2b9)
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/303c2557-9e44-498f-9717-6a1a916874fe)

# Algorithm
For the algorithm we used simple approach that relies on IR sensor to detect the presence of panel under the robot and using S shape algorithm we navigated along panels. Two issues arised:
## Chassis Drift: Motor Synchronization
Since we did not have encoders on our mototr we could not use encoder feedback to run the two motors at same speed therefore we relied on PWM signals and made the slowest motor's speed to be the mazimum speed. However a slight deviation remained, this problem will be solved as explained below:

## Which Direction to Rotate: Left or Right?
Since our design is modular and the user can put the robot on any corner, we need to be able to know our orientation. This problem is solved using MPU6050 where we read the angle to know if we are tilted left or right. To benefit more from the MPU6050 we used the acceleration and derived velocity combining with tilt angle to allow the robot to adjust its pose when deviating 

To test the accelerometer data, we coolected hundred of samples serialy through a python code which converts the reading to a csv file that can be ploted in matlab. We used matlab to analyze and process the data and the results obtained are shown below (we should mention that MPU6050 readings are noisy and drift with time therefore filters were used):
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/d09dcc33-46f8-4d18-afd3-8145c6abf5e6)
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/47127cc8-a789-41f5-a22e-50f8860deb94)
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/f9dad8ca-6c9f-499a-b03d-bca89f93d7fd)

# Bluetooth Application
To give the user the ability to better ontrol the rover in case of any failure, We created a bluettoth application that helps navigating the robot. The application was built using MIT app and the hardware used was HC-05 bluetooth module:
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/6660118f-3ae5-4719-a4d9-99a9a2c257e0)


# Further Work
## Computer Vision
This feature was under developement that allows the user to take a picture and send it to the rover allowing it to visualize and calculate the cleaning surface.
(the testing was done only on the PC since I did not establish a wireless connection between the rover and PC)
![WhatsApp Image 2023-05-28 at 17 26 29](https://github.com/adnanO999/CleanEnergy/assets/88556508/9d12b275-9d08-49e8-a344-32b1ae707fda)

## Solidworks Model
I tried to design a solidworks model for further design enhancement
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/891fc00b-8231-4e63-9a9d-8857bc6a189b)
![image](https://github.com/adnanO999/CleanEnergy/assets/88556508/a7940f54-6d83-40ab-a540-2a0fee704b86)

## Tracking the Rover
To obtain a closer look on how the robot is moving, I previously created a program that ensures communication between arduino, python and unity game engine.
The process works as follows: we need to add encoders to be able to get the better measurements for the displacement. Displacement and values accumulated MPU6050 can be combined and sent from aduino to python serialy (later we can use raspberrypi to eliminate the use of cable). The data collected in sent from python to unity and through a C# script I created a TCP or UDP connection based onpreference and the accuracy of data send and communication type. I followed an existing model to create this communication with a small modification in order to recieve the data in the correct format and shape.


# Summary
Solar panel cleaning rover This project aims to clean solar panels in more efficient and safe way. The design process followed several iterations and endedup using caterpillar model. The rover is designed to handle differnt slopes varying from 0 to 30 degree. A modular tensioner is mounted on both sides to enable smooth transition from on panel to the other and accomodate with height difference when moving across the panels. The Robot weight approximately 10 Kg however this weight can be reduced by removing the water tank and battery from the rover and mount them externally. S shape algorithm was used based on accelerometer and gyroscope data (pitch roll yaw angles) and projected on the panels surface. the microncontroller used was arduino mega thus processing was limited therefore I used serial communication to build python program to handle computer vision. Matlab and python codes were built using existing examples however with more modification to match our goal. These codes were used to collect data from accelerometer/gyroscope transform them to csv file and plot them to analyze the movement of the robot.


