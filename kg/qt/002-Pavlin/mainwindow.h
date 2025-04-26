#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBrush>
#include <QKeyEvent>
#include <QVector>
#include <QPointF>
#include "picture.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void loadFromFile(const QString& fileName);

protected:
	void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;

private:
	Ui::MainWindow *ui;
	std::unique_ptr<Picture> picture;
	bool keep_aspect_ratio = false;
	bool is_mouse = false;
	QPointF transform_point(QPointF point, QPointF base_size, QPointF new_size, QPointF new_position) const;
};
#endif // MAINWINDOW_H
