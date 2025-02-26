#include "./picture.h"
#include <qcontainerfwd.h>

Picture::Picture(double width, double height, const QVector<Path> &paths) noexcept {
	this->paths = paths;
	this->width = width;
	this->height = height;
}

double Picture::get_height() const noexcept {
	return height;
}

double Picture::get_width() const noexcept {
	return width;
}

void Picture::set_width(double width) noexcept {
	this->width = width;
}


void Picture::set_height(double height) noexcept {
	this->height = height;
}

const QVector<Path>& Picture::get_paths() const {
	return paths;
}

void Picture::add_paths(const QVector<Path> &paths) noexcept {
	this->paths.append(paths.constBegin(), paths.constEnd());
}

void Picture::clear() noexcept {
	paths.clear();
}
