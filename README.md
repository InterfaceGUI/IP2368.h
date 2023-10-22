# IP2368.h
An Arduino library for interfacing with the IP2368 IC. Provides functionalities for reading and managing charging states, battery percentage, and more.

英集芯 的 IP2368 是一個 有 I2C 通訊的充電管理IC。 此程式庫提供了與此 IC 的基本介面功能。 目前只實現了基本的讀取功能。

#### 特別注意

當 IP2368 進入休眠狀態後，您需要在 INT 腳位上輸出一個 HIGH 訊號。 在100ms後，IC將被喚醒，並且可以開始透過 I2C 進行通訊，IC休眠後I2C通訊會出現錯誤(在傳輸地址時收到NACK)。

<details> <summary>Example</summary>
  
```c
#include <Wire.h>
#define INT_PIN D4  // Change this to your desired pin

#include "IP2368.h"

IP2368 device();


void setup() {
  Serial.begin(9600);
  device.begin();
  pinMode(INT_PIN, OUTPUT);
}

void loop() {
  digitalWrite(INT_PIN, HIGH); //Keep awake
  delay(110);

  Serial.print("Battery Percentage: ");
  Serial.println(device.getBatteryPercentage());
  Serial.println(device.isCharging());
  Serial.println(device.isDischarging());

  IP2368::ChargeState currentState = device.getChargeState();
  Serial.println(device.isPDcharging());
  
  switch (currentState) {
    case IP2368::STANDBY:
        Serial.println("Standby");
        break;

    case IP2368::TRICKLE_CHARGE:
        Serial.println("Trickle Charge");
        break;

    case IP2368::CONSTANT_CURRENT:
        Serial.println("Constant Current Charging");
        break;

    case IP2368::CONSTANT_VOLTAGE:
        Serial.println("Constant Voltage Charging");
        break;

    case IP2368::CHARGE_WAIT:
        Serial.println("Charge Waiting (not started or other situations)");
        break;

    case IP2368::CHARGE_FULL:
        Serial.println("Charge Full");
        break;

    case IP2368::CHARGE_TIMEOUT:
        Serial.println("Charge Timeout");
        break;

    default:
        Serial.println("Unknown Charge State");
        break;
}

  delay(5000);
}
```

</details>
