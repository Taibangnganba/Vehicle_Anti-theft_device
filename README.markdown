# Vehicle Anti-Theft Device with Three Levels of Safety

## Overview

This repository contains the implementation of a **Vehicle Anti-Theft Device with Three Levels of Safety**, a project developed as part of a Bachelor of Technology in Electronics and Communication Engineering at the National Institute of Technology Manipur. The device integrates RFID, accelerometer, GPS, and GSM technologies to provide a robust, multi-layered security system to protect vehicles from theft.

The system was successfully tested on a two-wheeler scooter (Activa) and demonstrated effectiveness in real-world scenarios. This project aims to enhance vehicle security, offering authentication, movement detection, and real-time tracking capabilities.

## Features

- **Level 1: RFID Authentication**\
  Utilizes the MFRC522 RFID module to verify an authorized tag, enabling or disabling the vehicle's ignition.
- **Level 2: Motion Detection**\
  Employs an ADXL345 accelerometer to detect unauthorized vehicle movement, triggering alerts.
- **Level 3: Real-Time Tracking and Alerts**\
  Integrates a SIM808 module for GPS tracking and GSM communication, sending SMS alerts and making phone calls to the owner with the vehicle's location in case of a security breach.
- **Cost-Effective and User-Friendly**\
  Designed to be affordable, easy to install, and compatible with various vehicle types.
- **Arduino-Powered**\
  Built using an Arduino UNO microcontroller for seamless hardware and software integration.

## Hardware Requirements

- Arduino UNO
- MFRC522 RFID Reader/Writer Module
- ADXL345 Accelerometer
- SIM808 GPS & GSM Module
- 5V Relay Module
- Jumper Wires
- Power Supply (suitable for Arduino and SIM808, typically 3.4V–4.4V for SIM808)
- RFID Tags (MIFARE compatible)
- Breadboard or PCB for prototyping

## Software Requirements

- Arduino IDE (Download from https://www.arduino.cc/en/software)
- Libraries:
  - `MFRC522` for RFID functionality
  - `Adafruit_Sensor` and `Adafruit_ADXL345_U` for accelerometer
  - `DFRobot_SIM808` for GPS and GSM operations
  - `SoftwareSerial` for serial communication
  - `SPI` and `Wire` for communication protocols
- Embedded C++ for programming the Arduino

## Installation and Setup

1. **Hardware Setup**:

   - Connect the MFRC522 RFID module, ADXL345 accelerometer, SIM808 module, and 5V relay to the Arduino UNO as per the pin configurations described in the project documentation (`/docs/`).
   - Ensure a stable power supply for the SIM808 module (3.4V–4.4V).
   - Attach an appropriate antenna to the SIM808 for GPS and GSM functionality.
   - Insert a valid SIM card into the SIM808 module.

2. **Software Setup**:

   - Install the Arduino IDE on your computer.
   - Install the required libraries using the Arduino Library Manager or by downloading them from their respective repositories.
   - Open the provided Arduino code (`/src/vehicle_anti_theft.ino`) in the Arduino IDE.
   - Update the `PHONE_NUMBER` variable in the code with the owner's phone number (in international format, e.g., `+91xxxxxxxxxx`).
   - Update the `authorizedUID` array with the UID of your RFID tag.

3. **Uploading the Code**:

   - Connect the Arduino UNO to your computer via a USB cable (Type A to Type B).
   - Select the correct board (`Arduino UNO`) and port in the Arduino IDE (Tools &gt; Board and Tools &gt; Port).
   - Upload the code to the Arduino UNO.
   - Verify the setup by presenting the authorized RFID tag and monitoring the Serial Monitor for output.

4. **Testing**:

   - Test the RFID authentication by presenting the authorized tag to enable ignition.
   - Simulate vehicle movement to check accelerometer-based motion detection.
   - Verify that SMS alerts and phone calls are received with the correct GPS coordinates when unauthorized movement is detected.

## Repository Structure

- `/src/vehicle_anti_theft.ino`: The main Arduino code for the anti-theft device.
- `/docs/`: Contains the project documentation, including the thesis report and figures.
- `/media/`: Stores images and diagrams referenced in the documentation.
- `/schematics/`: Contains circuit diagrams and hardware design files (if available).
- `/libraries/`: Placeholder for required Arduino libraries (not included; install via Arduino IDE).

## Usage

1. Power on the device and ensure all components are properly connected.
2. Present the authorized RFID tag to the MFRC522 reader to enable the vehicle's ignition.
3. If unauthorized movement is detected (via the ADXL345), the device will:
   - Send an SMS with the vehicle's GPS coordinates.
   - Initiate a phone call to the owner's number.
4. The owner can send an SMS with the keyword "gps" to receive the vehicle's current location.

## Results

The device was tested on a two-wheeler scooter (Activa) over several weeks, demonstrating:

- Reliable RFID-based authentication.
- Accurate detection of unauthorized movement.
- Successful delivery of SMS alerts and phone calls with GPS coordinates.
- Practicality and cost-effectiveness for real-world vehicle security applications.

## Future Improvements

- Add support for multiple authorized RFID tags.
- Implement a mobile app for easier interaction and real-time notifications.
- Enhance power efficiency for battery-operated vehicles.
- Integrate additional sensors (e.g., tilt or vibration sensors) for improved detection.
- Explore IoT integration for remote monitoring via a web dashboard.

## Licenses

- **Software License**: The Arduino code in `/src/` is licensed under the MIT License. You are free to use, modify, and distribute the code, provided you include the copyright notice and disclaimer.

## Contributing

Contributions are welcome! Please fork the repository, make your changes, and submit a pull request. See CONTRIBUTING.md for guidelines.

## Acknowledgements

- **Dr. Loitongbam Surajkumar Singh**, Assistant Professor, Department of Electronics and Communication Engineering, NIT Manipur, for guidance and support.
- **Prof. Aheibam Dinamani Singh**, Head of Department, Electronics and Communication Engineering, NIT Manipur, for valuable suggestions.
- The administrative and laboratory staff at NIT Manipur for their assistance.
- Family and friends for their moral support.

## Contact

For queries or feedback, please contact:

- Kambam Taibangnganba (Enrolment No.: 20105006)
- Email: \[kambamtaibangnganba@gmail.com

## References

[1] Ashwini Dilip Lahire, “GPS & GSM based vehicle tracking and security system,” International Journal of Engineering Research and Development, Volume 12, Issue 6, PP.55-60 ,June 2016.
[2] V.Mulge, Mrs G. Sathyaprabha, Mr P.V.VaraPrasad Rao, “Anti-Theft Security System Using GSM, GPS, RFID Technology Based On Arm7,” International Journal of Research in Information Technology(IJRIT), Volume 2, Issue 9,Pg. 764-769, September 2014.
[3] A.Rajasekhar reddy, P.Anwar basha ,“The Terminal System Design based on hybrid RFID-GPS in Vehicular communications,” International Journal of Modern Engineering Research (IJMER), Vol.2, Issue.4, pp-2316-2319, July-Aug 2012. 
[4] Finkenzeller and R. Handbook,“Radio-frequency identification fundamentals and applications,” Chippenham: John Wiley & Son, 1999.
[5] S. Shepard, RFID: radio frequency identification. McGraw Hill Professional, 2005.
[6] Davis. B, DeLong. R, "Combined remote key control and immobilization system for vehicle security," Power Electronics in Transportation, 1996. IEEE 24-25 Oct. 1996 
[7] Khangura, K.S;Middleton,N.V; Ollivier,M.M, "Vehicle anti-theft system uses radio frequency identification," Vehicle Security Systems, IEE Colloquium 8 Oct 1993 
[8] Xin Chen, Patrick J, Flynn Kevin.Bowyer, "PCA-based face recognition in infrared imagery: baseline and comparative studies", AMFG 200,. IEEE International Workshop on 17 Oct. 2003 
[9] M. Turk, A. Pentland, "Eigenfaces for Recognition", Journal of Cognitive Neuroscience, 3(1), pp71 -86, 1991.
[10] Pentland, B. Moghaddam, T. Starner, "View-Based and Modular Eigenspaces for Face Recognition", IEEE CVPR, 1994.
[11] P.Belhumeur, J. Hespanha, and D. Kriegman, " Eigenfaces vs Fisherfaces: Recognition Using Class Specific Linear Projection," IEEE Trans. PAMI 19(7), 1997.
[12] A. Leonardis and H. Bischof H, "Dealing with occlusions in the eigenspace approach," CVPR, pp 453 -458, 1996.
[13] Hong Qiao, Shaoyan Zhang, Bo Zhang and Keane. J, " Face recognition using SVM decomposition methods," IROS 200.
[14] rong-ben,Guo Ke-you and Shi Shu-ming, "A monitoring method of driver fatigue behavior based on machine vision", Intelligent Vehicles Symposium, 2003. Proceedings. IEEE 9-11 June 2003 pp 110-113.
[15] Yinan Ma, Jing Wu, Chengnian Long, Yi-Bing Lin, "MobiDIV: A Privacy-Aware Real-Time Driver Identity Verification on Mobile Phone", IEEE Internet of Things Journal, vol.9, no.4, pp.2802-2816, 2022.
[16] Debashis Das, Sourav Banerjee, Utpal Biswas, "A secure vehicle theft detection framework using Blockchain and smart contract", Peer-to-Peer Networking and Applications, vol.14, no.2, pp.672, 2021.
[17] Debashis Das, Sourav Banerjee, Uttam Ghosh, Utpal Biswas, Ali Kashif Bashir, "A decentralized vehicle anti-theft system using Blockchain and smart contracts", Peer-to-Peer Networking and Applications, vol.14, no.5, pp.2775, 2021.
