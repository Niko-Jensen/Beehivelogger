# Beehive Environmental Monitoring – Arduino Project

This project records and stores environmental data from inside and outside a beehive using temperature, humidity, and light sensors. Data is logged to an SD card in CSV format with timestamps provided by a real-time clock (RTC).

## Features
- **Indoor and outdoor temperature measurement** using DHT22 sensors  
- **Indoor and outdoor humidity measurement** using DHT22 sensors  
- **Outdoor light level measurement** using an analog light sensor  
- **Automatic data logging** every 10 minutes (configurable)  
- **Data stored on SD card** in CSV format  
- **Real-Time Clock (RTC DS3231)** for accurate date and time stamps  
- **Serial monitoring** for debugging and real-time data display  

## Hardware Components
- Arduino (e.g., Mega or Uno with sufficient pins)  
- 2× DHT22 sensors (one inside, one outside)  
- RTC DS3231 real-time clock module  
- Analog light sensor (e.g., photoresistor)  
- SD card module  
- Various wires and resistors  

## Pin Configuration
- **DHT22 (inside):** Digital pin 6  
- **DHT22 (outside):** Digital pin 7  
- **Light sensor:** Analog pin A0  
- **SD card:** Pin 53 (chip select on Arduino Mega)  
- **RTC DS3231:** I²C (SDA/SCL)  

## Data Process
1. **Sensor readings**  
   - Temperature and humidity are read both inside and outside.  
   - Light level is measured outside using an analog input.  

2. **Timestamping**  
   - RTC DS3231 provides precise date and time information.  

3. **Data formatting**  
   - Data is structured as CSV:  
     ```
     Date,Time,Sensor,Temp. (C),Humidity (%),Light Level
     2025-09-01,12:00:00,Inside,34.5,65.0,NA
     2025-09-01,12:00:00,Outside,28.1,55.0,512
     ```

4. **Data logging**  
   - Data is written to `data.csv` on the SD card every 10 minutes.  
   - If any sensor fails to return valid readings, an error is printed to the Serial Monitor.  

## Usage
1. Connect all sensors and modules as described.  
2. Insert a formatted SD card into the SD card reader.  
3. Upload the code to the Arduino board.  
4. Open **Serial Monitor (9600 baud)** to view status and real-time readings.  
5. Data will automatically be stored on the SD card.  

## Error Handling
- If RTC is not detected: *"RTC error. Check wiring or battery."*  
- If SD card cannot initialize: *"SD card error. Check wiring."*  
- If a DHT sensor fails: *"Error with DHT sensor Inside/Outside."*  
- If data cannot be written to SD card: *"Could not write to SD card."*  

## Customization
- **Logging interval:** Default is 10 minutes (`600000 ms`). For testing, it can be changed to 6 seconds (`6000 ms`).  
- **File name:** The CSV file defaults to `data.csv` but can be changed in the code.  
