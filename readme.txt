-- setup --

clone from fork to Users/<username>/qmk_firmware
setup with https://docs.qmk.fm/#/newbs_getting_started

install atmel flip https://www.microchip.com/developmenttools/ProductDetails/FLIP
put keyboard in reset mode (fn+<> `) <diamond>
open device manager update atmega32u4 driver (atmel folder)


-- building --

open msys2 MinGW 64-bit
> qmk compile -kb dz60 -km q

open qmk_toolbox.exe
open dz50_q.hex
atmega32u4
put keyboard in reset mode
flash
