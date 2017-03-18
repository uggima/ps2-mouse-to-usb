# ps2-mouse-to-usb
for attiny85

edited digispark usb mouse example to allow input from a ps2 mouse using https://github.com/scanlime/navi-misc/tree/master/arduino/ps2. with a reduction delays in switching to master tx mode from 300us/stage to 150us to allow for informaiton to be collected from mouse/touchpad within the 10ms between usb packets.

also makes use of the digispark libraries (unchanged) https://digistump.com/wiki/digispark/tutorials/connecting / http://digistump.com/package_digistump_index.json
