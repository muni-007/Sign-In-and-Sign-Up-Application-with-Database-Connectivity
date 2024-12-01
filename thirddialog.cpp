#include "thirddialog.h"
#include "ui_thirddialog.h"
#include<QMessageBox>
#include<QString>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlError>
#include<QtSql/QSqlRecord>
#include<QDebug>
#include<QDate>
#include<QIntValidator>

    QString specialchar="!@#$%^&*()_+=?><.,;'-";             //declaration of special characters
    QString Numericals="0123456789";                                //declaration of numbers

thirdDialog::thirdDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::thirdDialog)
{
    ui->setupUi(this);

    //display a grayed-out placeholder text as long as line edit is empty

     ui->lineEdit_username->setPlaceholderText("Enter the username(8-16 chars)");         //set placeholder text at line_username
     ui->lineEdit_password->setPlaceholderText("Enter the password(8-16 chars)");         //set placeholder text at line_password
     ui->lineEdit_confirm->setPlaceholderText(" Enter confirm password ");                //set placeholder text at line_confirm password
     ui->lineEdit_mobilenumber->setPlaceholderText("Enter Mobile Number(0-9)");          //set placeholder text at line_mobile Number
     ui->lineEdit_address->setPlaceholderText("Enter Address");                          //set placeholder text at line_address

    setupLineEditValidator();                              //function calling -


     // QSql Database interfacing for representing the connection to database

     QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");                       // adds a database to list of database connection
     db.setDatabaseName("C:/project/signup_signin/mydb.db");            //sets the connection database name to name ,it set before connection is opened()
     if(db.open()){                                                                 //if database connection is connected
         ui->label_base->setText("connected to DataBase");            //If it return true ,database is connected
     }
     else{
         ui->label_base->setText("failed to connect DataBase");      //otherwise return false,database is not connected
     }

}

thirdDialog::~thirdDialog()
{
    delete ui;
}

void thirdDialog::on_pushButton_clicked()
{
    QString username=ui->lineEdit_username->text();                //assigning lineEdit_username text as username

    QString password=ui->lineEdit_password->text();            //assigning lineEdit_password text as password

    QString confirm=ui->lineEdit_confirm->text();                   //assigning lineEdit_confirm password text as confirm password

    QString mobileNumber=ui->lineEdit_mobilenumber->text();                          //assigning lineEdit_mobile number text as mobile number

    QString gender;

    //check_username(username);
    int i,j,count=0,count1=0;                      //assigning local varuables

    if(!((username.length()>7)&&(username.length()<16))){                                    //condition for username length should be minimum 8 characters and maximum 15 characters
        QMessageBox::warning(this,"Invalid Username","username should contain atleast 8 characters");  // If it return false, message should be generated
        return;                                                                                   //Return back to window, upto username text,upto condition returns false
    }

    for(i=0;i<username.length();i++){
        QChar a=username.at(i);                          //username text at i th place assigned as a
        if(a.isUpper()){                                           //condition to check upper characters in username line_Edit text each character
            QMessageBox::warning(this,"Invalid Username","Username should contain only lower character");        // If it return true, message should be generated
            return;                                                                //Return back to window, upto username text,upto condition returns false
        }
        else if(specialchar.contains(a)){                         //condition to check special characters in username line_Edit text each character
            QMessageBox::warning(this,"Invalid Username","Username should contain only lower character");   // If it return true, message should be generated
            return;                                                        //Return back to window, upto username text,upto condition returns false
        }
        else if(Numericals.contains(a)){                                //condition to check numericals in username line_Edit text each character
            QMessageBox::warning(this,"Invalid Username","Username should contain only lower character");    // If it return true, message should be generated
            return;                                               //Return back to window, upto username text,upto condition returns false
        }
    }

    //check_password(password);

    if(!((password.length()>7)&&(password.length()<16))){                    //condition for username length should be minimum 8 characters and maximum 15 characters
        QMessageBox::warning(this,"Create Account","password contain atleast 8 characters");  // If it return false, message should be generated
        return;                                                                    //Return back to window, upto username text,upto condition returns false
    }


    for(j=0;j<password.length();j++){
        QChar b=password.at(j);                          //password text at j th place assigned as b
        if(b.isUpper())                            //condition to check upper characters in password line_Edit text each character
        {
            count++;                                     //return true, then count should be increase
            continue;                                        //jump conditional statement for above character,to remove
        }
        else if(specialchar.contains(b)){                  //condition to check special characters in password line_Edit text each character
            count1++;                                              //return true, then count1 should be increase
            continue;                                                      //jump conditional statement for above character,to remove
        }
    }


    if(count==0)                         //conditional statement returns true when count is zero
    {
        QMessageBox::warning(this,"Invalid Password","Password should contain atleast one upper character"); // If it return true, message should be generated
        return;                                                       //Return back to window, upto password text,upto condition returns false
    }
        else if(count1==0)                         //conditional statement returns true when count1 is zero
    {
        QMessageBox::warning(this,"Invalid Password","Password should contain atleast one special character");  // If it return true, message should be generated
        return;                                            //Return back to window, upto password text,upto condition returns false
    }


    if(confirm!=password){                //conditional statement confirm password text is not equal to password text
        QMessageBox::warning(this,"Invalid confirm password","password and confirm password are not identical");  // If it return true, message should be generated
        return;                                      //Return back to window, upto confirm password text,upto condition returns false
    }


    //check_mobileNumber(mobileNumber);

    if(mobileNumber.length()!=10 )             //if mobile number length not equal 10, return true
    {
        QMessageBox::warning(this,"Invalid Mobile Number","Mobile Number must contain 10 digits");  // If it return true, message should be generated
        return;                                            //Return back to window, upto mobile number text,upto condition returns false
    }


    if(ui->male->isChecked()){          //condition holds the radio button male is checked
        gender=ui->male->text();                               //assign radio button(male) text to gender
    }
    else if(ui->female->isChecked()){      //condition holds the radio button female is checked
        gender=ui->female->text();              //assign radio button(female) text to gender
    }
    else if(ui->other->isChecked()){                    //condition holds the radio button female is checked
        gender=ui->other->text();                             //assign radio button(female) text to gender
    }
    else{             //if condition return false
        QMessageBox::warning(this,"Invalid gender","Gender not selected");  // If it return true, message should be generated
        return;                                                                        //Return back to window, upto mobile number text,upto condition returns false
    }



    //Data of Birth
    QString date=ui->comboBox_date->currentText();                   //assigned as date as current text in combobox_date,if selected
    QString month=ui->comboBox_month->currentText();                           //assigned as date as current text in combobox_month,if selected
    QString year=ui->comboBox_year->currentText();                                       //assigned as date as current text in combobox_year,if selected

    QString DOB=QString("%1 %2 %3").arg(date,month,year);                        // returns a copy of this string with the lowest numbered place marker replaced by string date,month,year

    if(DOB.isEmpty()){                              //if its is empty
        QMessageBox::warning(this,"Invaild date of birth","Date of Birth is not selected"); // if it return true, message should be generated
        return;                                                  //Return back to window, upto mobile number text,upto condition returns false
    }
    else if(date=="DATE"){                                     //if date combo box consists of "DATE" text
        QMessageBox::warning(this,"Invaild date of birth","Date is not selected");   // if it return true, message should be generated
        return;                            //Return back to window, upto mobile number text,upto condition returns false
    }
    else if(month=="MONTH"){                                    //if month combo box consists of "MONTH" text
        QMessageBox::warning(this,"Invaild date of birth","Month is not selected");  // if it return true, message should be generated
        return;                          //Return back to window, upto mobile number text,upto condition returns false
    }
    else if(year=="YEAR"){                              //if month combo box consists of "YEAR" text
        QMessageBox::warning(this,"Invaild date of birth","Year is not selected");  // if it return true, message should be generated
        return;                                  //Return back to window, upto mobile number text,upto condition returns false
    }

    int dayInt=date.toInt();                      //Returns the string date converted to an int ,as assigned to dayInt
    int monthInt=ui->comboBox_month->currentIndex();                 //Returns the string month converted to an int ,as assigned to monthInt
    int yearInt=year.toInt();                                //Returns the string date converted to an year ,as assigned to yearInt

    int age = calculate_age(dayInt,monthInt,yearInt);                     //function calling ,assigned as age

    if(!(age>18)){                                                    //if age is not greater than 18 ,then return true
        QMessageBox::warning(this,"Invaild Age","Age must be above 18 years");   // if it return true, message should be generated
        return;                                        //Return back to window, upto mobile number text,upto condition returns false
    }

    //ADDRESS
    QString Address=ui->lineEdit_address->text();                   //assigned address text in line Edit,if selected as address

    if(Address.isEmpty()){                                 //if address is empty,then return true
        QMessageBox::warning(this,"Invaild Address","Address is must contain text");  // if it return true, message should be generated
        return;                                  //Return back to window, upto mobile number text,upto condition returns false
    }

    //COUNTRY
    QString country=ui->comboBox_country->currentText();           //assigned country as current text in combobox_country,if selected
    if(country=="SELECT"){                                                                                 //if country combo box consists of "SELECT" text
        QMessageBox::warning(this,"Invaild Country","Country is not selected");             // if it return true, message should be generated
        return;                                                   //Return back to window, upto mobile number text,upto condition returns false
    }


    QSqlQuery query;                              //   QSqlQuery encapsulates the functionality query involved in retrieving data from SQL queries which are executed on a QSqlDatabase.
    query.prepare("SELECT *FROM name WHERE username=:username");    // Prepares the SQL query query for execution,Here select data of username in query
    {
        query.bindValue(":username",username);    //bind value :username to username in SQL query
        if(query.exec() && query.next())                //condition for execution of query of username and next query of username text matches,return true
        {
            QMessageBox::warning(this,"Invalid username","username already exists");    // if it return true, message should be generated
            return;                                                         //Return back to window, upto mobile number text,upto condition returns false
        }
    }

    QSqlQuery q;                       // QSqlQuery encapsulates the functionality query involved in retrieving data from SQL queries which are executed on a QSqlDatabase
    q.prepare("INSERT INTO name(username,password,confirm,mobileNumber,gender,DOB,age,Address,country)" "VALUES(:username,:password,:confirm,:mobileNumber,:gender,:DOB,:age,:Address,:country)");
                            // Prepares the SQL query q for execution,Here insert data of username,password,confirm password,mobile number,gender,date of birth,age,address,country into database table

     q.bindValue(":username",username);    //bind value :username to username in SQL query
     q.bindValue(":password",password);          //bind value :password to password in SQL query
     q.bindValue(":confirm",confirm);                    //bind value :confirm password to confirm password in SQL query
     q.bindValue(":mobileNumber",mobileNumber);                //bind value :mobile number to mobile number in SQL query
     q.bindValue(":gender",gender);                 //bind value gender: to gender in SQL query
     q.bindValue(":DOB",DOB);                                         //bind value :date of birth to date of birth in SQL query
     q.bindValue(":age",age);                                                   //bind value :age to age in SQL query
     q.bindValue(":Address",Address);           //bind value :address to address in SQL query
     q.bindValue(":country",country);                         //bind value :country to country in SQL query

    if(!q.exec()){                           //if query is not executed then Returns true
        qDebug()<<q.lastError().text();                          //Returns error information
        QMessageBox::information(this,"Create Account","failed");                         // if it return true, message should be failed to create
    }
    else{
        QMessageBox::information(this,"Create Account","account_created");              // if it return , message should be account created
        close();
    }


}

/*void thirdDialog::check_username(QString &u){
    int i;
    if(!((u.length()>7)&&(u.length()<16))){
        QMessageBox::warning(this,"Invalid Username","username should contain atleast 8 characters");
        return;
    }

    for(i=0;i<u.length();i++){
        QChar a=u.at(i);
        if(a.isUpper()){
            QMessageBox::warning(this,"Invalid Username","Username should contain only lower character");
            return;
        }
        else if(specialchar.contains(a)){
            QMessageBox::warning(this,"Invalid Username","Username should contain only lower character");
            return;
        }
        else if(Numericals.contains(a)){
            QMessageBox::warning(this,"Invalid Username","Username should contain only lower character");
            return;
        }
    }
}*/

/*void thirdDialog::check_password(QString &p){

    int j,count=0,count1=0;
    if(!((p.length()>7)&&(p.length()<16))){
        QMessageBox::warning(this,"Create Account","password contain atleast 8 characters");
        return;
    }


    for(j=0;j<p.length();j++){
        QChar b=p.at(j);
        if(b.isUpper())
        {
            count++;
            continue;
        }
        else if(specialchar.contains(b)){
            count1++;
            continue;
        }
    }


    if(count==0)
    {
        QMessageBox::warning(this,"Invalid Password","Password should contain atleast one upper character");
        return;
    }
    else if(count1==0)
    {
        QMessageBox::warning(this,"Invalid Password","Password should contain atleast one special character");
        return;
    }
}*/


/*void thirdDialog::check_mobileNumber(QString &m){
    int k;
    if(!(m.length()==10)){
        QMessageBox::warning(this,"Invalid Mobile Number","Mobile Number must contain 10 digits");
    }

    for(k=0;k<m.length();k++){
        QString c=m.at(k);
        if(Numericals.contains(c)){
            continue;
        }
        else{
            QMessageBox::warning(this,"Invalid Mobile Number","Mobile Number should contain only numerbers (0-9)");
            return;
        }
    }
}*/


int thirdDialog::calculate_age(int day, int month, int year){      //function defination for age calculation


    QDate birthDate(year, month, day);           // Create a QDate object for the birthdate

    QDate currentDate = QDate::currentDate();                    // Get the current date

    int age = currentDate.year() - birthDate.year();       // Calculate the age by subtracting the birthdate from the current date


    if (currentDate.month() < birthDate.month() || (currentDate.month() == birthDate.month() && currentDate.day() < birthDate.day())) {
                                           // Adjust if the birthdate hasn't occurred yet this year
        age--;
    }

    return age;
}

void thirdDialog::setupLineEditValidator() {
    QIntValidator *validator = new QIntValidator(0, 9999999999, this); // Allows only numbers up to 10 digits
    ui->lineEdit_mobilenumber->setValidator(validator); // Apply the validator to the QLineEdit
}
