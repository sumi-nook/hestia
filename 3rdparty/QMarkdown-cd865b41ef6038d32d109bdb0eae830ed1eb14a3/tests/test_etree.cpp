#include "test_etree.h"

#include <QTest>

#include "ElementTree.hpp"
#include "Serializers.h"

TestEtree::TestEtree() :
    root()
{}

TestEtree::~TestEtree()
{}

void TestEtree::initTestCase()
{}

void TestEtree::cleanupTestCase()
{}

void TestEtree::init()
{
    this->root = markdown::ElementTree();
}

void TestEtree::cleanup()
{}

void TestEtree::test_Element()
{
    markdown::Element elem = markdown::createElement("elem");
    QCOMPARE(markdown::to_xhtml_string(elem), QString("<elem></elem>"));
}

void TestEtree::test_tostring()
{
    markdown::Element elem = markdown::createElement("elem");
    QCOMPARE(pypp::xml::etree::tostring(elem), QString("<elem/>"));

    elem->set("b", "b");
    elem->set("a", "");
    QCOMPARE(pypp::xml::etree::tostring(elem), QString("<elem a=\"\" b=\"b\"/>"));

    pypp::xml::etree::SubElement(elem, "child");
    QCOMPARE(pypp::xml::etree::tostring(elem), QString("<elem a=\"\" b=\"b\"><child/></elem>"));
}

void TestEtree::test_element_names()
{
    markdown::Element el;

    el = markdown::createElement("name");
    QCOMPARE(el->tag, QString("name"));

    //el = markdown::Element(this->root, "{}name");
    //QCOMPARE(el.getTagName(), QString("name"));
}

void TestEtree::test_element_child()
{
    markdown::Element root = markdown::createElement("root");
    markdown::Element a = markdown::createSubElement(root, "a");
    markdown::Element b = markdown::createSubElement(root, "b");
    markdown::Element c = markdown::createSubElement(root, "c");
    QCOMPARE(root->size(), 3);
    QCOMPARE((*root)[0]->tag, a->tag);
    QCOMPARE((*root)[1]->tag, b->tag);
    QCOMPARE((*root)[2]->tag, c->tag);
    QCOMPARE((*root)[-1]->tag, c->tag);
    QCOMPARE((*root)[-2]->tag, b->tag);
    QCOMPARE((*root)[-3]->tag, a->tag);

    bool excepted1 = false;
    try {
        (*root)[3];
    } catch ( const pypp::IndexError & ) {
        excepted1 = true;
    }
    QCOMPARE(excepted1, true);

    bool excepted2 = false;
    try {
        (*root)[-4];
    } catch ( const pypp::IndexError & ) {
        excepted2 = true;
    }
    QCOMPARE(excepted2, true);
}

