# Doorbell Sensor

This device uses an optocoupler connected to the doorbell wires to trigger an ESP8266.
The optocoupler output should be wired to GPIO4. When the doorbell is pressed, the
sketch sends a notification to the diyHue bridge using an HTTP request.

Configure the WiFi credentials and bridge IP inside the sketch before uploading.
