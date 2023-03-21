#include "view/mainview.h"

#include "select.h"

MainView::MainView(vega::MainController* mainController,
                   vega::SelectController* selectController, QWidget* parent)
    : QWidget(parent),
      mainController_(mainController),
      selectController_(selectController) {
  setGeometry(500, 500, 400, 300);
  auto mainBox = new QVBoxLayout();
  auto bottomBox = new QHBoxLayout();
  auto closeBtn = new QPushButton("close");
  auto selectBtn = new QPushButton("select", this);
  listWidget = new QListWidget();

  mainController_->connectdb(&db);
  checkConnectdb();
  mainController_->fillListDevices(listWidget);

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
      this, "Message", "Вы действительно хотите выйти?",
      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    qApp->quit();
  }
}

void MainView::openWindomSelect() {
  QListWidgetItem* item = listWidget->currentItem();
  if (item) {
    QString deviceName = item->text();
    Select* select = new Select(deviceName, selectController_);
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

MainView::~MainView() { db.close(); }
