# ESP32-ModedLauncher

Fork de [bmorcelli/Launcher](https://github.com/bmorcelli/Launcher) personalizado para el **LilyGo T-Embed CC1101 (Plus)**, pensado para quien tiene varios firmwares (Bruce, Ghost ESP, Capibara, Furi...) en la SD y quiere elegir cuál arrancar sin liarse con menús.

## Qué cambia respecto al Launcher original

* **Arranque directo a un selector de firmwares**: en vez del menú SD/OTA/WUI/USB/PMan/CFG de siempre, al entrar al Launcher se escanea `SD:/firmware` y se listan directamente los `.bin` que haya ahí.
* **Instalación inteligente**: si ese `.bin` ya se instaló antes, se arranca al instante (solo cambia la partición de arranque); si es la primera vez, se flashea y luego arranca.
* **Nada se ha eliminado**: al final de la lista hay una opción **"Advanced Menu >"** que lleva al menú clásico completo (SD, OTA, WUI, USB, PMan, CFG) tal cual estaba en el proyecto original.
* **OTA unificado**: la descarga "Download->SD" del instalador online ahora cae en `SD:/firmware` en vez de `SD:/downloads`, así aparece directamente en el selector.
* **Splash screen propio**, sin parpadeos, con crédito visible al proyecto original.

## Cómo usarlo

1. Copia tus firmwares (`.bin`) a la carpeta `/firmware` de la SD (puedes montarla sin sacarla de la placa desde **Advanced Menu > USB**).
2. Enciende el T-Embed y pulsa el botón/encoder para entrar al Launcher.
3. Elige el firmware de la lista. Primera vez tarda lo normal (flasheo); las siguientes es instantáneo.
4. Si necesitas SD/OTA/WUI/USB/PMan/CFG, entra por **"Advanced Menu >"**, al final de la lista.

## Compilar y flashear

Proyecto basado en [PlatformIO](https://platformio.org/).

```bash
git clone --recurse-submodules https://github.com/Ghael-V/ESP32-ModedLauncher.git
cd ESP32-ModedLauncher
pio run -e lilygo-t-embed-cc1101 -t upload
```

## Créditos

Este proyecto es un fork con cariño del trabajo de [@bmorcelli](https://github.com/bmorcelli) en [Launcher](https://github.com/bmorcelli/Launcher), que da soporte a muchísimos más dispositivos (M5Stack, CYD, Marauder, y más) además de funciones que aquí quedan ocultas pero intactas en el Advanced Menu. Si buscas esa versión completa multi-dispositivo, esa es la que quieres.

Licencia MIT, ver [LICENSE](LICENSE).
