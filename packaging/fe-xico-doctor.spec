# FE-Xico Doctor: read-only system-health diagnostics (Python 3 + PySide6).
# Built from a source tarball of this repository (packaging/build-rpm.sh).
# Version comes from the VERSION file; packaging/build-rpm.sh checks they agree.

Name:           fe-xico-doctor
Version:        1.0.0
Release:        1%{?dist}
Summary:        Read-only system health diagnostics for FE-XicoOS

License:        Apache-2.0
URL:            https://github.com/RoYoshi/Doctor
Source0:        %{name}-%{version}.tar.gz

BuildArch:      noarch

BuildRequires:  python3-devel
BuildRequires:  desktop-file-utils

# Runtime: the Python standard library and Fedora's PySide6 (Qt Widgets GUI).
# Every diagnostic command (bootc, systemctl, journalctl, rpm, flatpak, lspci,
# nvidia-smi, ...) is optional: a missing tool is reported as Unknown.
Requires:       python3
Requires:       python3-pyside6
Requires:       hicolor-icon-theme
# The shipped bytecode is for this Fedora release's Python.
Requires:       python(abi) = %{python3_version}

%description
FE-Xico Doctor checks bootc deployments, updates, services, SELinux, graphics
drivers, controllers, storage, Flatpaks, network and logs, and explains what
it finds. It is strictly read-only: it never needs root, never changes the
system and never makes network requests. It has a desktop window and a
command-line interface with text, JSON (schema v2) and redacted reports.

%prep
%autosetup -n %{name}-%{version}

%build
# Pure Python: nothing to compile here (bytecode is generated in %%install).

%install
install -Dpm 0755 bin/fe-xico-doctor %{buildroot}%{_bindir}/fe-xico-doctor
install -d %{buildroot}%{_prefix}/lib/fe-xicoos
cp -pr fexico_doctor %{buildroot}%{_prefix}/lib/fe-xicoos/
find %{buildroot}%{_prefix}/lib/fe-xicoos/fexico_doctor -type d -exec chmod 0755 {} +
find %{buildroot}%{_prefix}/lib/fe-xicoos/fexico_doctor -type f -exec chmod 0644 {} +
# /usr is read-only on FE-XicoOS; ship the bytecode.
%py_byte_compile %{python3} %{buildroot}%{_prefix}/lib/fe-xicoos/fexico_doctor
install -Dpm 0644 data/io.github.royoshi.fexicodoctor.desktop \
    %{buildroot}%{_datadir}/applications/io.github.royoshi.fexicodoctor.desktop
install -Dpm 0644 data/fe-xico-doctor-report.schema.json \
    %{buildroot}%{_datadir}/fe-xicoos/fe-xico-doctor-report.schema.json
for size in 16 22 24 32 48 64 128 256 512; do
    install -Dpm 0644 data/icons/hicolor/${size}x${size}/apps/io.github.royoshi.fexicodoctor.png \
        %{buildroot}%{_datadir}/icons/hicolor/${size}x${size}/apps/io.github.royoshi.fexicodoctor.png
done

%check
desktop-file-validate %{buildroot}%{_datadir}/applications/io.github.royoshi.fexicodoctor.desktop
%{python3} -c 'import json, sys; json.load(open(sys.argv[1]))' \
    %{buildroot}%{_datadir}/fe-xicoos/fe-xico-doctor-report.schema.json
# Source-tree tests (probe fixtures, runner, report, view model, safety audit).
# GUI tests skip here when PySide6 is absent from the build root; CI runs them
# against the installed package.
PYTHONDONTWRITEBYTECODE=1 %{python3} -m unittest discover -s tests

%files
%license LICENSE
%doc README.md docs/FE_XICO_DOCTOR.md
%{_bindir}/fe-xico-doctor
# Shared with other FE-XicoOS files; Doctor owns only its package below.
%dir %{_prefix}/lib/fe-xicoos
%{_prefix}/lib/fe-xicoos/fexico_doctor/
%{_datadir}/applications/io.github.royoshi.fexicodoctor.desktop
%dir %{_datadir}/fe-xicoos
%{_datadir}/fe-xicoos/fe-xico-doctor-report.schema.json
%{_datadir}/icons/hicolor/*/apps/io.github.royoshi.fexicodoctor.png

%changelog
* Thu Nov 05 2026 RoYo <99851152+RoYoshi@users.noreply.github.com> - 1.0.0-1
- First standalone package. Same application as FE-XicoOS commit 2c2d24e
  (system_files/usr/lib/fe-xicoos/fexico_doctor), now developed here.
