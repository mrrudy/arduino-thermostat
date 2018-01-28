#include "Thermostat.h"

using namespace ThermostatInternal;

Thermostat::Thermostat()
: _lastReadoutTemp(0)
, _requestedTemp(21)
, _hysteresis(0.5)
, _state(STATE_HEATING_OFF)
, _lastReadoutTime(0)
, _readoutFreq(5*1000)
, _shouldCompare(false)
, _operationHandler(nullptr)
, _readoutHandler(nullptr)
{
}



bool Thermostat::setDesiredTemp(float requestedTemp){
  _requestedTemp = requestedTemp;
  _shouldCompare=true;
  return true; //TODO check if the temp that is given is a proper value and if not return false
}

Thermostat& Thermostat::setOperationHandler(ThermostatInternal::OperationHandler handler){
  _operationHandler=handler;
  return *this;
}
Thermostat& Thermostat::setReadoutHandler(ThermostatInternal::ReadoutHandler handler){
  _readoutHandler=handler;
  return *this;
}
Thermostat& Thermostat::setup(uint32_t readoutFreq, uint32_t hysteresis){
  _readoutFreq=readoutFreq;
  _hysteresis=hysteresis;
  _shouldCompare=true;
  return *this;
}
Thermostat& Thermostat::loop(){
  if(_shouldCompare==true){
    _shouldCompare=false;
    if(_lastReadoutTemp<=_requestedTemp-_hysteresis){//the temperature is too low, turn on heating
      _operationHandler(this, ThermostatOperation::HEATING_ON);
      return this;
    }
    if (_lastReadoutTemp>=_requestedTemp) {
      _operationHandler(this, ThermostatOperation::HEATING_OFF);
      return this;
    }
  }
  if (millis()-_lastReadoutTime>=_readoutFreq) {
    _lastReadoutTime=millis();
    _lastReadoutTemp=_readoutHandler();
    _shouldCompare=true; //TODO check if there was a change in the temp and only then compare
  }
}
