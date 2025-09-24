#include "todoistdata.h"

TodoistData::TodoistData(QObject *parent)
    : QObject{parent}
{
    loadSettings();
    threshold = new QTimer (this);
    fetchTasks(manager);
    connect(threshold, SIGNAL(timeout()), this, SLOT(callFetcher()));
    threshold->start(settingsData.timerThreshold);
    qDebug() << "timer start - " << settingsData.timerThreshold;
}

TodoistData::~TodoistData()
{
    threshold->stop();
    if (&manager)
        delete &manager;
}



void TodoistData::loadSettings()
{
    qDebug() << settingsData.apiToken << "   " << settingsData.timerThreshold << "  " << settingsData.tgUser;
}

void TodoistData::callFetcher()
{
    qDebug() << "timer call fetcher";
    fetchTasks(manager);
}

void TodoistData::fetchTasks(QNetworkAccessManager &manager) {
    QUrl url("https://api.todoist.com/rest/v2/tasks");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(settingsData.apiToken).toUtf8());

    QNetworkReply *reply = manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() != QNetworkReply::NoError) {
            reply->deleteLater();
            return;
        }

        // Обработка ответа
        QByteArray response_data = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
        qDebug() << jsonDoc;

        if (!jsonDoc.isArray()) {
            reply->deleteLater();
            return;
        }
        reply->deleteLater();
        taskSerializer(jsonDoc.array());
    });
}

void TodoistData::taskSerializer(QJsonArray tasks_)
{
    QJsonArray tasks = tasks_;

    if (tasks.isEmpty()) {
        qDebug() << "Not assigned tasks.";
    } else {
        qDebug() << "Assigned tasks:" << Qt::endl;

        for (const QJsonValue &taskValue : tasks)
            QJsonObject taskObject = taskValue.toObject();

        QString taskData = filterRecentTasks(taskFilter(tasks, settingsData.projectId, settingsData.assigneeId), settingsData.timerThreshold).join(" \n ");
        TgSender *tgSender = new TgSender(taskData);

        if (tgSender)
            delete tgSender;

    }
}

QStringList TodoistData::taskFilter(const QJsonArray &tasks, const QString &projectId, const QString &assigneeId)
{
    QStringList result;

    for (const QJsonValue &taskValue : tasks) {
        QString buffstr = "";
        QJsonObject taskObject = taskValue.toObject();

        QString taskProjectId = taskObject["project_id"].toString();
        QString taskAssigneeId = taskObject["assignee_id"].toString();

        if (taskProjectId == projectId && taskAssigneeId == assigneeId) {
            buffstr = taskObject["content"].toString() + " --- " + taskObject["url"].toString() + " --- " + taskObject["created_at"].toString();
            result.append(buffstr);
            buffstr.clear();
        }

    }
    return result;
}

QStringList TodoistData::filterRecentTasks(const QStringList &tasks, int timeThresholdMinutes)
{
    QStringList filteredTasks;
    QDateTime currentDateTime = QDateTime::currentDateTimeUtc();

    for (const QString &task : tasks) {
        QStringList parts = task.split("---");
        if (parts.size() < 3) {
            qDebug() << "Error. Incorrect format string:" << task;
            continue;
        }

        QString timestampStr = parts.last().trimmed();
        QDateTime taskDateTime = QDateTime::fromString(timestampStr, Qt::ISODate);

        if (!taskDateTime.isValid()) {
            qDebug() << "Error. Incorrect time format:" << timestampStr;
            continue;
        }

        qint64 timeDifferenceMinutes = taskDateTime.msecsTo(currentDateTime) / 60000;
        if (timeDifferenceMinutes <= timeThresholdMinutes - 1) {
            filteredTasks.append(task);
        }
    }

    return filteredTasks;
}

