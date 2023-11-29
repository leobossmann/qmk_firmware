# wired_sculpt

This Firmware is not entirely my own work, it is based on [Chad Austin's](https://github.com/chadaustin/qmk_firmware/tree/master/keyboards/handwired/sculpt) and [Jean Bernard's](https://github.com/qmk/qmk_firmware/tree/master/keyboards/ms_sculpt) work.

![wired_sculpt](imgur.com image replace me!)

*A short description of the keyboard/project*

* Keyboard Maintainer: [leobossmann](https://github.com/leobossmann)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make wired_sculpt:default

Flashing example for this keyboard:

    make wired_sculpt:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
