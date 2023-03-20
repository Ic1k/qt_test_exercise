#include "select.h"

Select::Select(QString deviceName_, QDialog *parent)
    : QDialog(parent),
      deviceName(deviceName_)

{
  // Заголовок и список процессов.
  QLabel *labelDevice = new QLabel(this);
  labelDevice->setText(deviceName);
  labelDevice->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  QListWidget *listProcess = new QListWidget;
  connect(listProcess, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(onProcessListClicked(QListWidgetItem *)));

  // Заполнение списка процессов
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

 //  Левая часть формы. Заголовок и список процессов.
  QVBoxLayout *leftLayout = new QVBoxLayout();
  leftLayout->addWidget(labelDevice);
  leftLayout->addWidget(listProcess);

  // Правая, верхняя часть формы.  Список прошивок и инструкций
  QTabWidget *tabWidget = new QTabWidget;
  listPdf = new QListWidget;
  listBin = new QListWidget;
  tabWidget->addTab(listPdf, "Инструкции");
  tabWidget->addTab(listBin, "Прошивки");

  // Правая, нижняя часть формы.
  QPushButton *btn_upload = new QPushButton("Загрузить файл", this);
  QPushButton *btn_download = new QPushButton("Скачать файл", this);
  connect(btn_upload, &QPushButton::clicked, this, &Select::uploadFile);
  connect(btn_download, &QPushButton::clicked, this, &Select::downloadFile);

  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(btn_upload);
  buttonLayout->addStretch();
  buttonLayout->addWidget(btn_download);

  QVBoxLayout *rightLayout = new QVBoxLayout();
  rightLayout->addWidget(tabWidget);
  rightLayout->addLayout(buttonLayout);

  // Объединенная форма.
  QHBoxLayout *centralLayout = new QHBoxLayout();
  centralLayout->addLayout(leftLayout);
  centralLayout->addLayout(rightLayout);
  this->setLayout(centralLayout);


}
// Разблокировка основного окна
void Select::closeEvent(QCloseEvent *event) { event->accept(); }

//Выбор элемента списка процессов
void Select::onProcessListClicked(QListWidgetItem *item) {
  processName = item->text();

  // Заполнение списка PDF
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

  // Заполнение списка BIN
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

//Кнопка загрузки файла
void Select::uploadFile() {
  //Диалоговое окно, получение полного адреса файла.
  QString pathFile = QFileDialog::getOpenFileName(
      this, tr("Open File"), QDir::homePath(), tr("PDF Files (*.pdf);;BIN Files (*.bin)"));
  //Получение имени файла
  QStringList parts = pathFile.split("/");
  QString fileName = parts.at(parts.size() - 1);

  //Добавление файла в таблицу
  QSqlQuery queryUpload;
  queryUpload.prepare("INSERT INTO files(name) VALUES (?)");
  queryUpload.addBindValue(fileName);
  queryUpload.exec();


  //Добавление зависимостей файла в таблицу
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

  int filesId = -1;
  QSqlQuery queryFilesId;
  queryFilesId.prepare(
      "select max(id) \
         from files");
  queryFilesId.exec();
  if (queryFilesId.next()) {
    filesId = queryFilesId.value(0).toInt();
  }

  QSqlQuery query;
  query.prepare(
      "INSERT INTO data (device_id, process_id, file_id) \
              VALUES (:deviceId, :processId, :filesId)");
  query.bindValue(":deviceId", deviceId);
  query.bindValue(":processId", processId);
  query.bindValue(":filesId", filesId);
  query.exec();
}

void Select::downloadFile() { qDebug() << "2"; }

Select::~Select() {}
