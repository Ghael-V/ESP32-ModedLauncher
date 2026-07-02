#include "firmware_picker.h"
#include "app_registry.h"
#include "backup_manager.h"
#include "display.h"
#include "idf/launcher_platform.h"
#include "sd_functions.h"
#include <algorithm>
#include <globals.h>

namespace {
const char *kFirmwareDir = "/firmware";

std::vector<String> listFirmwareBins() {
    std::vector<String> bins;
    if (!setupSdCard()) return bins;
    if (!SDM.exists(kFirmwareDir)) SDM.mkdir(kFirmwareDir);

    File dir = SDM.open(kFirmwareDir);
    if (!dir || !dir.isDirectory()) return bins;

    while (true) {
        bool isDir;
        String fullPath = dir.getNextFileName(&isDir);
        if (fullPath == "") break;
        if (isDir) continue;
        String nameOnly = fullPath.substring(fullPath.lastIndexOf("/") + 1);
        int dot = nameOnly.lastIndexOf(".");
        String ext = dot >= 0 ? nameOnly.substring(dot + 1) : "";
        ext.toUpperCase();
        if (ext != "BIN") continue;
        bins.push_back(fullPath);
    }
    dir.close();
    std::sort(bins.begin(), bins.end());
    return bins;
}

// Boots the already-installed OTA app for this SD file if there is one
// (instant boot-partition switch), otherwise flashes it fresh. To force
// a re-flash after updating a .bin on the SD card, use the SD browser's
// "Install" action from the Advanced Menu instead of this picker.
void launchFirmware(const String &path) {
    String appNum = generateAppNum(path);
    for (const LauncherAppMetadata &app : launcherLoadAppRegistry()) {
        if (app.appNum == appNum) {
            launcherBootAppByLabel(app.label.c_str());
            return;
        }
    }
    updateFromSD(path);
}
} // namespace

void showFirmwarePicker() {
    std::vector<String> bins = listFirmwareBins();
    if (bins.empty()) {
        displayRedStripe("No .bin in /firmware");
        launcherDelayMs(2000);
        return; // nothing to pick, fall back to the Advanced Menu
    }

    std::vector<LauncherAppMetadata> registry = launcherLoadAppRegistry();

    while (true) {
        std::vector<Option> opts;
        for (const String &path : bins) {
            String name = launcherAppNameFromFile(path);
            String appNum = generateAppNum(path);
            bool installed = false;
            for (const LauncherAppMetadata &app : registry) {
                if (app.appNum == appNum) {
                    installed = true;
                    break;
                }
            }
            String label = installed ? (name + " *") : name;
            opts.push_back({label, [path]() { launchFirmware(path); }});
        }
        opts.push_back({"Advanced Menu >", []() {}});

        int idx = loopOptions(opts);
        if (idx < 0) continue;                                 // ESC: stay on the firmware list
        if (idx == static_cast<int>(bins.size())) return;       // "Advanced Menu >" picked
        // A firmware was picked: launchFirmware() reboots on success.
        // If it failed (bad file, install error) it already showed the
        // error and returned, so just redraw the list.
    }
}
