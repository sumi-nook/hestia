#include "image.h"

#include <cmath>
#include <tuple>

#include <GL/gl.h>

#include <QImage>
#include <QPainter>
#include <QOpenGLTexture>


template <typename T>
int length(T n)
{
    int result = 0;
    while ( n != 0 ) {
        ++result;
        n >>= 1;
    }
    return result;
}

int power_of_two(int size, int maximum=-1)
{
    int max_size = std::pow(2, length(size));
    int min_size = max_size >> 1;
    int result = 0;
    if ( std::abs(max_size - size) < std::abs(size - min_size) ) {
        result = max_size;
    } else {
        result = min_size;
    }
    if ( maximum >= 0 ) {
        return std::min(result, maximum);
    }
    return result;
}

QImage pot_resize(const QImage &img, int maximum=-1)
{
    int w = img.width();
    int h = img.height();
    int base = power_of_two(std::max(w, h), maximum);
    double aspect;
    if ( w > h ) {
        aspect = double(h) / w;
        h = int(std::ceil(aspect * base));
        w = base;
    } else {
        aspect = double(w) / h;
        w = int(std::ceil(aspect * base));
        h = base;
    }
    return img.scaled(w, h, Qt::KeepAspectRatio, Qt::FastTransformation);
}

std::tuple<QImage, double, double> pot_square_resize(const QImage &img, int maximum=-1)
{
    QImage resized = pot_resize(img, maximum);
    int w = resized.width();
    int h = resized.height();
    int base = std::max(w, h);
    QImage new_img = QImage(base, base, img.format());
    new_img.fill(QColor(0, 0, 0));
    QPainter painter(&new_img);
    painter.drawImage(0, 0, resized);
    return std::make_tuple(new_img, double(w) / base, double(h) / base);
}


Image::Image(QOpenGLTexture *texture, double x, double y, int width, int height) :
    texture(texture),
    // mapping size
    x(x),
    y(y),
    // image size
    width(width),
    height(height),
    rect(-1, -1, 1, 1)
{

}

void Image::draw(const std::shared_ptr<DrawContext> &ctx)
{
    Q_UNUSED(ctx);
    glEnable(GL_TEXTURE_2D);

    this->texture->bind();

    glBegin(GL_QUADS);
    // left, top
    glTexCoord2d(1.0-this->x, 1.0-this->y);
    glVertex3d(this->rect.x, this->rect.y,  0.0);
    // left, bottom
    glTexCoord2d(1.0-this->x, 1.0);
    glVertex3d(this->rect.x, this->rect.h,  0.0);
    // right, bottom
    glTexCoord2d(1.0, 1.0);
    glVertex3d(this->rect.w, this->rect.h,  0.0);
    // right, top
    glTexCoord2d(1.0, 1.0-this->y);
    glVertex3d(this->rect.w, this->rect.y,  0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glFlush();
}

DrawObject::Ptr Image::create(QOpenGLTexture *texture, const QImage &image)
{
    QImage pot_img;
    double x, y;
    std::tie(pot_img, x, y) = pot_square_resize(image);
    int width = pot_img.width();
    int height = pot_img.height();

    texture->destroy();
    texture->create();
    texture->setData(pot_img.mirrored());
    return DrawObject::Ptr(new Image(texture, x, y, width, height));
}
