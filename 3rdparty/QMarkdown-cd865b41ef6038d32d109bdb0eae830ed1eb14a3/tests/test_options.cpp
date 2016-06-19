#include "test_options.h"

#include <QDebug>
#include <QTest>

TestOptions::TestOptions()
{

}

TestOptions::~TestOptions()
{

}

void TestOptions::initTestCase()
{

}

void TestOptions::cleanupTestCase()
{

}

void TestOptions::init()
{

}

void TestOptions::cleanup()
{

}

void TestOptions::html4()
{
    std::shared_ptr<markdown::Markdown> md = markdown::create_Markdown();
    md->set_output_format(markdown::Markdown::html4);
    QString converted = md->convert(
                "A test of the most  " "\n"
                "basic of html/xhtml differences.");
    QCOMPARE(converted,
             QString("<p>A test of the most<br>" "\n"
                     "basic of html/xhtml differences.</p>"));
}

void TestOptions::lazy_ol_off()
{
    std::shared_ptr<markdown::Markdown> md = markdown::create_Markdown();
    md->set_lazy_ol(false);
    QString converted = md->convert(
                "A numbered list from daringfireball:" "\n"
                "" "\n"
                "3. Bird" "\n"
                "1. McHale" "\n"
                "8. Parish" "\n"
                "" "\n"
                "Again:" "\n"
                "" "\n"
                "3. Bird" "\n"
                "1. McHale" "\n"
                "8. Parish" "\n"
                "" "\n"
                "Now starting with 1:" "\n"
                "" "\n"
                "1. Bird" "\n"
                "1. McHale" "\n"
                "8. Parish" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>A numbered list from daringfireball:</p>" "\n"
                     R"(<ol start="3">)" "\n"
                     "<li>Bird</li>" "\n"
                     "<li>McHale</li>" "\n"
                     "<li>Parish</li>" "\n"
                     "</ol>" "\n"
                     "<p>Again:</p>" "\n"
                     R"(<ol start="3">)" "\n"
                     "<li>Bird</li>" "\n"
                     "<li>McHale</li>" "\n"
                     "<li>Parish</li>" "\n"
                     "</ol>" "\n"
                     "<p>Now starting with 1:</p>" "\n"
                     "<ol>" "\n"
                     "<li>Bird</li>" "\n"
                     "<li>McHale</li>" "\n"
                     "<li>Parish</li>" "\n"
                     "</ol>"));
}

void TestOptions::no_attributes()
{
    std::shared_ptr<markdown::Markdown> md = markdown::create_Markdown();
    md->set_enable_attributes(false);
    QString converted = md->convert(
                "Regression *test* for issue 87" "\n"
                "" "\n"
                "It's run with enable_attributes=False so this {@id=explanation} should not become an attribute" "\n"
                "");
    QCOMPARE(converted,
             QString("<p>Regression <em>test</em> for issue 87</p>" "\n"
                     "<p>It's run with enable_attributes=False so this {@id=explanation} should not become an attribute</p>"));
}

void TestOptions::no_smart_emphasis()
{
    std::shared_ptr<markdown::Markdown> md = markdown::create_Markdown();
    md->set_smart_emphasis(false);
    QString converted = md->convert(
                "_connected_words_");
    QCOMPARE(converted,
             QString("<p><em>connected</em>words_</p>"));
}
