#include "environment.h"

#include <QRegularExpression>

#include <GL/gl.h>

inline const char *getString(GLenum name)
{
    return reinterpret_cast<const char *>(glGetString(name));
}

int getInteger(GLenum name)
{
    int temp;
    glGetIntegerv(name, &temp);
    return temp;
}

GlobalEnvironment::GlobalEnvironment() :
    vendor(getString(GL_VENDOR)),
    renderer(getString(GL_RENDERER)),
    version(getString(GL_VERSION)),
    extensions(QString(getString(GL_EXTENSIONS)).split(QRegularExpression("\\s"))),
    max_texture_size(getInteger(GL_MAX_TEXTURE_SIZE))
{

}

GlobalEnvironment::~GlobalEnvironment()
{

}

GlobalEnvironment::Ptr GlobalEnvironment::create()
{
    return GlobalEnvironment::Ptr(new GlobalEnvironment);
}
