#ifndef HESTIA_GL_FONT_H
#define HESTIA_GL_FONT_H

#include <memory>

#include <QMap>
#include <QString>

#include <FTGL/ftgl.h>

class FontRegistry
{
public:
    typedef std::shared_ptr<FontRegistry> Ptr;

    void installFont(const QString &name, const std::shared_ptr<FTFont> &font);
    std::shared_ptr<FTFont> font(const QString &name=QString());

    static Ptr create();

protected:
    QMap<QString, std::shared_ptr<FTFont>> fonts;

private:
    FontRegistry();

};

#endif // HESTIA_GL_FONT_H
