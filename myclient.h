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



class MyClient : public QWidget
{
    Q_OBJECT


private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit* m_ptxtinfo;
    QLineEdit* m_ptxtinput;
    quint16 m_nNextBlockSize;
    QString myIpAddress;
public:
    MyClient(const QString& strHost, int nPort, QWidget* pwgt = 0);
    void setIpAddress();
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotSendToServer();
    void slotConnected();
};

