# Embedded IoT Systems – Assignment_1 Task_B 
**Name:** Rizwana Bashir  
**Reg No:** 23-NTU-CS-1088  
**Section:** BSCS-5th-B  
**Course:** Embedded IoT Systems  

---

## Project Description  
This project demonstrates the use of a single push button to control multiple components including three LEDs (Green, Blue, and Purple) and a Buzzer, along with an OLED display for feedback.  
The OLED shows messages according to user interaction, indicating whether the LEDs are turned ON/OFF through a short press, or when the buzzer is activated using a long press.

---

## Hardware Components  
- ESP32 / Arduino board  
- 0.96" I2C OLED Display (SSD1306)  
- 3 LEDs (Green, Blue, Purple)  
- 1 Push Button  
- 1 Buzzer  
- Jumper Wires & Breadboard  

---

## Circuit Connections  

 **Component    Pin** 

GREEN LED      Connected to pin 19 
BLUE LED       Connected to pin 18 
PURPLE LED     Connected to pin 17 
PUSH BUTTON    Connected to pin 35 
BUZZER         Connected to pin 5 
OLED SDA       Connected to SDA (default) 
OLED SCL       Connected to SCL (default) 

---

## Working Description  

 Action  Description: 

 **Short Press**  Toggles all LEDs ON or OFF. The OLED displays “LEDs ON” or “LEDs OFF” accordingly. 
 **Long Press (more than 1.5 seconds)**  Activates the buzzer for a short duration and displays “Buzzer Activated” on the OLED. 

---

## Features  
OLED display for real-time feedback  
Button-based dual functionality (short and long press detection)  
LED control and buzzer alert integrated  
Clean and non-blocking logic using `millis()`  

---

## Code File  
All functionality is implemented in the main `.ino` file which initializes the OLED, reads button input, and controls the LEDs and buzzer accordingly.  

---
SchreenShots are Added in pdf file in Task-B folder.  
