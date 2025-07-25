#include "tgsender.h"

TgSender::TgSender(QString message, QObject *parent)
    : QObject{parent}
{
    qDebug() << "tg sender start --- " << message;
    QString botToken = "";
    QString userId = "";

    sendMessageToTelegramBot(botToken, message, userId);
}

void TgSender::sendMessageToTelegramBot(const QString &botToken, const QString &message, const QString &userId) {
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    // URL для отправки сообщения через Telegram Bot API
    QString apiUrl = QString("https://api.telegram.org/bot%1/sendMessage").arg(botToken);

    // Подготовка запроса
    QNetworkRequest request((QUrl(apiUrl)));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Тело запроса в формате JSON
    QJsonObject jsonBody;
    jsonBody["chat_id"] = userId;               // ID пользователя
    jsonBody["text"] = message;                // Сообщение

    QJsonDocument jsonDoc(jsonBody);
    QByteArray requestData = jsonDoc.toJson();

    // Выполнение POST-запроса
    QNetworkReply *reply = manager->post(request, requestData);

    // Обработка ответа от Telegram API
    QObject::connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Сообщение успешно отправлено!";
            qDebug() << reply->readAll();
        } else {
            qDebug() << "Ошибка отправки сообщения:" << reply->errorString();
        }
        reply->deleteLater(); // Освобождение памяти
    });
}
