#include "assist.h"

Assist::Assist()
{

}

void Assist::setUrlWebSocket(QString strUrl)
{
    qDebug()<<__FUNCTION__;
    mUrlWebSocket = strUrl;
}

void Assist::openWebSocket()
{
    qDebug()<<__FUNCTION__;
    connect(&mWebSocket, &QWebSocket::connected, this, &Assist::onConnected);
    connect(&mWebSocket, &QWebSocket::disconnected, this, &Assist::onDisconnected);
    //connect(&mWebSocket, &QWebSocket::bytesWritten, this, &Assist::onWebSocketBytesWritten);
    //connect(&mWebSocket, &QWebSocket::aboutToClose, this, &Assist::onAboutToClose);
    connect(&mWebSocket, &QWebSocket::textMessageReceived, this, &Assist::onTextMessageReceived);
    connect(&mWebSocket, &QWebSocket::binaryMessageReceived, this, &Assist::onBinaryReceived);
    connect(&mWebSocket, &QWebSocket::pong, this, &Assist::onPong);
    connect(&mWebSocket, &QWebSocket::stateChanged, this, &Assist::onStateChanged);
    //connect(&mWebSocket, &QWebSocket::error, this, &Assist::onMyWebSocketError);
    connect(&mWebSocket, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error), this, &Assist::onMyWebSocketError);

    mWebSocket.open(mUrlWebSocket);
}

void Assist::onConnected()
{
    qDebug()<<__FUNCTION__;
    QString strHeartBeat("heartbeat sent by mytest3 Assist");
    qDebug()<<"    going to send size:"<<strHeartBeat.toUtf8().size();
    qDebug()<<"    content:"<<strHeartBeat.toUtf8();
    mWebSocket.sendTextMessage(strHeartBeat.toUtf8());
}

void Assist::onDisconnected()
{
    qDebug()<<__FUNCTION__;
}

void Assist::onTextMessageReceived(const QString & message)
{
    qDebug()<<__FUNCTION__<< "Message received:" << message;
    mWebSocket.close();
}

void Assist::onMyWebSocketError(QAbstractSocket::SocketError error)
{
    qDebug()<<__FUNCTION__<<error;
    qDebug()<<__FUNCTION__<<mWebSocket.errorString();
}

void Assist::onWebSocketBytesWritten(qint64 bytes)
{
    qDebug()<<__FUNCTION__<<bytes;
}

void Assist::onAboutToClose()
{
    qDebug()<<__FUNCTION__;
}

void Assist::onBinaryReceived(const QByteArray & message)
{
    qDebug()<<__FUNCTION__<<message.length();
}

void Assist::onPong(quint64 elapsedTime, const QByteArray & payload)
{
    qDebug()<<__FUNCTION__<<elapsedTime<<payload.size();
}

void Assist::onStateChanged(QAbstractSocket::SocketState state)
{
    qDebug()<<__FUNCTION__<<state;
}

void Assist::setUrlHttpRequest(QString strUrl)
{
    qDebug()<<__FUNCTION__;
    mUrlHttpRequest = strUrl;
}

void Assist::openHttpRequest()
{
    mHttpManager = new QNetworkAccessManager(this);
    connect(mHttpManager, &QNetworkAccessManager::finished,this, &Assist::onHttpReplyFinished);
}

void Assist::doRequestGetStatus()
{
    qDebug()<<__FUNCTION__;
    mHttpRequest.setUrl(QUrl(mUrlHttpRequest+"/get_status?sync_connect"));
    mHttpRequest.setRawHeader("User-Agent", "MyOwnBrowser 1.0");

    mHttpReply = mHttpManager->get(mHttpRequest);
    connect(mHttpReply, &QNetworkReply::readyRead, this, &Assist::onHttpReplyReadyRead);
    connect(mHttpReply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &Assist::onHttpReplyError);
    connect(mHttpReply, &QNetworkReply::sslErrors,this, &Assist::onHttpSslReplyError);
    qDebug()<<"    "<<mHttpReply->url();
}

void Assist::onHttpReplyFinished(QNetworkReply * reply)
{
    qDebug()<<__FUNCTION__<<reply;
    qDebug()<<"    "<<reply->url();
    QByteArray theContents = reply->readAll();
    qDebug()<<"    size:"<<theContents.size();
    qDebug()<<"    data:"<<theContents;
    emit dataReady(theContents);
    reply->deleteLater();
}

void Assist::onHttpReplyReadyRead()
{
    qDebug()<<__FUNCTION__;
    qDebug()<<"    "<<mHttpReply->url();
}

void Assist::onHttpReplyError(QNetworkReply::NetworkError code)
{
    qDebug()<<__FUNCTION__<<code<<mHttpReply->errorString();
    qDebug()<<"    "<<mHttpReply->url();
}

void Assist::onHttpSslReplyError(const QList<QSslError> & errors)
{
    qDebug()<<__FUNCTION__<<errors<<mHttpReply->errorString();
    qDebug()<<"    "<<mHttpReply->url();
}

void Assist::onStartUpSingleShot()
{
    qDebug()<<__FUNCTION__;
    doRequestGetStatus();
}
