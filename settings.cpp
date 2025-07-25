#include "settings.h"

Settings::Settings(QObject *parent)
    : QObject{parent}
{
    QSettings settings(path, QSettings::IniFormat);

    settings.beginGroup("Todoist");
    apiToken = settings.value("api_token").toString();
    projectId = settings.value("project_id").toString();
    assigneeId = settings.value("assignee_id").toString();
    settings.endGroup();

}

Settings::~Settings()
{
    qDebug() << "delete settings";
}
