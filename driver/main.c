/*
	VitaShell
	Copyright (C) 2015-2017, TheFloW

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <psp2kern/kernel/cpu.h>
#include <psp2kern/kernel/modulemgr.h>
#include <psp2kern/kernel/sysmem.h>
#include <psp2kern/io/fcntl.h>

#include <stdio.h>
#include <string.h>

#include <taihen.h>

#define MOUNT_POINT_UX0 0x800
#define MOUNT_POINT_UMA0 0xF00 //used uma0 ID
#define MOUNT_CONFIG_PATH "ur0:tai/gamesd.cfg"

int module_get_offset(SceUID pid, SceUID modid, int segidx, size_t offset, uintptr_t *addr);

typedef struct {
	const char *dev;
	const char *dev2;
	const char *blkdev;
	const char *blkdev2;
	int id;
} SceIoDevice;

typedef struct {
	int id;
	const char *dev_unix;
	int unk;
	int dev_major;
	int dev_minor;
	const char *dev_filesystem;
	int unk2;
	SceIoDevice *dev;
	int unk3;
	SceIoDevice *dev2;
	int unk4;
	int unk5;
	int unk6;
	int unk7;
} SceIoMountPoint;

typedef struct {
	int microsd_mnt;
	SceIoDevice *microsd_dev;
	int mc_mnt;
	SceIoDevice *mc_dev;
} MountConfig;

static SceIoDevice uma_ux0_dev_sdcard = { "ux0:", "exfatux0", "sdstor0:gcd-lp-ign-entire", "sdstor0:gcd-lp-ign-entire", MOUNT_POINT_UX0 };
static SceIoDevice uma_ux0_dev_mc = { "ux0:", "exfatux0", "sdstor0:xmc-lp-ign-userext", "sdstor0:xmc-lp-ign-userext", MOUNT_POINT_UX0 };
static SceIoDevice uma_uma0_dev_sdcard = { "uma0:", "exfatuma0", "sdstor0:gcd-lp-ign-entire", "sdstor0:gcd-lp-ign-entire", MOUNT_POINT_UMA0 };
static SceIoDevice uma_uma0_dev_mc = { "uma0:", "exfatuma0", "sdstor0:xmc-lp-ign-userext", "sdstor0:xmc-lp-ign-userext", MOUNT_POINT_UMA0 };

// Default: microsd mounts to ux0 and mc is not mounted
static MountConfig mount_cfg = { MOUNT_POINT_UX0, &uma_ux0_dev_sdcard, -1, NULL };

static SceIoMountPoint *(* sceIoFindMountPoint)(int id) = NULL;

static SceIoDevice *ori_dev = NULL, *ori_dev2 = NULL;

static int exists(const char *path) {
	int fd = ksceIoOpen(path, SCE_O_RDONLY, 0);
	if (fd < 0)
		return 0;
	ksceIoClose(fd);
	return 1;
}

static void io_remount(int id) {
	ksceIoUmount(id, 0, 0, 0);
	ksceIoUmount(id, 1, 0, 0);
	ksceIoMount(id, NULL, 0, 0, 0, 0);
}

static void io_mount(int id) {
	ksceIoMount(id, NULL, 0, 0, 0, 0);
}

static void load_mount_cfg() {
	if (!exists(MOUNT_CONFIG_PATH)) {
		// TODO: consider creating the file with default settings
		return;
	}

	// Read the file contents
	int fd = ksceIoOpen(MOUNT_CONFIG_PATH, SCE_O_RDONLY, 0);
	char cfg_contents[32];
	int bytes_read = ksceIoRead(fd, cfg_contents, 31);
	ksceIoClose(fd);
	cfg_contents[bytes_read] = '\x00';

	// Parse the mountpoint for microsd
	if (strstr(cfg_contents, "microsd=ux0") != NULL) {
		mount_cfg.microsd_mnt = MOUNT_POINT_UX0;
		mount_cfg.microsd_dev = &uma_ux0_dev_sdcard;
	} else if (strstr(cfg_contents, "microsd=uma0") != NULL) {
		mount_cfg.microsd_mnt = MOUNT_POINT_UMA0;
		mount_cfg.microsd_dev = &uma_uma0_dev_sdcard;
	} else {
		mount_cfg.microsd_mnt = -1;
		mount_cfg.microsd_dev = NULL;
	}

	// Parse the mountpoint for memorycard
	if (strstr(cfg_contents, "memorycard=ux0") != NULL) {
		mount_cfg.mc_mnt = MOUNT_POINT_UX0;
		mount_cfg.mc_dev = &uma_ux0_dev_mc;
	} else if (strstr(cfg_contents, "memorycard=uma0") != NULL) {
		mount_cfg.mc_mnt = MOUNT_POINT_UMA0;
		mount_cfg.mc_dev = &uma_uma0_dev_mc;
	} else {
		mount_cfg.mc_mnt = -1;
		mount_cfg.mc_dev = NULL;
	}

	// Error check
	if (mount_cfg.microsd_mnt == mount_cfg.mc_mnt) {
		// Invalid configuration, both mounted to the same location
		// Revert to the default config
		mount_cfg.microsd_mnt = MOUNT_POINT_UX0;
		mount_cfg.microsd_dev = &uma_ux0_dev_sdcard;
		mount_cfg.mc_mnt = -1;
		mount_cfg.mc_dev = NULL;
	}
}

int shellKernelIsRedirected(int mountpoint, SceIoDevice *device) {
	SceIoMountPoint *mount = sceIoFindMountPoint(mountpoint);
	if (!mount) {
		return -1;
	}

	if (mount->dev == device && mount->dev2 == device) {
		return 1;
	}

	return 0;
}

int shellKernelUnredirect(int mountpoint) {
	SceIoMountPoint *mount = sceIoFindMountPoint(mountpoint);
	if (!mount) {
		return -1;
	}

	if (ori_dev && ori_dev2) {
		mount->dev = ori_dev;
		mount->dev2 = ori_dev2;

		ori_dev = NULL;
		ori_dev2 = NULL;
	}

	return 0;
}

int shellKernelRedirect(int mountpoint, SceIoDevice *device) {
	SceIoMountPoint *mount = sceIoFindMountPoint(mountpoint);
	if (!mount) {
		return -1;
	}

	if (mount->dev != device && mount->dev2 != device) {
		ori_dev = mount->dev;
		ori_dev2 = mount->dev2;
	}

	mount->dev = device;
	mount->dev2 = device;

	return 0;
}

// ux0 redirect by theflow
int redirect_ux0() {
	// Get tai module info
	tai_module_info_t info;
	info.size = sizeof(tai_module_info_t);
	if (taiGetModuleInfoForKernel(KERNEL_PID, "SceIofilemgr", &info) < 0)
		return -1;

	// Get important function
	module_get_offset(KERNEL_PID, info.modid, 0, 0x138C1, (uintptr_t *)&sceIoFindMountPoint);

	if (mount_cfg.microsd_mnt > 0 && mount_cfg.microsd_dev != NULL) {
		shellKernelRedirect(mount_cfg.microsd_mnt, mount_cfg.microsd_dev);
		if (mount_cfg.microsd_mnt == MOUNT_POINT_UMA0)
			io_mount(mount_cfg.microsd_mnt);
		else
			io_remount(mount_cfg.microsd_mnt);
	}
	if (mount_cfg.mc_mnt > 0 && mount_cfg.mc_dev != NULL) {
		shellKernelRedirect(mount_cfg.mc_mnt, mount_cfg.mc_dev);
		if (mount_cfg.mc_mnt == MOUNT_POINT_UMA0)
			io_mount(mount_cfg.mc_mnt);
		else
			io_remount(mount_cfg.mc_mnt);
	}

	return 0;
}

int poke_gamecard() {
	tai_module_info_t info;
	info.size = sizeof(tai_module_info_t);
	if (taiGetModuleInfoForKernel(KERNEL_PID, "SceSdstor", &info) < 0)
		return -1;

	void *args = 0;
	int (*int_insert)() = 0;
	int (*int_remove)() = 0;

	module_get_offset(KERNEL_PID, info.modid, 0, 0x3BD5, (uintptr_t *)&int_insert);
	module_get_offset(KERNEL_PID, info.modid, 0, 0x3BC9, (uintptr_t *)&int_remove);

	module_get_offset(KERNEL_PID, info.modid, 1, 0x1B20 + 40 * 1, (uintptr_t *)&args);

	int_remove(0, args);
	ksceKernelDelayThread(500 * 1000);
	int_insert(0, args);
	ksceKernelDelayThread(500 * 1000);

	return 0;
}

int suspend_callback(int resume, int eventid, void *args, void *opt) {
	if (eventid != 0x100000)
		return 0;

	poke_gamecard();

	return 0;
}

int register_callback() {
	ksceKernelRegisterSuspendCallback("gamesd", suspend_callback, NULL);
}

int gen_init_2_patch_uid;

// allow SD cards, patch by motoharu
void patch_sdstor() {
	tai_module_info_t sdstor_info;
	sdstor_info.size = sizeof(tai_module_info_t);
	if (taiGetModuleInfoForKernel(KERNEL_PID, "SceSdstor", &sdstor_info) >= 0) {
		//patch for proc_initialize_generic_2 - so that sd card type is not ignored
		char zeroCallOnePatch[4] = {0x01, 0x20, 0x00, 0xBF};
		gen_init_2_patch_uid = taiInjectDataForKernel(KERNEL_PID, sdstor_info.modid, 0, 0x2498, zeroCallOnePatch, 4); //patch (BLX) to (MOVS R0, #1 ; NOP)
	}
}

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp) {
	load_mount_cfg();
	patch_sdstor();
	poke_gamecard();
	register_callback();
	redirect_ux0();

	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
	return SCE_KERNEL_STOP_SUCCESS;
}
