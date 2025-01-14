/**
 * @brief Uses the built in Mama Duck with some customatizations.
 *
 * This example is a Mama Duck, but it is also periodically sending a message in
 * the Mesh It is setup to provide a custom Emergency portal, instead of using
 * the one provided by the SDK. Notice the background color of the captive
 * portal is Black instead of the default Red.
 *
 * @date 2020-09-21
 *
 * @copyright Copyright (c) 2020
 *
 */
#include <MamaDuck.h>
#include <arduino-timer.h>
#include <string>

// Setup BMP180
#include <Adafruit_BMP085_U.h>
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

#ifdef SERIAL_PORT_USBVIRTUAL
#define Serial SERIAL_PORT_USBVIRTUAL
#endif

// create a built-in mama duck
MamaDuck duck;

auto timer = timer_create_default();
const int INTERVAL_MS = 60000;

void setup() {
  // We are using a hardcoded device id here, but it should be retrieved or
  // given during the device provisioning then converted to a byte vector to
  // setup the duck NOTE: The Device ID must be exactly 8 bytes otherwise it
  // will get rejected
  std::string deviceId("MAMA0001");
  std::vector<byte> devId;
  devId.insert(devId.end(), deviceId.begin(), deviceId.end());

  // Use the default setup provided by the SDK
  duck.setupWithDefaults(devId);
  Serial.println("MAMA-DUCK...READY!");

  // BMP setup
  if (!bmp.begin()) {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print(
        "Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while (1)
      ;
  } else {
    Serial.println("BMP on");
  }

  // initialize the timer. The timer thread runs separately from the main loop
  // and will trigger sending a counter message.
  timer.every(INTERVAL_MS, runSensor);
}

void loop() {
  timer.tick();
  // Use the default run(). The Mama duck is designed to also forward data it
  // receives from other ducks, across the network. It has a basic routing
  // mechanism built-in to prevent messages from hoping endlessly.
  duck.run();
}

bool runSensor(void*) {
  float T, P;

  bmp.getTemperature(&T);
  Serial.println(T);
  bmp.getPressure(&P);
  Serial.println(P);

  String sensorVal = "Temp: " + String(T) + " Pres: " + String(P);

  duck.sendData(topics::sensor, sensorVal);

  return true;
}