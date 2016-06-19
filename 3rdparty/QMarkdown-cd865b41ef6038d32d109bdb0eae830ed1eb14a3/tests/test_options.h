#ifndef TEST_OPTIONS_H
#define TEST_OPTIONS_H

#include <QObject>

#include "Markdown.h"

class TestOptions : public QObject
{
    Q_OBJECT
public:
    TestOptions();
    ~TestOptions();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void html4();
    void lazy_ol_off();
    void no_attributes();
    void no_smart_emphasis();

};

#endif // TEST_OPTIONS_H
