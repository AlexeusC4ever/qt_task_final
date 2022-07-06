/********************************************************************************
** Form generated from reading UI file 'server-dlg.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_2D_DLG_H
#define UI_SERVER_2D_DLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ServerDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label_3;
    QPlainTextEdit *m_pTextEditChat;
    QPlainTextEdit *m_pTextEditErrors;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_pButtonClose;

    void setupUi(QDialog *ServerDialog)
    {
        if (ServerDialog->objectName().isEmpty())
            ServerDialog->setObjectName(QString::fromUtf8("ServerDialog"));
        ServerDialog->resize(330, 392);
        verticalLayout_2 = new QVBoxLayout(ServerDialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_3 = new QLabel(ServerDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_3);


        verticalLayout->addLayout(formLayout);

        m_pTextEditChat = new QPlainTextEdit(ServerDialog);
        m_pTextEditChat->setObjectName(QString::fromUtf8("m_pTextEditChat"));
        m_pTextEditChat->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(m_pTextEditChat->sizePolicy().hasHeightForWidth());
        m_pTextEditChat->setSizePolicy(sizePolicy);
        m_pTextEditChat->setReadOnly(true);

        verticalLayout->addWidget(m_pTextEditChat);

        m_pTextEditErrors = new QPlainTextEdit(ServerDialog);
        m_pTextEditErrors->setObjectName(QString::fromUtf8("m_pTextEditErrors"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_pTextEditErrors->sizePolicy().hasHeightForWidth());
        m_pTextEditErrors->setSizePolicy(sizePolicy1);
        m_pTextEditErrors->setMaximumSize(QSize(16777215, 30));
        m_pTextEditErrors->setReadOnly(true);

        verticalLayout->addWidget(m_pTextEditErrors);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(30, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_pButtonClose = new QPushButton(ServerDialog);
        m_pButtonClose->setObjectName(QString::fromUtf8("m_pButtonClose"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_pButtonClose->sizePolicy().hasHeightForWidth());
        m_pButtonClose->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(m_pButtonClose);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(ServerDialog);

        QMetaObject::connectSlotsByName(ServerDialog);
    } // setupUi

    void retranslateUi(QDialog *ServerDialog)
    {
        ServerDialog->setWindowTitle(QCoreApplication::translate("ServerDialog", "Server", nullptr));
        label_3->setText(QCoreApplication::translate("ServerDialog", "History:", nullptr));
        m_pButtonClose->setText(QCoreApplication::translate("ServerDialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ServerDialog: public Ui_ServerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_2D_DLG_H
