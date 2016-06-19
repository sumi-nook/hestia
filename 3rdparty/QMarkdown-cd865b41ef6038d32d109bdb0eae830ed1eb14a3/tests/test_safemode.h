#ifndef TEST_SAFEMODE_H
#define TEST_SAFEMODE_H

#include <QObject>

#include "Markdown.h"

class TestSafeMode : public QObject
{
    Q_OBJECT
public:
    TestSafeMode();
    ~TestSafeMode();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void html_then_blockquote();
    void inline_html_advanced();
    void inline_html_comments();
    void inline_html_simple();
    void link_targets();
    void remove();
    void replace();
    void script_tags();
    void unsafe_urls();

private:
    std::shared_ptr<markdown::Markdown> escape_md;
    std::shared_ptr<markdown::Markdown> remove_md;
    std::shared_ptr<markdown::Markdown> replace_md;

};

#endif // TEST_SAFEMODE_H
