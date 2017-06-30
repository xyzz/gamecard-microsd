usbmc
=====
This is VitaShell's patches for USB storage support as a standalone plugin. If 
loaded on startup (before SceShell), it will automatically mount the USB 
storage as `ux0` instead of the memory card or internal memory.

To install, copy the plugin to `ur0:tai/usbmc.skprx` and add that path to the 
taiHEN `ur0:tai/config.txt` under `*KERNEL`. If you have a memory card inserted 
or you have a Vita with internal memory (LCD and PSTV), you must delete 
`ux0:tai/config.txt` from the original memory and use `ur0:tai/config.txt` from 
now on. This is because taiHEN loads before the memory card redirection patches 
and will attempt to read config.txt from there first.

Full credits to The_FloW for these patches.
