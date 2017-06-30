# PS Vita gamecard to micrSD adapter

## Software

`driver` contains a kernel module. Add it to taihen's `config.txt` KERNEL section.

## Hardware

`board` contains Autodesk EAGLE schematics and board files. **Note: last revision still untested.**

Note how the pcb has a hole in place of microsd socket. You need to flip the socket and mount it into the hole .

![](https://i.imgur.com/5X5qVBu.jpg)

The socket should look like that. You can buy these from aliexpress for about $0.1-0.2/piece.

There's no case for the adapter. Make sure to cover testpoints with some tape to prevent shorts. You also will have to use tweezers to remove adapter from PS Vita. Don't grab the adapter by the socket or you risk damaging it.
