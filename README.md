# CreatingaLightMeter
Creating a Light Meter
# **Creating a Light Meter**

## **Overview**
This project uses a photoresistor to measure ambient light levels and dynamically control the brightness of LEDs. Additionally, UART communication is implemented to monitor and record minimum and maximum light intensity values in real time. The system features concurrent tasks, including fading LEDs and blinking LEDs, to demonstrate multitasking capabilities.

---

## **Hardware Setup**

### **Components**
- **Photoresistor**:
  - Pin 1 → 5V
  - Pin 2 → A0 and 220Ω resistor to GND
- **LEDs**:
  - Port D (Pins 2–7): Fading LEDs
  - Port B (Pins 8–9): Blinking LEDs
- **Resistors**:
  - 220Ω for each LED
  - 220Ω pull-down for the photoresistor

### **Connections**
#### **Photoresistor**
- Acts as a voltage divider to measure ambient light.
- Connected to A0 for analog input.

#### **LEDs**
- Port D (2–7): Fading LEDs controlled by PWM and software PWM.
- Port B (8–9): Blinking LEDs controlled via an interrupt.

---

## **Features**
1. **Light-Responsive Fading**:
   - The brightness of LEDs on Port D fades based on the ambient light level detected by the photoresistor.
   - Real-time adjustments using `analogRead()` and `map()` functions.

2. **Concurrent Blinking**:
   - LEDs on Port B blink independently at 1 Hz (ON for 1 second, OFF for 1 second).
   - Controlled via a timer interrupt without affecting fading LEDs.

3. **Real-Time Monitoring**:
   - Outputs the current, minimum, and maximum light intensity values to the Serial Monitor for debugging and analysis.

---

## **Software Overview**

### **Libraries**
- **Arduino.h**: Core library for Arduino functionality.
- **UART**: For serial communication.
- **Custom Software PWM**: Controls brightness for non-PWM pins.

### **Core Functionalities**
1. **Fading LEDs**:
   - Reads light intensity using `analogRead(A0)`.
   - Maps sensor readings to brightness values (0–255).
   - Applies brightness using `analogWrite()` and software PWM for non-PWM pins.

2. **Blinking LEDs**:
   - Uses a timer interrupt (Timer1) to toggle LEDs on Port B.
   - Operates independently of fading logic.

3. **Serial Communication**:
   - Prints current, minimum, and maximum light intensity values to the Serial Monitor for debugging.

---

## **Usage Instructions**

1. **Hardware Setup**:
   - Assemble the components as described in the **Hardware Setup** section.
   - Verify all connections against the schematic.

2. **Code Upload**:
   - Upload the provided code to your Arduino using the Arduino IDE or a compatible IDE.
   - Open the Serial Monitor at a baud rate of 9600 to view light intensity values.

3. **Test the System**:
   - Adjust the ambient light to observe fading behavior in Port D LEDs.
   - Verify blinking LEDs on Port B are not affected by fading operations.
   - Record the minimum and maximum light intensity values displayed on the Serial Monitor.

---

## **Example Serial Output**
```plaintext
Current: 65, Min: 57, Max: 79
Current: 63, Min: 57, Max: 79
Current: 70, Min: 57, Max: 79
