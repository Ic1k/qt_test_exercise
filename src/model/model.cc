#include "model.h"

#include <QSettings>

namespace vega {

void Model::connectdb(QSqlDatabase *db) {
  QSettings settings("config.ini", QSettings::IniFormat);

  // Загружаем настройки
  QString host = settings.value("mysql/host", "localhost").toString();
  QString user = settings.value("mysql/user", "root").toString();
  QString password = settings.value("mysql/password", "").toString();
  QString database = settings.value("mysql/database", "test").toString();

  *db = QSqlDatabase::addDatabase("QMYSQL");
  db->setDatabaseName(database);
  db->setHostName(host);
  db->setPort(3306);
  db->setUserName(user);
  db->setPassword(password);
  db->setConnectOptions("MYSQL_OPT_RECONNECT=1");
}

void Model::fillListDevices(QListWidget *listWidget) {
  QSqlQuery queryDevice;
  queryDevice.prepare("SELECT name FROM devices");
  queryDevice.exec();
  while (queryDevice.next()) {
    QString name = queryDevice.value(0).toString();
    listWidget->addItem(name);
  }
}
void Model::fillListProcess(QListWidget *listProcess, QString deviceName) {
  QSqlQuery queryProcess;
  queryProcess.prepare(
      "SELECT p.name \
             from data\
             join processes p on data.process_id = p.id \
             join devices d on data.device_id = d.id \
            where d.name = ? \
            group by p.name;");
  queryProcess.addBindValue(deviceName);
  queryProcess.exec();
  while (queryProcess.next()) {
    QString name = queryProcess.value(0).toString();
    listProcess->addItem(name);
  }
}

void Model::fillListPdfBin(QListWidget *listPdf, QListWidget *listBin,
                           QString deviceName, QString processName) {
  QSqlQuery queryPdf;
  queryPdf.prepare(
      "SELECT f.name \
                        from data \
                         join processes p on data.process_id = p.id \
                         join devices d on data.device_id = d.id \
                         join files f on f.id = data.file_id \
                         where d.name = ? AND p.name = ? AND f.name LIKE '%pdf'");
  queryPdf.addBindValue(deviceName);
  queryPdf.addBindValue(processName);
  queryPdf.exec();
  listPdf->clear();
  while (queryPdf.next()) {
    QString name = queryPdf.value(0).toString();
    listPdf->addItem(name);
  }

  QSqlQuery queryBin;
  queryBin.prepare(
      "SELECT f.name \
                      from data \
                       join processes p on data.process_id = p.id \
                       join devices d on data.device_id = d.id \
                       join files f on f.id = data.file_id \
                       where d.name = ? AND p.name = ? AND f.name LIKE '%bin'");
  queryBin.addBindValue(deviceName);
  queryBin.addBindValue(processName);
  queryBin.exec();
  listBin->clear();
  while (queryBin.next()) {
    QString name = queryBin.value(0).toString();
    listBin->addItem(name);
  }
}

void Model::insertFilesToData(QString deviceName, QString processName,
                              QString fileName) {
  // Добавление файла в таблицу files
  QSqlQuery queryUpload;
  queryUpload.prepare("INSERT INTO files(name) VALUES (?)");
  queryUpload.addBindValue(fileName);
  queryUpload.exec();

  qDebug() << deviceName;

  // Добавление зависимостей файла в таблицу data
  int deviceId = getdeviceId(deviceName);
  int processId = getprocessId(processName);
  int filesId = getfilesId();
  // qDebug() << deviceId;
  //  qDebug() << processId;
  //   qDebug() << filesId;
  QSqlQuery query;
  query.prepare(
      "INSERT INTO data (device_id, process_id, file_id) \
                VALUES (:deviceId, :processId, :filesId)");
  query.bindValue(":deviceId", deviceId);
  query.bindValue(":processId", processId);
  query.bindValue(":filesId", filesId);
  query.exec();
}

int Model::getdeviceId(QString deviceName) {
  int deviceId = -1;
  QSqlQuery queryDeviceId;
  queryDeviceId.prepare(
      "select id \
           from devices \
          where name = :name");
  queryDeviceId.bindValue(":name", deviceName);
  queryDeviceId.exec();
  if (queryDeviceId.next()) {
    deviceId = queryDeviceId.value(0).toInt();
  }
  return deviceId;
}

int Model::getprocessId(QString processName) {
  int processId = -1;
  QSqlQuery queryProcessId;
  queryProcessId.prepare(
      "select id \
           from processes \
          where name = :name");
  queryProcessId.bindValue(":name", processName);
  queryProcessId.exec();
  if (queryProcessId.next()) {
    processId = queryProcessId.value(0).toInt();
  }
  return processId;
}

int Model::getfilesId() {
  int filesId = -1;
  QSqlQuery queryFilesId;
  queryFilesId.prepare(
      "select max(id) \
           from files");
  queryFilesId.exec();
  if (queryFilesId.next()) {
    filesId = queryFilesId.value(0).toInt();
  }

  return filesId;
}
}  // namespace vega
