# FE-Xico Doctor

**FE-Xico Doctor** is a system maintenance, diagnostics, and configuration utility designed for **FE-Xico**, a Fedora Atomic-based Linux desktop.

Doctor provides a simple graphical interface for checking system health, running maintenance tasks, viewing command output, troubleshooting common problems, and managing advanced system settings without hiding what is actually happening underneath.

The goal is simple:

> Make Linux system maintenance easier without taking control away from the user.

---

## Project Status

> **Early Development**

FE-Xico Doctor is currently being built from the ground up.

The first development milestone focuses on:

* KDE / Kirigami application shell
* System information dashboard
* Safe maintenance actions
* Live command output
* Basic diagnostics
* Action status and error reporting

Privileged system modification will be added later using proper authorization mechanisms rather than running the entire application as root.

---

# Features

## System Dashboard

Doctor will provide a lightweight overview of important system information such as:

* CPU usage
* Memory usage
* Disk usage
* GPU information
* System uptime
* Kernel version
* FE-Xico version
* Failed systemd services
* Update status

Doctor is not intended to replace a full system monitor.

Instead, the dashboard provides quick information useful for maintenance and troubleshooting.

---

## Quick Maintenance

Common maintenance tasks can be performed directly from Doctor.

Planned actions include:

* Check failed services
* Update FE-Xico
* Check for system updates
* Restart PipeWire
* Rebuild KDE caches
* Check disk health
* Remove unused packages
* Check system logs
* Refresh system services
* Run system diagnostics

Actions clearly show what they are doing before making significant system changes.

---

## Live Console

Doctor includes an integrated console output viewer.

Commands launched by Doctor can display their output in real time:

```text
$ systemctl --failed

UNIT LOAD ACTIVE SUB DESCRIPTION
...

Process exited with code 0
```

The console can be expanded or hidden depending on how much detail the user wants.

This allows Doctor to provide a simple interface without hiding the commands running underneath it.

---

# Advanced Configuration

Advanced settings are intended for users who want more control over FE-Xico.

Doctor will show:

* Current value
* Proposed value
* What the setting changes
* Command being executed
* Configuration file being modified
* Reset-to-default option

Example:

```text
CPU Performance Profile

Current:
balanced

New:
performance

Command:
powerprofilesctl set performance

[ Reset to Default ]    [ Apply ]
```

Advanced settings will include clear warnings where necessary.

If a user does not understand what an option changes, the safest choice is to leave it at its default value.

---

# Design Philosophy

FE-Xico Doctor follows five principles:

## Preview

Users should be able to see what an action will do before potentially destructive or privileged changes are made.

## Observe

Commands should expose their output instead of silently operating in the background.

## Undo

Settings should provide a reasonable way to return to their previous or default state whenever possible.

## Explain

Doctor should explain what a setting or action actually changes.

## Log

Actions should leave enough information behind to determine what happened if something goes wrong.

---

# Security Model

FE-Xico Doctor is designed to run as a **normal user application**.

The entire GUI should never need to run as root.

Normal operations are executed directly through the Doctor backend.

Privileged operations will eventually use **Polkit / KDE KAuth** so that only the specific operation requiring elevated permissions receives them.

Conceptually:

```text
FE-Xico Doctor
      │
      ├── QML / Kirigami Interface
      │
      └── Doctor Backend
             │
             ├── QProcess
             │     └── Normal commands
             │
             └── KAuth / Polkit
                   └── Privileged actions
```

Commands are passed as programs and argument lists whenever possible instead of constructing unrestricted shell commands.

---

# Custom Actions

Doctor is planned to support declarative custom actions.

System actions may eventually live in:

```text
/usr/share/fe-xico-doctor/actions.d/
```

User-created actions may live in:

```text
~/.config/fe-xico-doctor/actions.d/
```

An action could look similar to:

```yaml
name: Check Failed Services
id: check-failed-services
category: Diagnostics

requires_admin: false

command:
  - systemctl
  - --failed
```

This allows new Doctor functionality to be added without requiring a new GUI implementation for every command.

---

# Planned Interface

Doctor is planned around several major sections:

```text
Dashboard
├── System Health
├── CPU
├── Memory
├── Storage
├── GPU
└── Update Status

Maintenance
├── Updates
├── Package Cleanup
├── KDE Maintenance
├── Audio
└── Backups

Diagnostics
├── Failed Services
├── Disk Health
├── Networking
├── Logs
└── System Information

Performance
├── Power Profile
├── CPU
├── GPU
└── Gaming Settings

Advanced
├── Services
├── Kernel Parameters
├── System Configuration
├── Custom Actions
└── Console
```

---

# Technology

FE-Xico Doctor is being developed using:

* **C++**
* **Qt 6**
* **QML**
* **KDE Kirigami**
* **KDE Frameworks 6**
* **CMake**
* **systemd**
* **Polkit / KAuth** for future privileged operations

Doctor is designed primarily for KDE Plasma and FE-Xico.

---

# Building

FE-Xico Doctor is currently intended to be built on a Fedora-based development environment.

Recommended dependencies include:

```bash
sudo dnf5 install \
    @development-tools \
    cmake \
    extra-cmake-modules \
    kf6-kirigami-devel \
    kf6-ki18n-devel \
    kf6-kcoreaddons-devel \
    kf6-kiconthemes-devel \
    kf6-qqc2-desktop-style \
    qt6-qtbase-devel \
    qt6-qtdeclarative-devel
```

For Fedora Atomic systems, developing inside a Toolbox or Distrobox container is recommended instead of layering development packages onto the host.

Clone the repository:

```bash
git clone https://github.com/RoYoshi/FE-Xico-Doctor.git
cd FE-Xico-Doctor
```

Configure:

```bash
cmake -B build -S .
```

Build:

```bash
cmake --build build
```

Run:

```bash
./build/bin/fe-xico-doctor
```

Build instructions may change while the project is under active development.

---

# Project Structure

```text
FE-Xico-Doctor/
├── CMakeLists.txt
├── README.md
├── src/
│   ├── CMakeLists.txt
│   ├── main.cpp
│   ├── Main.qml
│   ├── doctorbackend.cpp
│   └── doctorbackend.h
├── icons/
├── data/
└── actions/
```

As development progresses, system integration files, Polkit rules, action definitions, translations, tests, and packaging files will be added.

---

# Roadmap

### v0.1

* Application shell
* Kirigami interface
* Basic dashboard
* Non-privileged actions
* Live console output
* Failed-service diagnostics

### v0.2

* CPU monitoring
* Memory monitoring
* Disk monitoring
* GPU information
* Result cards
* Action history
* Improved diagnostics

### v0.3

* Declarative action system
* Maintenance categories
* Update management
* System-health checks
* Configuration preview

### v0.4

* Polkit / KAuth integration
* Privileged maintenance actions
* Safe configuration editing
* Reset-to-default support

### v0.5

* Custom user actions
* Advanced settings
* Expert Mode
* Command preview
* Additional FE-Xico integration

### v1.0

* Stable FE-Xico integration
* System maintenance dashboard
* Diagnostics
* Update management
* Privileged actions
* Extensible action system
* FE-Xico image integration

---

# FE-Xico Integration

Doctor is being developed primarily for the FE-Xico operating system.

FE-Xico is a Fedora Atomic-based Linux desktop focused on:

* Reproducibility
* System transparency
* KDE Plasma
* Atomic updates
* Performance
* Privacy
* User control

Doctor acts as the graphical maintenance and diagnostics layer for that philosophy.

It should simplify the system without preventing advanced users from seeing or understanding what is happening.

---

# Contributions

FE-Xico Doctor is currently an experimental personal project, but suggestions, bug reports, testing, and contributions are welcome as the project develops.

When contributing system actions, prioritize:

* Safety
* Transparency
* Reversibility
* Minimal privileges
* Clear user-facing explanations

---

# License

A license has not yet been finalized.

Before accepting substantial external contributions or distributing stable releases, an open-source license will be selected and added to the repository.

---

**FE-Xico Doctor**

*Maintain the system. Understand the system.*
