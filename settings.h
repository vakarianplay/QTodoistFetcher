#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QDir>

class Settings : public QObject
{
    Q_OBJECT
public:
    Settings(QObject *parent = nullptr);
    ~Settings();

    QString apiToken;
    QString projectId;
    QString assigneeId;
    qint32 timerThreshold;
    QString botToken;
    QString tgUser;


private:
    QString path = QDir::currentPath() + "/settings.ini";

};

#endif // SETTINGS_H
