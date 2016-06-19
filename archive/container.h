#ifndef HESTIA_ARCHIVE_CONTAINER_H
#define HESTIA_ARCHIVE_CONTAINER_H

#include <memory>

#include <QObject>
#include <QIODevice>
#include <QFile>

enum class ContainerType
{
    Scenario = 1,
    Image = 2,
};

class Container : public QObject, public std::enable_shared_from_this<Container>
{
    Q_OBJECT
public:
    typedef std::shared_ptr<Container> Ptr;

    Container(const QString &filepath, QObject *parent=nullptr);
    virtual ~Container();

    virtual bool isChanged() const = 0;
    virtual ContainerType type() const = 0;
    virtual QByteArray content() = 0;

    QString filePath() const
    { return this->filepath; }

signals:
    void changed(const Container::Ptr &);

private:
    QString filepath;

};

class FileContainer : public Container
{
public:
    FileContainer(const QString &filepath, QObject *parent=nullptr);

    bool isChanged() const
    { return false; }

    virtual QByteArray content();

protected:
    QFile file;

};

class InMemoryContainer : public Container
{
public:
    InMemoryContainer(const QString &filepath, QObject *parent=nullptr);

    bool isChanged() const
    { return true; }

    virtual QByteArray content()
    { return this->_content; }

    void setContent(const QByteArray &content)
    { this->_content = content; }

protected:
    QByteArray _content;

};

class FileScenario : public FileContainer
{
public:
    FileScenario(const QString &filepath, QObject *parent=nullptr);

    ContainerType type() const
    { return ContainerType::Scenario; }

    QString text();

};

class InMemoryScenario : public InMemoryContainer
{
public:
    InMemoryScenario(const QString &filepath, QObject *parent=nullptr);

    ContainerType type() const
    { return ContainerType::Scenario; }

    QString text();
    void setText(const QString &text);

};

class FileImage : public FileContainer
{
public:
    FileImage(const QString &filepath, QObject *parent=nullptr);

    ContainerType type() const
    { return ContainerType::Image; }

};


QString getScenarioText(const std::shared_ptr<Container> &scenario);

#endif // HESTIA_ARCHIVE_CONTAINER_H
