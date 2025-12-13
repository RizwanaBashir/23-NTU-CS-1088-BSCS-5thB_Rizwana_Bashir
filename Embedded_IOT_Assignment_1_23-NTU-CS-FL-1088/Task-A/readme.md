Name: Rizwana Bashir  
Reg No: 23-NTU-CS-1088 
Section: BSCS-5TH-B
Course:Embedded IoT Systems   

**Project Description**
This project controls three LEDs (Red, Blue, and Purple) using two push buttons and an OLED display.  
The OLED screen shows the current operating mode, while LEDs respond according to the selected mode.

 **Hardware Components**
- ESP32 / Arduino board  
- 0.96" I2C OLED Display (SSD1306)  
- 3 LEDs (Red, Blue, Purple)  
- 2 Push Buttons  
- Jumper Wires & Breadboard  

---
 **Circuit Connections**

 Component   Pin                        
 ----------  -------------------------- 
 RED LED     Connected to pin 19        
 BLUE LED    Connected to pin 18        
 PURPLE LED  Connected to pin 17        
 BUTTON 1    Connected to pin 34        
 BUTTON 2    Connected to pin 35        
 OLED SDA    Connected to SDA (default) 
 OLED SCL    Connected to SCL (default) 


---
 **Working Modes**
Mode	Description
1	All OFF – In this mode, all LEDs remain turned off.
2	Blink – All LEDs blink together alternately after every 500 milliseconds.
3	All ON – All LEDs stay continuously on without any blinking.
4	PWM Fade – The LEDs gradually fade in and out, creating a smooth brightness transition effect.

**Use:**
- **Button 1** : Switches to the next mode  
- **Button 2** : Resets back to Mode 1

**Wokwi link**: https://wokwi.com/projects/445786334087512065


ScreenShots are provided in pdf for Task-A folder




