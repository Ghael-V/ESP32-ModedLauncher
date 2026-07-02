#ifndef FIRMWARE_PICKER_H
#define FIRMWARE_PICKER_H

/*********************************************************************
** Scans SD:/firmware for .bin files and lets the user pick one.
** Firmwares already installed to an OTA partition boot instantly
** (just a boot-partition switch); new ones get flashed once.
** Only returns when the user asks for the Advanced Menu
** (SD/OTA/WUI/USB/PMan/CFG) or there's nothing to pick; the caller
** shows the full menu right after this returns.
**********************************************************************/
void showFirmwarePicker();

#endif
