/**
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - Henrik Ekblad
 * 
 * DESCRIPTION
 * Motion Sensor example using HC-SR501 
 * http://www.mysensors.org/build/motion
 *
 */

// Enable debug prints
// #define MY_DEBUG

// Enable and select radio type attached
#define MY_RADIO_NRF24
//#define MY_RADIO_RFM69

// Set LOW transmit power level as default, if you have an amplified NRF-module and
// power your radio separately with a good regulator you can turn up PA level.
// Possible values: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
#define MY_RF24_PA_LEVEL RF24_PA_LOW

// Set the operation chanell
// Possible range: 0-125
#define MY_RF24_CHANNEL 76

// This acts as base value for sensor nodeId addresses. 
// Change this (or channel) if you have more than one sensor network.
#define MY_RF24_BASE_RADIO_ID 0x00,0xFC,0xE1,0xA8,0xA8

// Set the datarate
// Possible values: RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
#define MY_RF24_DATARATE RF24_250KBPS

// Flash leds on rx/tx/err
#define MY_WITH_LEDS_BLINKING_INVERSE       // LEDs connected to groud
#define MY_DEFAULT_LED_BLINK_PERIOD 300     // Set blinking period
#define MY_DEFAULT_TX_LED_PIN  8            // Tx led Pin
#define MY_DEFAULT_RX_LED_PIN  7            // Rx led Pin
#define MY_DEFAULT_ERR_LED_PIN 6            // Error led pin

// Node ID - this must be unique for every node
#define MY_NODE_ID 1

#include <MySensors.h>

unsigned long SLEEP_TIME = 120000; // Sleep time between reports (in milliseconds)
#define DIGITAL_INPUT_SENSOR 3   // The digital input you attached your motion sensor.  (Only 2 and 3 generates interrupt!)
#define CHILD_ID 1   // Id of the sensor child

// Initialize motion message
MyMessage msg(CHILD_ID, V_TRIPPED);

void setup()  
{  
  pinMode(DIGITAL_INPUT_SENSOR, INPUT);      // sets the motion sensor digital pin as input
  digitalWrite(DIGITAL_INPUT_SENSOR, HIGH);
}

void presentation()  {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Motion Sensor", "1.0");

  // Register all sensors to gw (they will be created as child devices)
  present(CHILD_ID, S_MOTION);
}

void loop()     
{     
  // Read digital motion value
  bool tripped = digitalRead(DIGITAL_INPUT_SENSOR) == HIGH;
        
  Serial.println(tripped);
  send(msg.set(tripped?"1":"0"));  // Send tripped value to gw 

  // Sleep until interrupt comes in on motion sensor. Send update every two minute.
  sleep(digitalPinToInterrupt(DIGITAL_INPUT_SENSOR), CHANGE, SLEEP_TIME);
}


