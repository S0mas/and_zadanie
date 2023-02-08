#ifndef OKNO_H
#define OKNO_H

#include <QWidget>
#include <QPoint>

class QMouseEvent;
class QPaintEvent;
class QPainter;

QT_BEGIN_NAMESPACE
namespace Ui { class Okno; }
QT_END_NAMESPACE

class Okno : public QWidget
{
    Q_OBJECT

public:
    Okno(QWidget *parent = nullptr);
    ~Okno();

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
    Ui::Okno *ui;
    std::vector<QPoint> points;
};



#endif // OKNO_H
