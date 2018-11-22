#ifndef ASSISTANT_H
#define ASSISTANT_H
#include "qpoint.h"
#include "shapelib/shapefil.h"
#include "qrect.h"



namespace  zal_shape {

class Shapes;

class assistant
{
public:
    assistant(QRect rect);
    QRectF getGeoRect(){return _geoRect;}
    QRect getscreenRect(){return _screenRect;}
    //double getZoom(){return _zoom;}
   // double getGeoZoom(){return _geoZoom;}
    void updateZoomIn();
    void updateZoomOut();
    void updateWhenViewerChanged(QRect rect);
    void updateZoomAuto();

private:
    QRectF _geoRect;
    QRect _screenRect;

    double _zoom;
    double _scale;
    double _screenCenterX;
    double _screenCenterY;
//    double _screenWidth;
//    double _screenHeight;
    double _geoCenterX;
    double _geoCenterY;
    double _geoWidth;
    double _geoHeight;
//    double _geoOffsetX;
//    double _geoOffsetY;
//    double _screenOffsetX;
//    double _screenOffsetY;
};
}


#endif // ASSISTANT_H
