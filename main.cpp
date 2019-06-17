/*
  ReadField

  Description: Demonstates reading from a public channel which doesn't not require an API key and reading from a private channel which does requires a read API key.
               The value read from the public channel is the current outside temperature at MathWorks headquaters in Natick, MA.  The value from the
               private channel is an example counter that increments every 10 seconds.

  Hardware:  Arduino Ethernet

  !!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!

  Note:
  - Requires the Ethernet library

  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and
  analyze live data streams in the cloud. Visit https://www.thingspeak.com to sign up for a free account and create a channel.

  Documentation for the ThingSpeak Communication Library for Arduino is in the README.md folder where the library was installed.
  See https://www.mathworks.com/help/thingspeak/index.html for the full ThingSpeak documentation.

  For licensing information, see the accompanying license file.

  Copyright 2018, The MathWorks, Inc.
*/

#include "mbed.h"
#include "EthernetInterface.h"
#include "arduino_WString.h"
#include "secrets.h"
//#define THINGSPEAK_DBG_MSG
//#define THINGSPEAK_DBG_HTTP
#include "ThingSpeak.h"

Serial pc(USBTX, USBRX);
NetworkInterface *net;
ThingSpeak thingSpeak;
TCPSocket socket;

// Weather station channel details
unsigned long weatherStationChannelNumber = SECRET_CH_ID_WEATHER_STATION;
unsigned int temperatureFieldNumber = 4;

// Counting channel details
unsigned long counterChannelNumber = SECRET_CH_ID_COUNTER;
const char * myCounterReadAPIKey = SECRET_READ_APIKEY_COUNTER;
unsigned int counterFieldNumber = 1;
nsapi_size_or_error_t result;

int setup() {
#ifdef MBED_MAJOR_VERSION
  pc.printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif

  net = new EthernetInterface();
  if (!net) {
      pc.printf("Error! No network interface found.\n");
      return -1;
  }

  result = net->connect();
  if (result != 0) {
      pc.printf("Error! net->connect() returned: %d\n", result);
      return result;
  }

  // Show the network address
  const char *ip = net->get_ip_address();
  const char *netmask = net->get_netmask();
  const char *gateway = net->get_gateway();
  pc.printf("IP address: %s\n", ip ? ip : "None");
  pc.printf("Netmask: %s\n", netmask ? netmask : "None");
  pc.printf("Gateway: %s\n", gateway ? gateway : "None");

  nsapi_error_t open_result = socket.open(net);
  if (open_result != 0) {
      pc.printf("Error! socket.open(net) returned: %d\n", open_result);
      return open_result;
  }

  thingSpeak.setSerial(&pc);
  thingSpeak.begin(&socket);  // Initialize ThingSpeak

  return 0;
}

void loop() {

  int statusCode = 0;

  // Read in field 4 of the public channel recording the temperature
  float fTemperatureInF = thingSpeak.readFloatField(weatherStationChannelNumber, temperatureFieldNumber);
  String sTemperatureInF = thingSpeak.readStringField(weatherStationChannelNumber, temperatureFieldNumber);

  // Check the status of the read operation to see if it was successful
  statusCode = thingSpeak.getLastReadStatus();
  if(statusCode == 200){
    pc.printf("Temperature at MathWorks HQ: %s deg F\n", sTemperatureInF.c_str());
    pc.printf("Temperature at MathWorks HQ: %f deg F\n", fTemperatureInF);
  } else{
    pc.printf("Problem reading channel. HTTP error code %d\n", statusCode);
  }

  wait(15); // No need to read the temperature too often.

  // Read in field 1 of the private channel which is a counter
  long count = thingSpeak.readLongField(counterChannelNumber, counterFieldNumber, myCounterReadAPIKey);

   // Check the status of the read operation to see if it was successful
  statusCode = thingSpeak.getLastReadStatus();
  if(statusCode == 200){
    pc.printf("Counter: %ld\n", count);
  }
  else{
    pc.printf("Problem reading channel. HTTP error code %d\n", statusCode);
  }

  wait(15); // No need to read the counter too often.
}

int main() {
  if(setup() == 0) 
    while(true) loop();
  else
    while(true) wait(1);
}
