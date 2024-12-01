#ifndef DISPLAYDIALOG_H
#define DISPLAYDIALOG_H

#include <QDialog>

namespace Ui {
class displayDialog;
}

class displayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit displayDialog(QWidget *parent = nullptr);
    ~displayDialog();

private slots:
    void onNewfile();
    void onOpen();
    void onSave();
    void onSaveAs();
    void onCut();
    void onPaste();
    void onCopy();
private:
    Ui::displayDialog *ui;
    QString file_path;
};

#endif // DISPLAYDIALOG_H
