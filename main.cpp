#include <QApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>
#include "sessionmodel.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine *engine = new QQmlApplicationEngine;

    SessionModel *pSessionModel = new SessionModel;
    engine->rootContext()->setContextProperty("sessionModel", QVariant::fromValue(pSessionModel));

    engine->load(QUrl(QStringLiteral("qrc:/qml/window.qml")));

    return app.exec();
}

