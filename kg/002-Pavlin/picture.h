#pragma once
#include <QVector>
#include <QPointF>
#include <QColor>

struct Path {
	QVector<QPointF> points;
	bool isClosed = false;
	QColor fillColor = Qt::transparent;
	QColor strokeColor = Qt::darkBlue;
	qreal strokeWidth = 2.0;
};

struct Picture {
	explicit Picture(double width, double height, const QVector<Path> &paths) noexcept;
	Picture() noexcept = default;
	Picture(const Picture& pic) noexcept = default;
	const QVector<Path>& get_paths() const;
	void add_paths(const QVector<Path> &paths) noexcept;
	void clear() noexcept;
	double get_width() const noexcept;
	double get_height() const noexcept;
	void set_width(double width) noexcept;
	void set_height(double height) noexcept;
private:
	double width;
	double height;
	QVector<Path> paths;
};
