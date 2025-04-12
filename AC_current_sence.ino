#define CURRENT_SENSOR_PIN 33
#define OFFSET_ADC_VALUE 1876
#define SAMPLES 200   // Number of samples per measurement window
#define ADC_TO_CURRENT 0.02885  // Amps per ADC unit
#define RMS_DIVISOR 1.4142      // sqrt(2) for RMS

void setup() {
  Serial.begin(115200);
  analogReadResolution(12); // Set ADC to 12-bit resolution
  delay(1000);              // Give time for Serial Plotter to connect

  // Labels for Serial Plotter axes (optional, helps during plot view)
  Serial.println("ADC_Value\tRMS_Current");
}

void loop() {
  int adcValue;
  int maxAdc = 0;
  int minAdc = 4095;

  for (int i = 0; i < SAMPLES; i++) {
    adcValue = analogRead(CURRENT_SENSOR_PIN);

    if (adcValue > maxAdc) maxAdc = adcValue;
    if (adcValue < minAdc) minAdc = adcValue;

    // Also plot the real-time ADC values
    float current = (adcValue - OFFSET_ADC_VALUE) * ADC_TO_CURRENT;
    if (current < 0) current = 0;

    Serial.print(adcValue);
    Serial.print("\t");
    Serial.println(current, 2);  // Real-time current

    delayMicroseconds(100);  // ~10kHz sampling rate (adjustable)
  }

  // After collecting samples, calculate RMS current for display
  float peakAdc = (maxAdc - OFFSET_ADC_VALUE);
  float rmsCurrent = (peakAdc * ADC_TO_CURRENT) / RMS_DIVISOR;
  if (rmsCurrent < 0) rmsCurrent = 0;

  // Optional: plot steady RMS current over full cycle
  Serial.print("0\t");
  Serial.println(rmsCurrent, 2);

  delay(50); // Delay before next batch of plotting
}
