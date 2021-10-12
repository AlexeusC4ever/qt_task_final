#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlError>
#include <QtDebug>
#include <QQuickView>
#include <QQmlError>
#include <QtDebug>
#include <QQmlApplicationEngine>
#include "fieldmodel.h"
#include "sessionmodel.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QGuiApplication app(argc, argv);
//    qmlRegisterType<Cell>("cellItem", 1, 0, "CellItem");
    qmlRegisterType<FieldModel>("fieldModel", 1, 0, "FieldModel");
    qmlRegisterType<SessionModel>("sessionModel", 1, 0, "SessionModel");
//    QQmlApplicationEngine view(QUrl(QStringLiteral("qrc:/window.qml")));
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/window.qml")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

