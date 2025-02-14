#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <qpoint.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
}

void MainWindow::paintEvent(QPaintEvent *event) {
	Q_UNUSED(event);

	// художник
	QPainter painter(this);

	// рисуем зелёным пером
	QPen greenPen(Qt::green, 5);
	painter.setPen(greenPen);
	
	int width = this->width();
	int height = this->height();

	QPoint topPoint(width * 2 /3, 0);
	QPoint bottomPoint(width / 3, height);
	QPoint leftPoint(0, height * 1 /3);
	QPoint rightPoint(width, height / 3);

	painter.drawLine(leftPoint, topPoint);
	painter.drawLine(topPoint, rightPoint);
	painter.drawLine(rightPoint, bottomPoint);
	painter.drawLine(bottomPoint, leftPoint);

	// рисуем красным пером
	QPen redPen(Qt::red, 5);
	painter.setPen(redPen);

	painter.drawLine(QPoint(0, 0), QPoint(width, height));

	QPen bluePen(Qt::blue, 10);
	painter.setPen(bluePen);

	painter.drawLine(QPoint(90, 50), QPoint(width, 80));
}

MainWindow::~MainWindow()
{
	delete ui;
}
