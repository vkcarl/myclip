#include "clipmain.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Clip_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    ClipMain w;

//    w.resize(800, 600);
//    w.show();
//    return a.exec();

    w.show();
    QFile style_file(":/stylesheet.qss");
    bool success = style_file.open(QFile::ReadOnly | QIODevice::Text);
    if(success) {
        a.setStyleSheet(QString::fromUtf8(style_file.readAll()));
        style_file.close();
    }
    else {
        qWarning() << "Couldn't load stylesheet: " << style_file.fileName();
    }
    return a.exec();
}
