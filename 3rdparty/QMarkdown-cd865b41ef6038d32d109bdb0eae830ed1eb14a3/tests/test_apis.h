#ifndef TEST_APIS_H_
#define TEST_APIS_H_

#include <QObject>

#include <QSharedPointer>

#include "Markdown.h"
#include "BlockParser.h"
#include "Serializers.h"
#include "util.h"

class TestMarkdownBasics : public QObject
{
    Q_OBJECT
public:
    TestMarkdownBasics();
    ~TestMarkdownBasics();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testBlankInput();
    void testWhitespaceOnly();
    void testSimpleInput();

private:
    std::shared_ptr<markdown::Markdown> md;

};


/*!
  Tests of the BlockParser class.
*/
class TestBlockParser : public QObject
{
    Q_OBJECT
public:
    TestBlockParser();
    ~TestBlockParser();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testParseChunk();
    void testParseDocument();

private:
    std::shared_ptr<markdown::Markdown> md;
    std::shared_ptr<markdown::BlockParser> parser;

};

/*!
  Tests of the State class for BlockParser.
*/
class TestBlockParserState : public QObject
{
    Q_OBJECT
public:
    TestBlockParserState();
    ~TestBlockParserState();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testBlankState();
    void testSetSate();
    void testIsSate();
    void testReset();

private:
    markdown::State state;

};

/*!
  Test Markdown's HtmlStash.
*/
class TestHtmlStash : public QObject
{
    Q_OBJECT
public:
    TestHtmlStash();
    ~TestHtmlStash();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testSimpleStore();
    void testStoreMore();
    void testSafeStore();
    void testReset();
    //void testUnsafeHtmlInSafeMode();
    //void build_extension();

private:
    markdown::HtmlStash stash;
    QString placeholder;

};

/*!
  Test OrderedDict storage class.
*/
class TestOrderedDict : public QObject
{
    Q_OBJECT
public:
    TestOrderedDict();
    ~TestOrderedDict();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void testValues();
    void testKeys();
    void testItems();
    void testAddBefore();
    void testAddAfter();
    void testAddAfterEnd();
    void testAdd_begin();
    void testAdd_end();
    //void testAddBadLocation();
    //void testDeleteItem();
    void testChangeValue();
    void testChangeOrder();
    //void textBadLink();

private:
    markdown::OrderedDict<QString> odict;

};


class TestInlinePattern : public QObject
{
    Q_OBJECT
public:
    TestInlinePattern();
    ~TestInlinePattern();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void test_backtick();

private:
    std::shared_ptr<markdown::Markdown> md;

};


class TestTreeProcessor : public QObject
{
    Q_OBJECT
public:
    TestTreeProcessor();
    ~TestTreeProcessor();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void test_inline();

private:
    std::shared_ptr<markdown::Markdown> md;

};

#endif // TEST_APIS_H_

