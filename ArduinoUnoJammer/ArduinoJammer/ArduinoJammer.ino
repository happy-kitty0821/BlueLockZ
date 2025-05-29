/*
 * Author: Ayush Wanem Limbu
 * Purpose: RF24 signal generator that hops across predefined 2.4 GHz channels. Developed during the internship period
 * Usage: For educational and testing purposes only. Unauthorized jamming is illegal in many regions.
 * Hardware: Arduino UNO + nRF24L01+ module (CE=Pin 9, CSN=Pin 10)
 * Status Indicators:
 *   - Green LED (Pin 7): Device detected and running
 *   - Orange onboard LED (Pin 13): Device not detected
 */

#include <SPI.h>      //for RF24 communication
#include <RF24.h>     //library for nRF24L01+ module

// ----------------------------- Configuration Constants -----------------------------

constexpr uint8_t CE_PIN = 9;                      //chip Enable pin
constexpr uint8_t CSN_PIN = 10;                    //chip Select Not pin
constexpr rf24_datarate_e DATA_RATE = RF24_2MBPS;  //max data rate for full power
constexpr uint8_t POWER_LEVEL = RF24_PA_MAX;       //maximum transmission power
constexpr unsigned long CHANNEL_HOP_DELAY = 50;    //delay between channel hops in ms

constexpr uint8_t GREEN_LED_PIN = 7;               //green LED for RF24 OK
constexpr uint8_t ERROR_LED_PIN = 13;              //orange LED for RF24 error

//predefined frequency pattern (channels 0–125 are valid for nRF24)
const byte frequencyPattern[] = {
  32, 34, 46, 48, 50, 52,     //high frequency channels
  0, 1, 2, 4, 6, 8,           //low frequency channels
  22, 24, 26, 28, 30,         //mid-range channels
  74, 76, 78, 80, 82, 84, 86  //channels overlapping Bluetooth
};

const size_t patternSize = sizeof(frequencyPattern);  //number of channels in the pattern
size_t patternIndex = 0;                              //index to track current channel

RF24 radio(CE_PIN, CSN_PIN);  //creating an RF24 object with CE and CSN pins

// ----------------------------- function definitions -----------------------------

//initialize the RF24 module and start the carrier signal
void setupRadio() {
  if (!radio.begin()) {
    Serial.println(F("RF24 module not detected. Halting."));

    digitalWrite(GREEN_LED_PIN, LOW);    //turn off green LED
    digitalWrite(ERROR_LED_PIN, HIGH);   //turn on orange LED

    while (1);  //stop the execution if radio fails to initialize
  }

  radio.setDataRate(DATA_RATE);                          //setting the data rate
  radio.setPALevel(POWER_LEVEL);                         //setting the power level
  radio.setChannel(frequencyPattern[patternIndex]);      //start at first channel
  radio.startConstCarrier(POWER_LEVEL, frequencyPattern[0]);  //begin constant carrier wave

  Serial.println(F("RF24 Carrier Generator Started"));

  digitalWrite(ERROR_LED_PIN, LOW);    //turn off orange LED
  digitalWrite(GREEN_LED_PIN, HIGH);   //turn on green LED
}

//displaying the current channel info via Serial Monitor
void logStatus(byte channel) {
  Serial.print(F(" Hopping to channel: "));
  Serial.println(channel);
}

// ----------------------------- Arduino Uno Lifecycle Functions -----------------------------

void setup() {
  pinMode(GREEN_LED_PIN, OUTPUT);    //initialize green LED pin
  pinMode(ERROR_LED_PIN, OUTPUT);    //initialize orange LED pin

  Serial.begin(9600);      //start Serial for debugging
  delay(1000);             //small delay for stability

  setupRadio();            //initialize radio and start transmission
}

void loop() {
  patternIndex = (patternIndex + 1) % patternSize;              //move to next channel
  byte currentChannel = frequencyPattern[patternIndex];         //get the current channel
  radio.setChannel(currentChannel);                             //set channel on RF24
  logStatus(currentChannel);                                    //log the current channel
  delay(CHANNEL_HOP_DELAY);                                     //wait before next hop
}
