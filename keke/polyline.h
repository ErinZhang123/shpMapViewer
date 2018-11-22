#ifndef POLYLINE_H
#define POLYLINE_H


#include "zalshape.h"


namespace zal_shape
{
class Polyline: public Shape
{
public:
    Polyline(SHPHandle hShape);
    virtual void draw(QPainter* painter, QRectF geoRect,QRect screenRect);

    ~Polyline();


};
}

#endif // POLYLINE_H
