#ifndef TGSENDER_H
#define TGSENDER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

class TgSender : public QObject
{
    Q_OBJECT
public:
    TgSender(QString message, QObject *parent = nullptr);

private:
    void sendMessageToTelegramBot(const QString &botToken, const QString &message, const QString &userId);

};

#endif // TGSENDER_H
