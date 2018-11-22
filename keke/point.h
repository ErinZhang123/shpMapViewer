#ifndef POINT_H
#define POINT_H
#

#include "zalshape.h"


namespace zal_shape
{
class Point : public Shape
{
public:
    Point(SHPHandle hShape);
    virtual void draw(QPainter* painter, QRectF geoRect,QRect screenRect);



    ~Point();


};
}

#endif // POINT_H
