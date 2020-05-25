# UPDATE - Please read

Things are moving incredibly fast with both the core Arduino IDE and also the esp8266 dev team https://github.com/esp8266/arduino 

I'm struggling to keep my repo up to date with all the changes, so I suggest that all users of this repo, now look at either

This repo instead

https://github.com/sandeepmistry/esp8266-Arduino

or look at this issue thread, about installation via the IDE 1.6.3 boards manager

https://github.com/esp8266/Arduino/issues/57


I will keep this repo going for a while, but in the longer term it will definately be superseded by the main ESP8266 dev team's efforts at https://github.com/esp8266/arduino






### ESP8266 support files for Arduino 1.6.x 

This repo is based on github/esp8266/arduino for code source files and also www.arduinesp.com for toolchain

This is a windows only release. To make a linux release, you would need to compile the linux toolchain and install it in a different folder under tools.

##Instructions to install

In your My Documents/Arduino  folder

make a new folder named   hardware  
(if you don't already have one)

Then clone the repo into the hardware folder, or download the zip and unzip into the hardware folder

Download the official Arduino IDE 1.6.2 and install it (if you have 1.6.0 or 1.6.1 it should also work, and you can skip the next 2 steps)

If you have just done an clean install of 1.6.x... Run the Official IDE, (first run seems to take some time, I suspect its building a file cache)

Quit the official IDE as the first run doesn't seem to be able to see comm ports correctly

Restart the official IDE

Looking in the boards menu and you will see the Generic ESP8266  - select this

Under the programmer menu, select esptool (as the default appears to be no selection, which causes issues for upload)

Compile upload and enjoy ;-)


##Notes

Upload uses esptool.exe, which doesnt seem to report upload errors very well. 

Each upload consists of 2 separate files. 
esptool.exe prints about 20 dots as the first file is uploaded and around 100 dots when the second file is uploaded.
If after the upload the esp8266 doesnt seem to be doing what you expect, I'd recommend that you try uploading again

Also not, power supply issues seem to be common during uploads. i.e so although the esp8266 may work fine with the original firmware (AT command set), you may not be supplying the board with enough power to program it.

