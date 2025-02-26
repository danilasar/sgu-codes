#include "picture_fabric.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <QFile>
#include <QXmlStreamReader>
#include <stdexcept>
#include <system_error>


PictureFabric::PictureFabric(std::unique_ptr<Picture> pic) noexcept {
	picture = std::move(pic);
}

std::unique_ptr<Picture> PictureFabric::get_picture() {
	return std::move(picture);
}

void PictureFabric::make_rabbit() {
	auto data = parse_xml_file("rabbit.xml");
	if(data) {
		const QVector<Path> &paths = *data;
		this->picture->add_paths(paths);
	}
}

void PictureFabric::make_mouse() {
	auto data = parse_xml_file("mouse.xml");
	if(data) {
		const QVector<Path> &paths = *data;
		this->picture->add_paths(paths);
	}
}

std::unique_ptr<QVector<Path>> PictureFabric::parse_xml_file(QString path) const {
	QVector<Path> *paths = new QVector<Path>();
	paths->clear();

	QFile file(path);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		throw std::filesystem::filesystem_error(
			"Не могу открыть файл",
			std::filesystem::path(path.toStdString()),
			std::error_code()
		);
	}

	QXmlStreamReader xml(&file);
	Path current_path;

	while(!xml.atEnd() && !xml.hasError()) {
		QXmlStreamReader::TokenType token = xml.readNext();

		if(token == QXmlStreamReader::StartElement) {
			if(xml.name() == "Picture") {
				bool wok = true, hok = true;
				try {
					this->picture->set_width(xml.attributes().value("width").toDouble(&wok));
				} catch(...) { wok = false; }
				try {
					this->picture->set_height(xml.attributes().value("height").toDouble(&hok));
				} catch(...) { hok = false; }
				if(!(wok && hok)) {
					std::cerr << "Неверные размеры изображения" << std::endl;
				}
			} else if(xml.name() == "Path") {
				current_path = Path();
				current_path.isClosed = xml.attributes().value("closed") == "true";

				QXmlStreamAttributes attrs = xml.attributes();
				if(attrs.hasAttribute("fill")) {
					try {
						current_path.fillColor = QColor(attrs.value("fill").toString());
					} catch(...) {
						std::cerr << "Неверный цвет фона у одного из контуров" << std::endl;
					}
				}

				if(attrs.hasAttribute("stroke")) {
					try {
						current_path.strokeColor = QColor(attrs.value("stroke").toString());
					} catch(...) {
						std::cerr << "Неверный цвет обрамления одного из контуров" << std::endl;
					}
				}

				if(attrs.hasAttribute("stroke-width")) {
					try {
						current_path.strokeWidth = attrs.value("stroke-width").toDouble();
					} catch(...) {
						std::cerr << "Неверная толщина контура" << std::endl;
					}
				}
			} else if(xml.name() == "Point") {
				bool okX, okY;
				float x = xml.attributes().value("x").toFloat(&okX);
				float y = xml.attributes().value("y").toFloat(&okY);

				if(okX && okY) {
					current_path.points.append(QPointF(x, y));
				}
			}
		} else if(token == QXmlStreamReader::EndElement) {
			if(xml.name() == "Path") {
				if(current_path.points.size() > 1) {
					paths->append(current_path);
				}
			}
		}
	}
	if(xml.hasError()) {
		throw std::runtime_error(xml.errorString().toStdString());
	}
	return std::unique_ptr<QVector<Path>>(paths);
}
