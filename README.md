# PS Vita gamecard to microSD adapter

## Software

`driver` contains a kernel module. Add it to taihen's `config.txt` KERNEL section.

Your microSD card must have no partition table. exFAT filesystem should be written directly to the device. On linux, do:

```
mkfs.exfat /dev/sdx
```

I'm not sure how to do the same on windows. After that, the card still works on both linux and windows, however other devices might have some problems.

## Hardware

`board` contains Autodesk EAGLE schematics and board files. **Note: last revision still untested.**

The pcb has to be 1mm thick.

Note how the pcb has a hole in place of microsd socket. You need to flip the socket and mount it into the hole .

![](https://i.imgur.com/5X5qVBu.jpg)

The socket should look like that. You can buy these from aliexpress for about $0.1-0.2/piece.

There's no case for the adapter. Make sure to cover testpoints with some tape to prevent shorts. You also will have to use tweezers to remove adapter from PS Vita. Don't grab the adapter by the socket or you risk damaging it.

The adapter does not use Vita gamecard push-pull mechanism. If you feel a spring while inserting it, this means you are inserting it wrong.

If you accidentally short contacts, the Vita will power off. However, in my testing, this does not seem to cause any permanent damage.

Once you insert the adapter, you can replace microSD without taking the adapter out.

### Alternative designs

You can find some alternative and improved designs here:

* https://github.com/Gadorach/SD2VITA

(Send a pr if you want to be included here)
