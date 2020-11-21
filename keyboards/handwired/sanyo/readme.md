# Fujitsu N860-2531-T00105B "Sanyo" keyboard with Arduino Pro Micro

![Sanyo MBC-55 with keyboard](https://www.old-computers.com/museum/photos/sanyo_mbc550_1.jpg)

Using an Arduino to make the [Sanyo MBC-55](https://www.old-computers.com/museum/computer.asp?st=1&c=473) keyboard usable with modern computers.

* Keyboard Maintainer: [Laurence de Bruxelles](https://github.com/lfdebrux)
* Hardware Supported: N86D-2531-R001/02 PCB with controller replaced by Arduino Pro Micro
* Hardware Availability: Find someone selling one on [deskthority](https://deskthority.net/viewforum.php?f=11), then rewire it yourself

This keyboard was nicknamed "the Sanyo" in [Chyrosan22's video review of it](https://deskthority.net/viewtopic.php?t=13970).

Inside it uses an NEC μPD8049HC (a clone of the Intel MCS-48, I think) as the
controller, with a Texas Instruments SN74159 demultiplexer to select columns.
It uses an [idiosyncratic serial protocol](http://www.seasip.info/VintagePC/sanyo.html)
which isn't much use for anything, since there isn't an ALT or META key and you
can't even use the CTRL key normally.

To be able to use QMK I replaced the controller with an Arduino Pro Micro; a
lot of the 40 pins on the original MCU are unused so you only need 16 pins, so
a Nano or a Micro would probably do just as well. I also ran a wire from the
external reset switch on the keyboard to the reset pin on the Arduino.

Read the comments in the code for more notes on this hardware conversion.

Make example for this keyboard (after setting up your build environment):

    make sanyo:default

Flashing example for this keyboard:

    make sanyo:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
