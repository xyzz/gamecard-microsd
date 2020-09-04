/*
	gamecard-microsd
	Copyright 2017-2018, xyz
	Copyright 2020, Yoti

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

/*
	This software contains code derived from VitaShell.
	Included below is the license header from VitaShell.
*/

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
#include <psp2kern/kernel/threadmgr.h>

#include <stdio.h>
#include <string.h>

#include <taihen.h>

#define MOUNT_POINT_ID 0x800

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

static SceIoMountPoint *(* sceIoFindMountPoint)(int id) = NULL;

static SceIoDevice *ori_dev = NULL, *ori_dev2 = NULL;

static void io_remount(int id) {
	ksceIoUmount(id, 0, 0, 0);
	ksceIoUmount(id, 1, 0, 0);
	ksceIoMount(id, NULL, 0, 0, 0, 0);
}

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

// ux0 redirect by theflow
int redirect_ux0() {
	// Get tai module info
	tai_module_info_t info;
	info.size = sizeof(tai_module_info_t);
	if (taiGetModuleInfoForKernel(KERNEL_PID, "SceIofilemgr", &info) < 0)
		return -1;

	// Get important function
	switch (info.module_nid) {
		case 0x7A1DBDE6: // 3.55 retail
		case 0xEF58597E: // 3.57 retail
		case 0x9642948C: // 3.60 retail
			module_get_offset(KERNEL_PID, info.modid, 0, 0x138C1, (uintptr_t *)&sceIoFindMountPoint);
			break;

		case 0xE923F19C: // 3.61 retail
			module_get_offset(KERNEL_PID, info.modid, 0, 0x138D5, (uintptr_t *)&sceIoFindMountPoint);
			break;

		case 0x5FC2B87D: // 3.63 retail
		case 0xA96ACE9D: // 3.65 retail
		case 0x3347A95F: // 3.67 retail
		case 0x90DA33DE: // 3.68 retail
			module_get_offset(KERNEL_PID, info.modid, 0, 0x182F5, (uintptr_t *)&sceIoFindMountPoint);
			break;

		case 0xF16E72C7: // 3.69 retail
		case 0x81A49C2B: // 3.70 retail
		case 0xF2D59083: // 3.71 retail
		case 0x9C16D40A: // 3.72 retail
		case 0xF7794A6C: // 3.73 retail
			module_get_offset(KERNEL_PID, info.modid, 0, 0x18735, (uintptr_t *)&sceIoFindMountPoint);
			break;

		default:
			return -1;
	}

	shellKernelRedirectUx0();
	io_remount(MOUNT_POINT_ID);

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

tai_hook_ref_t hook_get_partition;
tai_hook_ref_t hook_write;
tai_hook_ref_t hook_mediaid;

uint32_t magic = 0x7FFFFFFF;

void *sdstor_mediaid;

void *my_get_partition(const char *name, size_t len) {
	void *ret = TAI_CONTINUE(void*, hook_get_partition, name, len);
	if (!ret && len == 18 && strcmp(name, "gcd-lp-act-mediaid") == 0) {
		return &magic;
	}
	return ret;
}

uint32_t my_write(uint8_t *dev, void *buf, uint32_t sector, uint32_t size) {
	if (dev[36] == 1 && sector == magic) {
		return 0;
	}
	return TAI_CONTINUE(uint32_t, hook_write, dev, buf, sector, size);
}

uint32_t my_mediaid(uint8_t *dev) {
	uint32_t ret = TAI_CONTINUE(uint32_t, hook_mediaid, dev);

	if (dev[36] == 1) {
		memset(dev + 20, 0xFF, 16);
		memset(sdstor_mediaid, 0xFF, 16);

		return magic;
	}
	return ret;
}

// allow SD cards, patch by motoharu
void patch_sdstor() {
	tai_module_info_t sdstor_info;
	sdstor_info.size = sizeof(tai_module_info_t);
	if (taiGetModuleInfoForKernel(KERNEL_PID, "SceSdstor", &sdstor_info) < 0)
		return;

	module_get_offset(KERNEL_PID, sdstor_info.modid, 1, 0x1720, (uintptr_t *) &sdstor_mediaid);

	// patch for proc_initialize_generic_2 - so that sd card type is not ignored
	char zeroCallOnePatch[4] = {0x01, 0x20, 0x00, 0xBF};
	taiInjectDataForKernel(KERNEL_PID, sdstor_info.modid, 0, 0x2498, zeroCallOnePatch, 4); //patch (BLX) to (MOVS R0, #1 ; NOP)
	taiInjectDataForKernel(KERNEL_PID, sdstor_info.modid, 0, 0x2940, zeroCallOnePatch, 4);

	taiHookFunctionOffsetForKernel(KERNEL_PID, &hook_get_partition, sdstor_info.modid, 0, 0x142C, 1, my_get_partition);
	taiHookFunctionOffsetForKernel(KERNEL_PID, &hook_write, sdstor_info.modid, 0, 0x2C58, 1, my_write);
	taiHookFunctionOffsetForKernel(KERNEL_PID, &hook_mediaid, sdstor_info.modid, 0, 0x3D54, 1, my_mediaid);
}

// allow Memory Card remount
void patch_appmgr() {
	tai_module_info_t appmgr_info;
	appmgr_info.size = sizeof(tai_module_info_t);
	if (taiGetModuleInfoForKernel(KERNEL_PID, "SceAppMgr", &appmgr_info) >= 0) {
		uint32_t nop_nop_opcode = 0xBF00BF00;
		switch (appmgr_info.module_nid) {
			case 0x94CEFE4B: // 3.55 retail (untested)
			case 0xDFBC288C: // 3.57 retail (untested)
			case 0xDBB29DB7: // 3.60 retail
			case 0xB5F8EA7C: // 3.61 retail (untested)
			case 0x23B967C5: // 3.63 retail (untested)
			case 0x1C9879D6: // 3.65 retail
				taiInjectDataForKernel(KERNEL_PID, appmgr_info.modid, 0, 0xB338, &nop_nop_opcode, 4);
				taiInjectDataForKernel(KERNEL_PID, appmgr_info.modid, 0, 0xB368, &nop_nop_opcode, 2);
				break;

			case 0x54E2E984: // 3.67 retail
			case 0xC3C538DE: // 3.68 retail
				taiInjectDataForKernel(KERNEL_PID, appmgr_info.modid, 0, 0xB344, &nop_nop_opcode, 4);
				taiInjectDataForKernel(KERNEL_PID, appmgr_info.modid, 0, 0xB374, &nop_nop_opcode, 2);
				break;

			case 0x321E4852: // 3.69 retail
			case 0x700DA0CD: // 3.70 retail
			case 0xF7846B4E: // 3.71 retail
			case 0xA8E80BA8: // 3.72 retail
			case 0xB299D195: // 3.73 retail (untested)
				taiInjectDataForKernel(KERNEL_PID, appmgr_info.modid, 0, 0xB34C, &nop_nop_opcode, 4);
				taiInjectDataForKernel(KERNEL_PID, appmgr_info.modid, 0, 0xB37C, &nop_nop_opcode, 2);
				break;
		}
	}
}

void _start() __attribute__ ((weak, alias("module_start")));
int module_start(SceSize args, void *argp) {
	patch_sdstor();
	patch_appmgr();
	poke_gamecard();
	redirect_ux0();

	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize args, void *argp) {
	return SCE_KERNEL_STOP_SUCCESS;
}
