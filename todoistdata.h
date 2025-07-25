#ifndef TODOISTDATA_H
#define TODOISTDATA_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>
#include "settings.h"
#include <QDebug>

class TodoistData : public QObject
{
    Q_OBJECT
public:
    explicit TodoistData(QObject *parent = nullptr);

private:
    Settings settingsData;
    QNetworkAccessManager manager;
    // struct SettingsParams
    // {
    //     QString apiToken;
    //     QString projectId;
    //     QString assigneeId;
    // };

    // SettingsParams settingsData;

    void loadSettings();
    void fetchTasks(QNetworkAccessManager &manager);
    void taskSerializer(QJsonArray tasks_);
    QStringList taskFilter(const QJsonArray &tasks, const QString &projectId, const QString &assigneeId);

};

#endif // TODOISTDATA_H
