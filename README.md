## The Muscle-Car Project

This is our repository for the "Social Technology Lab 1" project, completed for this course in the winter semester (A.Y. 2021/2022), at the University of Southern Denmark, Odense, Denmark.

### The Team

The prototype was realised by me, [Paul](https://github.com/Phamtastisk) and [Riccardo](https://github.com/vareight) with love between the "Cheese building" and the "The Maersk Mc-Kinney Moller Institute" at SDU.

### What Is Involved

This project consists of some hardware parts:

- Arduino Uno board placed on the forearm
- RC transceiver connected to the forearm board
- EMG muscle sensor for reading the arm's muscle's contractions
- Gyroscope around the wrist to read rotation
- Small car with 2 brushless DC motors
- Arduino Uno board on the car
- RC transceiver connected to the car board

And software coded using Arduino IDE for both Arduino boards:

- Car [code](https://github.com/FilippoPaganelli/MuscleCar/edit/main/Arduino%20Code/StringTest_receiver/StringTest_receiver.ino)
- Forearm [code](https://github.com/FilippoPaganelli/MuscleCar/blob/main/Arduino%20Code/Transmitter_gyro_sensor/Transmitter_gyro_sensor.ino)

### How It Works

The forearm "console" reads speed values and steering degree **as** contractions of the forearm flexor muscles and wrist rotation degree from the gyroscope.
This data is sent to the RC receiver on the car from the RC transmitter on the forearm. Speed then determines how fast the car's motors spin and the steering value controls the car steering degree.

Want to see this prototype working? Check out our [playlist on YouTube](https://www.youtube.com/playlist?list=PLxWyn44N0_NZ6fT0Qxhb622j6sGIwBC1E)!

### The Purpose

It was simply a course project, but we really enjoyed working on it, so much that me and Paul are now expanding it for his second university project and my Master's thesis.
However, the original concept did not change. We're trying to provide a tool to make the **forearm/wrist/hand rehabilitation's monitoring** easier, both for the therapist and for the patient. As for the latter, we also want to make the rehab experience less *repetitive* and more *rewarding* by allowing the patient to see immediate and long-term progress indicators.

Check out the new project repos:
- [Mobile app + Arduino code](https://github.com/FilippoPaganelli/RehTracker_mobile-app)
- [Full-stack webapp](https://github.com/FilippoPaganelli/RehTracker_full-stack-webapp)
