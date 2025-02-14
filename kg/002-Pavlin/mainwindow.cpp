#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QPen>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

void MainWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Настройка кисти и пера
    QPen pen(QColor(139, 0, 0), 2); // Красный цвет для линий
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush); // Без заливки, только контуры

    // Нарисуем основные части павлина: хвост, тело и голову

    // Хвост павлина (многоугольники)
    QVector<QPolygonF> tailPolygons;

    // Пример для одной части хвоста
    QPolygonF tailPiece1;
    tailPiece1 << QPointF(50, 50) << QPointF(100, 10) << QPointF(150, 50)
               << QPointF(100, 90);
    tailPolygons.append(tailPiece1);

    // Отрисовка хвоста
    for (const auto &polygon : tailPolygons) {
        painter.drawPolygon(polygon);
    }

    // Тело павлина (простая форма)
    QPolygonF body;
    body << QPointF(100, 150) << QPointF(120, 200) << QPointF(80, 200);
    painter.drawPolygon(body);

    // Голова павлина
    painter.drawLine(100, 150, 100, 100); // Шея
    painter.drawEllipse(90, 90, 20, 20); // Голова

    // Глаз (маленький круг)
    painter.setBrush(Qt::black);
    painter.drawEllipse(95, 95, 5, 5); // Глаз

    // Клюв павлина (треугольник)
    QPolygonF beak;
    beak << QPointF(100, 105) << QPointF(110, 115) << QPointF(90, 115);
    painter.setBrush(Qt::red);
    painter.drawPolygon(beak);
}

MainWindow::~MainWindow()
{
	delete ui;
}

