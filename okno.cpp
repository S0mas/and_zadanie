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

} // namespace

Okno::Okno(QWidget *parent) : QWidget(parent), ui(new Ui::Okno) {
  ui->setupUi(this);
  refreshPointsCountText();
  generatePoints();
  ui->displayFrame->setWindowOpacity(0.2);
}

Okno::~Okno() { delete ui; }

// Buttons----------------------------------------
void Okno::on_clearButton_clicked() {
  clearPoints();
  refreshPointsCountText();
  vecCleared = true;
  update();
}

void Okno::on_closeButton_clicked() { QApplication::exit(); }

void Okno::on_generateButton_clicked() {
  if (vecCleared || points.size() < startPointsCount) {
    generatePoints();
    refreshPointsCountText();
    vecCleared = false;
    update();
  }
}

// Points-----------------------------------------
void Okno::refreshPointsCountText() { ui->points_count_label->setText(QString::number(points.size(), 10)); }

void Okno::generatePoints() // dodac resizing
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
  refreshPointsCountText();
}

void Okno::clearPoints() { points.clear(); }

// Mouse draw and delete-------------------------------------
void Okno::mousePressEvent(QMouseEvent *event) {
  QPoint mousePoint{event->pos()};
  bool mouseCollision{false};
  std::vector<QPoint>::iterator itToDelete;

  for (std::vector<QPoint>::iterator it = points.begin(); it != points.end(); ++it) {
    int distance = 160;
    if ((pow((*it).x() - mousePoint.x(), 2) < distance) && (pow((*it).y() - mousePoint.y(), 2) < distance)) {
      mouseCollision = true;
      itToDelete = it;
    }
  }
  if (!mouseCollision)
    points.push_back(mousePoint);
  else
    points.erase(itToDelete);

  update();
  refreshPointsCountText();
}

// Draw-------------------------------------------
void Okno::paintEvent(QPaintEvent *e) {
  QPainter painter(this);
  drawLines(painter);
  drawPoints(painter);
}

void Okno::drawPoints(QPainter &painter) const {
  configurePainterForPoints(painter);
  for(const auto& point : points)
  {
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
