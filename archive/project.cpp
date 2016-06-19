#include "project.h"

#include <QDir>


QStringList walk(const QString &dirname)
{
    QStringList result;

    QDir dir(dirname);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::NoDot | QDir::NoDotDot);
    for ( const QFileInfo &info : dir.entryInfoList() ) {
        if ( info.isDir() && info.isReadable() ) {
            result += walk(info.filePath());
        } else {
            result.append(info.filePath());
        }
    }

    return result;
}


Project::~Project()
{

}

void Project::reload()
{
    if ( this->filepath.isEmpty() ) {
        return;
    }
    this->_containers.clear();
    for ( auto path : walk(this->filepath) ) {
        QString fileName = QFileInfo(path).fileName();
        if ( fileName.endsWith(".txt") ||
             fileName.endsWith(".md") ) {
            this->append(std::make_shared<FileScenario>(path));
        } else if ( fileName.endsWith(".png") ) {
            this->append(std::make_shared<FileImage>(path));
        } else {
            continue;
        }
    }
}

void Project::append(const Container::Ptr &container)
{
    this->_containers.append(container);
    connect(container.get(), &Container::changed, this, &Project::containerChanged);
    emit this->changed(container);
}

Project::Ptr Project::create()
{
    return Ptr(new Project);
}

Project::Ptr Project::create(const QString &filepath)
{
    return Ptr(new Project(filepath));
}

void Project::containerChanged(const Container::Ptr &container)
{
    this->saved = false;
    emit this->changed(container);
}

Project::Project(const QString &filepath) :
    _containers(),
    filepath(filepath),
    saved(true)
{
    if ( filepath.isEmpty() ) {
        return;
    }
    this->reload();
}
