#include "esrishapefactory.h"
#include "point.h"
#include "polyline.h"
#include "polygon.h"
using namespace zal_shape;

AbstractShapeFactory* ESRIShapeFactory::_instance = nullptr;

AbstractShapeFactory* ESRIShapeFactory::getInstance(void)
{

    if(!_instance)
    {
        _instance = new ESRIShapeFactory;
    }
    return _instance;
}


Shape* ESRIShapeFactory::CreateShape(std::string path)
{
    //open an SHPHandle using SHPOpen
    SHPHandle hShape = SHPOpen(path.c_str(), "rb+");
    //then create a shape pointer based on the
    //SHP_TYPE of the SHPHandle
    std::string name = path;
    int i = name.find_last_of('\\');
    name = name.substr( i+1, name.length() - i -1);

    switch(hShape->nShapeType)
    {
    case SHPT_POINT || SHPT_POINTM:
    {
        Shape* shape = new Point(hShape);
        if (shape)
        {

            shape->setName(name);
        }
        return shape;
    }
    case SHPT_ARC:
    {
        Shape* shape = new Polyline(hShape);
        if (shape)
        {

            shape->setName(name);
        }
        return shape;
    }
    case SHPT_POLYGON:
    {

        Shape* shape = new Polygon(hShape);
        if (shape)
        {

            shape->setName(name);
        }
        return shape;
        return shape;
    }
    default:
        return nullptr;
    }
}

