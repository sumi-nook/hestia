#include <QtTest>
#include <QCoreApplication>

#include "test_pypp.h"
#include "test_etree.h"
#include "test_apis.h"
#include "test_basic.h"
#include "test_misc.h"
#include "test_safemode.h"
#include "test_options.h"
#include "test_extensions.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app)

    typedef QSharedPointer<QObject> Test;
    QList<Test> tests = {
        Test(new TestPypp()),
        Test(new TestEtree()),
        Test(new TestMarkdownBasics()),
        Test(new TestBlockParser()),
        Test(new TestBlockParserState()),
        Test(new TestHtmlStash()),
        Test(new TestOrderedDict()),
        Test(new TestInlinePattern()),
        Test(new TestTreeProcessor()),
        Test(new TestBasic()),
        Test(new TestMISC()),
        Test(new TestSafeMode()),
        Test(new TestOptions()),
        Test(new TestExtensions()),
    };

    for ( QSharedPointer<QObject> &test : tests ) {
        if ( int ret = QTest::qExec(test.data(), argc, argv) != 0 ) {
            return ret;
        }
    }

    return 0;
}

