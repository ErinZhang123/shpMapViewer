#include "shapesview.h"
#include "ui_shapesview.h"

#include <QPainter>
#include "zalshapes.h"

ShapesView::ShapesView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapesView)
{
    ui->setupUi(this);


}

ShapesView::~ShapesView()
{
    delete ui;

}

void ShapesView::paintEvent(QPaintEvent *)
{

    QPainter *painter = new QPainter(this);
    painter->begin(this);
    painter->setRenderHint(QPainter::Antialiasing);

   _assistant->updateWhenViewerChanged(new QRect(0,0,this->width(),this->height()));


    /*
    paintingRect.setLeft(rect().width()/10);
    paintingRect.setTop(rect().height()/10);
    paintingRect.setWidth(rect().width()/2);
    paintingRect.setHeight(rect().height()/2);
    //*/
    //_shapes->drawAllShapes(painter, rect());

    if(getGlobalData())
        getGlobalData()->drawAll(painter, _assistant);

    painter->end();

}
