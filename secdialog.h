#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>
#include<displaydialog.h>
#include<imgdialog.h>
namespace Ui {
class secDialog;
}

class secDialog : public QDialog
{
    Q_OBJECT

public:
    explicit secDialog(QWidget *parent = nullptr);
    ~secDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::secDialog *ui;
    displayDialog *displaydialog;
    imgDialog *imgdialog;
};

#endif // SECDIALOG_H
