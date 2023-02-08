#include "okno.h"
#include "./ui_okno.h"

namespace {

void configurePainterForPoints(QPainter &painter) {
  QPen pen(Qt::white);
  pen.setWidth(2);
  painter.setPen(pen);

  QBrush brush(Qt::lightGray);
  painter.setBrush(brush);
}

void configurePainterForLines(QPainter &painter) {
  QPen pen(Qt::green);
  pen.setWidth(2);
  painter.setPen(pen);
}

bool checkCollision(const QPoint &point1, const QPoint &point2, const int minimumDistance) {
  return (pow(point1.x() - point2.x(), 2) < minimumDistance) && (pow(point1.y() - point2.y(), 2) < minimumDistance);
}

} // namespace

Okno::Okno(QWidget *parent) : QWidget(parent), ui(new Ui::Okno) {
  ui->setupUi(this);
  generatePoints();
  ui->displayFrame->setWindowOpacity(0.2);
}

Okno::~Okno() { delete ui; }

void Okno::on_clearButton_clicked() {
  clearPoints();
  vecCleared = true;
  update();
}

void Okno::on_closeButton_clicked() { QApplication::exit(); }

void Okno::on_generateButton_clicked() {
  if (vecCleared || points.size() < startPointsCount) {
    generatePoints();
    vecCleared = false;
    update();
  }
}

void Okno::refreshPointsCountText() { ui->points_count_label->setText(QString::number(points.size(), 10)); }

void Okno::generatePoints() // TODO: Add resizing
{
  while (points.size() < startPointsCount) {
    if (points.size() == 0) {
      int x = QRandomGenerator::global()->bounded(30, 770);
      int y = QRandomGenerator::global()->bounded(50, 530);
      points.push_back(QPoint(x, y));
    } else {
      int x = QRandomGenerator::global()->bounded(30, 770);
      int y = QRandomGenerator::global()->bounded(60, 530);
      bool collision{false};
      for (auto &p : points) {
        if ((pow(p.x() - x, 2) < 300) && (pow(p.y() - y, 2) < 300)) {
          collision = true;
        }
      }
      if (!collision)
        points.push_back(QPoint(x, y));
    }
  }
}

void Okno::clearPoints() { points.clear(); }

void Okno::mousePressEvent(QMouseEvent *event) {
  QPoint mousePoint{event->pos()};
  if (auto found = findCollision(mousePoint, 160); found != points.end()) {
    points.erase(found);
  } else {
    points.push_back(mousePoint);
  }

  update();
}

void Okno::paintEvent(QPaintEvent *e) {
  QPainter painter(this);
  drawLines(painter);
  drawPoints(painter);
  refreshPointsCountText();
}

std::vector<QPoint>::const_iterator Okno::findCollision(const QPoint &point1, const int distance) const {
  return std::find_if(points.begin(), points.end(), [point1, distance](auto const &point2) { return checkCollision(point1, point2, distance); });
}

void Okno::drawPoints(QPainter &painter) const {
  configurePainterForPoints(painter);
  for (const auto &point : points) {
    painter.drawEllipse(point, 8, 8);
  }
}

void Okno::drawLines(QPainter &painter) const {
  if (points.size() > 1) {
    configurePainterForLines(painter);
    for (std::vector<QPoint>::const_iterator it = points.begin(); it != points.end() - 1; ++it) {
      painter.drawLine(*it, *(it + 1));
    }
  }
}
