#include <QCoreApplication>
#include "logmanager.h"
#include <QTimer>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LogManager logger;
    logger.appendLog("Sistem başlatıldı.");
    logger.appendLog("Veritabanı bağlantısı kuruldu.");
    logger.appendLog("Kullanıcı oturumu açıldı.");
    logger.appendLog("Loglama başarıyla çalışıyor.");

    QTimer::singleShot(1000, &a, &QCoreApplication::quit);
    return a.exec();
}
