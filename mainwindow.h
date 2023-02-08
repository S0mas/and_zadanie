#pragma once

#include <QWidget>

class InteractivePointsTable;

namespace Ui { class MainWindow; }

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_clearButton_clicked();
    void on_closeButton_clicked();
    void on_generateButton_clicked();
    void refreshPointsCountText();

private:
    Ui::MainWindow *ui;
    InteractivePointsTable* interactivePointsTable;
};
