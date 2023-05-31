<p align="center"><a href="https://spothings.github.io" target="_blank"><img src="https://raw.githubusercontent.com/spothings/spothings.github.io/master/public/asset/img/spothings.png" width="200"></a></p>
<h3 align="center">spothings</h3>
<p align="center">Make everything automatic and make things easier.</p>

---

## About Project
I have created a project solely for exploring the features of the NodeMCU microcontroller (ESP8266) and fulfilling my desire to create an automatic backlight for my desk that adjusts according to day and night time using an LDR sensor. Several variables are stored in the ESP8266 EEPROM to prevent data loss upon restart. Additionally, I have incorporated a Telegram bot as an alternative method for remote control. I may consider adding more features in the future.

[![Development Status](https://img.shields.io/badge/status-development-red)](https://github.com/spothings/strip-table/tree/dev)
![GitHub last commit](https://img.shields.io/github/last-commit/spothings/strip-table)

![strip-table-view](img/strip-table-view.jpg)

## Feature
-  [Current](https://github.com/spothings/strip-table/releases)
	- Turn on and off the lights using relay
	- Use NTP client to get value day or night
	- Using the LDR sensor to get the light intensity
	- Using average light intensity for reasons of stability of sensor readings
	- Make auto sampling dark value
-  [Development](https://github.com/spothings/strip-table/tree/dev-code)
	- Using EEPROM to store data
	- Using Telegram bot for remote control

## Development
- [Documentation](/doc)
- [Project Workflow](/flow)
- [Source Code](/src/main)
- [Board Schematic](/sch)
- [PCB and Gerber File](/pcb)

## Contributor
<a href="https://github.com/spothings/strip-table/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=spothings/strip-table" />
</a>

Made with [contrib.rocks](https://contrib.rocks).

## Donation
If you think this project is helpful, you can make a donation. For those of you who want to make a donation, we would really appreciate it. Donations can be made through [Buy Me a Coffee](https://www.buymeacoffee.com/bukanspot) and [PayPal](https://paypal.me/bukanspot).

## License
This project is using [spothings template](https://github.com/spothings/spothings). Copyright, Privacy Policy and License also sourced from there.