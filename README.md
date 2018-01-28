# Arduino Thermostat

This Arduino library that handles basic logic for thermostat opeartion.

## Features

* Histeresis support


## Requirement

* Arduino millis() is a base for the library.

## Installation

1. Download the [latest version](https://github.com/mrrudy/arduino-thermostat/archive/master.zip)
2. Load the `.zip` with **Sketch → Include Library → Add .ZIP Library**

## API

See examples folder for examples.

#### Thermostat ()

Instantiate a Thermostat instance.


#### bool setDesiredTemp (float `requestedTemp`)

Sets new desired temperature which will be compared with measured one.

#### Thermostat& loop()

Must be called in `loop()`. **Don't call `delay()` in loop() as it will block the loop, so Thermostat will malfunction.**

#### Thermostat& setOperationHandler (ThermostatInternal::OperationHandler `handler`)

Set the operation handler to service operations as defined in ThermostatOperation (e.g. HEATING_ON).

Must be called at least one time before .loop().

#### Thermostat& setReadoutHandler (ThermostatInternal::ReadoutHandler `handler`)

Set the function handler that needs to be called to get current readout of the temperature. Function needs to return float.

#### Thermostat& setup(uint32_t `readoutFreq`, uint32_t `hysteresis`);

Allows to setup how often the readout of the current temperature will happen and what is the hysteresis.
