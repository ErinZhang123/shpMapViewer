#include "ShapesView.h"
#include "ui_ShapesView.h"
#include <QMouseEvent>
#include <QPainter>
#include "zalshapes.h"
#include "assistant.h"
ShapesView::ShapesView(QWidget *parent) :
    QWidget(parent),
    _pMain(NULL),
    _pMove(NULL),
//    _pan(false),_mouse_moving(false),_mouse_left_pressed(false),
    ui(new Ui::ShapesView)
{
    ui->setupUi(this);
   _assistant=new zal_shape::assistant(this->rect());

}

ShapesView::~ShapesView()
{
    delete ui;

}
 void ShapesView::updateWhenDataChanged()
 {
     _assistant->updateWhenViewerChanged(*(new QRect(0,0,this->width(),this->height())));
     update();
 }

void ShapesView::paintEvent(QPaintEvent *)
{
if(zal_shape::Shapes::getGlobalData()->size()>0)
{
    QPainter *painter = new QPainter(this);
    painter->begin(this);
    painter->setRenderHint(QPainter::Antialiasing);


   if(_pMain) delete(_pMain);
   _pMain=new QPixmap(this->size());
   QPainter local_painter(_pMain);

   flushBkg(&local_painter);
    /*
    paintingRect.setLeft(rect().width()/10);
    paintingRect.setTop(rect().height()/10);
    paintingRect.setWidth(rect().width()/2);
    paintingRect.setHeight(rect().height()/2);
    //*/
    //_shapes->drawAllShapes(painter, rect());


        zal_shape::Shapes::getGlobalData()->drawAll(&local_painter, _assistant);

   painter->drawPixmap(0,0,this->width(),this->height(),*_pMain,0,0,this->width(),this->height());

    painter->end();
}
}


void ShapesView::updateZoomOut()
{
    _assistant->updateZoomOut();
    update();
}
void ShapesView::updateZoomIn()
{
    _assistant->updateZoomIn();
    update();
}
void ShapesView::updateZoomAuto()
{
    _assistant->updateZoomAuto();
    update();
}
void ShapesView::flushBkg(QPainter* painter)
{
    QBrush _bkgBrush=*(new  QBrush(Qt::white, Qt::SolidPattern));
    painter->fillRect(this->rect(),_bkgBrush);
}

//void ShapesView::mousePressEvent(QMouseEvent *event)
//{
//    if(event->button()==Qt::LeftButton)
//    {
//        if(_pan)
//        {
//            //ui.lineEdit->setText(tr("鼠标左键按下:")+str);
//            _ref_mouse_point.setX(event->x());
//            _ref_mouse_point.setY(event->y());
//            _mouse_left_pressed = true;
//        }
//    }
//    else if(event->button()==Qt::RightButton)
//    {
//         //ui.lineEdit->setText(tr("鼠标右键按下:")+str);
//    }
//    else if(event->button()==Qt::MidButton)
//    {
//        // ui.lineEdit->setText(tr("鼠标中键按下:")+str);
//    }
//}
