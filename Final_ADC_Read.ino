#define SAMPLES 1  // Only 1 sample per channel for fast updates
#define PAD_LOW 1600
#define PAD_HIGH 2200

// ADC input pins
#define SENSOR_A_PIN 33
#define SENSOR_B_PIN 32
#define SENSOR_C_PIN 35

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);  // 12-bit ADC (0–4095)

  // Labels for Serial Plotter (MUST match printed values per line)
  Serial.println("ADC_A\tADC_B\tADC_C\tPAD_LOW\tPAD_HIGH");
}

// ── Individual ADC read functions ──
int readADC_A() {
  return analogRead(SENSOR_A_PIN);
}

int readADC_B() {
  return analogRead(SENSOR_B_PIN);
}

int readADC_C() {
  return analogRead(SENSOR_C_PIN);
}

void loop() {
  int adcA = readADC_A();
  int adcB = readADC_B();
  int adcC = readADC_C();

  // Serial Plotter Output (tab-separated, one line)
  Serial.print(adcA);      Serial.print("\t");
  Serial.print(adcB);      Serial.print("\t");
  Serial.print(adcC);      Serial.print("\t");
  Serial.print(PAD_LOW);   Serial.print("\t");  // Lock Y-axis min at 0
  Serial.println(PAD_HIGH);                    // Lock Y-axis max at 4095

  delay(50);  // Adjust for smoother or faster plotting
}
