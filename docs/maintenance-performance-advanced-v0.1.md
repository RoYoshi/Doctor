# FE-Xico Doctor: Maintenance, Performance and Advanced draft

This extends RoYo's existing Kirigami/C++ v0.1 Doctor application and README.

## Maintenance
- Restart current user's PipeWire, pipewire-pulse and WirePlumber services (audio will briefly interrupt).
- Rebuild the KDE service/application cache with kbuildsycoca6.
- Inspect failed user services and recent user journal warnings.

## Performance
- Inspect powerprofilesctl current/available profiles.
- Apply performance, balanced (reset), or power-saver profiles, subject to device support and system authorization.
- GPU/game tuning remains planned; no fake switches.

## Advanced
- Inspect enabled system services, kernel command-line arguments, disks and network devices.
- Custom actions, kernel edits and configuration writes remain planned, disabled in this prototype.

## Behavior and limitations
Mutating commands display exact command and an explanation in a confirmation dialog. All commands are fixed named actions using QProcess argument lists; no raw shell or unbounded user input. Existing live console, stop button and timeout remain. FE-Xico Updater owns upgrades/rollbacks. This is an **uncompiled draft** until Qt/Kirigami CI and graphical Wayland testing pass. Do not include in a published OS image yet.
