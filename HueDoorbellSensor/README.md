## Hue Doorbell Sensor

This device monitors the input of a doorbell through an optocoupler connected to an ESP8266.
When the doorbell rings the optocoupler pulls the I/O line low and a request is sent to the diyHue bridge.

### Wiring
- Doorbell wires -> optocoupler -> GPIO5 (D1) on the ESP8266
- Optocoupler output uses the internal pull‑up resistor

### Behaviour
Pressing the doorbell triggers a single HTTP request to the configured diyHue bridge using the `ZLLSwitch` device type.

Configure WiFi credentials, bridge IP and adjust the pin if required in `HueDoorbellSensor.ino` before uploading.
