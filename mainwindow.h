#pragma once

#include <QWidget>
#include <QPoint>

class QMouseEvent;
class QPaintEvent;
class QPainter;
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

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    void refreshPointsCountText();
    void generatePoints();
    void clearPoints();
private:
    std::vector<QPoint>::const_iterator findCollision(const QPoint& point1, int distance) const;
    void drawPoints(QPainter& painter) const;
    void drawLines(QPainter& painter) const;

private:
    Ui::MainWindow *ui;
    std::vector<QPoint> points;
};
