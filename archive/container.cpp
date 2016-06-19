#include "container.h"


template <class T, QIODevice::OpenModeFlag MODE=QIODevice::ReadOnly>
class AutoClose
{
public:
    AutoClose(T &file) :
        file(file)
    {
        this->file.open(MODE);
    }

    ~AutoClose()
    {
        this->file.close();
    }

    T &file;

};


Container::Container(const QString &filepath, QObject *parent) :
    QObject(parent),
    filepath(filepath)
{

}

Container::~Container()
{

}


FileContainer::FileContainer(const QString &filepath, QObject *parent) :
    Container(filepath, parent),
    file(filepath)
{

}

QByteArray FileContainer::content()
{
    AutoClose<QFile> ac(this->file);
    Q_UNUSED(ac);
    return this->file.readAll();
}


InMemoryContainer::InMemoryContainer(const QString &filepath, QObject *parent) :
    Container(filepath, parent),
    _content()
{

}


FileScenario::FileScenario(const QString &filepath, QObject *parent) :
    FileContainer(filepath, parent)
{

}

QString FileScenario::text()
{
    return QString::fromUtf8(this->content());
}


InMemoryScenario::InMemoryScenario(const QString &filepath, QObject *parent) :
    InMemoryContainer(filepath, parent)
{

}

QString InMemoryScenario::text()
{
    return QString::fromUtf8(this->_content);
}

void InMemoryScenario::setText(const QString &text)
{
    QString old = this->text();
    this->setContent(text.toUtf8());
    if ( old != text ) {
        emit this->changed(this->shared_from_this());
    }
}


FileImage::FileImage(const QString &filepath, QObject *parent) :
    FileContainer(filepath, parent)
{

}

QString getScenarioText(const std::shared_ptr<Container> &scenario)
{
    std::shared_ptr<FileScenario> file = std::dynamic_pointer_cast<FileScenario>(scenario);
    if ( file ) {
        return file->text();
    }

    std::shared_ptr<InMemoryScenario> inMemory = std::dynamic_pointer_cast<InMemoryScenario>(scenario);
    if ( inMemory ) {
        return inMemory->text();
    }

    return QString();
}
