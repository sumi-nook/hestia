#include "test_apis.h"

#include <QTest>


TestMarkdownBasics::TestMarkdownBasics() :
    QObject()
{}

TestMarkdownBasics::~TestMarkdownBasics()
{}

void TestMarkdownBasics::initTestCase()
{}

void TestMarkdownBasics::cleanupTestCase()
{}

void TestMarkdownBasics::init()
{
    //! Create instance of Markdown.
    this->md = markdown::create_Markdown();
}

void TestMarkdownBasics::cleanup()
{}

/*!
  Test blank input.
*/
void TestMarkdownBasics::testBlankInput()
{
    QCOMPARE(this->md->convert(QString()), QString());
}

/*!
  Test input of only whitespace.
*/
void TestMarkdownBasics::testWhitespaceOnly()
{
    QCOMPARE(this->md->convert(" "), QString());
}

/*!
  Test simple input.
*/
void TestMarkdownBasics::testSimpleInput()
{
    QCOMPARE(this->md->convert("foo"), QString("<p>foo</p>"));
}



TestBlockParser::TestBlockParser() :
    QObject()
{}

TestBlockParser::~TestBlockParser()
{}

void TestBlockParser::initTestCase()
{}

void TestBlockParser::cleanupTestCase()
{}

void TestBlockParser::init()
{
    //! Create instance of BlockParser.
    this->md = markdown::create_Markdown();
    this->parser = this->md->parser;
}

void TestBlockParser::cleanup()
{}

/*!
  Test BlockParser.parseChunk.
*/
void TestBlockParser::testParseChunk()
{
    markdown::Element root = markdown::createElement("div");
    QString text = "foo";
    this->parser->parseChunk(root, text);
    QCOMPARE(markdown::to_xhtml_string(root), QString("<div><p>foo</p></div>"));
}

/*!
  Test BlockParser.parseDocument.
*/
void TestBlockParser::testParseDocument()
{
    QStringList lines = {"#foo", "", "bar", "", "    baz"};
    markdown::ElementTree tree = this->parser->parseDocument(lines);
    QCOMPARE(markdown::to_xhtml_string(tree.getroot()), QString("<div><h1>foo</h1><p>bar</p><pre><code>baz\n</code></pre></div>"));
}


TestBlockParserState::TestBlockParserState()
{}

TestBlockParserState::~TestBlockParserState()
{}

void TestBlockParserState::initTestCase()
{}

void TestBlockParserState::cleanupTestCase()
{}

void TestBlockParserState::init()
{
    this->state = markdown::State();
}

void TestBlockParserState::cleanup()
{}

/*!
  Test State when empty.
*/
void TestBlockParserState::testBlankState()
{
    QCOMPARE(this->state.toList(), QStringList());
}

/*!
  Test State.set().
*/
void TestBlockParserState::testSetSate()
{
    this->state.set("a_state");
    QCOMPARE(this->state.toList(), QStringList({"a_state"}));
    this->state.set("state2");
    QCOMPARE(this->state.toList(), QStringList({"a_state", "state2"}));
}

/*!
  Test State.isstate().
*/
void TestBlockParserState::testIsSate()
{
    QCOMPARE(this->state.isstate("anything"), false);
    this->state.set("a_state");
    QCOMPARE(this->state.isstate("a_state"), true);
    this->state.set("state2");
    QCOMPARE(this->state.isstate("state2"), true);
    QCOMPARE(this->state.isstate("a_state"), false);
    QCOMPARE(this->state.isstate("missing"), false);
}

/*!
  Test State.reset().
*/
void TestBlockParserState::testReset()
{
    this->state.set("a_state");
    this->state.reset();
    QCOMPARE(this->state.toList(), QStringList());
    this->state.set("state1");
    this->state.set("state2");
    this->state.reset();
    QCOMPARE(this->state.toList(), QStringList({"state1"}));
}


TestHtmlStash::TestHtmlStash()
{

}

TestHtmlStash::~TestHtmlStash()
{

}

void TestHtmlStash::initTestCase()
{

}

void TestHtmlStash::cleanupTestCase()
{

}

void TestHtmlStash::init()
{
    this->stash = markdown::HtmlStash();
    this->placeholder = this->stash.store("foo");
}

void TestHtmlStash::cleanup()
{

}

/*!
  Test HtmlStash.store.
*/
void TestHtmlStash::testSimpleStore()
{
    QCOMPARE(this->placeholder, this->stash.get_placeholder(0));
}

/*!
  Test HtmlStash.store with additional blocks.
*/
void TestHtmlStash::testStoreMore()
{
    QString placeholder = this->stash.store("bar");
    QCOMPARE(placeholder, this->stash.get_placeholder(1));
    QCOMPARE(this->stash.html_counter, 2);
    QCOMPARE(this->stash.rawHtmlBlocks, markdown::HtmlStash::Items({
        markdown::HtmlStash::Item({"foo", false}),
        markdown::HtmlStash::Item({"bar", false}),
    }));
}

/*!
  Test HtmlStash.store with 'safe' html.
*/
void TestHtmlStash::testSafeStore()
{
    this->stash.store("bar", true);
    QCOMPARE(this->stash.rawHtmlBlocks, markdown::HtmlStash::Items({
        markdown::HtmlStash::Item({"foo", false}),
        markdown::HtmlStash::Item({"bar", true}),
    }));
}

/*!
  Test HtmlStash.reset.
*/
void TestHtmlStash::testReset()
{
    this->stash.reset();
    QCOMPARE(this->stash.html_counter, 0);
    QCOMPARE(this->stash.rawHtmlBlocks, markdown::HtmlStash::Items());
}


TestOrderedDict::TestOrderedDict()
{

}

TestOrderedDict::~TestOrderedDict()
{

}

void TestOrderedDict::initTestCase()
{

}

void TestOrderedDict::cleanupTestCase()
{

}

void TestOrderedDict::init()
{
    this->odict = markdown::OrderedDict<QString>();
    this->odict["first"] = QString("This");
    this->odict["third"] = QString("a");
    this->odict["fourth"] = QString("self");
    this->odict["fifth"] = QString("test");
}

void TestOrderedDict::cleanup()
{

}

/*!
  Test output of OrderedDict.values().
*/
void TestOrderedDict::testValues()
{
    QCOMPARE(this->odict.values(), QList<QString>({"This", "a", "self", "test"}));
}

/*!
  Test output of OrderedDict.keys().
*/
void TestOrderedDict::testKeys()
{
    QCOMPARE(this->odict.keys(), QStringList({"first", "third", "fourth", "fifth"}));
}

/*!
  Test output of OrderedDict.items().
*/
void TestOrderedDict::testItems()
{
    QCOMPARE(this->odict.items(), markdown::OrderedDict<QString>::Pairs({
        qMakePair(QString("first"), QString("This")),
        qMakePair(QString("third"), QString("a")),
        qMakePair(QString("fourth"), QString("self")),
        qMakePair(QString("fifth"), QString("test")),
    }));
}

/*!
  Test adding an OrderedDict item before a given key.
*/
void TestOrderedDict::testAddBefore()
{
    this->odict.add("second", "is", "<third");
    QCOMPARE(this->odict.items(), markdown::OrderedDict<QString>::Pairs({
        qMakePair(QString("first"), QString("This")),
        qMakePair(QString("second"), QString("is")),
        qMakePair(QString("third"), QString("a")),
        qMakePair(QString("fourth"), QString("self")),
        qMakePair(QString("fifth"), QString("test")),
    }));
}

/*!
  Test adding an OrderDict item after a given key.
*/
void TestOrderedDict::testAddAfter()
{
    this->odict.add("second", "is", ">first");
    QCOMPARE(this->odict.items(), markdown::OrderedDict<QString>::Pairs({
        qMakePair(QString("first"), QString("This")),
        qMakePair(QString("second"), QString("is")),
        qMakePair(QString("third"), QString("a")),
        qMakePair(QString("fourth"), QString("self")),
        qMakePair(QString("fifth"), QString("test")),
    }));
}

/*!
  Test adding an OrderedDict item after the last key.
*/
void TestOrderedDict::testAddAfterEnd()
{
    this->odict.add("sixth", ".", ">fifth");
    QCOMPARE(this->odict.items(), markdown::OrderedDict<QString>::Pairs({
        qMakePair(QString("first"), QString("This")),
        qMakePair(QString("third"), QString("a")),
        qMakePair(QString("fourth"), QString("self")),
        qMakePair(QString("fifth"), QString("test")),
        qMakePair(QString("sixth"), QString(".")),
    }));
}

/*!
  Test adding an OrderedDict item using "_begin".
*/
void TestOrderedDict::testAdd_begin()
{
    this->odict.add("zero", "CRAZY", "_begin");
    QCOMPARE(this->odict.items(), markdown::OrderedDict<QString>::Pairs({
        qMakePair(QString("zero"), QString("CRAZY")),
        qMakePair(QString("first"), QString("This")),
        qMakePair(QString("third"), QString("a")),
        qMakePair(QString("fourth"), QString("self")),
        qMakePair(QString("fifth"), QString("test")),
    }));
}

/*!
  Test adding an OrderedDict item using "_end".
*/
void TestOrderedDict::testAdd_end()
{
    this->odict.add("sixth", ".", "_end");
    QCOMPARE(this->odict.items(), markdown::OrderedDict<QString>::Pairs({
        qMakePair(QString("first"), QString("This")),
        qMakePair(QString("third"), QString("a")),
        qMakePair(QString("fourth"), QString("self")),
        qMakePair(QString("fifth"), QString("test")),
        qMakePair(QString("sixth"), QString(".")),
    }));
}

/*!
  Test OrderedDict change value.
*/
void TestOrderedDict::testChangeValue()
{
    this->odict["fourth"] = "CRAZY";
    QCOMPARE(this->odict.items(), markdown::OrderedDict<QString>::Pairs({
        qMakePair(QString("first"), QString("This")),
        qMakePair(QString("third"), QString("a")),
        qMakePair(QString("fourth"), QString("CRAZY")),
        qMakePair(QString("fifth"), QString("test")),
    }));
}

/*!
  Test OrderedDict change order.
*/
void TestOrderedDict::testChangeOrder()
{
    this->odict.link("fourth", "<third");
    QCOMPARE(this->odict.items(), markdown::OrderedDict<QString>::Pairs({
        qMakePair(QString("first"), QString("This")),
        qMakePair(QString("fourth"), QString("self")),
        qMakePair(QString("third"), QString("a")),
        qMakePair(QString("fifth"), QString("test")),
                                                                        }));
}

TestInlinePattern::TestInlinePattern()
{

}

TestInlinePattern::~TestInlinePattern()
{

}

void TestInlinePattern::initTestCase()
{
    this->md = markdown::create_Markdown();
}

void TestInlinePattern::cleanupTestCase()
{

}

void TestInlinePattern::init()
{

}

void TestInlinePattern::cleanup()
{

}

void TestInlinePattern::test_backtick()
{
    std::shared_ptr<markdown::Pattern> backtick = this->md->inlinePatterns["backtick"];
    QRegularExpressionMatch match = backtick->getCompiledRegExp().match("`code`");
    QCOMPARE(match.hasMatch(), true);
    QCOMPARE(match.captured(), QString("`code`"));
}

TestTreeProcessor::TestTreeProcessor()
{

}

TestTreeProcessor::~TestTreeProcessor()
{

}

void TestTreeProcessor::initTestCase()
{
    this->md = markdown::create_Markdown();
}

void TestTreeProcessor::cleanupTestCase()
{

}

void TestTreeProcessor::init()
{

}

void TestTreeProcessor::cleanup()
{

}

void TestTreeProcessor::test_inline()
{
    std::shared_ptr<markdown::TreeProcessor> inlineProcessor = this->md->treeprocessors["inline"];

    markdown::Element root = markdown::createElement("div");
    markdown::Element p = markdown::createSubElement(root, "p");
    p->text = "`<http://example.com>`";

    markdown::Element ret = inlineProcessor->run(root);
    QCOMPARE(ret->tag, QString("div"));
    QCOMPARE(ret->child()[0]->tag, QString("p"));
    QCOMPARE(ret->child()[0]->child()[0]->tag, QString("code"));
    QCOMPARE(ret->child()[0]->child()[0]->text, QString("<http://example.com>"));
}
