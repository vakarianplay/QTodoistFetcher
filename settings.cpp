#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject{parent}
{
    QSettings settings(path, QSettings::IniFormat);

    settings.beginGroup("Todoist");
    apiToken = settings.value("api_token").toString();
    projectId = settings.value("project_id").toString();
    assigneeId = settings.value("assignee_id").toString();
    timerThreshold = settings.value("time_threshold").toInt() * 60000;
    settings.endGroup();

    settings.beginGroup("Telegram");
    botToken = settings.value("bot_token").toString();
    tgUser = settings.value("user_id").toString();
    settings.endGroup();

}

Settings::~Settings()
{
    qDebug() << "delete settings";
}
