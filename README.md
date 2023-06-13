# Ultrasonic_Car_Speedometer_with_Speed_Breaker

This project is an Implementation of SONAR. 
I have measured the speed of the car using three ultrasonic distance sensors and then servos 
trigger a speed breaker if the velocity reading exceeds the pre-set trigger velocity

I made this project when I was in 10th grade and I competed with seniors of grade 11 or 12.
You can refer to the documentation for the project [here](documentation.pdf) that I made for the Competition BoscoFest 2019.

This is a easy to understand alternative of speed cameras that measure speed of a car may analysing the distance of the car from the camera in each frame.

To make this project, you need these parts
1. Arduino Board          the brains of the operation
2. servo motor * 2    to control the speed breaker  ( at a certain angle, speed breaker is effective )
3. ultrasonic distance sensor * 3                to measure the distance of the car from the road side
4. a speed breaker mechanism that can be controlled by a servo. In my case, I used a modified cylinder rotated by two servo motors on either sides

Make The circuit according to the [wiring instructions](Wiring_Instructions.txt).
Upload The [code](Arduino_code.ino) into the arduino board.
Adjust the servo angles according to your use case
