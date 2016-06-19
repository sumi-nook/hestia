#ifndef TEST_EXTENSIONS_H
#define TEST_EXTENSIONS_H

#include <QObject>

#include "Markdown.h"

class TestExtensions : public QObject
{
    Q_OBJECT
public:
    TestExtensions();
    ~TestExtensions();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void admonition();
    void attr_list();

    // extra
    void abbr();
    void def_in_list();
    void tables();
    void tables_and_attr_list();

};

#endif // TEST_EXTENSIONS_H
