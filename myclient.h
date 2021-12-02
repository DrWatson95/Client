#pragma once

#include <QtWidgets>
#include <QTextEdit>
#include <QTcpSocket>
#include <QTcpServer>



class MyClient : public QWidget
{
    Q_OBJECT


private:
    QTcpSocket* m_pTcpSocket;
    QTextEdit* m_ptxtinfo;
    QLineEdit* m_ptxtinput;
    quint16 m_nNextBlockSize;
public:
    MyClient(const QString& strHost, int nPort, QWidget* pwgt = 0);
private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotSendToServer();
    void slotConnected();
};

