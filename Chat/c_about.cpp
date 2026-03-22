#include "c_about.h"
#include "ui_c_about.h"

C_About::C_About(QWidget *parent)
    : ElaDialog(parent)
    , ui(new Ui::C_About)
{
    ui->setupUi(this);
}

C_About::~C_About()
{
    delete ui;
}
