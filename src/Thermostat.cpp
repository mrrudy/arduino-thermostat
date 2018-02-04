#include "Thermostat.h"

using namespace ThermostatInternal;

Thermostat::Thermostat()
        : _lastReadoutTemp(999) //need to be high to initially turn off heating untill first proper readout happens
        , _requestedTemp(21)
        , _hysteresis(0.5)
        , _state(STATE_HEATING_UNK)
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
Thermostat& Thermostat::setup(uint32_t readoutFreq, float hysteresis){
        _readoutFreq=readoutFreq;
        _hysteresis=hysteresis;
        _shouldCompare=true; //TODO check if handlers are set before requesting comparition
        return *this;
}
Thermostat& Thermostat::loop(){
        if(_shouldCompare==true) {
                _shouldCompare=false;
                Debugf("Will compare read temp: %f to requested temp: %f with histeresis: %f", _lastReadoutTemp, _requestedTemp, _hysteresis);
                if(_lastReadoutTemp<=_requestedTemp-_hysteresis && _state != STATE_HEATING_ON) { //the temperature is too low, turn on heating
                        _operationHandler(this, ThermostatOperation::HEATING_ON);
                        _state=STATE_HEATING_ON;
                        return *this;
                }
                if (_lastReadoutTemp>=_requestedTemp && _state != STATE_HEATING_OFF) {
                        _operationHandler(this, ThermostatOperation::HEATING_OFF);
                        _state=STATE_HEATING_OFF;
                        return *this;
                }
        }
        if (millis()-_lastReadoutTime>=_readoutFreq) {
                _lastReadoutTime=millis();
                float temp_redout=_readoutHandler(this);
                if (temp_redout!=_lastReadoutTemp) {
                        _lastReadoutTemp=temp_redout;
                        _shouldCompare=true;
                }
                return *this;
        }
}

//void setup(){};
//void loop(){};
