#include "model.h"
#include <QSettings>

namespace vega {

void Model::connectdb(QSqlDatabase *db) {

//    QSettings settings("config.ini", QSettings::IniFormat);

//    settings.setValue("mysql/host", "172.17.0.2");
//    settings.setValue("mysql/user", "root");
//    settings.setValue("mysql/password", "root");
//    settings.setValue("mysql/database", "vega_db");


    QSettings settings("config.ini", QSettings::IniFormat);

    // Загружаем настройки
    QString host = settings.value("mysql/host", "localhost").toString();
    QString user = settings.value("mysql/user", "root").toString();
    QString password = settings.value("mysql/password", "").toString();
    QString database = settings.value("mysql/database", "test").toString();



    *db = QSqlDatabase::addDatabase("QMYSQL");
  db->setDatabaseName("database");
  db->setHostName("host");
  db->setPort(3306);
  db->setUserName("user");
  db->setPassword("password");
  db->setConnectOptions("MYSQL_OPT_RECONNECT=1");
}



}  // namespace vega
