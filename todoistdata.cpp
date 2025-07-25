#include "todoistdata.h"

TodoistData::TodoistData(QObject *parent)
    : QObject{parent}
{
    loadSettings();
    fetchTasks(manager);
}

void TodoistData::loadSettings()
{
    // Settings setup;
    // settingsData.apiToken = setup.apiToken;
    // settingsData.assigneeId = setup.assigneeId;
    // settingsData.projectId = setup.projectId;
    qDebug() << settingsData.apiToken;
}

void TodoistData::fetchTasks(QNetworkAccessManager &manager) {
    QUrl url("https://api.todoist.com/rest/v2/tasks"); // URL для получения задач
    QNetworkRequest request(url);

    // Установка заголовков
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(settingsData.apiToken).toUtf8());

    // Выполняем GET запрос
    QNetworkReply *reply = manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Ошибка запроса: " << reply->errorString().toStdString();
            reply->deleteLater();
            return;
        }

        // Обработка ответа
        QByteArray response_data = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response_data);
        qDebug() << jsonDoc;

        if (!jsonDoc.isArray()) {
            qDebug() << "Некорректный формат JSON";
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
        qDebug() << "Нет задач, назначенных на вас.";
    } else {
        qDebug() << "Задачи, назначенные на вас:" << Qt::endl;

        for (const QJsonValue &taskValue : tasks) {
            QJsonObject taskObject = taskValue.toObject();
            // qDebug() << "- " << taskObject["content"].toString() << " ---------- " << taskObject["project_id"].toString() << " -- "
            //          << taskObject["assignee_id"].toString() << " -- " << taskObject["url"].toString() << " | " << taskObject["created_at"].toString();


            // if (taskObject.contains("project_id")) {
            //     qDebug() << " (Проект ID: " << taskObject["project_id"].toInt() << ")";
            // }

        }
        qDebug() << taskFilter(tasks, settingsData.projectId, settingsData.assigneeId);
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

        if (taskProjectId == projectId /*&& taskAssigneeId == assigneeId*/) {
            buffstr = taskObject["content"].toString() + " --- " + taskObject["url"].toString() + " --- " + taskObject["created_at"].toString();
            result.append(buffstr);
            buffstr.clear();
        }

    }
    return result;
}
