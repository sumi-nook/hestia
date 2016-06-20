#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator qtTr, appTr;
    QStringList trDirs = {"i18n", "."};

    // Qt Translations
    for ( const QString &dir : trDirs ) {
        if ( qtTr.load("qt_" + QLocale::system().name(), dir) ) {
            app.installTranslator(&qtTr);
            break;
        }
    }
    // App Translations
    for ( const QString &dir : trDirs ) {
        if ( appTr.load("hestia_" + QLocale::system().name(), dir) ) {
            app.installTranslator(&appTr);
            break;
        }
    }

    MainWindow win;
    win.show();

    return app.exec();
}
