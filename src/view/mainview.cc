#include "view/mainview.h"

MainView::MainView(vega::Controller* controller, QWidget* parent)
    : QWidget(parent), controller_(controller) {
  setGeometry(500, 500, 400, 300);
  auto mainBox = new QVBoxLayout();
  auto bottomBox = new QHBoxLayout();
  auto closeBtn = new QPushButton("close");
  auto selectBtn = new QPushButton("select", this);
  listWidget = new QListWidget();

  controller_->connectdb(&db);
  checkConnectdb();
  fillQlist();

  connect(closeBtn, &QPushButton::clicked, this, &MainView::closeApp);
  connect(selectBtn, &QPushButton::clicked, this, &MainView::openWindomSelect);

  bottomBox->addWidget(closeBtn, 0, Qt::AlignLeft);
  bottomBox->addWidget(selectBtn, 0, Qt::AlignRight);

  mainBox->addWidget(listWidget);
  mainBox->addLayout(bottomBox);
  setLayout(mainBox);
}

void MainView::closeApp() {
  QMessageBox::StandardButton reply = QMessageBox::question(
      this, "Message", "Are you sure you want to quit?",
      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    qApp->quit();
  }
}

void MainView::openWindomSelect() {
  QListWidgetItem* item = listWidget->currentItem();
  if (item) {
    QString deviceName = item->text();
    Select* select = new Select(deviceName);
    select->exec();
  }
}

void MainView::checkConnectdb() {
  if (!db.open()) {
    qDebug() << "Not connect for database\n"
             << db.lastError().driverText() << "\n";
  } else {
    qDebug() << "Connect succefull\n";
  }
}

void MainView::fillQlist() {
  QSqlQuery queryDevice;
  queryDevice.prepare("SELECT name FROM devices");

  if (!queryDevice.exec()) {
    qDebug() << "Error executing query: " << queryDevice.lastError().text();
  }

  listWidget->clear();

  while (queryDevice.next()) {
    QString name = queryDevice.value(0).toString();
    listWidget->addItem(name);
  }
}

MainView::~MainView() { db.close(); }