#include "base.h"

DrawObject::~DrawObject()
{

}

Point2D::Point2D(int x, int y) :
    x(x),
    y(y)
{

}

Point3D::Point3D(int x, int y, int z) :
    x(x),
    y(y),
    z(z)
{

}

Rect::Rect(int x, int y, int w, int h) :
    x(x),
    y(y),
    w(w),
    h(h)
{

}
