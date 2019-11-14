
#include <Wire.h>

/*
 *  mC        | SDA       | SCL
 *  --------------------------------
 *  AVR       | A4        | A5
 *  ESP8266   | D2(GPIO4) | D1(GPIO5)
 *  ESP32     | GPIO21    | GPOI22
 *  
 */

void setup() {
  
  Wire.begin(); // Atmega
  //Wire.begin(SDA_pin, SCL_pin); // I2C on specified pins on ESP8266
  Serial.begin(115200);
}

void loop() {
  
  byte error, address;
  int nDevices;

  Serial.println(F("Scanning..."));

  nDevices = 0;
  
  for(address = 1; address < 127; address++ ) {

    delay(1); // EPS WDT prevent
    
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print(F("found: "));
      printAddr(address);
      Serial.print(F(" - "));
      Serial.flush();
      Serial.print(addrToDevice(address));
      Serial.flush();
      Serial.println();

      nDevices++;
      
    } else if (error==4) {
      Serial.print(F("Unknow error at address: "));
      printAddr(address);
      Serial.println();
    }
  }
  
  if(nDevices == 0){
    Serial.println(F("No I2C devices found"));
  }
  else
    Serial.println(F("done"));
    Serial.println(F("-----------------------------------------------------------"));

  delay(10000);
}


String addrToDevice(byte addr){
    
    switch (addr) {
        case 0x00 : { return F("0x00"); }
        case 0x20 : { return F("MCP23017 I/O expander"); }
        case 0x27 : { return F("DISPLAY PCF8574T(hd44780)"); }
        case 0x39 : { return F("TSL2561 Light Sensor"); } 
        case 0x3F : { return F("DISPLAY PCF8574T(hd44780)"); }
        case 0x3C : { return F("SSD1306 Oled Display"); }
        case 0x40 : { return F("PCA9685 Servo, PWM driver"); }
        case 0x48 : { return F("ADS1115 ADC"); }
        case 0x50 : { return F("24C32 EEPROM"); }
        case 0x57 : { return F("24C32 EEPROM"); }
        case 0x68 : { return F("DS1307, DS3231 RTC"); }
        case 0x70 : { return F("PCA9685 Servo, PWM driver reset address"); }
        case 0x76 : { return F("BME280, BMP280 Temperature Pressure [Humidity] sensor"); }
        case 0x77 : { return F("BME280, BMP280 Temperature Pressure [Humidity] sensor"); }
        default : { return F("unknown device"); }
    }
}

void printAddr(byte addr){
    Serial.print("0x");
    if(addr < 16){ 
        Serial.print("0");
     }
     Serial.print(addr, HEX);
}
