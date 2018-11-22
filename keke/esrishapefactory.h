#ifndef ESRISHAPEFACTORY_H
#define ESRISHAPEFACTORY_H

#include "abstractshapefactory.h"
#include "zalshape.h"

namespace zal_shape
{
class ESRIShapeFactory: public AbstractShapeFactory
{

public:
    ESRIShapeFactory(){}
    virtual ~ESRIShapeFactory(){}

    static AbstractShapeFactory* getInstance(void);

    virtual Shape* CreateShape(std::string path);


private:
    static AbstractShapeFactory* _instance;
};
}
#endif // ESRISHAPEFACTORY_H
