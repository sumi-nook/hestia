#include "test_pypp.h"

#include <QTest>

TestPypp::TestPypp()
{}

TestPypp::~TestPypp()
{}

void TestPypp::initTestCase()
{}

void TestPypp::cleanupTestCase()
{}

void TestPypp::init()
{}

void TestPypp::cleanup()
{}

void TestPypp::test_reversed()
{
    QCOMPARE(pypp::reversed(QList<int>({2, 1, 3})), QList<int>({3, 1, 2}));
}

void TestPypp::test_sorted()
{
    QCOMPARE(pypp::sorted(QList<int>({2, 1, 3})), QList<int>({1, 2, 3}));
    QCOMPARE(pypp::sorted(QList<int>({2, 1, 3}), true), QList<int>({3, 2, 1}));
    QCOMPARE(pypp::sorted(QList<int>({2, 1, 3}), [](int lhs, int rhs) -> bool { return lhs < rhs; }), QList<int>({1, 2, 3}));
    QCOMPARE(pypp::sorted(QList<int>({2, 1, 3}), [](int lhs, int rhs) -> bool { return lhs > rhs; }), QList<int>({3, 2, 1}));
}

void TestPypp::test_slice_end()
{
    QCOMPARE(pypp::slice(0)(QString("0123456789")), QString());
    QCOMPARE(pypp::slice(1)(QString("0123456789")), QString("0"));
    QCOMPARE(pypp::slice(10)(QString("0123456789")), QString("0123456789"));
    QCOMPARE(pypp::slice(-1)(QString("0123456789")), QString("012345678"));
    QCOMPARE(pypp::slice(-10)(QString("0123456789")), QString());
}

void TestPypp::test_slice_begin_end()
{
    QCOMPARE(pypp::slice(1, 2)(QString("0123456789")), QString("1"));
    QCOMPARE(pypp::slice(2, 1)(QString("0123456789")), QString());
    QCOMPARE(pypp::slice(1, 10)(QString("0123456789")), QString("123456789"));
    QCOMPARE(pypp::slice(-1, 10)(QString("0123456789")), QString("9"));
    QCOMPARE(pypp::slice(-5, -1)(QString("0123456789")), QString("5678"));
    QCOMPARE(pypp::slice(-10, 3)(QString("0123456789")), QString("012"));
    QCOMPARE(pypp::slice(-10, -11)(QString("0123456789")), QString());
}

void TestPypp::test_begin_slice()
{
    QCOMPARE(pypp::begin_slice(0)(QString("0123456789")), QString("0123456789"));
    QCOMPARE(pypp::begin_slice(1)(QString("0123456789")), QString("123456789"));
    QCOMPARE(pypp::begin_slice(10)(QString("0123456789")), QString());
    QCOMPARE(pypp::begin_slice(-1)(QString("0123456789")), QString("9"));
    QCOMPARE(pypp::begin_slice(-10)(QString("0123456789")), QString("0123456789"));
}

void TestPypp::test_str_expandtabs()
{
    QCOMPARE(pypp::expandtabs("\t", 4), pypp::str(4, ' '));
    QCOMPARE(pypp::expandtabs("+\t", 4), pypp::str("+   "));
    QCOMPARE(pypp::expandtabs("++\t", 4), pypp::str("++  "));
    QCOMPARE(pypp::expandtabs("+++\t", 4), pypp::str("+++ "));
    QCOMPARE(pypp::expandtabs("++++\t", 4), pypp::str("++++    "));
    QCOMPARE(pypp::expandtabs("\t+\t", 4), pypp::str("    +   "));
    QCOMPARE(pypp::expandtabs("++\n\t", 4), pypp::str("++\n    "));
}

void TestPypp::test_re_sub()
{
    auto repl = [](const QRegularExpressionMatch &) -> QString { return QString(); };
    QCOMPARE(pypp::re::sub(QRegularExpression("\\d"), repl, "123, 456"), QString(", "));
}


