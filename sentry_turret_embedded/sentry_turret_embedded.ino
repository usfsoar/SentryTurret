#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "SOAR_Servo.h"
#include "SOAR_Taser.h"
#include <queue>

SOAR_Servo torsoServo(A0);
SOAR_Servo armsServo(A1);
SOAR_Taser taser(A2);
std::queue<String> messageQueue;


BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;
  }
};

class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0) {
            messageQueue.push(String(value.c_str()));  // Enqueue the incoming message
        }
    }
};
void setup(){
    Serial.begin(115200);
    BLEDevice::init("SOAR_SentryTurret");
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    BLEService *pService = pServer->createService("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
    pCharacteristic = pService->createCharacteristic(
        "6E400002-B5A3-F393-E0A9-E50E24DCCA9E",
        BLECharacteristic::PROPERTY_NOTIFY);

    pCharacteristic->addDescriptor(new BLE2902());
    BLECharacteristic *pRxCharacteristic = pService->createCharacteristic(
        "6E400003-B5A3-F393-E0A9-E50E24DCCA9E",
        BLECharacteristic::PROPERTY_WRITE);
    pRxCharacteristic->setCallbacks(new MyCallbacks());
    pService->start();
    // Start advertising
    pServer->getAdvertising()->start();

    torsoServo.setup();
    armsServo.setup();
    taser.setup();
}
void loop(){
    // Disconnecting
  if (!deviceConnected && oldDeviceConnected)
  {
    delay(500);                  // Give the Bluetooth stack the chance to get things ready
    pServer->startAdvertising(); // Restart advertising
    Serial.println("Advertising started");
    oldDeviceConnected = deviceConnected;
  }

  // // Connecting
  if (deviceConnected && !oldDeviceConnected)
  {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }

    while (!messageQueue.empty()) {
        String msg = messageQueue.front();
        messageQueue.pop();
        if (msg.startsWith("AT:")) {
            int num = msg.substring(3).toInt();
            Serial.print("AT command received with value: ");
            Serial.println(num);
            armsServo.autoMove(num);
        } else if (msg.startsWith("TT:")) {
            int num = msg.substring(3).toInt();
            Serial.print("TT command received with value: ");
            Serial.println(num);
            torsoServo.autoMove(num);
        } else if (msg.startsWith("ZT:")) {
            int num = msg.substring(3).toInt();
            Serial.print("ZT command received with value: ");
            Serial.println(num);
            if(num==1){
              Serial.println("Taser ON");
              taser.fire();
            }
            if(num==0){
              Serial.println("Taser OFF");
              taser.stop();
            }

        }
    }
}