#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "picture_fabric.h"
#include <QFile>
#include <QPainter>
#include <QPainterPath>
#include <QXmlStreamReader>
#include <QPen>
#include <iostream>
#include <qnamespace.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setFocusPolicy(Qt::StrongFocus);
	PictureFabric fabric(std::make_unique<Picture>());
	fabric.make_rabbit();
	picture = std::move(fabric.get_picture());
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if(event->key() == Qt::Key_N && event->modifiers() == Qt::NoModifier) {
		picture->clear();
		PictureFabric fabric(std::move(picture));
		fabric.make_mouse();
		picture = std::move(fabric.get_picture());
		update();
	}
}

void MainWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

	// Настройка кисти и пера
	QPen pen(QColor(139, 0, 0), 2); // Красный цвет для линий
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush); // Без заливки, только контуры

	const QVector<Path> &paths = picture->get_paths();
	for(const Path& polyline : paths) {
		if(polyline.points.size() < 2) {
			continue;
		}
		QPainterPath path;
		path.moveTo(polyline.points.first() * 50);

		for(int i = 1; i < polyline.points.size(); ++i) {
			path.lineTo(polyline.points[i] * 50);
		}

		if(polyline.isClosed) {
			path.closeSubpath();
		}

		if(polyline.fillColor.alpha() > 0) {
			painter.fillPath(path, polyline.fillColor);
		}

		if(polyline.strokeWidth > 0) {
			QPen pen(polyline.strokeColor, polyline.strokeWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
			painter.strokePath(path, pen);
		}

		//painter.drawPath(path);
	}

}

MainWindow::~MainWindow()
{
	delete ui;
}

