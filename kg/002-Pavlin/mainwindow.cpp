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
#include <qpoint.h>

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
	if(event->modifiers() == Qt::NoModifier) {
		if(event->key() == Qt::Key_N) {
			is_mouse = !is_mouse;
			picture->clear();
			PictureFabric fabric(std::move(picture));
			if(is_mouse) {
				fabric.make_mouse();
			} else {
				fabric.make_rabbit();
			}
			picture = std::move(fabric.get_picture());
		}
		if(event->key() == Qt::Key_M) {
			keep_aspect_ratio = !keep_aspect_ratio;
		}
		//update();
		repaint();
	}
}

QPointF MainWindow::transform_point(QPointF point, QPointF base_size, QPointF new_size, QPointF new_position) const {
	double x = (double)point.x() / (double)base_size.x();
	double y = (double)point.y() / (double)base_size.y();
	y *= -1;
	y += 1;
	QPointF new_point;
	if(keep_aspect_ratio) {
		new_point = QPointF { x * new_size.x(), y * new_size.y() };
	} else {
		auto scale = std::min(new_size.x(), new_size.y());
		new_point = scale * QPointF { x, y };
	}
	return new_point;
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
		QPointF new_point = transform_point(
			polyline.points.first(),
			QPointF { picture->get_width(), picture->get_height() },
			QPointF { static_cast<double>(this->width()), static_cast<double>(this->height()) },
			QPointF { 0, 0 }
		);
		QPainterPath path;
		path.moveTo(new_point);

		for(int i = 1; i < polyline.points.size(); ++i) {
			new_point = transform_point(
				polyline.points[i],
				QPointF { picture->get_width(), picture->get_height() },
				QPointF { static_cast<double>(this->width()), static_cast<double>(this->height()) },
				QPointF { 0, 0 }
			);
			path.lineTo(new_point);
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
		QWidget::paintEvent(event);
	}

}

MainWindow::~MainWindow()
{
	delete ui;
}

