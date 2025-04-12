#define SAMPLES 100
#define PAD_LOW 2
#define PAD_HIGH 10

// Sensor A
#define SENSOR_A_PIN 33
#define OFFSET_A 1879
#define CALIBRATION_A 0.027

// Sensor B
#define SENSOR_B_PIN 32
#define OFFSET_B 2013
#define CALIBRATION_B 0.027

// Sensor C
#define SENSOR_C_PIN 35
#define OFFSET_C 1808
#define CALIBRATION_C 0.027

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // ESP32 ADC resolution (0–4095)

  // Label headers for Serial Plotter
  Serial.println("Current_A\tCurrent_B\tCurrent_C\t");
}

float readRMSCurrent(int pin, int offset, float calibration, int &minAdc, int &maxAdc) {
  minAdc = 4095;
  maxAdc = 0;
  int adcVal;

  for (int i = 0; i < SAMPLES; i++) {
    adcVal = analogRead(pin);
    if (adcVal > maxAdc) maxAdc = adcVal;
    if (adcVal < minAdc) minAdc = adcVal;
    delayMicroseconds(100); // Sampling delay
  }

  float peak = (maxAdc - offset);
  float rmsCurrent = (peak * calibration) / 1.4142;
  if (rmsCurrent < 0) rmsCurrent = 0;

  return rmsCurrent;
}

void loop() {
  int minA, maxA, minB, maxB, minC, maxC;
  float currentA = readRMSCurrent(SENSOR_A_PIN, OFFSET_A, CALIBRATION_A, minA, maxA);
  float currentB = readRMSCurrent(SENSOR_B_PIN, OFFSET_B, CALIBRATION_B, minB, maxB);
  float currentC = readRMSCurrent(SENSOR_C_PIN, OFFSET_C, CALIBRATION_C, minC, maxC);

 /* // ───── Serial Monitor Output ─────
  Serial.println("====== Current Sensor Readings ======");
  Serial.print("Sensor A -> RMS: "); Serial.print(currentA, 2); //Serial.print(" A | ADC Min: "); Serial.print(minA); Serial.print(" Max: "); Serial.println(maxA);
  Serial.print("Sensor B -> RMS: "); Serial.print(currentB, 2); //Serial.print(" A | ADC Min: "); Serial.print(minB); Serial.print(" Max: "); Serial.println(maxB);
  Serial.print("Sensor C -> RMS: "); Serial.print(currentC, 2); //Serial.print(" A | ADC Min: "); Serial.print(minC); Serial.print(" Max: "); Serial.println(maxC);
  Serial.println("=====================================\n");
*/
  // ───── Serial Plotter Output ─────
Serial.print(currentA, 2); Serial.print("\t");
Serial.print(currentB, 2); Serial.print("\t");
Serial.print(currentC, 2); Serial.print("\t");
Serial.print(1);           Serial.print("\t"); // Pad_Low
Serial.println(12);                          // Pad_High


  delay(200); // Refresh rate
}
