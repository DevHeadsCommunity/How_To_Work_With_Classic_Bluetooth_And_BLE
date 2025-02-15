#include "BluetoothSerial.h"

const char *pin = "1234"; // Secure PIN.

String device_name = "ESP32-BT-Slave";

char Incoming_value = 0;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void setup() 
{
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  SerialBT.begin(device_name);
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif
}

void loop() {
  if(SerialBT.available() > 0)  
  {
    Incoming_value = SerialBT.read();      
    Serial.print(Incoming_value);        
    Serial.print("\n");        
    if(Incoming_value == '1')             
      digitalWrite(2, HIGH);  
    else if(Incoming_value == '0')       
      digitalWrite(2, LOW);   
  }                            
}
