#ifndef Thermostat_h
#define Thermostat_h

#include "Arduino.h"

#include "ThermostatOperation.hpp"

//#include "Thermostat/StoredState.hpp"

class Thermostat;

namespace ThermostatInternal {

  enum State : uint8_t {
    STATE_HEATING_OFF, // heating off
    STATE_HEATING_ON
  };

  typedef void (*OperationHandler)(::Thermostat* s, ::ThermostatOperation operation);
  typedef float (*ReadoutHandler)(::Thermostat* s);
}

class Thermostat {
private:
  float _lastReadoutTemp;
  float _requestedTemp;
  float _hysteresis;
  uint32_t _lastReadoutTime;
  uint32_t _readoutFreq;
  bool _shouldCompare;

  ThermostatInternal::State _state;

  ThermostatInternal::OperationHandler _operationHandler;
  ThermostatInternal::ReadoutHandler _readoutHandler;

public:
  Thermostat();
  bool setDesiredTemp(float requestedTemp);
  Thermostat& loop();
  Thermostat& setOperationHandler(ThermostatInternal::OperationHandler handler);
  Thermostat& setReadoutHandler(ThermostatInternal::ReadoutHandler handler);
  Thermostat& setup(uint32_t readoutFreq, uint32_t hysteresis);
};

#endif
