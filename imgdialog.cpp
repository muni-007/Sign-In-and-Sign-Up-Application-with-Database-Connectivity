#include "imgdialog.h"
#include "ui_imgdialog.h"
#include<QPixmap>

imgDialog::imgDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::imgDialog)
{
    ui->setupUi(this);

    QPixmap pix(":/img/image/image123.jpeg"); //provides reading an image file
    int w=ui->label->width();         //finds the width of label
    int h=ui->label->height();              //finds the length or height of label
    ui->label->setPixmap(pix.scaled(h,w,Qt::KeepAspectRatio));           //scaling the pix to the given size,using aspect ratio
}

imgDialog::~imgDialog()
{
    delete ui;
}
