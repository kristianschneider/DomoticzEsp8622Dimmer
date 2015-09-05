# Domoticz Esp8622 WIFI Dimmer
## A ESP8266 based dimmer for Domotiz Lua, with nice ramped fading  
---
This code allows you to run a PWM based led dimmer of the ESP8266.
I previously tried to do this with NodeMCU, but it was too unstable, so I ended up doing this in native, via the Arduino IDE.
In Domotiz you will have to set up a LUA script as described here in [this excellent blog post series](http://blog.quindorian.org/2014/12/esp8266-wifi-led-dimmer-part-1-of-x.html) I also used the PWM curcuit he describes, so cudos to [Quindor](https://plus.google.com/+Quindor/about).

The code will ensure that it fades in and out quite nicely. And in the LUA script there is a logarithmic lookup table for dimmer values, so that the brightness are better adjusted for human eye sight across the range in Domotiz.

Due to, what I think is a limitation of my circuit, LED strip, or power supply, it flickers when the dimmer uses a PWM value less than 8. So in those cases I just turn it of completely.

You are more than welcome to do a pull request or ask questions.



