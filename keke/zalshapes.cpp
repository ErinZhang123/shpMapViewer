#include "zalshapes.h"
#include "zalshape.h"
#include <iterator>
#include "assistant.h"
#include "mainwindow.h"

using namespace zal_shape;

Shapes* Shapes::_gData = NULL;

void Shapes::initGlobalData(MainWindow* observer)
{
    _gData = new Shapes(observer);
}

Shapes* Shapes::getGlobalData()
{
    return _gData;
}

void Shapes::releaseGlobalData()
{
    if (_gData)
        delete _gData;
}


Shapes::Shapes(MainWindow* observer):  
    _observer(observer)
{
    _objectList.clear();
    _geoFullRect=*(new QRectF(0,0,0,0));
}
bool Shapes::addShape(Shape* pShape)
{
    if(!pShape)return false;
    else
    {
         std::vector<Shape*>::iterator itr;
        for (itr = _objectList.begin(); itr!= _objectList.end(); itr++)
        {
            if ((*itr)->getName() == pShape->getName())
            {
                delete pShape;
                return true;
            }
        }

        _objectList.push_back(pShape);
        updateGeoFullRectAdd(pShape);
        //		AutoZoom(pShape->GetName());

    }
    notify();
    return true;
}

bool Shapes::addShape(std::string path)
{
    Shape* pShape =
            ESRIShapeFactory::getInstance()->
            CreateShape(path);

    if(!pShape)
        return false;

        _objectList.push_back(pShape);

        //itr = _objectList.begin();
        //_geoOffsetX = (*itr)->GetRcSource().left + 2000 / m_dfZoom;
        //m_dfGeoOffsetY = (*itr)->GetRcSource().top - 100 / m_dfZoom;



        updateGeoFullRectAdd(pShape);



    notify();
    return true;

}

void Shapes::removeShape(std::string name)
{
    std::vector<Shape*>::iterator itr;

    for(itr = _objectList.begin(); itr<_objectList.end(); itr++)
    {
        std::string objName = (*itr)->getName();
        if(objName == name)
        {
            _objectList.erase(itr);


            break;
        }
    }
notify();
}
void Shapes::clear()
{
    _objectList.clear();
    notify();
}
//void Shapes::update(QRect rcDest)
//{
//    _rcDest = rcDest;
//    _redrawAll = true;

//    if(_bmpMain)
//        delete _bmpMain;
//    _bmpMain= new QPixmap( QSize( _rcDest.width(), _rcDest.height() ) );

//    if(_bmpMove)
//        delete _bmpMove;
//    _bmpMove= new QPixmap( QSize( _rcDest.width(), _rcDest.height() ) );
//    notify();
//}



void Shapes::drawAll(QPainter* painter,assistant* _assistant)
{
    if(!_objectList.empty())
    {
        QRectF geoRect=_assistant->getGeoRect();
        QRect screenRect=_assistant->getscreenRect();
        std::vector<Shape*>::iterator itr;
            for(itr = _objectList.begin(); itr!=_objectList.end(); itr++)
            {
                (*itr)->draw(painter,geoRect,screenRect);
            }





    }
}
void Shapes::updateGeoFullRectAdd(Shape* pShape)
{
    QRectF rect=pShape->getGeoFullRect();
    if(_geoFullRect.top()==0&&_geoFullRect.left()==0&&_geoFullRect.right()==0&&_geoFullRect.bottom()==0)
    _geoFullRect=rect;
    else
    {
    if(rect.top()<_geoFullRect.top())_geoFullRect.setTop(rect.top());
    if(rect.left()<_geoFullRect.left())_geoFullRect.setLeft(rect.left());
    if(rect.right()>_geoFullRect.right())_geoFullRect.setRight(rect.right());
    if(rect.bottom()>_geoFullRect.bottom())_geoFullRect.setBottom(rect.bottom());

     }
}



void Shapes::notify()
{
    _observer->updateWhenDataChanged();
}



//void Shapes::renderMove(QPainter* painter,int nOffsetX, int nOffsetY)
//{
//    int nStatus;//状态变量

//    //******************************************************************************************************************//
//    //绘图过程分为两个部分，移动后的目标DC区域分为新视图(阴影部分)，横向补丁和纵向补丁。										//
//    //新视图为旧的DC拖动后遗留在当前目标DC上的部分，该部分不必重绘，先BitBlt到Move DC。										//
//    //然后BitBlt到目标DC即可。横向补丁和纵向补丁为拖动后进入当前目标DC的新的区域，该区域										//
//    //需要重绘。新视图和两个补丁的分布有四中情况，如下图所示。																//
//    //																													//
//    //	1: nOffsetX>0; nOffsetY>0.	2: nOffsetX<0; nOffsetY<0. 3: nOffsetX>0; nOffsetY<0.  4: nOffsetX<0; nOffsetY>0	//
//    //	________________________	________________________	________________________	________________________	//
//    //	|///////////////|		|	|		|横向补丁		|	| 横向补丁		|		|	|		|///////////////|	//
//    //	|// 新视图//////|纵向	|	| 纵向	|_______________|	|_______________|纵向	|	| 纵向 	|///新视图//////|	//
//    //	|///////////////|		|	|		|///////////////|	|///////////////|补丁	|	| 补丁	|///////////////|	//
//    //	|///////////////|补丁	|	| 补丁	|///////////////|	|///////////////|		|	|		|///////////////|	//
//    //	| 横向补丁		|		|	|		|/// 新视图/////|	|///新视图//////|		|	|		|	横向补丁		|	//
//    //	|_______________|_______|	|_______|///////////////|	|///////////////|_______|	|_______|_______________|	//
//    //																													//
//    //******************************************************************************************************************//

//    ////////状态设定//////
//    if (nOffsetX >=0 &&  nOffsetY >= 0)
//        nStatus = 0;

//    if (nOffsetX <=0 &&  nOffsetY <= 0)
//        nStatus = 1;

//    if (nOffsetX >=0 &&  nOffsetY <= 0)
//        nStatus = 2;

//    if (nOffsetX <=0 &&  nOffsetY >= 0)
//        nStatus = 3;

//    ////////绘制目标DC/////////

//    if (_drawPatch)
//    {//鼠标左键未放开，只绘制新视图，不绘制补丁，Main DC不进行更新

//        QPainter movePainter(_bmpMove);

//        //绘制Move DC背景
//        movePainter.fillRect(_rcDest, _bkgBrush);

//        //从Main DC 截取相应内容并复制到Move DC的新视图区域
//        movePainter.drawPixmap(0,0,_rcDest.width(), _rcDest.height(), *_bmpMain,
//                               nOffsetX, nOffsetY, _rcDest.width(), _rcDest.height());

//        //复制全部Move DC到目标DC
//        painter->drawPixmap(0,0,_rcDest.width(),_rcDest.height(),*_bmpMove,0,0,_rcDest.width(),_rcDest.height());
//    }
//    else
//    {//鼠标左键松开，绘制补丁，Main DC进行更新

//        QPainter mainPainter(_bmpMain);

//        //将Move DC 复制到Main DC
//        mainPainter.drawPixmap(0,0,_rcDest.width(),_rcDest.height(),*_bmpMove,0,0,_rcDest.width(),_rcDest.height());

//        //绘制补丁只需提供补丁地理偏移量（偏移量为补丁区域左下角地理坐标）和补丁尺寸。

//        QPoint ptPatch;	//当前绘制补丁的左上角点
//        QSize szPatch;	//当前绘制补丁的尺寸
//        QRect rcPatch;	//当前绘制补丁的区域

//        double dfPatchGeoOffsetX;	//当前绘制补丁对应的地理偏移量
//        double dfPatchGeoOffsetY;

//        //////////绘制纵向补丁//////////
//        szPatch = QSize(abs(nOffsetX), _rcDest.height());

//        switch(nStatus)
//        {
//        case 0:
//            ptPatch.setX( _rcDest.width() - abs(nOffsetX));
//            ptPatch.setY( 0 );
//            dfPatchGeoOffsetX = _geoOffsetX + _rcDest.width() / _zoom;
//            dfPatchGeoOffsetY = _geoOffsetY - abs(nOffsetY) / _zoom;
//            break;

//        case 1:
//            dfPatchGeoOffsetX = _geoOffsetX - abs(nOffsetX) / _zoom;
//            dfPatchGeoOffsetY = _geoOffsetY + abs(nOffsetY) / _zoom;
//            ptPatch.setX( 0 );
//            ptPatch.setY( 0 );
//            break;

//        case 2:
//            dfPatchGeoOffsetX = _geoOffsetX + _rcDest.width() / _zoom;
//            dfPatchGeoOffsetY = _geoOffsetY + abs(nOffsetY) / _zoom;
//            ptPatch.setX( _rcDest.width() - abs(nOffsetX) );
//            ptPatch.setY( 0 );
//            break;

//        case 3:
//            dfPatchGeoOffsetX = _geoOffsetX - abs(nOffsetX) / _zoom;
//            dfPatchGeoOffsetY = _geoOffsetY - abs(nOffsetY) / _zoom;
//            ptPatch.setX( 0);
//            ptPatch.setY( 0);
//            break;
//        }

//        rcPatch = QRect(ptPatch,szPatch);

//        pastePatch(rcPatch, &mainPainter, dfPatchGeoOffsetX, dfPatchGeoOffsetY);

//        //////////绘制横向补丁//////////
//        szPatch = QSize(_rcDest.width() - abs(nOffsetX), abs(nOffsetY));

//        switch(nStatus)
//        {
//        case 0:
//            ptPatch.setX ( 0);
//            ptPatch.setY( _rcDest.height() - abs(nOffsetY) );
//            dfPatchGeoOffsetX = _geoOffsetX + abs(nOffsetX) / _zoom;
//            dfPatchGeoOffsetY = _geoOffsetY - abs(nOffsetY) / _zoom;
//            break;

//        case 1:
//            dfPatchGeoOffsetX = _geoOffsetX ;
//            dfPatchGeoOffsetY = _geoOffsetY + _rcDest.height() / _zoom;
//            ptPatch.setX( abs(nOffsetX) );
//            ptPatch.setY( 0 );

//            break;

//        case 2:
//            dfPatchGeoOffsetX = _geoOffsetX + abs(nOffsetX) / _zoom;
//            dfPatchGeoOffsetY = _geoOffsetY + _rcDest.height() / _zoom;
//            ptPatch.setX( 0);
//            ptPatch.setY( 0);
//            break;

//        case 3:
//            dfPatchGeoOffsetX = _geoOffsetX;
//            dfPatchGeoOffsetY = _geoOffsetY - abs(nOffsetY) / _zoom;
//            ptPatch.setX( abs(nOffsetX) );
//            ptPatch.setY( _rcDest.height() - abs(nOffsetY) );
//            break;
//        }

//        rcPatch = QRect(ptPatch,szPatch);

//        pastePatch(rcPatch, &mainPainter, dfPatchGeoOffsetX, dfPatchGeoOffsetY);

//        /////////////更新偏移量/////////////////
//        switch(nStatus)
//        {
//        case 0:
//            _geoOffsetX += abs(nOffsetX) / _zoom;
//            _geoOffsetY -= abs(nOffsetY) / _zoom;
//            break;

//        case 1:
//            _geoOffsetX -= abs(nOffsetX) / _zoom;
//            _geoOffsetY += abs(nOffsetY) / _zoom;
//            break;

//        case 2:
//            _geoOffsetX += abs(nOffsetX) / _zoom;
//            _geoOffsetY += abs(nOffsetY) / _zoom;
//            break;

//        case 3:
//            _geoOffsetX -= abs(nOffsetX) / _zoom;
//            _geoOffsetY -= abs(nOffsetY) / _zoom;
//            break;
//        }

//        ////////////更新目标DC///////////////////
//        painter->drawPixmap(0, 0, _rcDest.width(), _rcDest.height(), *_bmpMain, 0,0,_rcDest.width(),_rcDest.height());
//        _drawPatch = false;
//    }
//}

//void Shapes::pastePatch(QRect rcPatch, QPainter* pDstPainter,double dfOffsetX, double dfOffsetY)
//{
//    QPixmap bmpPatch( QSize(rcPatch.width(), rcPatch.height()) );
//    QPainter patchPainter(&bmpPatch);
//    patchPainter.fillRect(QRect(QPoint(0,0),QSize(rcPatch.width(),rcPatch.height())),_bkgBrush);

//    std::vector<Shape*>::iterator itr;

//    for(itr = _objectList.begin(); itr!=_objectList.end(); itr++)
//    {
//        (*itr)->draw(&patchPainter, QRect(QPoint(0,0),QSize(rcPatch.width(),rcPatch.height())), dfOffsetX, dfOffsetY) ;
//    }

//    pDstPainter->drawPixmap(rcPatch.left(), rcPatch.top(), rcPatch.width(), rcPatch.height(),bmpPatch, 0, 0,0,0);
//}

