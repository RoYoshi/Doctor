"""Dependency-free checks for the first Doctor GUI draft."""

from pathlib import Path
import unittest


ROOT = Path(__file__).resolve().parents[1]
HEADER = (ROOT / "src/doctorbackend.h").read_text()
BACKEND = (ROOT / "src/doctorbackend.cpp").read_text()
UI = (ROOT / "src/Main.qml").read_text()
DESKTOP = (ROOT / "io.github.royoshi.fexicodoctor.desktop").read_text()
CMAKE = (ROOT / "CMakeLists.txt").read_text()


class DoctorDraftTests(unittest.TestCase):
    def test_diagnostics_are_explicitly_allowlisted(self):
        self.assertIn("runAction(const QString &actionId)", HEADER)
        for name in ("failed-services", "deployment", "flatpaks"):
            self.assertIn(f'"{name}"', BACKEND)
            self.assertIn(f'DoctorBackend.runAction("{name}")', UI)
        self.assertNotIn("runCommand(", HEADER)
        self.assertNotIn("runCommand(", UI)
        self.assertNotIn("/bin/sh", BACKEND)
        self.assertNotIn("/bin/bash", BACKEND)
        self.assertNotIn("pkexec", BACKEND)
        self.assertNotIn("sudo", BACKEND)

    def test_health_dashboard_has_live_properties(self):
        for property_name in (
            "osName", "feXicoVersion", "kernelText", "cpuText",
            "memoryText", "diskText", "uptimeText", "gpuText",
        ):
            self.assertIn(f"Q_PROPERTY(QString {property_name} ", HEADER)
            self.assertIn(f"DoctorBackend.{property_name}", UI)
        self.assertIn("m_timeout.setInterval(15000)", BACKEND)

    def test_desktop_launcher_and_owner_icon(self):
        self.assertIn("Type=Application", DESKTOP)
        self.assertIn("Exec=fe-xico-doctor", DESKTOP)
        self.assertIn("Icon=io.github.royoshi.fexicodoctor", DESKTOP)
        self.assertIn("FILES io.github.royoshi.fexicodoctor.desktop", CMAKE)
        self.assertIn("FILES icons/io.github.royoshi.fexicodoctor.svg", CMAKE)


if __name__ == "__main__":
    unittest.main()
