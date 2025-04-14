#include "xwidget.h"

#include <QApplication>
#include <QLocale>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QTranslator>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "3D_audio_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }



    XWidget w;
    qApp->setProperty("MainXWidget", QVariant::fromValue(&w)); // 存储指针
    w.show();

    return a.exec();
}


