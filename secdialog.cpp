#include "secdialog.h"
#include "ui_secdialog.h"
#include<thirddialog.h>
#include<QCoreApplication>
#include<QMessageBox>
#include<QString>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlError>
#include<QtSql/QSqlRecord>
#include<QDebug>
#include<QProcessEnvironment>

secDialog::secDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::secDialog)
{
    ui->setupUi(this);
}

secDialog::~secDialog()
{
    delete ui;
}

void secDialog::on_pushButton_clicked()
{
    QString username=ui->lineEdit_username->text();            //assigned username as line_Edit username text
    QString password=ui->lineEdit_password->text();                 //assigned password as line_Edit password text

    // QSql Database interfacing for representing the connection to database

    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");      // adds a database to list of database connection
    db.setDatabaseName("C:/project/signup_signin/mydb.db");             //sets the connection database name to name ,it set before connection is opened()
    if(!db.open()){               //if database connection is not connected
        QMessageBox::information(this,"Database failed","database connection failed");       //returns true ,database is not connected
        return;                                      //Return back to window, upto username text,upto condition returns false
    }
    QSqlQuery q;                    //   QSqlQuery encapsulates the functionality query involved in retrieving data from SQL queries which are executed on a QSqlDatabase
    q.prepare("SELECT *FROM name WHERE username = :username and password = :password");   // Prepares the SQL query query for execution,Here select data of username,password in query if present
    q.bindValue(":username",username);          //bind value :username to username in SQL query
    q.bindValue(":password",password);                //bind value :password to password in SQL query
    if(!q.exec()){                                                   //if query is not executed then Returns true
        qDebug()<<q.lastError().text();                                         //Returns error information
        QMessageBox::information(this,"Query failed","Query failed to execute");   // if it return true, message should be failed to execute
        return;                      //Return back to window, upto mobile number text,upto condition returns false
    }
    int count=0;
    while(q.next()){          //condition for execution of query of text username and password matches,return true
        count++;           //count incremented
    }
    if(count==1){           //if count is 1 ,returns true
        qDebug()<<"login Successful";
        //QMessageBox::information(this,"login is success","login is sucessful");
        hide();
        // displaydialog =new displayDialog(this);
        // displaydialog->show();
        imgdialog=new imgDialog(this);       //opens imageDialog window
        imgdialog->show();

    }
    else{       //if condition returns false
        qDebug()<<"login Failed : Invalid username or Password";        //compile message generated
        QMessageBox::information(this,"login is not success","login is Failed");    // if it return false, message should be failed to execute
    }
}



