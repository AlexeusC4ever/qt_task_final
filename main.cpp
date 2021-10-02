#include <QGuiApplication>
#include <QQuickView>
#include <QQmlError>
#include <QtDebug>
#include <QQmlApplicationEngine>
#include "fieldmodel.h"
#include "sessionmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

//    qmlRegisterType<Cell>("cellItem", 1, 0, "CellItem");
    qmlRegisterType<FieldModel>("fieldModel", 1, 0, "FieldModel");
    qmlRegisterType<SessionModel>("sessionModel", 1, 0, "SessionModel");
    QQmlApplicationEngine view(QUrl(QStringLiteral("qrc:/window.qml")));

//    QList <QQmlError> errors = view.errors();

//    foreach (const QQmlError &rcError, errors)
//       qDebug() << rcError.toString();


    return app.exec();
}
