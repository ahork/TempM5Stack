#include <M5StickC.h>
#include <Wire.h>

// MLX90614       M5stick

// Vin            3.3V
// GND            GND
// SCL            G26
// SDA            G0

void setup() {
  
  M5.begin();
  
  Wire.begin(0,26);
  Serial.begin(115200);

  M5.Lcd.setRotation(3);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0, 40);

  // active Wifi for call a WebService to send T°
  
}

uint16_t result;
float temperature;

void loop() {
  Wire.beginTransmission(0x5A);          // Send Initial Signal and I2C Bus Address
  Wire.write(0x07);                      // Send data only once and add one address automatically.
  Wire.endTransmission(false);           // Stop signal
  Wire.requestFrom(0x5A, 2);             // Get 2 consecutive data from 0x5A, and the data is stored only.
  result = Wire.read();                  // Receive DATA
  result |= Wire.read() << 8;            // Receive DATA
  
  temperature = result * 0.02 - 273.15;
  
  M5.Lcd.fillRect(0,0,200,200,BLACK);
  M5.Lcd.setCursor(0, 40);

  
  M5.Lcd.print((temperature);
  M5.Lcd.print(" °C");
  Serial.println(result);



  // Send Temps a WebService for statistiques    

  delay(500);
  M5.update();
}
