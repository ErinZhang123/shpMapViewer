#include "zalshape.h"
#include "qpoint.h"


using namespace zal_shape;

namespace zal_shape {
class shapePrivate{
    
    friend class Shape;
    friend class Point;
    friend class Polyline;
    friend class Polygon;
private:
    
    
    SHPHandle _hShape;
    SHPTree* _tree;

    int* _recordsHit;
    int _countRecordsHit;

    std::string _name;
    QRectF _geoFullRect;
    
    
};

}

Shape::Shape(void):
    _hShape(NULL),
    _recordsHit(NULL),
    _countRecordsHit(-1),
    _name("Unknown")

{
_geoFullRect=*(new QRectF(0,0,0,0));
}


Shape::~Shape(void)
{
    if(_tree)
        SHPDestroyTree(_tree);

    if(_hShape)
    {
        SHPClose(_hShape);
        _hShape = NULL;
    }

    if(_recordsHit != NULL)
    {
        delete[] _recordsHit;
        _recordsHit = NULL;
        _countRecordsHit = -1;
    }
}


//void Shape::computeRangeHit(double pdfRangeHit[4], QRect rcDest, double geoOffsetX, double geoOffsetY)
//{
//    //left
//    pdfRangeHit[0] = geoOffsetX;
//    //top
//    pdfRangeHit[1] = geoOffsetY;
//    //right
//    pdfRangeHit[2] = pdfRangeHit[0] + rcDest.width()/ _zoom;
//    //bottom
//    pdfRangeHit[3] = pdfRangeHit[1] + rcDest.height()/_zoom;

//    for (int i=0; i<4; i++)
//    {
//        pdfRangeHit[i] /= _preZoomFactor;
//    }
//}


//void Shape::computeRecordHit(QRect rcDest, double geoOffsetX, double geoOffsetY,bool usingShxTree)
//{
//    if(!_hShape )
//        return;

//    if (!usingShxTree)
//    {
//        return;
//    }
//    else
//    {
//        //Compute geo range Hit
//        double pdfRangeHit[4];
//        computeRangeHit(pdfRangeHit, rcDest, geoOffsetX, geoOffsetY);

//        //Select the record in the range of rcDevice
//        double padfBoundsMin[4];
//        double padfBoundsMax[4];

//        padfBoundsMin[0] = pdfRangeHit[0];//left
//        padfBoundsMin[1] = pdfRangeHit[1];//top
//        padfBoundsMax[0] = pdfRangeHit[2];//right
//        padfBoundsMax[1] = pdfRangeHit[3];//bottom

//        _recordsHit = SHPTreeFindLikelyShapes(_tree, padfBoundsMin, padfBoundsMax,&_countRecordsHit );
//    }


//}

QPoint Shape::geo2Screen(SHPObject* record, int verticeIndex,QRectF geoRect,QRect screenRect)

    {
        double  geoRectCentralX=geoRect.x()+geoRect.width()/2;
        double geoRectCentralY=geoRect.y()+geoRect.height()/2;
        double zoom;
        double zoomX=screenRect.width()/ geoRect.width();
        double zoomY=screenRect.height()/geoRect.height();
        zoom=zoomX<zoomY?zoomX:zoomY;

        double offsetFromOriginX=(record->padfX[verticeIndex]- geoRectCentralX)* zoom;
        double offsetFromOriginY=(record->padfY[verticeIndex]- geoRectCentralY) * zoom;

        int screenCentralX = screenRect.width()/2;
        int screenCentralY = screenRect.height()/2;

        double X = screenCentralX + offsetFromOriginX;
        double Y = screenCentralY -offsetFromOriginY;

        return QPoint(X,Y);
    }



void Shape::createFromHandle(SHPHandle hShape)
{
    _hShape = hShape;
    if(!_hShape)
        return ;

   _geoFullRect.setTop(_hShape->adBoundsMin[1]);
   _geoFullRect.setLeft(_hShape->adBoundsMin[0]);
   _geoFullRect.setBottom(_hShape->adBoundsMax[1]);
   _geoFullRect.setRight(_hShape->adBoundsMax[0]);

    _tree = SHPCreateTree( _hShape, 2,10, NULL, NULL );
    SHPTreeTrimExtraNodes( _tree );
}
