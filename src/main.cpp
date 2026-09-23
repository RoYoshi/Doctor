#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "doctorbackend.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("fe-xico-doctor");
    QCoreApplication::setOrganizationName("FE-Xico");

    DoctorBackend backend;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(
        "DoctorBackend",
        &backend
    );

    engine.loadFromModule(
        "io.github.royoshi.fexicodoctor",
        "Main"
    );

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}