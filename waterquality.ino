#define PH_PIN A0       // Analog pin for pH sensor
#define NTU_PIN A1      // Analog pin for turbidity sensor
#define PPM_PIN A2      // Analog pin for TDS meter (PPM sensor)

void setup() {
  Serial.begin(9600);  // Initialize Serial communication
}

void loop() {
  // Read raw sensor values
  float pHValue = 7 + ((3.85 - analogRead(PH_PIN) * (5.0 / 1023.0)) / 0.16428571428);  // Map pH sensor output (example calibration)
  float NTUValue = -200 * (analogRead(NTU_PIN) * (5.0 / 1023.0)) + 740;  // Map turbidity output to NTU
  float voltage = analogRead(PPM_PIN) * (5.0 / 1023.0);
  float ppmValue = (133.42 * voltage * voltage * voltage - 255.86 * voltage * voltage + 857.39 * voltage) * 0.5;  // Map TDS output to PPM (example range)

  // Print the sensor readings
  Serial.println("----- Water Quality Readings -----");
  Serial.print("pH: ");
  Serial.println(pHValue);
  Serial.print("NTU: ");
  Serial.println(NTUValue);
  Serial.print("PPM: ");
  Serial.println(ppmValue);

  // Water safety evaluation and suggestions
  if (pHValue > 8.5 || pHValue < 6.5) {
    Serial.println("pH Alert: Water is UNSAFE to drink!");
    Serial.println("Suggestion: Adjust pH using lime juice (to reduce pH) or baking soda (to increase pH).");
  }

  if (NTUValue > 1.0) {
    Serial.println("Turbidity Alert: Water is UNSAFE to drink!");
    Serial.println("Suggestion: Filter the water using activated charcoal or fine mesh filters.");
  }

  if (ppmValue > 300) {
    Serial.println("PPM Alert: Water is UNSAFE to drink!");
    Serial.println("Suggestion: Use a reverse osmosis (RO) filter to reduce PPM levels.");
  }

  if (pHValue >= 6.5 && pHValue <= 8.5 && NTUValue <= 1.0 && ppmValue <= 300) {
    Serial.println("Water is SAFE to drink!");
  }

  Serial.println("----------------------------------\n");
  delay(10000);  // Wait 2 seconds before taking next reading
}
