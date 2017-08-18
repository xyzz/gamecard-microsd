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

#define MOUNT_POINT_ID 0x800

#define MOUNT_POINT_ID2 0xF00 //used uma0 ID

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

static SceIoDevice uma_ux0_dev = { "ux0:", "exfatux0", "sdstor0:gcd-lp-ign-entire", "sdstor0:gcd-lp-ign-entire", MOUNT_POINT_ID };

static SceIoDevice uma_uma0_dev = { "uma0:", "exfatuma0", "sdstor0:xmc-lp-ign-userext", "sdstor0:xmc-lp-ign-userext", MOUNT_POINT_ID2 }; //For Vita MU

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

////{Region Scraps

int shellKernelIsUx0Redirected() {
	SceIoMountPoint *mount = sceIoFindMountPoint(MOUNT_POINT_ID);
	if (!mount) {
		return -1;
	}

	if (mount->dev == &uma_ux0_dev && mount->dev2 == &uma_ux0_dev) {
		return 1;
	}

	return 0;
}

int shellKernelUnredirectUx0() {
	SceIoMountPoint *mount = sceIoFindMountPoint(MOUNT_POINT_ID);
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

////}

int shellKernelRedirectUx0() {
	SceIoMountPoint *mount = sceIoFindMountPoint(MOUNT_POINT_ID);
	if (!mount) {
		return -1;
	}

	if (mount->dev != &uma_ux0_dev && mount->dev2 != &uma_ux0_dev) {
		ori_dev = mount->dev;
		ori_dev2 = mount->dev2;
	}

	mount->dev = &uma_ux0_dev;
	mount->dev2 = &uma_ux0_dev;

	return 0;
}

int shellKernelRedirectUma0() {
	SceIoMountPoint *mount = sceIoFindMountPoint(MOUNT_POINT_ID2);
	if (!mount) {
		return -1;
	}

	if (mount->dev != &uma_uma0_dev && mount->dev2 != &uma_uma0_dev) {
		ori_dev = mount->dev;
		ori_dev2 = mount->dev2;
	}

	mount->dev = &uma_uma0_dev;
	mount->dev2 = &uma_uma0_dev;

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

	shellKernelRedirectUx0();
	io_remount(MOUNT_POINT_ID);
	shellKernelRedirectUma0(); //Added uma0 mount was ux0 ie Vita MU
	io_mount(MOUNT_POINT_ID2); //No need to remount since it's not mounted!

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
	patch_sdstor();
	poke_gamecard();
	register_callback();
	if(exists("sdstor0:gcd-lp-ign-entire"))
	{
	redirect_ux0();
	}
	else
	{
	}
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
	return SCE_KERNEL_STOP_SUCCESS;
}
