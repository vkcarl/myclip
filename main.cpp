#include "clipmain.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMediaPlayer>
#include <QVideoWidget>

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

    // 创建视频播放器和视频显示控件
    QMediaPlayer *player = new QMediaPlayer;
    QVideoWidget *videoWidget = new QVideoWidget(&w);

    // 设置视频文件源
    player->setSource(QUrl::fromLocalFile("../encode/juren-30s.mp4"));

    // 将视频输出设置到视频显示控件
    player->setVideoOutput(videoWidget);

    // 将视频控件设置为主窗口的中心控件
    w.setCentralWidget(videoWidget);

    // 播放视频
    player->play();

    w.resize(800, 600);
    w.show();
    return a.exec();
}
