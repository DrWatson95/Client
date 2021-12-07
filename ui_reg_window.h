/********************************************************************************
** Form generated from reading UI file 'reg_window.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REG_WINDOW_H
#define UI_REG_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_reg_window
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label_Confirm;
    QLineEdit *passwordLineEdit;
    QPushButton *registerPushButton;
    QLabel *label_Name;
    QLineEdit *nameLineEdit;
    QLabel *labelWelcome;
    QLabel *label_Pass;
    QLineEdit *confirmLineEdit;

    void setupUi(QWidget *reg_window)
    {
        if (reg_window->objectName().isEmpty())
            reg_window->setObjectName(QString::fromUtf8("reg_window"));
        reg_window->resize(382, 174);
        horizontalLayout = new QHBoxLayout(reg_window);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_Confirm = new QLabel(reg_window);
        label_Confirm->setObjectName(QString::fromUtf8("label_Confirm"));
        QFont font;
        font.setPointSize(12);
        label_Confirm->setFont(font);
        label_Confirm->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_Confirm, 4, 0, 1, 1);

        passwordLineEdit = new QLineEdit(reg_window);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));

        gridLayout->addWidget(passwordLineEdit, 3, 1, 1, 1);

        registerPushButton = new QPushButton(reg_window);
        registerPushButton->setObjectName(QString::fromUtf8("registerPushButton"));

        gridLayout->addWidget(registerPushButton, 5, 1, 1, 1);

        label_Name = new QLabel(reg_window);
        label_Name->setObjectName(QString::fromUtf8("label_Name"));
        label_Name->setFont(font);
        label_Name->setMidLineWidth(0);
        label_Name->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_Name, 2, 0, 1, 1);

        nameLineEdit = new QLineEdit(reg_window);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        gridLayout->addWidget(nameLineEdit, 2, 1, 1, 1);

        labelWelcome = new QLabel(reg_window);
        labelWelcome->setObjectName(QString::fromUtf8("labelWelcome"));
        labelWelcome->setFont(font);
        labelWelcome->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(labelWelcome, 1, 1, 1, 1);

        label_Pass = new QLabel(reg_window);
        label_Pass->setObjectName(QString::fromUtf8("label_Pass"));
        label_Pass->setFont(font);
        label_Pass->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_Pass, 3, 0, 1, 1);

        confirmLineEdit = new QLineEdit(reg_window);
        confirmLineEdit->setObjectName(QString::fromUtf8("confirmLineEdit"));

        gridLayout->addWidget(confirmLineEdit, 4, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(reg_window);

        QMetaObject::connectSlotsByName(reg_window);
    } // setupUi

    void retranslateUi(QWidget *reg_window)
    {
        reg_window->setWindowTitle(QCoreApplication::translate("reg_window", "Form", nullptr));
        label_Confirm->setText(QCoreApplication::translate("reg_window", "confirm", nullptr));
        registerPushButton->setText(QCoreApplication::translate("reg_window", "Register", nullptr));
        label_Name->setText(QCoreApplication::translate("reg_window", "name", nullptr));
        labelWelcome->setText(QCoreApplication::translate("reg_window", "authentificate yourself", nullptr));
        label_Pass->setText(QCoreApplication::translate("reg_window", "password", nullptr));
    } // retranslateUi

};

namespace Ui {
    class reg_window: public Ui_reg_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REG_WINDOW_H
