# PS Vita gamecard to microSD adapter

## Software

`driver` contains a kernel module. Add it to taihen's `config.txt` KERNEL section. You can download a precompiled `.skprx` from the [Releases](https://github.com/xyzz/gamecard-microsd/releases) section.

Your microSD card must have no partition table. exFAT filesystem should be written directly to the device. On Linux, do:

```
mkfs.exfat /dev/sdx # (without a number)
```

On Windows, this works: https://redd.it/6o4gqh / https://redd.it/6o62vx

After that, the card still works on both Linux and Windows, however other devices might have some problems.

### Compiling the driver

To compile:

```
cd driver
mkdir build && cd build
cmake ..
make
```

## Hardware

`board` contains Autodesk EAGLE schematics and board files. **Note: last revision still untested.**

The pcb has to be 1mm thick. This means I only tested 1mm thick PCBs and found them to work fine. I don't know if other thicknesses work.

Note how the pcb has a hole in place of microsd socket. You need to flip the socket and mount it into the hole .

![](https://i.imgur.com/5X5qVBu.jpg)

The socket should look like that. You can buy these from aliexpress for about $0.1-0.2/piece. Check out [issue 2](https://github.com/xyzz/gamecard-microsd/issues/2) for a buying guide.

There's no case for the adapter. Make sure to cover testpoints with some tape to prevent shorts. (v3.0 of the design has no test pads so you do not have to insulate anything). You also will have to use tweezers to remove adapter from PS Vita. Don't grab the adapter by the socket or you risk damaging it.

The adapter does not use Vita gamecard push-pull mechanism. If you feel a spring while inserting it, this means you are inserting it wrong.

If you accidentally short contacts, the Vita will power off. However, in my testing, this does not seem to cause any permanent damage.

Once you insert the adapter, you can replace microSD without taking the adapter out.

### Version history

#### v3.0

* Reduced gamecard pads total width by 0.2mm.
* Removed testpads.
* Removed unused INS pad on the microSD socket side.
* Changed routing to reduce number of VIAs and the probability of electrons falling out of the board.

This design is not tested yet.

#### v2.0

* Reduced gamecard pads total width by 1.0mm.
* Removed fourth microsd socket leg.

This design is not tested by me yet, but other people confirmed it works.

#### v1.0

Original design.

### Alternative designs

You can find some alternative designs here:

* https://github.com/Gadorach/SD2VITA
* https://www.elotrolado.net/hilo_proyecto-hardmod-para-poner-un-lector-de-micro-sd-en-la-psvita_2229693 (Spanish)

(Send a pr if you want to be included here)
