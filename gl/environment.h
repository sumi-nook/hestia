#ifndef HESTIA_GL_ENVIRONMENT_H
#define HESTIA_GL_ENVIRONMENT_H

#include <memory>

#include <QString>
#include <QStringList>

class GlobalEnvironment
{
public:
    ~GlobalEnvironment();

    typedef std::shared_ptr<GlobalEnvironment> Ptr;

    static Ptr create();

    const QString vendor;
    const QString renderer;
    const QString version;
    const QStringList extensions;
    const int max_texture_size;

private:
    GlobalEnvironment();

};

#endif // HESTIA_GL_ENVIRONMENT_H
