# AutoCAN: Smart EV Health Monitoring and Battery Management System

## 📌 Project Overview

**AutoCAN** is a smart Electric Vehicle (EV) health monitoring and battery management system developed using **LPC2129 ARM7 microcontrollers** and **CAN (Controller Area Network) communication**.

The system consists of three Electronic Control Units (ECUs) that work together to monitor battery and engine conditions, control the cooling motor, and display real-time vehicle information on a **16×4 LCD**.

The project demonstrates a practical multi-ECU architecture similar to the communication used in automotive embedded systems.

---

## 🚗 System Architecture

```text
              ┌──────────────────────────┐
              │ ECU1 – Battery Monitoring│
              │          Unit            │
              └────────────┬─────────────┘
                           │
                           │ CAN
                           ▼
                    ┌─────────────┐
                    │ CAN Network │
                    └──────┬──────┘
                           │
             ┌─────────────┴─────────────┐
             │                           │
             ▼                           ▼
   ┌─────────────────────┐     ┌──────────────────────┐
   │ ECU2 – Motor Control│     │ ECU3 – Dashboard Unit│
   │ Unit (Cooling Motor)│     │                      │
   └──────────┬──────────┘     └──────────────────────┘
              │
              ▼
       Cooling Motor
```

---

## 🔋 ECU1 – Battery Monitoring Unit

ECU1 is responsible for monitoring the main battery parameters.

### Functions

* Battery voltage monitoring
* Battery current monitoring
* Battery temperature monitoring
* Battery status detection
* Battery fault detection
* CAN data transmission

### Battery Status

| Status    |   Code |
| --------- | -----: |
| NORMAL    | `0x00` |
| UNDERVOLT | `0x01` |
| OVERTEMP  | `0x02` |
| FAULT     | `0x03` |

### CAN Messages

| CAN ID  | Parameter           |
| ------- | ------------------- |
| `0x101` | Battery Temperature |
| `0x102` | Battery Voltage     |
| `0x103` | Battery Current     |
| `0x104` | Battery Status      |

---

## ⚙️ ECU2 – Motor Control Unit (Cooling Motor Control)

ECU2 monitors the **engine temperature** and automatically controls the cooling motor.

### Working

1. ECU2 reads the engine temperature through the ADC.
2. The temperature is compared with the predefined limit.
3. If the temperature is **≥ 30°C**, the cooling motor is turned **ON**.
4. If the temperature is **< 30°C**, the cooling motor is turned **OFF**.
5. Engine temperature and cooling motor status are transmitted through CAN.

### Motor Status

| Status    |   Code |
| --------- | -----: |
| MOTOR OFF | `0x04` |
| MOTOR ON  | `0x05` |

### CAN Messages

| CAN ID  | Parameter            |
| ------- | -------------------- |
| `0x105` | Engine Temperature   |
| `0x106` | Cooling Motor Status |

---

## 📟 ECU3 – Dashboard Unit

ECU3 receives information from ECU1 and ECU2 through the CAN network and displays the vehicle health information on a **16×4 LCD**.

### Dashboard Displays

* Battery voltage
* Battery current
* Battery temperature
* Battery status
* Engine temperature
* Cooling motor status

### Example Display

```text
BAT_V:48.0V I=10.2A
BTEMP:35C  OVERTEMP
ENGINE_TEMP:38C
COOL_MOTOR:ON
```

---

## 🔄 CAN Communication

The CAN network provides communication between all three ECUs.

```text
ECU1
 │
 ├── 0x101 → Battery Temperature
 ├── 0x102 → Battery Voltage
 ├── 0x103 → Battery Current
 └── 0x104 → Battery Status
 │
 └────────────── CAN ──────────────► ECU3


ECU2
 │
 ├── 0x105 → Engine Temperature
 └── 0x106 → Cooling Motor Status
 │
 └────────────── CAN ──────────────► ECU3
```

---

## 🛠️ Hardware Used

* LPC2129 ARM7 Microcontroller
* CAN Transceiver
* Temperature Sensor
* Voltage Sensor / Voltage Divider
* ACS712 Current Sensor
* DC Cooling Motor
* 16×4 LCD
* 9V Battery / Power Supply
* Motor Driver Interface
* Connecting Wires and Supporting Components

---

## 💻 Software and Technologies

* Embedded C
* ARM7 / LPC2129
* CAN Communication
* ADC
* LCD Interface
* Keil µVision
* Embedded C Drivers

---

## ⭐ Key Features

* Real-time EV battery monitoring
* Battery voltage, current, and temperature measurement
* Automatic battery status detection
* Engine temperature monitoring
* Automatic cooling motor control
* Multi-ECU CAN communication
* Real-time dashboard display
* Fault and safety monitoring
* LPC2129 ARM7 embedded implementation

---

## 🎯 Project Objective

The main objective of AutoCAN is to develop a reliable embedded system for **real-time EV health monitoring and safety management**. The project demonstrates how multiple ECUs can communicate through CAN to monitor critical vehicle parameters and automatically respond to high-temperature conditions.

---

## 📌 Conclusion

AutoCAN demonstrates a practical automotive embedded system in which **ECU1 monitors the battery, ECU2 monitors engine temperature and controls the cooling motor, and ECU3 provides a centralized dashboard**. CAN communication enables reliable data exchange between the ECUs, making the system suitable as a prototype for EV health monitoring and thermal management applications.

---

## 👨‍💻 Project Type

**Embedded Systems | Automotive Electronics | Electric Vehicle | CAN Communication | Battery Monitoring | Motor Control**
