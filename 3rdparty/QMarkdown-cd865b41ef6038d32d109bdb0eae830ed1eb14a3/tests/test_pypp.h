#ifndef TEST_PYPP_H
#define TEST_PYPP_H

#include <QObject>

#include "pypp.hpp"

class TestPypp : public QObject
{
    Q_OBJECT
public:
    TestPypp();
    ~TestPypp();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void init();
    void cleanup();

    void test_reversed();
    void test_sorted();
    void test_slice_end();
    void test_slice_begin_end();
    void test_begin_slice();
    void test_str_expandtabs();
    void test_re_sub();

};

#endif // TEST_PYPP_H
