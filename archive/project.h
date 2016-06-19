#ifndef HESTIA_ARCHIVE_PROJECT_H
#define HESTIA_ARCHIVE_PROJECT_H

#include <memory>

#include <QObject>

#include "container.h"

class Project : public QObject
{
    Q_OBJECT
public:
    typedef std::shared_ptr<Project> Ptr;
    virtual ~Project();

    void reload();

    void append(const Container::Ptr &container);

    QString filePath() const
    { return this->filepath; }

    void setFilePath(const QString &filepath)
    { this->filepath = filepath; }

    QList<Container::Ptr> &containers()
    { return this->_containers; }

    const QList<Container::Ptr> &containers() const
    { return this->_containers; }

    bool isChanged() const
    { return ! this->saved; }

    static Ptr create();
    static Ptr create(const QString &filepath);

signals:
    void changed(const Container::Ptr &container);

public slots:
    void containerChanged(const Container::Ptr &container);

protected:
    Project(const QString &filepath=QString());

    QList<Container::Ptr> _containers;

private:
    QString filepath;
    bool saved;

};

#endif // HESTIA_ARCHIVE_PROJECT_H
