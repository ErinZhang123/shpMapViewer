#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shapelib/shapefil.h"
#include <QFileDialog>
#include <QPainter>

#include <QMessageBox>
#include "ShapesView.h"
#include "zalshapes.h"
#include "DockWidget.h"
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionopen,SIGNAL(triggered(bool)),this,SLOT(openShapeFile()));
  zal_shape::Shapes::initGlobalData(this);

  connect(ui->actionzoomOut,SIGNAL(triggered(bool)),this,SLOT(zoomOut()));
  connect(ui->actionzoomIn,SIGNAL(triggered(bool)),this,SLOT(zoomIn()));
  connect(ui->actionzoomAuto,SIGNAL(triggered(bool)),this,SLOT(zoomAuto()));


    _fileBar = new DockWidget(this);
     _fileBar->setMaximumWidth(300);
    this->addDockWidget(Qt::LeftDockWidgetArea, _fileBar, Qt::Vertical);

     _shapesView = new ShapesView(this);
     this->setCentralWidget(_shapesView);



     this->show();
}

void MainWindow::openShapeFile()
{
    QFileDialog dialog(this,tr("Open File"),"", tr("*.shp"));
    dialog.setFileMode(QFileDialog::ExistingFiles);

    QStringList pathList;
    if(dialog.exec())
        pathList = dialog.selectedFiles();
    else
        return;

    for(int i=0; i<pathList.size(); i++)
    {
        QFileInfo fi(pathList.at(i));

        if(!fi.isFile())
            continue;

        zal_shape::Shapes::getGlobalData()->addShape(fi.filePath().toStdString());

    }

}

void MainWindow::closeAllFiles()
{
    zal_shape::Shapes::getGlobalData()->clear();

}

MainWindow::~MainWindow()
{
    delete ui;

    if( zal_shape::Shapes::getGlobalData())
        zal_shape::Shapes::releaseGlobalData();

}

void MainWindow::updateWhenDataChanged()
{
    update();
    this->_shapesView->updateWhenDataChanged();
    this->_fileBar->updateListview();
}

void MainWindow:: zoomOut()
{
    this->_shapesView->updateZoomOut();
}

void MainWindow:: zoomIn()
{
    this->_shapesView->updateZoomIn();
}

void MainWindow:: zoomAuto()
{
    this->_shapesView->updateZoomAuto();
}
