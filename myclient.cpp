#include "myclient.h"
#include "ui_myclient.h"


MyClient::MyClient(const QString& strHost,
                   int nPort,
                   QWidget* pwgt /*=О*/):
                   QWidget(pwgt),
                   m_nNextBlockSize(0),
                   hostAddress(strHost),
                   hostPort(nPort)
{
    connect(&ui_Auth, &auth_window::sgnClose, this, &MyClient::slotForCloseSignal);
    timer = new QTimer();
    timer->start(100);
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(hostAddress, hostPort);
    connect(timer, &QTimer::timeout, this, &MyClient::onTimeout);
    connect(&ui_Auth, SIGNAL(login_button_clicked()),this, SLOT(sendAuthInfo()));
    //connect(&ui_Auth,SIGNAL(destroyed()), this, SLOT(show()));
    connect(&ui_Auth,SIGNAL(register_button_clicked()), this, SLOT(registerWindowShow()));
    connect(&ui_Reg,SIGNAL(register_button_clicked2()),this,SLOT(sendRegInfo()));
    connect(&ui_Reg,SIGNAL(returnPressed()), this, SLOT(sendUsefulMessage()));
    //connect(&ui_Reg,SIGNAL(destroyed()),&ui_Auth, SLOT(show()));
    setIpAddress();
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead() ), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(slotError(QAbstractSocket::SocketError))) ;
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
        case MessageID::Authorization:
        {
            quint8 isAuthorization;
            in >> isAuthorization;
            if(isAuthorization){
                ui_Auth.close();
                ui_Reg.close();
                this->show();
            }else{
                ui_Auth.setTextOnlabelError("USER NOT FOUND");
            }
            qDebug() << "Authorization";
            break;
        }
        case MessageID::Registration:
        {
            quint8 isRegistration;
            in >> isRegistration;
            if(isRegistration){
                ui_Reg.hide();
                ui_Auth.show();
                ui_Auth.setTextOnlabelError("");
            }else{
                ui_Reg.setIsSuccessReg(isRegistration);
            }
            qDebug() << "Registration";
            break;
        }
        case MessageID::UsefulExchange:
        {
            QString text;
            in >> text;
            m_ptxtinfo->append(text);
            qDebug() << "UsefulExchange";
            break;
        }
        case MessageID::CheckConnected:
        {
            quint8 isConnected;
            in >> isConnected;
//            if(isConnected)
//                ui_Auth.setText("CONNECTED");
//            else
//                ui_Auth.setText("NO CONNECTION");
            qDebug() << "CheckConnected";
            break;
        }
        default:
        {
            qDebug() << "default: Unknown Message";
            break;
        }
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
        out << m_username << m_userpass;
        SendToServer(&arrBlock,MessageID::Registration);

    }
    else{
        qDebug() << "Enter coorectly password";
    }
}

void MyClient::sendUsefulMessage()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    QString allMessage = m_username + QString(": ") + m_ptxtinput->text().toUtf8();
    if(m_ptxtinput->text() != ""){
       out << allMessage;
       m_ptxtinput->clear();
       SendToServer(&arrBlock,MessageID::UsefulExchange);
    }
}

void MyClient::onTimeout()
{
    if(m_pTcpSocket->state() != QAbstractSocket::SocketState::ConnectedState){
        if(ui_Auth.isVisible()){
            ui_Auth.setEnableRegisterButton(false);
            ui_Auth.setEnableLoginButton(false);
            ui_Auth.setTextOnLabelConnected("NO CONNECTION");
            ui_Auth.getLabelConnected()->setStyleSheet("QLabel { background-color : red; color : black; border-radius: 13px;}");
        }else if(ui_Reg.isVisible()){
            ui_Reg.setTextOnLabelConnected("NO CONNECTION");
            ui_Reg.setEnableRegisterButton(false);
        }else if(this->isVisible()){
            this->hide();
            ui_Auth.show();
            ui_Auth.setTextOnLabelConnected("NO CONNECTION");
        }
        m_pTcpSocket->connectToHost(hostAddress, hostPort);
    }else if(m_pTcpSocket->state() == QAbstractSocket::SocketState::ConnectedState){
        if(ui_Auth.isVisible()){
            ui_Auth.setEnableRegisterButton(true);
            ui_Auth.setEnableLoginButton(true);
            ui_Auth.setTextOnLabelConnected("CONNECTED");
            ui_Auth.getLabelConnected()->setStyleSheet("QLabel { background-color : green; color : black; border-radius: 13px;}");
        }else if(ui_Reg.isVisible()){
            ui_Reg.setTextOnLabelConnected("CONNECTED");
            ui_Reg.setEnableRegisterButton(true);
        }
    }
}

void MyClient::slotForCloseSignal(bool val1)
{
    //this->show();
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
