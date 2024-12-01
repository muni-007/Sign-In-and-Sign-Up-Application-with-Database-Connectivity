#ifndef THIRDDIALOG_H
#define THIRDDIALOG_H

#include <QDialog>

namespace Ui {
class thirdDialog;
}

class thirdDialog : public QDialog
{
    Q_OBJECT

public:
    explicit thirdDialog(QWidget *parent = nullptr);
    ~thirdDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::thirdDialog *ui;
    int calculate_age(int day,int month,int year);
    //void check_username(QString &u);
    //void check_password(QString &p);
    //void check_mobileNumber(QString &m);
    void setupLineEditValidator();

};

#endif // THIRDDIALOG_H
