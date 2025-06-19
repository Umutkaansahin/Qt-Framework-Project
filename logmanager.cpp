#include "logmanager.h"

LogManager::LogManager()
{
    logDirectory = "logs";
    QDir().mkpath(logDirectory);
    loadConfig();
}

void LogManager::loadConfig()
{
    QFile configFile("config.json");
    if (!configFile.open(QIODevice::ReadOnly)) {
        logType = "daily";
        maxFileCount = 7;
        interval = 1;
        return;
    }

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(configFile.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject())
        return;

    QJsonObject obj = doc.object();
    logType = obj["log_type"].toString("daily");
    maxFileCount = obj["max_file_count"].toInt(7);
    interval = obj["interval"].toInt(1);
}

QString LogManager::getCurrentLogFileName()
{
    QString format;
    QDateTime now = QDateTime::currentDateTimeUtc();

    if (logType == "hourly") format = "yyyy-MM-dd_HH";
    else if (logType == "minutely") format = "yyyy-MM-dd_HH-mm";
    else if (logType == "secondly") format = "yyyy-MM-dd_HH-mm-ss";
    else format = "yyyy-MM-dd";

    return logDirectory + "/" + now.toString(format) + ".txt";
}

void LogManager::appendLog(const QString& message)
{
    rotateLogsIfNeeded();

    QFile file(getCurrentLogFileName());
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        QString timestamp = QDateTime::currentDateTimeUtc().toString(Qt::ISODate) + "Z";
        out << "[" << timestamp << "] " << message << "\n";
        file.close();
    }
}

void LogManager::rotateLogsIfNeeded()
{
    QDir dir(logDirectory);
    QStringList files = dir.entryList(QStringList() << "*.txt", QDir::Files, QDir::Time);

    std::reverse(files.begin(), files.end());

    while (files.size() > maxFileCount) {
        QString filePath = logDirectory + "/" + files.first();
        qDebug() << "Silme denemesi:" << filePath;
        bool removed = QFile::remove(filePath);
        qDebug() << "Silme sonucu:" << removed;
        if (removed) {
            files.removeFirst();
        } else {
            qDebug() << "Dosya silinemedi:" << filePath;
            break;
        }
    }
}


