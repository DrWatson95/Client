#include "myclient.h"
#include "ui_myclient.h"

MyClient::MyClient(const QString& strHost,
                   int nPort,
                   QWidget* pwgt /*=О*/):
                   QWidget(pwgt)
                 , m_nNextBlockSize(0)
{
    connect(&ui_Auth, SIGNAL(login_button_clicked()),                                   //соединение сигнала кнопки авторизации экземпляра окна авторизации
            this, SLOT(sendAuthInfo()));                                               //со слотом-обработчиком авторизации
    connect(&ui_Auth,SIGNAL(destroyed()),                                               //соединение сигнала уничтожения экземпляра окна авторизации
            this, SLOT(show()));                                                        //с методом отображения главного окна
    connect(&ui_Auth,SIGNAL(register_button_clicked()),                                 //соединение сигнала кнопки регистрации экземпляра окна авторизации
            this,SLOT(registerWindowShow()));                                           //со слотом вызывающим окно регистрации
    connect(&ui_Reg,SIGNAL(register_button_clicked2()),                                 //соединение кнопки регистрации экземпляра окна авторизации
            this,SLOT(sendRegInfo()));                                                 //со слотом-обработчиком регистраци
    connect(&ui_Reg,SIGNAL(destroyed()),
            &ui_Auth, SLOT(show()));
    setIpAddress();
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead() ), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT (slotError (QAbstractSocket: :SocketError))) ;
    m_ptxtinfo = new QTextEdit;
    m_ptxtinput = new QLineEdit;
    m_ptxtinfo->setReadOnly(true);
    QPushButton* pcmd = new QPushButton("&Send");
    connect(pcmd, SIGNAL(clicked() ), SLOT(sendUsefulMessage() ));
    connect(m_ptxtinput, SIGNAL(returnPressed()), this, SLOT ( sendUsefulMessage () )) ;
    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));
    pvbxLayout->addWidget(m_ptxtinfo);
    pvbxLayout->addWidget(m_ptxtinput);
    pvbxLayout->addWidget(pcmd);
    setLayout(pvbxLayout);
}

void MyClient::setIpAddress()
{
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    myIpAddress = list[2].toString();
}

void MyClient::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    quint8 id;
    in >> id;
    switch (id) {
    case static_cast<quint8>(MessageID::Authorization):{
        //in.device()->seek(1);
        quint8 b;
        in >> b;
        if(b){
            ui_Auth.close();
            ui_Reg.close();
            this->show();
        }else{
            ui_Auth.setText("NOT FOUND");
        }
        qDebug() << "0";
        break;
    }
    case static_cast<quint8>(MessageID::Registration):{
        //in.device()->seek(1);
        quint8 b;
        in >> b;
        if(b){
            ui_Reg.hide();
            ui_Auth.show();
        }else{
            ui_Reg.setIsSuccessReg();
        }
        qDebug() << "1";
        break;
    }
    case static_cast<quint8>(MessageID::UsefulExchange):{
        QString text;
        QString text2;
        in >> text >> text2;
        m_ptxtinfo->append(text + ": " + text2);
        qDebug() << "2";
        break;
    }
    case static_cast<quint8>(MessageID::CheckConnected):{
        quint8 b;
        in >> b;
        if(b){
            qDebug() << "hereee";
            ui_Auth.setText("CONNECTED");
        }
        //this->show();
        qDebug() << "3";
        break;
    }
    default:
            break;
    }
}
//    QDataStream in(m_pTcpSocket);
//    //in.setVersion(QDataStream::Qt_5_3);
//        QTime time;
//        QString str;
//        in >> time >> str;
//        m_ptxtinfo->append(time.toString() +" "+ str);
//        m_nNextBlockSize = 0;
//    }




void MyClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Error: "+ (err == QAbstractSocket::HostNotFoundError?
                            "The host was not found." :
                            err == QAbstractSocket::RemoteHostClosedError?
                                "The remote host is closed." :
                                err == QAbstractSocket::ConnectionRefusedError?
                                    "The connection was refused." :
                                    QString(m_pTcpSocket->errorString())
                                    );
    m_ptxtinfo->append(strError);

}

void MyClient::SendToServer(QByteArray *data, MessageID id)
{
    QByteArray arrBlock;
    arrBlock.append(( (quint8)id));
    arrBlock.append(*data);
    m_pTcpSocket->write(arrBlock);
    //m_ptxtinput->setText("");

}

void MyClient::slotConnected()
{
    m_ptxtinfo->append("Received the connected() signal");
}

void MyClient::sendAuthInfo()
{
    m_username = ui_Auth.getLogin();
    m_userpass = ui_Auth.getPass();
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out << m_username << m_userpass;
    SendToServer(&arrBlock,MessageID::Authorization);
}

void MyClient::sendRegInfo()
{
    if(ui_Reg.checkPass()){
        m_username = ui_Reg.getName();
        m_userpass = ui_Reg.getPass();
        QByteArray arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_2);
        out << m_username << m_userpass;
        SendToServer(&arrBlock,MessageID::Registration);
    }
    else{
        qDebug() << "Confirm password coorectly";
    }
}

void MyClient::sendUsefulMessage()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out << m_ptxtinput->text();
    m_ptxtinput->clear();
    SendToServer(&arrBlock,MessageID::UsefulExchange);
}

void MyClient::registerWindowShow()
{
    ui_Auth.hide();
    ui_Reg.show();
}

void MyClient::display()                                                              //реализация пользотвальского метода отображения главного окна
{

    ui_Auth.show();                                                                     //отобразить окно авторизации(НЕ главное окно)
}
