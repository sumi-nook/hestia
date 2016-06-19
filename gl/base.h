#ifndef HESTIA_GL_BASE_H
#define HESTIA_GL_BASE_H

#include <functional>
#include <memory>

class DrawContext;


class DrawObject
{
public:
    typedef std::shared_ptr<DrawObject> Ptr;

    virtual ~DrawObject();

    virtual void draw(const std::shared_ptr<DrawContext> &ctx) = 0;

};


class FunctionObject : public DrawObject
{
public:
    typedef std::function<void(const std::shared_ptr<DrawContext> &)> Function;

    ~FunctionObject()
    {

    }

    void draw(const std::shared_ptr<DrawContext> &ctx)
    {
        this->func(ctx);
    }

    static DrawObject::Ptr create(const Function &func)
    {
        return DrawObject::Ptr(new FunctionObject(func));
    }

protected:
    FunctionObject(const Function &func) :
        func(func)
    {

    }

    Function func;

};


class Point2D
{
public:
    Point2D(int x, int y);

    int x;
    int y;
};


class Point3D
{
public:
    Point3D(int x, int y, int z);

    int x;
    int y;
    int z;
};


class Rect
{
public:
    Rect(int x, int y, int w, int h);

    int x;
    int y;
    int w;
    int h;
};

#endif // HESTIA_GL_BASE_H

