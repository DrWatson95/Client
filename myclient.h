#pragma once

#include <QTextEdit>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QTime>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QNetworkInterface>
#include "auth_window.h"
#include "reg_window.h"
#include "globalcommonheader.h"



class MyClient : public QWidget
{
    Q_OBJECT

private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit* m_ptxtinfo;
    QLineEdit* m_ptxtinput;
    quint16 m_nNextBlockSize;
    QString myIpAddress;
    auth_window ui_Auth;                                            //композит - экземпляр класса Auth_Window
    reg_window ui_Reg;
    QString m_username;
    QString m_userpass;
    void SendToServer(QByteArray *data, MessageID id);
public:
    MyClient(const QString& strHost, int nPort, QWidget* pwgt = 0);
    void setIpAddress();
    void display();
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotConnected();
    void sendAuthInfo();
    void sendRegInfo();
    void registerWindowShow();
    void sendUsefulMessage();
    //void registerUser();
};

