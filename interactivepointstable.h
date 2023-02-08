#pragma once
#include <QWidget>

class InteractivePointsTable : public QWidget {
  Q_OBJECT

public:
  explicit InteractivePointsTable(QWidget *parent = nullptr);
public:
  std::size_t pointsCount() const;
public slots:
  void clearPoints();
  void generateRandomPoints();
signals:
  void pointsCountChanged();

protected:
  void mousePressEvent(QMouseEvent *event);
  void paintEvent(QPaintEvent *event);
private:
  std::vector<QPoint>::const_iterator findCollision(const QPoint& point1, int distance) const;
  void drawPoints(QPainter& painter) const;
  void drawLines(QPainter& painter) const;
private:
  std::vector<QPoint> points;
};
