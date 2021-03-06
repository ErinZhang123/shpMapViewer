#ifndef ZALSHAPES_H
#define ZALSHAPES_H


#include <vector>
#include <string>
#include <qpoint.h>
#include <qrect.h>
#include <qbrush.h>
#include <qpainter.h>
#include "esrishapefactory.h"

#include "zalshape.h"

//if include mainwindow "Shapes is not a type"
class MainWindow;


namespace zal_shape
{


class Shape;

class Shapes
{

public:

    Shapes(MainWindow* observer);
    bool addShape(Shape* pShape);
    bool addShape(std::string path);
    void removeShape(std::string path);
    QRectF getGeoFullRect(){return _geoFullRect;}
    void drawAll(QPainter* painter,assistant* assistant);
    void notify();
    Shape* at(int index) {return _objectList.at(index);}
    int size() {return _objectList.size();}
void clear();

static void initGlobalData(MainWindow* observer);
static zal_shape::Shapes* getGlobalData() ;
static void releaseGlobalData();
protected:
   void updateGeoFullRectAdd(Shape* pShape);

private:
static Shapes* _gData;
    std::vector<Shape*> _objectList;//vector<shared_ptr<Shape>>
    MainWindow* _observer;
    QRectF _geoFullRect;

};
}




#endif // ZALSHAPES_H
