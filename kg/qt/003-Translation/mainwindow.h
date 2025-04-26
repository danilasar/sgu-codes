#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <mutex>
#include <QMainWindow>
#include <QBrush>
#include <QKeyEvent>
#include <QVector>
#include <QPointF>
#include "picture/picture.h"
#include "math/vec.h"
#include "math/translation_matrix.h"

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
	void resizeEvent(QResizeEvent *event) override;
	void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;

private:
	Ui::MainWindow *ui;
	std::unique_ptr<Picture::Picture> picture;
	mutable std::mutex picture_mutex;
	Math::TranslationMatrix T = Math::TranslationMatrix(1.f);
	Math::TranslationMatrix initT = Math::TranslationMatrix(1.f);
	bool keep_aspect_ratio = false;
	bool is_mouse = false;
	bool reprepare_transforms_needle = false;
	Math::Vec2 transform_point(Math::Vec2 point, Math::TranslationMatrix M);
	void prepare_transforms(QPointF base_size, QPointF new_size, QPointF new_position);
};
#endif // MAINWINDOW_H
