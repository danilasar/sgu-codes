#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QPainter>
#include <QPainterPath>
#include <QXmlStreamReader>
#include <QPen>
#include <iostream>
#include <qxmlstream.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	loadFromFile("aboba.xml");
}

void MainWindow::loadFromFile(const QString& filename) {
	m_polylines.clear();

	QFile file(filename);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}

	QXmlStreamReader xml(&file);
	PolylineData currentPolyline;

	while(!xml.atEnd() && !xml.hasError()) {
		QXmlStreamReader::TokenType token = xml.readNext();

		if(token == QXmlStreamReader::StartElement) {
			if(xml.name() == "Polyline") {
				currentPolyline = PolylineData();
				currentPolyline.isClosed = xml.attributes().value("closed") == "true";

				QXmlStreamAttributes attrs = xml.attributes();
				if(attrs.hasAttribute("fill")) {
					try {
						currentPolyline.fillColor = QColor(attrs.value("fill").toString());
					} catch(...) {
						std::cerr << "Неверный цвет фона у одного из контуров" << std::endl;
					}
				}

				if(attrs.hasAttribute("stroke")) {
					try {
						currentPolyline.strokeColor = QColor(attrs.value("stroke").toString());
					} catch(...) {
						std::cerr << "Неверный цвет обрамления одного из контуров" << std::endl;
					}
				}

				if(attrs.hasAttribute("stroke-width")) {
					try {
						currentPolyline.strokeWidth = attrs.value("stroke-width").toDouble();
					} catch(...) {
						std::cerr << "Неверная толщина контура" << std::endl;
					}
				}
			} else if(xml.name() == "Point") {
				bool okX, okY;
				float x = xml.attributes().value("x").toFloat(&okX);
				float y = xml.attributes().value("y").toFloat(&okY);

				if(okX && okY) {
					currentPolyline.points.append(QPointF(x, y));
				}
			}
		} else if(token == QXmlStreamReader::EndElement) {
			if(xml.name() == "Polyline") {
				if(currentPolyline.points.size() > 1) {
					m_polylines.append(currentPolyline);
				}
			}
		}
	}
	if(xml.hasError()) {
		std::cerr << "Ошибка XML: " << xml.errorString().toStdString() << std::endl;
	}

	update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

	// Настройка кисти и пера
	QPen pen(QColor(139, 0, 0), 2); // Красный цвет для линий
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush); // Без заливки, только контуры

	for(const auto& polyline : std::as_const(m_polylines)) {
		if(polyline.points.size() < 2) {
			continue;
		}
		QPainterPath path;
		path.moveTo(polyline.points.first());

		for(int i = 1; i < polyline.points.size(); ++i) {
			path.lineTo(polyline.points[i]);
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

