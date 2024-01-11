#ifndef CLIPMAIN_H
#define CLIPMAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ClipMain; }
QT_END_NAMESPACE

class ClipMain : public QMainWindow
{
    Q_OBJECT

public:
    ClipMain(QWidget *parent = nullptr);
    ~ClipMain();

private:
    Ui::ClipMain *ui;
};
#endif // CLIPMAIN_H
