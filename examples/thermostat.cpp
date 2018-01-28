#include <Arduino.h>

#include <Thermostat.h>

Thermostat thermostat;

void serveThermostatOperationChange(Thermostat *t, ThermostatOperation operation) {
        switch (operation) {
        case ThermostatOperation::HEATING_ON:
                //TODO turn heating on
                break;
        case ThermostatOperation::HEATING_OFF:
                //TODO turn heating off
                break;
        }
}

float performTempReadout(Thermostat *t) {
        //TODO return real temperature read from sensor
        return 21.5;
}

void setup() {
        thermostat
        .setup(5*1000, 0.5)
        .setOperationHandler(serveThermostatOperationChange)
        .setReadoutHandler(performTempReadout)
        .setDesiredTemp(21)
        ;
}

void loop() {
        thermostat.loop();
        // put your main code here, to run repeatedly:
}
