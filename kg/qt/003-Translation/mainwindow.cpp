#include "mainwindow.h"
#include "math/vec.h"
#include "math/units/degree.h"
#include "./ui_mainwindow.h"
#include "picture/picture_fabric.h"
#include <QFile>
#include <QPainter>
#include <QPainterPath>
#include <QXmlStreamReader>
#include <QPen>
#include <iostream>
#include <qpoint.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	setFocusPolicy(Qt::StrongFocus);
	Picture::PictureFabric fabric(std::make_unique<Picture::Picture>());
	fabric.make_rabbit();
	picture = std::move(fabric.get_picture());
	reprepare_transforms_needle = true;
}

void MainWindow::resizeEvent(QResizeEvent *event) {
	reprepare_transforms_needle = true;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if(event->modifiers() == Qt::NoModifier) {
		std::lock_guard<std::mutex> picture_lock(picture_mutex);
		Picture::PictureFabric fabric(std::move(picture));
		float Wcx { this->width() / 2.f };
		float Wcy { this->height() / 2.f };
		switch(event->key()) {
			case Qt::Key_N:
			is_mouse = !is_mouse;
			fabric.clear();
			if(is_mouse) {
				fabric.make_mouse();
			} else {
				fabric.make_rabbit();
			}
			reprepare_transforms_needle = true;
			break;
		case Qt::Key_M:
			keep_aspect_ratio = !keep_aspect_ratio;
			reprepare_transforms_needle = true;
			break;
		case Qt::Key_R:
		case Qt::Key_Y:
		case Qt::Key_E:
		case Qt::Key_Q: {
				Math::Radian rotation = 0.01;
				if(event->key() == Qt::Key_R || event->key() == Qt::Key_Y) {
					rotation = 0.05;
				}
				if(event->key() == Qt::Key_E || event->key() == Qt::Key_Y) {
					rotation = static_cast<float>(rotation) * -1.;
				}
				T =	Math::TranslationMatrix::translate(-Wcx, -Wcy) * T;
				T = Math::TranslationMatrix::rotate(Math::Radian(rotation)) * T;
				T = Math::TranslationMatrix::translate(Wcx, Wcy) * T;
			}
			break;
		case Qt::Key_T:
		case Qt::Key_F:
		case Qt::Key_G:
		case Qt::Key_H:
		case Qt::Key_W:
		case Qt::Key_A:
		case Qt::Key_S:
		case Qt::Key_D: {
			float speed = 1, speed_x = 0, speed_y = 0;
			const Qt::Key tfgh[] { Qt::Key_T, Qt::Key_F, Qt::Key_G, Qt::Key_H };
			if(std::find(std::begin(tfgh), std::end(tfgh), event->key()) != std::end(tfgh)) {
				speed = 10;
			}
			const Qt::Key negative[] { Qt::Key_A, Qt::Key_W, Qt::Key_F, Qt::Key_T };
			if(std::find(std::begin(negative), std::end(negative), event->key()) != std::end(negative)) {
				speed *= -1;
			}
			const Qt::Key horizontal[] { Qt::Key_A, Qt::Key_D, Qt::Key_F, Qt::Key_H };
			if(std::find(std::begin(horizontal), std::end(horizontal), event->key()) != std::end(horizontal)) {
				speed_x = speed;
			} else {
				speed_y = speed;
			}
			T = Math::TranslationMatrix::translate(speed_x, speed_y) * T;
			}
			break;
		// увеличение или уменьшение в 1.1 раза
		case Qt::Key_Z:
			if(std::abs(T.x.x) > 1e9 || std::abs(T.y.y) > 1e9) break;
			T = Math::TranslationMatrix::scale(1.1f) * T;
			break;
		case Qt::Key_X:
			if(std::abs(T.x.x) < 1e-9 || std::abs(T.y.y) < 1e-9) break;
			T = Math::TranslationMatrix::scale(1. / 1.1f) * T;
			break;
		case Qt::Key_I:
			if(std::abs(T.x.x) > 1e9) break;
			T =	Math::TranslationMatrix::translate(-Wcx, 0.f) * T;
			T = Math::TranslationMatrix::scale(1.1f, 1.f) * T;
			T =	Math::TranslationMatrix::translate(Wcx, 0.f) * T;
			break;
		case Qt::Key_K:
			if(std::abs(T.x.x) < 1e-9) break;
			T =	Math::TranslationMatrix::translate(-Wcx, 0.f) * T;
			T = Math::TranslationMatrix::scale(1.f / 1.1f, 1.f) * T;
			T =	Math::TranslationMatrix::translate(Wcx, 0.f) * T;
			break;
		case Qt::Key_O:
			if(std::abs(T.y.y) > 1e9) break;
			T =	Math::TranslationMatrix::translate(0.f, -Wcy) * T;
			T = Math::TranslationMatrix::scale(1.f, 1.1f) * T;
			T =	Math::TranslationMatrix::translate(0.f, Wcy) * T;
			break;
		case Qt::Key_L:
			if(std::abs(T.y.y) < 1e-9) break;
			T =	Math::TranslationMatrix::translate(0.f, -Wcy) * T;
			T = Math::TranslationMatrix::scale(1.f, 1.f / 1.1f) * T;
			T =	Math::TranslationMatrix::translate(0.f, Wcy) * T;
			break;
		case Qt::Key_U:
			T =	Math::TranslationMatrix::translate(-Wcx, 0.f) * T;
			T = Math::TranslationMatrix::scale(-1.f, 1.f) * T;
			T =	Math::TranslationMatrix::translate(Wcx, 0.f) * T;
			break;
		case Qt::Key_J:
			T =	Math::TranslationMatrix::translate(0.f, -Wcy) * T;
			T = Math::TranslationMatrix::scale(1.f, -1.f) * T;
			T =	Math::TranslationMatrix::translate(0.f, Wcy) * T;
			break;
		case Qt::Key_Escape:
			T = Math::TranslationMatrix(1.f);
			break;
		}
		picture = std::move(fabric.get_picture());
		//update();
		repaint();
	}
}

void MainWindow::prepare_transforms(QPointF base_size, QPointF new_size, QPointF new_position) {
	double Sx = static_cast<double>(new_size.x()) / static_cast<double>(base_size.x());
	double Sy = static_cast<double>(new_size.y()) / static_cast<double>(base_size.y());
	if(keep_aspect_ratio) {
		Sx = Sy = std::min(Sx, Sy);
	}
	float Ty = Sy * base_size.y(); // смещение
	initT = Math::TranslationMatrix::translate(0.f, Ty) * Math::TranslationMatrix::scale(Sx, -Sy);
	reprepare_transforms_needle = false;
}

Math::Vec2 MainWindow::transform_point(Math::Vec2 point, Math::TranslationMatrix M) {
	Math::Vec3 homo(point, 1.0f);
	Math::Vec3 norm = M * homo;
	norm.z = 1;
	//std::cout << '(' << homo.x << ',' << homo.y << ',' << homo.z << ")\t->\t(" << norm.x << ',' << norm.y << ',' << norm.z << std::endl;
	Math::Vec2 result = norm.normalize();
	return result;
}

void MainWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

	if(reprepare_transforms_needle) {
		prepare_transforms(
			QPointF { picture->get_width(), picture->get_height() },
			QPointF { static_cast<double>(this->width()), static_cast<double>(this->height()) },
			QPointF { 0, 0}
		);
	}
	auto M = T * initT;
	//auto M = initT * T;

	// Настройка кисти и пера
	QPen pen(QColor(139, 0, 0), 2); // Красный цвет для линий
	painter.setPen(pen);
	painter.setBrush(Qt::NoBrush); // Без заливки, только контуры

	const QVector<Picture::Path> &paths = picture->get_paths();
	for(const Picture::Path& polyline : paths) {
		if(polyline.points.size() < 2) {
			continue;
		}
		QPointF new_point = transform_point(
			polyline.points.first(),
			M
		);
		QPainterPath path;
		path.moveTo(new_point);

		for(int i = 1; i < polyline.points.size(); ++i) {
			new_point = transform_point(
				polyline.points[i],
				M
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

