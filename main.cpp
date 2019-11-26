#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include "blocks_data_model.h"
#include <words_data_model.h>
#include "client.h"
#include "settings.h"
#include "localfilesdatamodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    qmlRegisterType<Blocks_data_model>("Blocks_data_model_qml", 1, 0, "Blocks_data_model");
    qmlRegisterType<Words_data_model>("Words_data_model_qml", 1, 0, "Words_data_model");
    qmlRegisterType<Client>("Client_qml", 1, 0, "Client");
    qmlRegisterType<Settings>("Settings_qml", 1, 0, "Settings");
    qmlRegisterType<LocalFilesDataModel>("LocalFilesDataModel_qml", 1, 0, "LocalFilesDataModel");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
