#include "polyline.h"
using namespace zal_shape;

Polyline::Polyline(SHPHandle hShape)
{
    createFromHandle(hShape);

}

void Polyline::draw(QPainter* painter, QRectF geoRect,QRect screenRect)
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

     for(int i=0; i<_countRecordsHit;i++)
        {
        SHPObject * oSHP = SHPReadObject(_hShape,_recordsHit[i]);//Get current object

            if(oSHP->nParts==1)//count of parts is 1
            {
                QVector<QPoint> vertices;
                for(int k=oSHP->panPartStart[0]; k<oSHP->nVertices; k++)
                {
                    QPoint pt;
                 pt=geo2Screen(oSHP,k,geoRect,screenRect);
                vertices.append(pt);
                }
                painter->drawPolyline(QPolygon(vertices));
            }
            else//count of parts is more than 1
            {
                for(int j=0; j<oSHP->nParts-1; j++)//����part��record����
                {
                    QVector<QPoint> vertices;
                    for(int k=oSHP->panPartStart[j]; k<oSHP->panPartStart[j+1]; k++)
                    {
                        QPoint pt;
                        pt=geo2Screen(oSHP,k,geoRect,screenRect);
                        vertices.append(pt);
                    }
                    painter->drawPolyline(QPolygon(vertices));
                }

                QVector<QPoint> vertices;
                for(int k=oSHP->panPartStart[oSHP->nParts-1]; k<oSHP->nVertices; k++)
                {
                    QPoint pt;
                    pt=geo2Screen(oSHP,k,geoRect,screenRect);
                    vertices.append(pt);
                }
                painter->drawPolyline(QPolygon(vertices));
            }

            SHPDestroyObject(oSHP);
        }

        if(_recordsHit)
        {
            delete[] _recordsHit;
            _recordsHit = NULL;
            _countRecordsHit = -1;
        }
    //}

}
Polyline::~Polyline()
{}

