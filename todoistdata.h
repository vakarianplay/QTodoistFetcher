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
#include <QDateTime>
#include "tgsender.h"
#include <QTimer>

class TodoistData : public QObject
{
    Q_OBJECT
public:
    explicit TodoistData(QObject *parent = nullptr);
    ~TodoistData();

private slots:
    void callFetcher();

private:
    Settings settingsData;
    QNetworkAccessManager manager;
    QTimer* threshold;
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
    QStringList filterRecentTasks(const QStringList &tasks, int timeThresholdMinutes);

};

#endif // TODOISTDATA_H
