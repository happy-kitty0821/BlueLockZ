<h1 align="center">🔒 BlueLockZ</h1>
<p align="center">
  <strong>RF24 Signal Generator & Channel Hopper</strong><br>
  Developed during internship at <a href="https://vairavtech.com" target="_blank">Vairav Tech</a><br>
  <em>For educational and testing purposes only</em>
</p>

<hr>

## 📌 Project Description

BlueLockZ is a 2.4 GHz RF signal generator/jammer designed using an Arduino UNO and an nRF24L01+ module. It actively hops across a set of predefined RF channels to simulate transmission, useful for testing RF resilience or analyzing frequency behavior. 

> ⚠️ **Note:** Unauthorized RF jamming is illegal in many jurisdictions. This tool is strictly for authorized and educational use.

---

## ⚙️ Features

<ul>
  <li>Hops across custom 2.4 GHz frequency channels</li>
  <li>Generates constant carrier waves</li>
  <li>Blocks bluetooth signals and disconnects bluetooth devices</li>
  <li>Visual indicators for device status</li>
  <li>Green LED (Pin 7): RF24 Module Connected</li>
  <li>Orange LED (Pin 13): RF24 Module Not Detected</li>
</ul>

---

## 🔌 Pinout Table

| Component        | Arduino Pin | Description                  |
|------------------|-------------|------------------------------|
| nRF24L01+ CE     | 9           | Chip Enable pin              |
| nRF24L01+ CSN    | 10          | Chip Select Not pin          |
| nRF24L01+ MOSI   | 11          | SPI Master Out Slave In      |
| nRF24L01+ MISO   | 12          | SPI Master In Slave Out      |
| nRF24L01+ SCK    | 13          | SPI Clock                    |
| Green LED        | 7           | RF24 OK Indicator            |
| Orange LED       | 13          | RF24 Not Detected Indicator  |

---

## 📁 File Structure

```plaintext
├── ArduinoUnoJammer/
│   ├── ArduinoJammer/
│   │   ├── ArduinoJammer.ino    # Main Arduino sketch
├── README.md                   # This readme file
```