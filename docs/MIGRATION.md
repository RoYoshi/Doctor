# Migration from FE-XicoOS (November 2026)

FE-Xico Doctor v1.0 was developed inside the FE-XicoOS repository
(`RoYoshi/FE-Xico`). It was moved here from FE-XicoOS commit
`2c2d24e8ab970dc6525d8cfebd85204e0d8072f5`. Its earlier history stays in
FE-XicoOS's Git history.

The C++/Qt/Kirigami prototype that this repository held before (v0.1) is
preserved, unchanged, on the `archive/cpp-prototype` branch (commit
`cd23e29`). It is no longer developed. The Python/PySide6 application is the
one FE-XicoOS users have been running, and it replaces the prototype here.

## Files

The whole application (all 18 Python modules), the desktop entry,
the report schema, all nine icon sizes, the icon source art and the licence
are byte-identical to FE-XicoOS commit `2c2d24e`.

| FE-XicoOS (`2c2d24e`) | Here | |
|---|---|---|
| `system_files/usr/lib/fe-xicoos/fexico_doctor/__init__.py` | `fexico_doctor/__init__.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/context.py` | `fexico_doctor/context.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/engine.py` | `fexico_doctor/engine.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/gui.py` | `fexico_doctor/gui.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/model.py` | `fexico_doctor/model.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/probes/__init__.py` | `fexico_doctor/probes/__init__.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/probes/hardware.py` | `fexico_doctor/probes/hardware.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/probes/logs.py` | `fexico_doctor/probes/logs.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/probes/network.py` | `fexico_doctor/probes/network.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/probes/security.py` | `fexico_doctor/probes/security.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/probes/software.py` | `fexico_doctor/probes/software.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/probes/storage.py` | `fexico_doctor/probes/storage.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/probes/system.py` | `fexico_doctor/probes/system.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/probes/updates.py` | `fexico_doctor/probes/updates.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/report.py` | `fexico_doctor/report.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/runner.py` | `fexico_doctor/runner.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/theme.py` | `fexico_doctor/theme.py` | identical |
| `system_files/usr/lib/fe-xicoos/fexico_doctor/viewmodel.py` | `fexico_doctor/viewmodel.py` | identical |
| `system_files/usr/bin/fe-xico-doctor` | `bin/fe-xico-doctor` | adapted: source-checkout fallback now looks next to `bin/` (the installed path `/usr/lib/fe-xicoos` is still tried first, so installed behaviour is unchanged) |
| `system_files/usr/share/applications/io.github.royoshi.fexicodoctor.desktop` | `data/io.github.royoshi.fexicodoctor.desktop` | identical |
| `system_files/usr/share/fe-xicoos/fe-xico-doctor-report.schema.json` | `data/fe-xico-doctor-report.schema.json` | identical |
| `system_files/usr/share/icons/hicolor/128x128/apps/io.github.royoshi.fexicodoctor.png` | `data/icons/hicolor/128x128/apps/io.github.royoshi.fexicodoctor.png` | identical |
| `system_files/usr/share/icons/hicolor/16x16/apps/io.github.royoshi.fexicodoctor.png` | `data/icons/hicolor/16x16/apps/io.github.royoshi.fexicodoctor.png` | identical |
| `system_files/usr/share/icons/hicolor/22x22/apps/io.github.royoshi.fexicodoctor.png` | `data/icons/hicolor/22x22/apps/io.github.royoshi.fexicodoctor.png` | identical |
| `system_files/usr/share/icons/hicolor/24x24/apps/io.github.royoshi.fexicodoctor.png` | `data/icons/hicolor/24x24/apps/io.github.royoshi.fexicodoctor.png` | identical |
| `system_files/usr/share/icons/hicolor/256x256/apps/io.github.royoshi.fexicodoctor.png` | `data/icons/hicolor/256x256/apps/io.github.royoshi.fexicodoctor.png` | identical |
| `system_files/usr/share/icons/hicolor/32x32/apps/io.github.royoshi.fexicodoctor.png` | `data/icons/hicolor/32x32/apps/io.github.royoshi.fexicodoctor.png` | identical |
| `system_files/usr/share/icons/hicolor/48x48/apps/io.github.royoshi.fexicodoctor.png` | `data/icons/hicolor/48x48/apps/io.github.royoshi.fexicodoctor.png` | identical |
| `system_files/usr/share/icons/hicolor/512x512/apps/io.github.royoshi.fexicodoctor.png` | `data/icons/hicolor/512x512/apps/io.github.royoshi.fexicodoctor.png` | identical |
| `system_files/usr/share/icons/hicolor/64x64/apps/io.github.royoshi.fexicodoctor.png` | `data/icons/hicolor/64x64/apps/io.github.royoshi.fexicodoctor.png` | identical |
| `tools/theme/build_doctor_icon.py` | `tools/build_doctor_icon.py` | adapted: paths for the new layout (`tools/`, `data/icons/`) |
| `tools/theme/fe-xico-doctor-icon-source.png` | `tools/fe-xico-doctor-icon-source.png` | identical |
| `tests/doctor_testlib.py` | `tests/doctor_testlib.py` | adapted: imports the package from the repository root |
| `tests/test_fe_xico_doctor.py` | `tests/test_fe_xico_doctor.py` | adapted: paths for the new layout; checks of FE-XicoOS's Containerfile and build scripts moved to FE-XicoOS |
| `tests/test_fe_xico_doctor_probes.py` | `tests/test_fe_xico_doctor_probes.py` | identical |
| `docs/FE_XICO_DOCTOR.md` | `docs/FE_XICO_DOCTOR.md` | adapted: paths, packaging and CI notes; the runtime checklist now names Doctor's own badge icon (it said the FE-Xico hat, which Doctor no longer uses) |
| `LICENSE` | `LICENSE` | identical |

Kept in FE-XicoOS, because they belong to the image rather than the
application:
- `build_files/run-doctor-gui-check.sh`, the image-build GUI check;
- the VM workflow's screenshot step;
- the build-failure annotation test;
- the checks that the image installs and verifies the Doctor RPM.

## Same behaviour

On one machine, the original FE-XicoOS launcher and this repository's
launcher were run from their source trees:

| Check | Result |
|---|---|
| `--version`, `--list-checks` | identical output (28 checks) |
| `--json` | same schema (`fe-xico-doctor/report` v2), same top-level keys, the same 32 findings with the same IDs, categories, severities and titles. The only text difference is the memory figure in `hardware.cpu_memory`, which changes between any two runs |
| `--text --redact` | identical apart from the snapshot duration |
| usage errors (`--deadline 2`, `--text --json`, unknown option) | exit 2 in both |
| exit status of a full scan | 0 in both |

CI then shows that the installed RPM behaves like this source tree. As an
unprivileged user it compares the same checks and the same findings
(`packaging/ci/check-installed.sh`), and runs the GUI smoke and self tests.
