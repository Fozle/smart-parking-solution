# Smart Parking System (IoT-Based)

## 📌 Project Overview
In many busy urban areas worldwide, finding an empty parking space is a major challenge that leads to wasted time and increased traffic[cite: 1]. This Smart Parking System addresses this problem by providing a real-time web-based solution that helps users locate available parking spots instantly[cite: 1].

## 🚀 Key Features
*   **Real-Time Monitoring**: Uses ultrasonic sensors to detect vehicle presence in individual slots[cite: 1].
*   **Automated Gate Control**: A servo motor opens the gate automatically when a car is detected at the entrance, provided space is available[cite: 1].
*   **Web Dashboard**: Displays live occupancy data, allowing users to check status remotely before arriving[cite: 1].
*   **Cloud Integration**: All parking data is synced to the Firebase Realtime Database for instant updates[cite: 1].
*   **Local Status Display**: An LCD screen provides immediate feedback on available slots at the physical location[cite: 1].

## 🛠️ Hardware Components
*   **Microcontroller**: ESP32-S3[cite: 1]
*   **Sensors**: 4x Ultrasonic Sensors (HC-SR04)[cite: 1]
*   **Actuators**: 1x Servo Motor[cite: 1]
*   **Other**: LCD Display, Breadboards, and Jumper Wires[cite: 1]

## 💻 Tech Stack
*   **Language**: C++ (Arduino IDE)[cite: 1]
*   **Backend**: Firebase Realtime Database[cite: 1]
*   **Web Platform**: Vercel (for dashboard hosting)[cite: 1]
*   **Libraries**: `WiFi.h`, `Firebase_ESP_Client.h`, `NewPing.h`, `ESP32Servo.h`[cite: 1]

## 👥 Team Members
*   **Fozle Arafat Chowdhury**: Firmware development, hardware wiring, and Firebase integration[cite: 1].
*   **Tawhidul Islam**: Web application development[cite: 1].
*   **Fahim Uddin Mashrur**: Hardware setup and system testing[cite: 1].

## 🔧 Installation & Setup
1.  **Hardware**: Connect the sensors and servo motor to the ESP32 according to the pin assignments in the source code[cite: 1].
2.  **Configuration**: Open the `.ino` file and update your Wi-Fi credentials (`WIFI_SSID`, `WIFI_PASSWORD`) and Firebase API key[cite: 1].
3.  **Upload**: Flash the code to your ESP32 using the Arduino IDE[cite: 1].
4.  **Monitor**: Open the Serial Monitor at 115200 baud to verify the connection and sensor readings[cite: 1].

---
*Developed during an internship at Savonia University of Applied Sciences.*[cite: 1]

<img width="1919" height="1079" alt="Screenshot 2026-05-04 121634" src="https://github.com/user-attachments/assets/ef2debaa-b855-4421-96e9-fd0fb7d52664" />
<img width="967" height="848" alt="Screenshot 2026-05-04 121728" src="https://github.com/user-attachments/assets/fd17517a-3e06-4a2b-821d-3a0709991835" />
<img width="803" height="377" alt="image" src="https://github.com/user-attachments/assets/f914e14f-bbd7-41cc-900f-bd297a3ffa81" />

