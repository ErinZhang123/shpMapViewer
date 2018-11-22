#include "assistant.h"
#include "zalshapes.h"
using namespace zal_shape;

assistant::assistant(QRect rect):_scale(1)
{
    _screenRect=rect;
    _geoRect=zal_shape::Shapes::getGlobalData()->getGeoFullRect();
    double zoomX=_screenRect.width()/ _geoRect.width();
    double zoomY=_screenRect.height()/_geoRect.height();
    _zoom=zoomX<zoomY?zoomX:zoomY;
    _geoCenterX=(_geoRect.left()+_geoRect.right())/2;
    _geoCenterY=(_geoRect.top()+_geoRect.bottom())/2;
    _screenCenterX=(_screenRect.left()+_screenRect.right())/2;
    _screenCenterY=(_screenRect.top()+_screenRect.bottom())/2;
    _geoWidth=_geoRect.width();
    _geoHeight=_geoRect.height();


}
void assistant::updateWhenViewerChanged(QRect rect)
{
    _screenRect=rect;
     _geoRect=zal_shape::Shapes::getGlobalData()->getGeoFullRect();
     double zoomX=_screenRect.width()/ _geoRect.width();
     double zoomY=_screenRect.height()/_geoRect.height();
     _zoom=zoomX<zoomY?zoomX:zoomY;


    _geoWidth=rect.width()/_zoom;
    _geoHeight=rect.height()/_zoom;
    _geoCenterX=(_geoRect.left()+_geoRect.right())/2;
    _geoCenterY=(_geoRect.top()+_geoRect.bottom())/2;
    _screenCenterX=(_screenRect.left()+_screenRect.right())/2;
    _screenCenterY=(_screenRect.top()+_screenRect.bottom())/2;
    _geoRect.setLeft(_geoCenterX-_geoWidth/2);
    _geoRect.setRight(_geoCenterX+_geoWidth/2);
    _geoRect.setTop(_geoCenterY-_geoHeight/2);
    _geoRect.setBottom(_geoCenterY+_geoHeight/2 );

}
void assistant::updateZoomOut()
{
    _scale*=1.5;
    _geoWidth/=1.5;
    _geoHeight/=1.5;
    _geoRect.setLeft(_geoCenterX-_geoWidth/2);
    _geoRect.setRight(_geoCenterX+_geoWidth/2);
    _geoRect.setTop(_geoCenterY-_geoHeight/2);
    _geoRect.setBottom(_geoCenterY+_geoHeight/2);

}

void assistant::updateZoomIn()
{
    _scale/=1.5;
    _geoWidth*=1.5;
    _geoHeight*=1.5;
    _geoRect.setLeft(_geoCenterX-_geoWidth/2);
    _geoRect.setRight(_geoCenterX+_geoWidth/2);
    _geoRect.setTop(_geoCenterY-_geoHeight/2);
    _geoRect.setBottom(_geoCenterY+_geoHeight/2);

}
void assistant::updateZoomAuto()
{

    _geoWidth*=_scale;
    _geoHeight*=_scale;
    _geoRect.setLeft(_geoCenterX-_geoWidth/2);
    _geoRect.setRight(_geoCenterX+_geoWidth/2);
    _geoRect.setTop(_geoCenterY-_geoHeight/2);
    _geoRect.setBottom(_geoCenterY+_geoHeight/2);
    _scale=1;

}
