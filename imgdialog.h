#ifndef IMGDIALOG_H
#define IMGDIALOG_H

#include <QDialog>

namespace Ui {
class imgDialog;
}

class imgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit imgDialog(QWidget *parent = nullptr);
    ~imgDialog();

private:
    Ui::imgDialog *ui;
};

#endif // IMGDIALOG_H
