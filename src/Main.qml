import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow {
    id: root

    width: 1000
    height: 700

    title: "FE-Xico Doctor"

    property bool consoleVisible: false

    pageStack.initialPage: Kirigami.ScrollablePage {
        title: "FE-Xico Doctor"

        ColumnLayout {
            width: parent.width
            spacing: Kirigami.Units.largeSpacing

            Kirigami.Heading {
                text: "System Health"
                level: 1
            }

            Controls.Frame {
                Layout.fillWidth: true

                RowLayout {
                    anchors.fill: parent

                    ColumnLayout {
                        Controls.Label {
                            text: "CPU"
                            font.bold: true
                        }

                        Controls.Label {
                            text: "Coming soon"
                        }
                    }

                    ColumnLayout {
                        Controls.Label {
                            text: "Memory"
                            font.bold: true
                        }

                        Controls.Label {
                            text: "Coming soon"
                        }
                    }

                    ColumnLayout {
                        Controls.Label {
                            text: "Disk"
                            font.bold: true
                        }

                        Controls.Label {
                            text: "Coming soon"
                        }
                    }
                }
            }

            Kirigami.Heading {
                text: "Quick Maintenance"
                level: 1
            }

            RowLayout {
                Controls.Button {
                    text: "Check Failed Services"

                    onClicked: {
                        consoleText.text = ""

                        DoctorBackend.runCommand(
                            "systemctl",
                            ["--failed"]
                        )
                    }
                }

                Controls.Button {
                    text: root.consoleVisible
                        ? "Hide Console"
                        : "Show Console"

                    onClicked:
                        root.consoleVisible =
                            !root.consoleVisible
                }
            }

            Controls.Frame {
                Layout.fillWidth: true
                Layout.preferredHeight: 280

                visible: root.consoleVisible

                ColumnLayout {
                    anchors.fill: parent

                    Controls.Label {
                        text: "FE-Xico Doctor Console"
                        font.bold: true
                    }

                    Controls.ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Controls.TextArea {
                            id: consoleText

                            readOnly: true
                            wrapMode: TextEdit.WrapAnywhere

                            font.family: "monospace"
                        }
                    }
                }
            }

            Kirigami.Heading {
                text: "Advanced"
                level: 1
            }

            Controls.Label {
                Layout.fillWidth: true

                text:
                    "Advanced actions can directly modify system " +
                    "configuration. If you do not understand an " +
                    "option, leave it at its default value."

                wrapMode: Text.WordWrap
            }
        }
    }

    Connections {
        target: DoctorBackend

        function onCommandStarted(command) {
            consoleText.text +=
                "$ " + command + "\n\n"

            root.consoleVisible = true
        }

        function onConsoleOutput(text) {
            consoleText.text += text
        }

        function onCommandFinished(exitCode) {
            consoleText.text +=
                "\n\nProcess exited with code " +
                exitCode + "\n"
        }

        function onCommandError(error) {
            consoleText.text +=
                "\nERROR: " + error + "\n"
        }
    }
}