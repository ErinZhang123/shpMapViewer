#ifndef POLYGON_H
#define POLYGON_H


#include "zalshape.h"

namespace zal_shape {
class Polygon:public Shape
{
public:
    Polygon(SHPHandle hShape);
    virtual void draw(QPainter* painter, QRectF geoRect,QRect screenRect);

    ~Polygon();


};
}
#endif // POLYGON_H
