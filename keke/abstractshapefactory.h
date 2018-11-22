#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H


#include "zalshape.h"
namespace zal_shape {
class AbstractShapeFactory
{
  public:
    virtual ~AbstractShapeFactory(){}
    virtual Shape* CreateShape(std::string path)=0;
protected:
    AbstractShapeFactory(){}//;?

};
}
#endif // SHAPEFACTORY_H
