#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBrush>
#include <QVector>
#include <QPointF>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct PolylineData {
	QVector<QPointF> points;
	bool isClosed = false;
	QColor fillColor = Qt::transparent;
	QColor strokeColor = Qt::darkBlue;
	qreal strokeWidth = 2.0;
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void loadFromFile(const QString& fileName);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	Ui::MainWindow *ui;
	QVector<PolylineData> m_polylines;
};
#endif // MAINWINDOW_H
