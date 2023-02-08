#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "interactivepointstable.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow), interactivePointsTable(new InteractivePointsTable(this)) {
  ui->setupUi(this);
  ui->verticalLayout->insertWidget(1, interactivePointsTable, 1);
  connect(interactivePointsTable, &InteractivePointsTable::pointsCountChanged, this, &MainWindow::refreshPointsCountText);
  refreshPointsCountText();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_clearButton_clicked() const { interactivePointsTable->clearPoints(); }

void MainWindow::on_closeButton_clicked() const { QApplication::exit(); }

void MainWindow::on_generateButton_clicked() const { interactivePointsTable->generateRandomPoints(); }

void MainWindow::refreshPointsCountText() const { ui->pointsCountLabel->setText(QString::number(interactivePointsTable->pointsCount())); }
