#include "okno.h"
#include "./ui_okno.h"

Okno::Okno(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Okno)
{
    ui->setupUi(this);
    showPointsCount();
    setRandomPoints();
    ui->displayFrame->setWindowOpacity(0.2);
}

Okno::~Okno()
{
    delete ui;
}

//Buttons----------------------------------------
void Okno::on_clearButton_clicked()
{
    clearPoints();
    showPointsCount();
    vecCleared = true;
    update();
}

void Okno::on_closeButton_clicked()
{
    QApplication::exit();
}

void Okno::on_generateButton_clicked()
{
    if(vecCleared || PointsVectorSize() < startPointsCount)
    {
    setRandomPoints();
    showPointsCount();
    vecCleared = false;
    update();
    }
}

//Points-----------------------------------------
void Okno::showPointsCount()
{
   ui->points_count_label->setText(QString::number(PointsVectorSize(),10));
}

void Okno::setRandomPoints() // dodac resizing
{
    while (PointsVectorSize() < startPointsCount)
    {
        if (PointsVectorSize() == 0)
        {
            int x = QRandomGenerator::global()->bounded(30,770);
            int y = QRandomGenerator::global()->bounded(50,530);
            PointsVector.push_back(QPoint(x,y));
        }
        else
        {
            int x = QRandomGenerator::global()->bounded(30,770);
            int y = QRandomGenerator::global()->bounded(60,530);
            bool collision{false};
            for (auto &p : PointsVector)
            {
                if ( (pow(p.x()-x, 2) < 300) && (pow(p.y()-y, 2) < 300) )
                {
                    collision = true;
                }
            }
            if (!collision) PointsVector.push_back(QPoint(x,y));
        }
    }
    showPointsCount();
}

void Okno::clearPoints()
{
    PointsVector.clear();
}

size_t Okno::PointsVectorSize()
{
    return PointsVector.size();
}

//Mouse draw and delete-------------------------------------
void Okno::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePoint {event->pos()};
    bool mouseCollision {false};
    std::vector<QPoint>::iterator itToDelete;

    for (std::vector<QPoint>::iterator it = PointsVector.begin() ; it != PointsVector.end(); ++it)
    {
        int distance = 160;
        if ( (pow((*it).x() - mousePoint.x(), 2) < distance) && (pow((*it).y() - mousePoint.y(), 2) < distance) )
        {
            mouseCollision = true;
            itToDelete = it;
        }
    }
    if (!mouseCollision) PointsVector.push_back(mousePoint);
    else PointsVector.erase(itToDelete);

    update();
    showPointsCount();
}

//Draw-------------------------------------------
void Okno::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    drawLinePointToPoint(&paint);
    drawPointsVector(&paint);
}

void Okno::drawPointsVector(QPainter *paint)
{
    QPen point_pen(Qt::white);
    point_pen.setWidth(2);
    paint->setPen(point_pen);
    QBrush brush(Qt::lightGray);
    paint->setBrush(brush);

    for_each (PointsVector.begin(), PointsVector.end(),
              [&](QPoint point){paint->drawEllipse(point, 8, 8);});
}

void Okno::drawLinePointToPoint(QPainter *paint)
{
    if (PointsVectorSize() > 1)
    {
        QPen line_pen(Qt::green);
        line_pen.setWidth(2);
        paint->setPen(line_pen);
        for (std::vector<QPoint>::iterator it = PointsVector.begin() ; it != PointsVector.end()-1; ++it)
        {
            paint->drawLine(*it, *(it+1));
        }
    }
}



