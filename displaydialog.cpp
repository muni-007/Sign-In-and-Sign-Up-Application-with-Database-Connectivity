#include "displaydialog.h"
#include "ui_displaydialog.h"
#include<QMenuBar>
#include<QAction>
#include<QVBoxLayout>
#include<QToolBar>
#include<QIcon>
#include<QFileDialog>
#include<QMessageBox>
#include<QFile>
displayDialog::displayDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::displayDialog)
{
    ui->setupUi(this);

    QMenuBar *menuBar=new QMenuBar(this);

    QMenu *fileMenu =menuBar->addMenu("FILE");
    QMenu *editMenu =menuBar->addMenu("EDIT");

    QAction *newAction=new QAction(QIcon(":/img/image/Screenshot 2024-10-24 115611.png"),"New",this);
    QAction *openAction =new QAction(QIcon(":/img/image/Screenshot 2024-10-24 115619.png"),"Open",this);
    QAction *saveAction =new QAction(QIcon(":/img/image/Screenshot 2024-10-24 115627.png"),"Save",this);
    QAction *saveAsAction=new QAction(QIcon(":/img/image/Screenshot 2024-10-24 115627.png"),"SaveAs",this);
    QAction *cutAction =new QAction(QIcon(":/img/image/Screenshot 2024-10-24 115705.png"),"Cut",this);
    QAction *copyAction=new QAction(QIcon(":/img/image/Screenshot 2024-10-24 115712.png"),"Copy",this);
    QAction *pasteAction=new QAction(QIcon(":/img/image/Screenshot 2024-10-24 115723.png"),"Paste",this);

    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);

    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    connect(newAction,SIGNAL(triggered()),this,SLOT(onNewfile()));
    connect(openAction,SIGNAL(triggered()),this,SLOT(onOpen()));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(onSave()));
 connect(saveAsAction,SIGNAL(triggered()),this,SLOT(onSaveAs()));
    connect(cutAction,SIGNAL(triggered()),this,SLOT(onCut()));
    connect(copyAction,SIGNAL(triggered()),this,SLOT(onCopy()));
    connect(pasteAction,SIGNAL(triggered()),this,SLOT(onPaste()));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMenuBar(menuBar);
    setLayout(layout);

    // QToolBar *toolBar=new QToolBar(this);
    // toolBar->addAction(newAction);
    // toolBar->addAction(openAction);
    // toolBar->addAction(saveAction);

    // layout->addWidget(toolBar);



}

displayDialog::~displayDialog()
{
    delete ui;
}

void displayDialog::onNewfile(){
    ui->textEdit->clear();
}

void displayDialog::onOpen(){
    QString file_name=QFileDialog::getOpenFileName(this,"open the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"..","file Not open");
        return;
    }
    QTextStream in(&file);
    QString text =in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void displayDialog::onSave(){
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"..","file Not open");
        return;
    }
    QTextStream out(&file);
    QString text =ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}

void displayDialog::onSaveAs(){
    QString file_name=QFileDialog::getSaveFileName(this,"open the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"..","file Not open");
        return;
    }
    QTextStream out(&file);
    QString text =ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();
}

void displayDialog::onCut(){
    ui->textEdit->cut();
}

void displayDialog::onCopy(){
    ui->textEdit->copy();
}

void displayDialog::onPaste(){
    ui->textEdit->paste();
}
