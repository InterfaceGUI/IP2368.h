#ifndef IP2368_H
#define IP2368_H

#include <Arduino.h>
#include <Wire.h>

class IP2368 {
public:
  void begin();
  uint8_t getBatteryPercentage();
  enum ChargeState {
        STANDBY = 0,
        TRICKLE_CHARGE = 1,
        CONSTANT_CURRENT = 2,
        CONSTANT_VOLTAGE = 3,
        CHARGE_WAIT = 4,
        CHARGE_FULL = 5,
        CHARGE_TIMEOUT = 6
    };
  ChargeState getChargeState();
  bool isCharging();
  bool isChargeFull();
  bool isDischarging();
  bool isVbusPresent();
  bool isVbusOvervoltage();
  bool isTypeCSinkConnected();

private:
  uint8_t _intPin;
  uint8_t readRegister(uint8_t regAddress);
};

#endif
