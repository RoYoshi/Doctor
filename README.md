# FE-Xico Doctor

**FE-Xico Doctor** is a read-only system-health application for
[FE-XicoOS](https://github.com/RoYoshi/FE-Xico), a Fedora bootc desktop. It
checks:
- bootc deployments and updates;
- services and SELinux;
- graphics drivers, including NVIDIA, and game controllers;
- storage, Flatpaks, network and logs.

For each finding it explains what it means and what you can do.

It never needs root, never changes the system and never makes network
requests.

- **Desktop window:** status at a glance, check groups, filters, details and
  report export (PySide6 / Qt Widgets, light and dark themes).
- **Command line:** `fe-xico-doctor --text | --json | --summary | --list-checks`,
  with `--redact` for reports you want to share. Exit status: 0 no error,
  1 error found, 2 usage error, 3 Doctor failed.
- **Report:** JSON schema `fe-xico-doctor/report` v2
  (`data/fe-xico-doctor-report.schema.json`).

Full documentation: [docs/FE_XICO_DOCTOR.md](docs/FE_XICO_DOCTOR.md).

## Status

Version **1.0.0**. This is the application that FE-XicoOS has shipped since
Doctor v1.0. Until 2026-11 it lived in the FE-XicoOS repository
(`system_files/usr/lib/fe-xicoos/fexico_doctor`). It moved here unchanged
from FE-XicoOS commit `2c2d24e`; [docs/MIGRATION.md](docs/MIGRATION.md) has
the file-by-file record. This repository is now the only place Doctor is
developed, tested and released. FE-XicoOS installs the signed RPM.

The earlier C++/Kirigami prototype (v0.1) is preserved on the
[`archive/cpp-prototype`](https://github.com/RoYoshi/FE-Xico-Doctor/tree/archive/cpp-prototype)
branch.

## Layout

| Path | Installed as |
|---|---|
| `bin/fe-xico-doctor` | `/usr/bin/fe-xico-doctor` |
| `fexico_doctor/` | `/usr/lib/fe-xicoos/fexico_doctor/` |
| `data/io.github.royoshi.fexicodoctor.desktop` | `/usr/share/applications/` |
| `data/fe-xico-doctor-report.schema.json` | `/usr/share/fe-xicoos/` |
| `data/icons/hicolor/` | `/usr/share/icons/hicolor/` (raster badge, 16–512 px) |
| `tools/build_doctor_icon.py` | developer tool: regenerates the icons from `tools/fe-xico-doctor-icon-source.png` |
| `packaging/` | RPM spec, build script and CI checks |

## Develop and test

```bash
python3 -m unittest discover -s tests            # source tests (GUI tests need python3-pyside6)
bin/fe-xico-doctor --summary                     # run from the checkout
QT_QPA_PLATFORM=offscreen bin/fe-xico-doctor --gui-self-test
```

## Build the RPM

On Fedora (45 or 44) with `rpm-build python3-devel desktop-file-utils`:

```bash
packaging/build-rpm.sh          # → dist/fe-xico-doctor-X.Y.Z-1.fcNN.noarch.rpm and the SRPM
```

Runtime dependencies are `python3`, `python3-pyside6`, `hicolor-icon-theme`
and the matching `python(abi)`. All diagnostic tools (bootc, systemctl,
journalctl, rpm, flatpak, lspci, nvidia-smi, …) are optional: Doctor reports
a missing one as Unknown.

Fedora 45 enforces RPM signatures, so a locally built, unsigned package will
not install there. Use the signed release, or sign the package with your own
key and import that key first.

## Releases

Signed releases are created by hand through the protected release workflow;
see [docs/RELEASING.md](docs/RELEASING.md) for versioning, signing, and how
FE-XicoOS pins a release.

## License

Apache-2.0 (see `LICENSE`), as in FE-XicoOS, where this code originated.
