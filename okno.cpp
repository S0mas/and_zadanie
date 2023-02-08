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
  update();
}

void Okno::on_closeButton_clicked() { QApplication::exit(); }

void Okno::on_generateButton_clicked() {
  if (points.size() < startPointsCount) {
    generatePoints();
    update();
  }
}

void Okno::refreshPointsCountText() { ui->points_count_label->setText(QString::number(points.size(), 10)); }

void Okno::generatePoints() // TODO: Add resizing
{
  while(points.size() < startPointsCount)
  {
    QPoint candidatePoint{QRandomGenerator::global()->bounded(30, 770), QRandomGenerator::global()->bounded(60, 530)};

    if(auto found = findCollision(candidatePoint, 300); found == points.end())
    {
      points.push_back(candidatePoint);
    }
  }
}

void Okno::clearPoints() { points.clear(); }

void Okno::mousePressEvent(QMouseEvent *event) {
  const auto &mouseClickPoint = event->pos();
  if (auto found = findCollision(mouseClickPoint, 160); found != points.end()) {
    points.erase(found);
  } else {
    points.push_back(mouseClickPoint);
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
    for (auto it = points.begin(); it != points.end() - 1; ++it) {
      painter.drawLine(*it, *(it + 1));
    }
  }
}
