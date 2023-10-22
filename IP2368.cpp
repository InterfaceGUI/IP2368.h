#include "IP2368.h"

#define IP2368_ADDRESS 0x75

// Registers
#define SOC_CAP_DATA 0x30
#define RSTATE_CTL0 0x31
#define RSTATE_CTL1 0x32
#define STATE_CTL2 0x33
#define RTYPEC_STATE 0x34

IP2368::IP2368() : {}

void IP2368::begin() {
  Wire.begin();
}

uint8_t IP2368::readRegister(uint8_t regAddress) {
  delay(2);
  Wire.beginTransmission(IP2368_ADDRESS);
  Wire.write(regAddress);
  uint8_t errorCode = Wire.endTransmission(false);  // 不發送停止信號
  
  if (errorCode) {
    //Serial.print("Error during transmission: ");
    //Serial.println(errorCode);
    return -1;
  }

  uint8_t bytesRead = Wire.requestFrom(IP2368_ADDRESS, (uint8_t)1, (bool)true);  // 請求1個字節，並發送停止信號
  
  if (bytesRead != 1) {
    //Serial.println("Failed to read from device!");
    return -1;
  }
  return Wire.read();

}

uint8_t IP2368::getBatteryPercentage() {
  return readRegister(SOC_CAP_DATA);
}

bool IP2368::isCharging() {
  return readRegister(RSTATE_CTL0) & (1 << 5);
}

bool IP2368::isChargeFull() {
  return readRegister(RSTATE_CTL0) & (1 << 4);
}

bool IP2368::isDischarging() {
  return readRegister(RSTATE_CTL0) & (1 << 3);
}

IP2368::ChargeState IP2368::getChargeState() {
    uint8_t data = readRegister(RSTATE_CTL0);
    uint8_t stateBits = data & 0x07;
    return static_cast<ChargeState>(stateBits);
}

bool IP2368::isVbusPresent() {
  return readRegister(STATE_CTL2) & (1 << 7);
}

bool IP2368::isVbusOvervoltage() {
  return readRegister(STATE_CTL2) & (1 << 6);
}

bool IP2368::isTypeCSinkConnected() {
  return readRegister(RTYPEC_STATE) & (1 << 7);
}

