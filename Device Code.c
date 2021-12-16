
#include <Arduino.h>
#include <SPI.h>
#include <BLEPeripheral.h>
#include <stdint.h>
#include <string.h>
#define DEAD_BEEF       
             




BLEPeripheral blePeripheral;  // BLE Peripheral Device
BLEService uuid_Service("8d87f23c12e3499faa7d86eea7d1518f"); // UUID BLE Service

// BLE Switch Characteristic - custom 128-bit UUID, read and notificable
BLECharacteristic  switchCharacteristic("8d87f23c-12e3-499f-aa7d-86eea7d1518f", BLENotify,6);
BLEDescriptor CCCDDescriptor("2902", "CCCD");

//Buffer to send data throw BLE
uint8_t Buffer_2[6];

int primer_numero_EF;
int primer_numero_SC;
int segundo_numero_SC;
int primer_numero_SS;

//Variable to set usual data o unusual data --> 0 = Usual data ; 1 = Unusual data
int data = 0; 

//Variable to change from usual to unusual data
int i=0;
String mensaje;

void setup() {
 
  Serial.begin(9600);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("HeartCare");
  blePeripheral.setAdvertisedServiceUuid(uuid_Service.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(uuid_Service);
  blePeripheral.addAttribute(switchCharacteristic);

  // set the initial value for the characeristic:
  switchCharacteristic.setValue(0);

  // begin advertising BLE service:
  blePeripheral.begin();

  Serial.println("BLE Heart Care Peripheral");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      if (i%4==0)
      {
        data = 1;
      }
      if (data == 0)
      {
        primer_numero_EF = random(50,80);
        primer_numero_SC = random(0,1);
        segundo_numero_SC = random(5,7);
        primer_numero_SS = random(135,145);
        mensaje="USUAL DATA SENT\n";
      }
      if (data == 1)
      {
        primer_numero_EF = random(30,35);
        primer_numero_SC = 2;
        segundo_numero_SC = random(4,7);
        primer_numero_SS = random(120,125);
        mensaje="UNUSUAL DATA SENT\n";
      }
      
      Buffer_2[0]=primer_numero_EF;
      Buffer_2[1]=primer_numero_SC;
      Buffer_2[2]=segundo_numero_SC;
      Buffer_2[3]=primer_numero_SS;
      switchCharacteristic.setValue(Buffer_2,6);
      if(switchCharacteristic.value()){
        Serial.print(mensaje);
      }
      delay(5000);
      i++;
      data = 0;

    }

    // when the central disconnects, print it out:
    Serial.print(F("Desconectado de: "));
    Serial.println(central.address());
  }
}