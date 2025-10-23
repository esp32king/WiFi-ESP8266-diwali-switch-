## 🚩 Diwali Switch — Jai Shree Ram Edition 2025 🕉️

✨ A stunning ESP8266 Smart Switch Captive Portal project to control relays (lights, fan, room, crackers) via a beautiful web interface in Jai Shree Ram style!
No Wi-Fi setup needed — it creates its own Hotspot + Captive Portal for instant access.

## 🌟 Features

⚡ Captive Portal Access — Just connect to “Diwali Switch”, it auto-opens the control page.

🎨 Beautiful Jai Shree Ram UI — Fireworks, diyas, garland lights, and glowing text.

🔘 Control 4 Relays — Crackers, Lights, Fan, and Room.

💡 All Switches Button — Turn all ON/OFF together.

📱 Mobile-Friendly Layout — Perfectly fits Android screens.

🔥 Diwali Animation Effects — Floating diyas, fireworks, blinking lights.

🕉️ Fully Offline — Works without internet, all hosted on ESP8266.

## 🧩 Hardware Requirements
Component	Quantity	Notes
🔌 ESP8266 NodeMCU / Wemos D1 Mini	1	Main microcontroller
⚙️ Relay Module (4-Channel)	1	To control your devices
🔋 Power Supply (5V)	1	To power the ESP and relays
🧠 Jumper Wires	As needed	For connections
## ⚙️ Pin Configuration
Relay	GPIO Pin	NodeMCU Label
Relay 1	5	D1
Relay 2	4	D2
Relay 3	0	D3
Relay 4	2	D4

## 💡 Logic:
LOW = ON, HIGH = OFF

## 🧱 How It Works

Power on your ESP8266.

It creates a Wi-Fi hotspot named “Diwali Switch” 📶

Connect to it from your phone (no password required).

The Captive Portal opens automatically — or open any page manually.

Control your relays instantly from the glowing Jai Shree Ram dashboard! ⚡

## 🧰 Setup & Upload Instructions

🧩 Install Arduino IDE

Add ESP8266 Board Manager via:

https://arduino.esp8266.com/stable/package_esp8266com_index.json


Select NodeMCU 1.0 (ESP-12E Module)

## 📂 Install Libraries

ESP8266WiFi.h

ESP8266WebServer.h

DNSServer.h

LittleFS.h

(All come pre-installed with the ESP8266 core.)

## 💾 Upload the Code

Copy the .ino code to Arduino IDE

Select the correct Port & Board

Hit Upload 🚀

## 🧠 Open Serial Monitor (115200 baud)

You’ll see:

AP IP: 192.168.4.1
HTTP server started


📱 Connect to Wi-Fi “Diwali Switch” and enjoy controlling everything 🎆

## 🎨 Screenshot Preview

🌸 Glowing Jai Shree Ram interface
🪔 Floating diyas and fireworks background
🔘 Control buttons for Crackers, Lights, Fan, Room
💡 Real-time relay status update

(You can add a real screenshot here if you like!)

## 🧞‍♂️ Credits

Made with ❤️ by <a href="https://github.com/esp32king"> KR$HNA </a>

🪔 Diwali Edition 2025 — जय श्री राम! 🚩

## ⚠️ License

This project is released under the MIT License — feel free to modify and share.
