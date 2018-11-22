#ifndef SHAPE_H
#define SHAPE_H

#include "shapelib/shapefil.h"
#include <string>
#include <qpoint.h>
#include <qrect.h>
#include <qpen.h>
#include <QPainter>

namespace zal_shape
{
class assistant;
class shapePrivate;



class Shape
{
public:
    Shape();
    virtual ~Shape(void);
    virtual void draw(QPainter* , QRectF geoRect,QRect screenRect) = 0 ;
    std::string getName(void){return _name;}
    void setName(std::string name) {_name = name;}
    QRectF getGeoFullRect(){return _geoFullRect;}
    //const inline SHPHandle getHandle() const {return _hShape;}

    inline int getShapeType() {return _hShape->nShapeType;}

protected:

    void createFromHandle(SHPHandle hShape);

    QPoint geo2Screen(SHPObject* record, int verticeIndex,QRectF geoRect,QRect screenRect);

protected:

    SHPHandle _hShape;
    SHPTree* _tree;

    int* _recordsHit;
    int _countRecordsHit;

    std::string _name;
    QRectF _geoFullRect;

};








}



#endif // SHAPE_H
