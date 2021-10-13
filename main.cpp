#include <QApplication>
#include <QQuickView>
#include <QQmlError>
#include <QtDebug>
#include <QQmlApplicationEngine>
//#include "fieldmodel.h"
#include "sessionmodel.h"
//#include "cell.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine *engine = new QQmlApplicationEngine;

//    QQmlComponent *pComponent = new QQmlComponent;
//    qmlRegisterType<Cell>("cellItem", 1, 0, "CellItem");
    SessionModel *pSessionModel = new SessionModel(engine);
    engine->rootContext()->setContextProperty("sessionModel", QVariant::fromValue(pSessionModel));

    engine->load(QUrl(QStringLiteral("qrc:/qml/window.qml")));

    return app.exec();
}

