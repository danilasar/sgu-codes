#pragma once
#include "picture.h"
#include <QVector>
#include <memory>

struct PictureFabric {
	explicit PictureFabric(std::unique_ptr<Picture> pic) noexcept;
	PictureFabric() = delete;
	PictureFabric(const PictureFabric& f) = delete;
	void make_rabbit();
	void make_mouse();
	std::unique_ptr<Picture> get_picture();
private:
	std::unique_ptr<QVector<Path>> parse_xml_file(QString path) const;
	std::unique_ptr<Picture> picture;
};
