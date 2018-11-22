#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qfiledialog.h"
#include "shapelib/shapefil.h"
#include "qstring.h"

class DockWidget;
class ShapesView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateWhenDataChanged();
private slots:
    void openShapeFile();
    void closeAllFiles();
    void zoomOut();
    void zoomIn();
    void zoomAuto();
private:
    Ui::MainWindow *ui;
    ShapesView* _shapesView;
    DockWidget* _fileBar;

};

#endif // MAINWINDOW_H
