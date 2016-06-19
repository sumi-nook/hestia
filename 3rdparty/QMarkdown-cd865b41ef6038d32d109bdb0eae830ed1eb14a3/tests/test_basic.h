#ifndef TEST_BASIC_H
#define TEST_BASIC_H

#include <QObject>

#include "Markdown.h"

class TestBasic : public QObject
{
    Q_OBJECT
public:
    TestBasic();
    ~TestBasic();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void amps_and_angle_encoding();
    void angle_links_and_img();
    void auto_links();
    void backlash_escapes();
    void blockquotes_with_code_blocks();
    void codeblock_in_list();
    void hard_wrapped();
    void horizontal_rules();
    void inline_html_advanced();
    void inline_html_comments();
    void inline_html_simple();
    void links_inline();
    void links_reference();
    void literal_quotes();
    void markdown_documentation_basics();
    void markdown_syntax();
    void nested_blockquotes();
    void ordered_and_unordered_list();
    void strong_and_em_together();
    void tabs();
    void tidyness();

private:
    std::shared_ptr<markdown::Markdown> md;

};

#endif // TEST_BASIC_H
