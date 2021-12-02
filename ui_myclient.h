/********************************************************************************
** Form generated from reading UI file 'myclient.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCLIENT_H
#define UI_MYCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyClient
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MyClient)
    {
        if (MyClient->objectName().isEmpty())
            MyClient->setObjectName(QString::fromUtf8("MyClient"));
        MyClient->resize(400, 300);
        menuBar = new QMenuBar(MyClient);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        MyClient->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MyClient);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MyClient->addToolBar(mainToolBar);
        centralWidget = new QWidget(MyClient);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MyClient->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MyClient);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MyClient->setStatusBar(statusBar);

        retranslateUi(MyClient);

        QMetaObject::connectSlotsByName(MyClient);
    } // setupUi

    void retranslateUi(QMainWindow *MyClient)
    {
        MyClient->setWindowTitle(QCoreApplication::translate("MyClient", "MyClient", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyClient: public Ui_MyClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCLIENT_H
