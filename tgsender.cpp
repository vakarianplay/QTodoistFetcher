#include "tgsender.h"

TgSender::TgSender(QString message, QObject *parent)
    : QObject{parent}
{
    qDebug() << "tg sender start --- " << message;
    QString botToken = settingsData.botToken;
    QString userId = settingsData.tgUser;

    sendMessageToTelegramBot(botToken, message, userId);
}

void TgSender::sendMessageToTelegramBot(const QString &botToken, const QString &message, const QString &userId)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QString apiUrl = QString("https://api.telegram.org/bot%1/sendMessage").arg(botToken);
    QNetworkRequest request((QUrl(apiUrl)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject jsonBody;
    jsonBody["chat_id"] = userId;
    jsonBody["text"] = message;

    QJsonDocument jsonDoc(jsonBody);
    QByteArray requestData = jsonDoc.toJson();
    QNetworkReply *reply = manager->post(request, requestData);
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Messages send!";
            qDebug() << reply->readAll();
        } else {
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
    });
}
