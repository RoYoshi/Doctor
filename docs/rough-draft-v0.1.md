# FE-Xico Doctor — first GUI draft (v0.1)

This extends RoYo's **existing C++ / Qt 6 / KDE Kirigami draft**. It does not
replace it with another toolkit, and keeps the existing Doctor SVG artwork.

## What works in this draft

- A Kirigami dashboard with live CPU model, memory, root-storage free space,
  GPU vendor hint, system uptime, kernel and FE-Xico version (if present).
- Three explicit, read-only diagnostics with visible command and live output:
  failed systemd services, current bootc deployment, and system Flatpak apps.
- A Stop button, 15-second command timeout, friendly errors when tools are
  unavailable, and a visible console that stays hidden until needed.
- A non-empty desktop launcher and installation of the existing Doctor icon.

It is deliberately **not a system monitor**: the resource values are snapshots
from local kernel/sysfs data, not continuously sampled charts. GPU vendor
detection is only a hint and does not validate the driver or gaming readiness.

## Boundaries

- The GUI runs as a normal user. It does not run itself as root.
- The backend uses a fixed set of process/argument pairs. QML cannot pass an
  arbitrary executable or shell command to Doctor.
- No `sudo`, `pkexec`, `bootc upgrade`, rollback, service restart, RPM removal,
  root-filesystem writes, or automatic repairs are performed.
- The bootc status command may be unavailable to an unprivileged user; the
  console reports the real error, and Doctor does not silently elevate.
- FE-Xico Updater stays responsible for upgrading or rolling back the OS.

## Build and run on Fedora development environment

Use the dependencies in the repository README (prefer Distrobox on bootc).

```bash
cmake -S . -B build
cmake --build build -j2
./build/bin/fe-xico-doctor
```

The devcontainer may need an updated dependency set for the newest Fedora
Qt/Kirigami versions. The current draft is **not yet baked into FE-XicoOS**.

## Next iterations

1. Hardware testing on FE-XicoOS KDE Wayland; check console layout, theme,
   the icon, and actual `bootc status` permissions.
2. Separate diagnostic history and result cards (read-only first).
3. Configurable actions with strict schema validation and command preview.
4. A privileged helper for specific approved repairs, with explicit operation
   details, authentication, and a practical undo strategy.

No step should affect the user's current pinned or booted deployment until
we have tested it separately.
