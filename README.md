# Raspberry Pi SPI based RGB LED network server

This app was written by James Hagerman.

This project is a socket server that takes space delimitated strings of 24 bit hex colors and 
dumps those colors out over the raspberry pi's SPI bus to the Total Control Lighting addressable 
LED chains.

Also included is a Processing app that will connect to the raspberry pi and cycle through HSB
colors as quickly as it can based on the Hue cycling from 0-360 degrees.

This project depends on the wiringPi libraries by Gordon Drogon. Thanks Gordon!

Some of the code was also ripped from the Total Control Lighting Arduino TCL library. Since TCL 
doesn't tell it's customers what chipset is being used in their products, this was the only sure
way to get the code working correctly.


## Build


Build on the Pi itself:

```
make
```

Transfer all files to the Pi using SCP THEN build on the pi via SSH:

```
make -f Makefile.scp
```