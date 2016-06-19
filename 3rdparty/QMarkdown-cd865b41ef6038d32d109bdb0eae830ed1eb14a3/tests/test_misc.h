#ifndef TEST_MISC_H
#define TEST_MISC_H

#include <QObject>

#include "Markdown.h"

class TestMISC : public QObject
{
    Q_OBJECT
public:
    TestMISC();
    ~TestMISC();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void CRLF_line_ends();
    void adjacent_headers();
    void amp_in_url();
    void ampersand();
    void arabic();
    void attributes2();
    void attributes_image_ref();
    void autolinks_with_asterisks();
    void autolinks_with_asterisks_russian();
    void backtick_escape();
    void bidi();
    void blank_block_quote();
    void blank_lines_in_codeblocks();
    void block_html5();
    void block_html_attr();
    void block_html_simple();
    void blockquote();
    void blockquote_below_paragraph();
    void blockquote_hr();
    void bold_links();
    void br();
    void bracket_re();
    void brackets_in_img_title();
    void code_first_line();
    void comments();
    void div();
    void em_around_links();
    void em_strong();
    void em_strong_complex();
    void email();
    void escaped_chars_in_js();
    void escaped_links();
    void funky_list();
    void h1();
    void hash();
    void header_in_lists();
    void headers();
    void hline();
    void html();
    void html_comments();
    void image();
    void image_2();
    void image_in_links();
    void ins_at_start_of_paragraph();
    void inside_html();
    void japanese();
    void lazy_block_quote();
    void link_with_parenthesis();
    void lists();
    void lists2();
    void lists3();
    void lists4();
    void lists5();
    void lists6();
    void lists7();
    void lists8();
    void markup_inside_p();
    void mismatched_tags();
    void missing_link_def();
    void more_comments();
    void multi_line_tags();
    void multi_paragraph_block_quote();
    void multi_test();
    void multiline_comments();
    void nested_lists();
    void nested_patterns();
    void normalize();
    void numeric_entity();
    void para_with_hr();
    void php();
    void pre();
    void raw_whitespace();
    void russian();
    void smart_em();
    void some_test();
    void span();
    void strong_with_underscores();
    void stronintags();
    void tabs_in_lists();
    void two_spaces();
    void uche();
    void underscores();
    void url_spaces();

private:
    std::shared_ptr<markdown::Markdown> md;

};

#endif // TEST_MISC_H
