⚡ 3-Phase AC Current Measurement using ESP32 & WCS1700
========================================================

This project demonstrates real-time measurement and plotting of 3-phase AC current using Winson WCS1700 Hall-effect current sensors interfaced with an ESP32 microcontroller. It captures both ADC waveforms and RMS current values for all three phases.

🔧 Hardware Used
---------------

| Component             | Description                                                                 |
| --------------------- | --------------------------------------------------------------------------- |
| ESP32 Dev Board       | 12-bit ADC, WiFi + Bluetooth MCU                                            |
| WCS1700 Sensor (x3)   | Hall-effect current sensor, 70A max, ~33mV/A sensitivity                     |
| AC Source (3-Phase)   | Live 3-phase load or signal generator for testing                            |
| Breadboard/Wires      | For connections                                                              |
| 3-Phase Load          | Represents the electrical load (e.g., motors, lights) connected to the AC source. |

🧠 About the WCS1700 Sensor
--------------------------

* Type: Hall-effect sensor (non-intrusive, isolated)
* Sensitivity: ~33mV/A
* Offset Voltage: ~1.65V at 0A (for 3.3V supply)
* Measurement Range: 0-70A
* Output Type: Analog Voltage
* Bandwidth: 23 kHz
* Working Voltage: 3V-12V

The WCS1700 is a cost-effective solution for AC current measurement.  It provides electrical isolation, meaning the sensor is galvanically isolated from the current-carrying conductor.  This is a crucial safety feature.

⚙️ Features
------------

* 🌀 Real-time measurement of RMS AC Current on all 3 phases
* 🔍 Visualization of raw ADC waveforms
* 🧮 Offset correction and calibration per sensor
* 📊 Compatible with Arduino Serial Plotter
* ✅ Non-intrusive measurement
* ✅ Galvanic isolation

📌 Pin Configuration
-----------------

| Phase | Sensor      | ESP32 Pin | Notes                                                                   |
| ----- | ----------- | --------- | ----------------------------------------------------------------------- |
| A     | WCS1700-A   | GPIO 33   | Connect the analog output pin of the WCS1700 to this ESP32 ADC pin.      |
| B     | WCS1700-B   | GPIO 32   | Connect the analog output pin of the WCS1700 to this ESP32 ADC pin.      |
| C     | WCS1700-C   | GPIO 35   | Connect the analog output pin of the WCS1700 to this ESP32 ADC pin.      |
| VCC   | WCS1700 (x3)| 3.3V      | Connect the VCC pin of all three WCS1700 sensors to the 3.3V pin on the ESP32. |
| GND   | WCS1700 (x3)| GND       | Connect the GND pin of all three WCS1700 sensors to the GND pin on the ESP32. |

**Important Notes on Pin Configuration:**

* Ensure that the ESP32 and WCS1700 share a common ground.
* The WCS1700 operates on 3.3V.  Do not connect it to 5V, as this could damage the sensor.
* The ESP32 pins used for ADC should be capable of handling analog input.

📥 Installation & Setup
----------------------

1.  **Install Arduino IDE:** Download and install the Arduino IDE from the official website.
2.  **Install ESP32 board support:**
    * Open the Arduino IDE.
    * Go to `File` \> `Preferences`.
    * Add the following URL to the "Additional Board Manager URLs" field:
        ```
        [https://raw.githubusercontent.com/espressif/arduino-esp32/master/package_esp32_index.json](https://raw.githubusercontent.com/espressif/arduino-esp32/master/package_esp32_index.json)
        ```
    * Click "OK".
    * Go to `Tools` \> `Board` \> `Boards Manager...`.
    * Search for "ESP32" and install the "esp32" by Espressif Systems.
3.  **Connect Hardware:** Connect the WCS1700 sensors to the ESP32 as described in the "Pin Configuration" section.  Make sure all connections are secure.
4.  **Select ESP32 Board and Port:**
    * In the Arduino IDE, go to `Tools` \> `Board` and select your ESP32 board (e.g., "ESP32 Dev Module").
    * Go to `Tools` \> `Port` and select the COM port to which your ESP32 is connected.
5.  **Upload the Sketch:**
    * Open the provided Arduino sketch (e.g., `3phase_current_plot.ino`) in the Arduino IDE.
    * Click the "Upload" button (right arrow) to compile and upload the code to your ESP32.
6.  **Open Serial Monitor and Serial Plotter:**
    * After the code has been uploaded, open the Serial Monitor by going to `Tools` \> `Serial Monitor`.  Set the baud rate to 115200.  This will display the numeric current readings.
    * Open the Serial Plotter by going to `Tools` \> `Serial Plotter`.  This will display the ADC waveforms and RMS current values graphically.  Ensure the baud rate is also set to 115200.

📈 Output
--------

➤ Serial Monitor

The Serial Monitor displays real-time current values (in Amps) and the minimum and maximum ADC values for each phase.  This can be useful for debugging and verifying the sensor data.  Example output:

Sensor A -> RMS: 3.21 A | ADC Min: 1754 Max: 2023Sensor B -> RMS: 2.97 A | ADC Min: 1898 Max: 2130Sensor C -> RMS: 4.12 A | ADC Min: 1680 Max: 1960
➤ Serial Plotter

The Serial Plotter provides a visual representation of the data:

* **Live ADC Waveforms:** Shows the raw analog voltage readings from the WCS1700 sensors.  The Y-axis range is 0-4095 (corresponding to the 12-bit ADC of the ESP32).  You should see sinusoidal waveforms.
* **Real-time RMS Current Values:** Plots the calculated RMS current for each phase.

🔄 Real-Time Current Calculation
-----------------------------

The ESP32 code calculates the RMS current from the ADC readings using the following formula:

float peak = (maxAdc - offset);float rmsCurrent = (peak * calibration) / 1.4142;
Where:

* `offset`: The ADC value when no current is flowing (zero current reading).  This is critical for accurate measurements.
* `maxAdc`: The maximum ADC value in a given AC cycle.
* `peak`: The peak ADC value (maxAdc - offset)
* `calibration`: A scaling factor that converts the ADC reading to Amps.  It is derived from the sensor's sensitivity (33mV/A) and the ESP32's ADC characteristics.
* `1.4142`: The square root of 2, used to convert peak current to RMS current for a sinusoidal waveform.

**Calibration:**

The calibration value is calculated as follows:

1.  The WCS1700 has a sensitivity of 33mV/A.
2.  The ESP32 ADC has a resolution of 12 bits, meaning it can read values from 0 to 4095.
3.  The ESP32's ADC reference voltage is 3.3V.

Therefore:

ADC resolution per volt = 4096 / 3.3V = 1241.21  ADC units/VoltADC resolution per mV = 1241.21 / 1000 = 1.24121 ADC units/mVADC resolution per Amp = 1.24121  ADC units/mV * 33mV/A = 40.96  ADC units/Ampcalibration = 1/40.96 =  0.0244  Amps/ADCThe value may vary slightly. It is recommended to calibrate.


To ensure the accuracy and reliability of your 3-phase current measurement system, consider the following verification and validation steps:

1.  **Zero-Current Calibration:**
    * Ensure no current is flowing through the WCS1700 sensors.
    * Record the ADC values for each sensor. These are your `offset` values.
    * Update the `offset` values in your Arduino sketch.
2.  **Multi-Point Calibration:**
    * Apply known current values (e.g., using a current source or a calibrated load) to each phase.
    * Record the corresponding ADC values.
    * Compare the measured current (calculated from the ADC values) with the known current values.
    * Adjust the `calibration` value in your Arduino sketch to minimize the error between the measured and known currents.  A linear fit or a lookup table may be needed for best accuracy.
3. **Accuracy Testing:**
    * Use a calibrated reference meter to measure the actual current.
    * Compare the current measurements from your system to those of the reference meter over a range of current values.
    * Calculate the percentage error at each measurement point.
    * Assess whether the accuracy of your system meets the requirements of your application.
4.  **Repeatability Testing:**
    * Apply a constant current and take multiple readings over a period.
    * Calculate the standard deviation of the readings.  This will indicate the repeatability (precision) of your system.
5.  **Temperature Variation Testing:**
     * If your system will be used in an environment with varying temperatures, test its accuracy over the expected temperature range.
     * Hall-effect sensors can exhibit some temperature drift, so this testing is important.
6.  **Frequency Response Testing**
     * Test the system's response over the frequency range of the AC power being measured (typically 50/60Hz).
7.  **Long-Term Stability Testing:**
        * Monitor the system's performance over an extended period to check for any drift in the calibration or accuracy.
8.  **Load Variation Testing:**
        * Test the system under different load conditions (e.g., balanced and unbalanced loads) to ensure it provides accurate readings in various scenarios.

**Example Verification Form**

| Test Case        | Description                                                                                             | Expected Result                                                                                               | Measured Result                                                                                              | Pass/Fail | Notes                                                                                                                                 |
| ---------------- | ------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------ | --------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| Zero-Current     | Verify ADC output with no current flow.                                                                  | ADC value within +/- 5 of calibrated offset value.                                                              | A: 1802, B: 2030, C: 1795                                                                                    | PASS      | Offset values calibrated at 25°C.                                                                                                   |
| Calibration @ 5A | Apply 5A AC current to Phase A.                                                                         | Measured current within +/- 0.1A of reference meter.                                                            | 5.08 A                                                                                                       | PASS      | Reference meter accuracy: +/- 0.05A                                                                                                   |
| Calibration @ 10A| Apply 10A AC current to Phase A                                                                         | Measured current within +/- 0.1A of reference meter.                                                            | 10.05 A                                                                                                      | PASS      |                                                                                                                                     |
| Repeatability    | Apply 7A AC current to Phase B, take 10 readings.                                                        | Standard deviation of readings < 0.05A.                                                                         | Mean: 7.02A, SD: 0.03A                                                                                       | PASS      | Room Temperature 23°C                                                                                                        |
| Temperature Test | Apply 8A current, vary ambient temperature from 20°C to 50°C.                                              | Current reading variation < 0.2A.                                                                             | See attached graph.                                                                                          | PASS      |                                                                                                                                     |
| Frequency Test   | Apply 10A at 50Hz and 60Hz                                                                                | Current reading variation < 0.1A                                                                              | 50Hz: 10.02A, 60Hz: 10.09A                                                                                   | PASS      |                                                                                                                                     |
| Load Balance     | Apply 5A to Phase A, 5A to Phase B, 5A to Phase C                                                        | All phases measure 5A +/- 0.15A                                                                                 | A: 5.03A, B: 4.98A, C: 5.01A                                                                                  | PASS      |                                                                                                                                     |
| Unbalanced Load  | Apply 3A to Phase A, 6A to Phase B, 9A to Phase C                                                        | All phases measure within +/- 0.15A of applied current                                                          | A: 3.09A B: 6.02A C: 9.12A                                                                                   | PASS      |                                                                                                                                     |

This form provides a template.  You should modify it to fit your specific testing requirements.

🛠️ Future Improvements
----------------------

* 📡 Transmit current data to a cloud platform (e.g., ThingSpeak, AWS IoT) using WiFi.
* 💾 Log readings to an SD card or a database for historical analysis.
* 📉 Implement FFT (Fast Fourier Transform) to analyze the frequency spectrum of the AC current and detect harmonics.
* 📦 Design a robust enclosure and an industrial-grade PCB for field deployment.
* 📟 Add an LCD or OLED display for local monitoring of current values.
* 🚨 Implement over-current protection by triggering an alarm or a relay when the current exceeds a safe threshold.

📚 References
------------

* [WCS1700 Datasheet](https://www.evelta.com/wcs1700-hall-effect-base-linear-current-sensor/)
* [ESP32 ADC Reference](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html)
* [Arduino Serial Plotter](https://www.arduino.cc/en/Guide/ToolsSerialPlotter)
* [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32)

🛠️ Author
----------

Ganesh Solapure
