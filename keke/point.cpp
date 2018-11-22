#include "point.h"
using namespace zal_shape;
Point::Point(SHPHandle hShape)
{

    createFromHandle(hShape);

}
void Point::draw(QPainter* painter, QRectF geoRect,QRect screenRect)
{
    QPen pen(QColor(255,0,0));
     pen.setWidth(2);
     painter->setPen(pen);
      double padfBoundsMin[2],padfBoundsMax[2];
     padfBoundsMin[0] = geoRect.left();//left
     padfBoundsMin[1] = geoRect.top();//top
     padfBoundsMax[0] = geoRect.right();//right
     padfBoundsMax[1] = geoRect.bottom();//bottom
     _recordsHit = SHPTreeFindLikelyShapes(_tree, padfBoundsMin, padfBoundsMax,&_countRecordsHit );

    //begin drawing
    for(int i=0; i<_countRecordsHit;i++)
    {
        SHPObject * oSHP = SHPReadObject(_hShape,_recordsHit[i]);//Get current object

        QPoint pt;
        pt=geo2Screen(oSHP,0,geoRect,screenRect);

        int nHalfSize = 2;

        painter->drawRect(
            pt.x() - nHalfSize,
            pt.y() - nHalfSize,
            nHalfSize*2 +1,
            nHalfSize*2 +1);

        SHPDestroyObject(oSHP);
    }

    if(_recordsHit != NULL)
    {
        delete[] _recordsHit;
        _recordsHit = NULL;
        _countRecordsHit = -1;
    }
}
Point::~Point(){}
