import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow {
    id: root
    width: 1060
    height: 760
    minimumWidth: 760
    minimumHeight: 560
    title: "FE-Xico Doctor"

    property bool consoleVisible: false

    pageStack.initialPage: Kirigami.ScrollablePage {
        title: "System Overview"

        ColumnLayout {
            width: parent.width
            spacing: Kirigami.Units.largeSpacing

            RowLayout {
                Layout.fillWidth: true

                ColumnLayout {
                    Layout.fillWidth: true
                    Kirigami.Heading {
                        text: "FE-Xico Doctor"
                        level: 1
                    }
                    Controls.Label {
                        text: "Maintain the system. Understand the system."
                        opacity: 0.8
                    }
                }

                Controls.Label {
                    text: "v0.1  ·  EARLY DRAFT"
                    color: Kirigami.Theme.highlightColor
                    font.bold: true
                }
            }

            Controls.Frame {
                Layout.fillWidth: true

                ColumnLayout {
                    anchors.fill: parent
                    spacing: Kirigami.Units.smallSpacing

                    Kirigami.Heading {
                        text: "This FE-XicoOS installation"
                        level: 2
                    }
                    Controls.Label {
                        Layout.fillWidth: true
                        text: DoctorBackend.osName
                        font.bold: true
                        wrapMode: Text.WordWrap
                    }
                    Controls.Label {
                        Layout.fillWidth: true
                        text: "FE-Xico version: " + DoctorBackend.feXicoVersion
                              + "    ·    Kernel: " + DoctorBackend.kernelText
                        wrapMode: Text.WordWrap
                    }
                    Controls.Label {
                        text: "Uptime: " + DoctorBackend.uptimeText
                        opacity: 0.8
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Kirigami.Heading {
                    Layout.fillWidth: true
                    text: "System Health"
                    level: 2
                }
                Controls.Button {
                    text: "Refresh"
                    icon.name: "view-refresh"
                    onClicked: DoctorBackend.refreshSystemInfo()
                }
            }

            GridLayout {
                Layout.fillWidth: true
                columns: 3
                columnSpacing: Kirigami.Units.largeSpacing
                rowSpacing: Kirigami.Units.largeSpacing

                Controls.Frame {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 160
                    ColumnLayout {
                        anchors.fill: parent
                        Controls.Label { text: "CPU"; font.bold: true }
                        Controls.Label {
                            Layout.fillWidth: true
                            text: DoctorBackend.cpuText
                            wrapMode: Text.WordWrap
                        }
                    }
                }
                Controls.Frame {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 160
                    ColumnLayout {
                        anchors.fill: parent
                        Controls.Label { text: "MEMORY"; font.bold: true }
                        Controls.Label {
                            Layout.fillWidth: true
                            text: DoctorBackend.memoryText
                            wrapMode: Text.WordWrap
                        }
                    }
                }
                Controls.Frame {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 160
                    ColumnLayout {
                        anchors.fill: parent
                        Controls.Label { text: "ROOT STORAGE"; font.bold: true }
                        Controls.Label {
                            Layout.fillWidth: true
                            text: DoctorBackend.diskText
                            wrapMode: Text.WordWrap
                        }
                    }
                }
            }

            Controls.Label {
                Layout.fillWidth: true
                text: "GPU: " + DoctorBackend.gpuText
                      + "    ·    Driver validation coming in v0.2"
                wrapMode: Text.WordWrap
            }

            Kirigami.Heading {
                text: "Quick Diagnostics"
                level: 2
            }

            Controls.Label {
                Layout.fillWidth: true
                text: "These checks are read-only. Doctor shows the exact command "
                      + "and its output in the console below."
                wrapMode: Text.WordWrap
                opacity: 0.8
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: Kirigami.Units.smallSpacing

                Controls.Button {
                    text: "Failed Services"
                    icon.name: "dialog-warning"
                    enabled: !DoctorBackend.busy
                    onClicked: DoctorBackend.runAction("failed-services")
                }
                Controls.Button {
                    text: "Bootc Deployment"
                    icon.name: "system-software-update"
                    enabled: !DoctorBackend.busy
                    onClicked: DoctorBackend.runAction("deployment")
                }
                Controls.Button {
                    text: "Installed Flatpaks"
                    icon.name: "applications-other"
                    enabled: !DoctorBackend.busy
                    onClicked: DoctorBackend.runAction("flatpaks")
                }
                Controls.BusyIndicator {
                    running: DoctorBackend.busy
                    visible: running
                    Layout.preferredWidth: Kirigami.Units.iconSizes.medium
                    Layout.preferredHeight: Kirigami.Units.iconSizes.medium
                }
                Controls.Button {
                    text: "Stop"
                    enabled: DoctorBackend.busy
                    onClicked: DoctorBackend.stopCommand()
                }
            }

            RowLayout {
                Layout.fillWidth: true
                Kirigami.Heading {
                    text: "Live Console"
                    level: 2
                    Layout.fillWidth: true
                }
                Controls.Button {
                    text: root.consoleVisible ? "Hide" : "Show"
                    onClicked: root.consoleVisible = !root.consoleVisible
                }
            }

            Controls.Frame {
                Layout.fillWidth: true
                Layout.preferredHeight: 250
                visible: root.consoleVisible

                ColumnLayout {
                    anchors.fill: parent
                    Controls.Label {
                        text: "Doctor executes only its listed diagnostics, never a shell."
                        opacity: 0.8
                    }
                    Controls.ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        Controls.TextArea {
                            id: consoleText
                            readOnly: true
                            wrapMode: TextEdit.WrapAnywhere
                            font.family: "monospace"
                            placeholderText: "Choose a diagnostic above to see its output."
                        }
                    }
                }
            }

            Kirigami.Heading {
                text: "Maintenance & Advanced"
                level: 2
            }
            Controls.Label {
                Layout.fillWidth: true
                text: "Coming later: repairs, power profiles, KDE maintenance, "
                      + "GPU controls and custom actions. FE-Xico Updater remains "
                      + "responsible for upgrades and rollbacks."
                wrapMode: Text.WordWrap
                opacity: 0.8
            }
        }
    }

    Connections {
        target: DoctorBackend

        function onCommandStarted(command) {
            consoleText.text = "$ " + command + "\n\n"
            root.consoleVisible = true
        }
        function onConsoleOutput(text) {
            // Bound in-memory console growth from unexpectedly chatty commands.
            consoleText.text = (consoleText.text + text).slice(-100000)
        }
        function onCommandFinished(exitCode) {
            consoleText.text += "\nProcess exited with code " + exitCode + "\n"
        }
        function onCommandError(error) {
            consoleText.text += "\nERROR: " + error + "\n"
            root.consoleVisible = true
        }
    }
}
