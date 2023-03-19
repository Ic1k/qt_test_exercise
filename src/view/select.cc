#include "select.h"

Select::Select(QString deviceName_, QDialog *parent)
    : QDialog(parent),
      deviceName(deviceName_)

{
  // Левая часть формы. Заголовок и список процессов.
  QLabel *labelDevice = new QLabel(this);
  labelDevice->setText(deviceName);
  labelDevice->setAlignment(Qt::AlignTop | Qt::AlignLeft);

  QListWidget *listProcess = new QListWidget;
  connect(listProcess, SIGNAL(itemClicked(QListWidgetItem *)), this,
          SLOT(onItemClicked(QListWidgetItem *)));



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

  if (!queryProcess.exec()) {
    qDebug() << "Error executing query: " << queryProcess.lastError().text();
  }

  listProcess->clear();

  while (queryProcess.next()) {
    QString name = queryProcess.value(0).toString();
    listProcess->addItem(name);
  }

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

  //  this->resize(500, 300);
}

void Select::closeEvent(QCloseEvent *event) { event->accept(); }

void Select::onItemClicked(QListWidgetItem *item) {
  QString prosessName = item->text();

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
  queryPdf.addBindValue(prosessName);

  if (!queryPdf.exec()) {
    qDebug() << "Error executing query: " << queryPdf.lastError().text();
  }

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
  queryBin.addBindValue(prosessName);

  if (!queryBin.exec()) {
    qDebug() << "Error executing query: " << queryBin.lastError().text();
  }

  listBin->clear();

  while (queryBin.next()) {
    QString name = queryBin.value(0).toString();
    listBin->addItem(name);
  }
}



void Select::uploadFile() {
    QString pathFile = QFileDialog::getOpenFileName(
          this, "Open a file", QDir::homePath(), "PDF or BIN(*.pdf, *.bin)");
    QStringList parts = pathFile.split("/");
    QString fileName = parts.at(parts.size() - 1);
    QSqlQuery queryUpload;
    queryUpload.prepare("INSERT INTO files(name) VALUES (?)");
    queryUpload.addBindValue(fileName);
    queryUpload.exec();

     int  device_id,process_id,file_id;

    queryUpload.prepare(
        "select id \
           from devices \
          where name = 'MT - 24'");
//      qDebug() << deviceName;
//                        queryUpload.addBindValue(deviceName);
//    queryUpload.next();

      device_id = queryUpload.value(0).toInt()+1;
 qDebug() << device_id;
//    queryUpload.prepare(
//        "select id \
//           from processes \
//          where name = ?");
//      queryUpload.addBindValue(listProcess->currentItem()->text());
//      process_id = queryUpload.value(0).toInt();

//    queryUpload.prepare(
//        "select max(id) \
//           from files \
//           ");
//      queryUpload.addBindValue(listProcess->currentItem()->text());
//      process_id = queryUpload.value(0).toInt();


//    queryUpload.prepare("INSERT INTO data(device_id, process_id, file_id) VALUES (?, ?, ?),");
//    queryUpload.addBindValue(device_id);
//    queryUpload.addBindValue(process_id);
//    queryUpload.addBindValue(file_id);
//    queryUpload.exec();



}
void Select::downloadFile() {
 qDebug() << "2";
}

Select::~Select() {}
