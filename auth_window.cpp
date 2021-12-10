#include "auth_window.h"
#include "ui_auth_window.h"

auth_window::auth_window(QWidget *parent) :                                 //реализация конструктора
    QWidget(parent),                                                        //список инициализации
    ui(new Ui::auth_window)
{
    ui->setupUi(this);                                                      //вызов функции размещения GUI
    ui->lineEdit_2->setEchoMode(QLineEdit::EchoMode::Password);
}

auth_window::~auth_window()                                                 //реализация деструктора
{
    delete ui;                                                              //удалить указатель на экземпляр класса(уничтожить GUI)
}

void auth_window::on_registerPushButton_2_clicked()                         //реализация слота нажатия кнопки регистрации
{
    emit register_button_clicked();
}

void auth_window::on_loginPushButton_clicked()                              //реализация слота нажатия кнопки авторизации
{
    emit login_button_clicked();
}

void auth_window::on_lineEdit_textEdited(const QString &arg1)
{
    auth_window::m_username = arg1;
}

void auth_window::on_lineEdit_2_textEdited(const QString &arg1)
{
    auth_window::m_userpass = arg1;
}

QString auth_window::getLogin()
{
    return auth_window::m_username;
}

QString auth_window::getPass()
{
    return auth_window::m_userpass;
}
void auth_window::setTextOnlabelError(QString str)
{
    ui->labelError->setText(str);
}

void auth_window::setTextOnLabelConnected(QString text)
{
    ui->labelConnected->setText(text);
}

void auth_window::setEnableRegisterButton(bool b)
{
    ui->registerPushButton_2->setEnabled(b);
}

void auth_window::setEnableLoginButton(bool b)
{
    ui->loginPushButton->setEnabled(b);
}

void auth_window::closeEvent(QCloseEvent* event)
{
    emit sgnClose(true);
    event->accept();
}

QLabel* auth_window::getLabelConnected()
{
    return ui->labelConnected;
}



void auth_window::on_lineEdit_returnPressed()
{
    int nKey = Qt::Key_Tab;
    QKeyEvent* tab = new QKeyEvent(QEvent::KeyPress, nKey, Qt::NoModifier);
    QApplication::sendEvent(this, tab);
}


void auth_window::on_lineEdit_2_returnPressed()
{
    emit login_button_clicked();
}
