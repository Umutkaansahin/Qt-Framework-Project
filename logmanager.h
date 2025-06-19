#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QString>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QTextStream>

class LogManager
{
public:
    LogManager();
    void appendLog(const QString& message);

private:
    void loadConfig();
    void rotateLogsIfNeeded();
    QString getCurrentLogFileName();

    QString logType;
    int maxFileCount;
    int interval;
    QString logDirectory;
};

#endif // LOGMANAGER_H
