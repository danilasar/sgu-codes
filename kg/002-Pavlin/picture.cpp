#include "./picture.h"
#include <qcontainerfwd.h>

Picture::Picture(const QVector<Path> &paths) noexcept {
	this->paths = paths;
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
