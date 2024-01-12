#ifndef PLAYSLIDER_H
#define PLAYSLIDER_H

#include <QSlider>

class PlayerSlider : public QSlider
{
    Q_OBJECT
signals:
    void sigProgress(qint64 i64Pos);

public:
    PlayerSlider(QWidget *parent = nullptr);

    bool    m_bPressed;
    void    setProgress(qint64);

    void    mousePressEvent(QMouseEvent *e)override;// 按下
    void    mouseMoveEvent(QMouseEvent *e)override;// 移动
    void    mouseReleaseEvent(QMouseEvent *e)override;// 抬起释放
};

#endif // PLAYSLIDER_H
