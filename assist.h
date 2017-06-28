#ifndef ASSIST_H
#define ASSIST_H

#include <QObject>
#include <QMetaType>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class Assist : public QWebSocket
{
    Q_OBJECT

public:
    Assist();
    void setUrlWebSocket(QString strUrl);
    void setUrlHttpRequest(QString strUrl);
    void openWebSocket();
    void openHttpRequest();
    void doRequestGetStatus();

private:
    QWebSocket mWebSocket;
    QString mUrlWebSocket;
    QString mUrlHttpRequest;
    QNetworkAccessManager *mHttpManager;
    QNetworkRequest mHttpRequest;
    QNetworkReply *mHttpReply;

signals:
    void dataReady(QByteArray ba);

public slots:
    void onStartUpSingleShot();

private slots:
    void onConnected();  //void connected();
    void onDisconnected();  //void disconnected();
    void onTextMessageReceived(const QString & message);  //void textMessageReceived(const QString & message);
    void onAboutToClose();  //void aboutToClose();
    //void binaryFrameReceived(const QByteArray & frame, bool isLastFrame);
    void onBinaryReceived(const QByteArray & message);  //void binaryMessageReceived(const QByteArray & message);
    void onWebSocketBytesWritten(qint64 bytes);//void bytesWritten(qint64 bytes);
    void onMyWebSocketError(QAbstractSocket::SocketError error);  //void error(QAbstractSocket::SocketError error);
    void onPong(quint64 elapsedTime, const QByteArray & payload);  //void pong(quint64 elapsedTime, const QByteArray & payload);
    //void proxyAuthenticationRequired(const QNetworkProxy & proxy, QAuthenticator * authenticator);
    //void readChannelFinished();
    //void sslErrors(const QList<QSslError> & errors);
    void onStateChanged(QAbstractSocket::SocketState state);  //void stateChanged(QAbstractSocket::SocketState state);
    //void textFrameReceived(const QString & frame, bool isLastFrame);

    void onHttpReplyFinished(QNetworkReply * reply); //void QNetworkAccessManager::finished(QNetworkReply * reply)
    void onHttpReplyReadyRead();
    void onHttpReplyError(QNetworkReply::NetworkError code);
    void onHttpSslReplyError(const QList<QSslError> & errors);
};

#endif // ASSIST_H
