#pragma once
#include "picture.h"
#include "../math/vec.h"
#include <QVector>
#include <QXmlStreamReader>
#include <memory>

namespace Picture {
	struct PictureFabric {
		explicit PictureFabric(std::unique_ptr<Picture> pic) noexcept;
		PictureFabric() = delete;
		PictureFabric(const PictureFabric& f) = delete;
		void make_rabbit();
		void make_mouse();
		void clear();
		std::unique_ptr<Picture> get_picture();
	private:
		std::unique_ptr<QVector<Path>> parse_xml_file(QString path) const;
		std::unique_ptr<QVector<Path>> xml_parse_points(QXmlStreamReader& xml);
		std::unique_ptr<Picture> picture;
	};
}
