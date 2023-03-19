#include "model.h"

namespace vega {

void Model::connectdb(QSqlDatabase *db) {
  *db = QSqlDatabase::addDatabase("QMYSQL");
  db->setDatabaseName("vega_db");
  db->setHostName("172.17.0.2");
  db->setPort(3306);
  db->setUserName("root");
  db->setPassword("root");
  db->setConnectOptions("MYSQL_OPT_RECONNECT=1");
}

}  // namespace vega
