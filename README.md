## The Muscle-Car Project

This is our repository for the "Social Technology Lab" project, completed for this course in the winter semester (A.Y. 2021/2022), at the University of Southern Denmark, Odense, Denmark.

### The Team

The prototype was realised by me, [Paul]() and [Riccardo]() with love between the "Cheese building" and the "The Maersk Mc-Kinney Moller Institute" at SDU.

### The Purpose

This project consists of some hardware parts:

- Arduino Uno board placed on the forearm
- RC transceiver connected to the forearm board
- EMG muscle sensor for reading the arm's muscle's contractions
- Gyroscope around the wrist to read rotation
- Small car with 2 brushless DC motors
- Arduino Uno board on the car
- RC transceiver connected to the car board

And software coded using Arduino IDE for both Arduino boards:

- Car [code]()
- Forearm [code]()

### How It Works

The forearm "console" reads speed values and steering degree **as** contractions of the forearm flexor muscles and wrist rotation degree from the gyroscope.
This data is sent to the RC receiver on the car from the RC transmitter on the forearm. Speed then determines how fast the car's motors spin and the steering value controls the car steering degree.

Want to see this prototype working? Check out our [playlist on YouTube]()!
