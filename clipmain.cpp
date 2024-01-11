#include "clipmain.h"
#include "ui_clipmain.h"

ClipMain::ClipMain(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClipMain)
{
    ui->setupUi(this);
}

ClipMain::~ClipMain()
{
    delete ui;
}

