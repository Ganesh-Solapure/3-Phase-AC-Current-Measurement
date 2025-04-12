#define PAD_LOW -200   // Padding for Y-axis lower limit
#define PAD_HIGH 200   // Padding for Y-axis upper limit

// ADC input pins
#define SENSOR_A_PIN 33
#define SENSOR_B_PIN 32
#define SENSOR_C_PIN 35

// Offsets (zero current ADC values)
#define OFFSET_A 1879
#define OFFSET_B 2013
#define OFFSET_C 1808

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // ESP32 ADC resolution (0–4095)

  // Plot labels (match the print order)
  Serial.println("Delta_A\tDelta_B\tDelta_C\tPAD_LOW\tPAD_HIGH");
}

int readDeltaADC(int pin, int offset) {
  int adc = analogRead(pin);
  return adc - offset;
}

void loop() {
  int deltaA = readDeltaADC(SENSOR_A_PIN, OFFSET_A);
  int deltaB = readDeltaADC(SENSOR_B_PIN, OFFSET_B);
  int deltaC = readDeltaADC(SENSOR_C_PIN, OFFSET_C);

  // Serial Plotter Output
  Serial.print(deltaA);    Serial.print("\t");
  Serial.print(deltaB);    Serial.print("\t");
  Serial.print(deltaC);    Serial.print("\t");
  Serial.print(PAD_LOW);   Serial.print("\t");  // Anchor Y-axis min
  Serial.println(PAD_HIGH);                    // Anchor Y-axis max

  delay(50);  // Plot refresh rate
}
