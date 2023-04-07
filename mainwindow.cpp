#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
double calculatorValue = 0, secondValue = 0, result = 0;
bool divTrigger;
bool mulTrigger;
bool addTrigger;
bool subTrigger;
bool equalPressed = false;
bool clear = true;
bool dot;
bool once = false;
bool same;
char opreator;
int numCounter = 0;
const QString DIVISION_SYMBOL = "\u00F7";
const QString MULTIPLICATION_SYMBOL = "\u00D7";
const QString SUBSTRACTION_SYMBOL = "\u2212";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->inputField->setReadOnly(true);
    ui->inputField->setText(QString::number(calculatorValue));
    ui->divideButton->setText(QString::fromUtf8("\u00F7"));
    ui->multiplyButton->setText(QString::fromUtf8("\u00D7"));
    ui->subButton->setText(QString::fromUtf8("\u2212"));
    QPushButton *numButtons[10];
    for(int i=0; i < 10; i++){
        QString btnName = "button" + QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(btnName);
        connect(numButtons[i], SIGNAL(pressed()), this, SLOT(number_pressed()));
        connect(numButtons[i], SIGNAL(released()), this, SLOT(number_released()));
    }
    connect(ui->divideButton, SIGNAL(pressed()), this, SLOT(mathButtonpressed()));
    connect(ui->multiplyButton, SIGNAL(pressed()), this, SLOT(mathButtonpressed()));
    connect(ui->addButton, SIGNAL(pressed()), this, SLOT(mathButtonpressed()));
    connect(ui->subButton, SIGNAL(pressed()), this, SLOT(mathButtonpressed()));
    connect(ui->equalsButton, SIGNAL(pressed()), this, SLOT(equal_pressed()));
    connect(ui->equalsButton, SIGNAL(pressed()), this, SLOT(equal()));
    connect(ui->equalsButton, SIGNAL(released()), this, SLOT(equal_released()));
    //connect(ui->clearButton, SIGNAL(pressed()), this, SLOT(clear_pressed()));
    connect(ui->clearButton, SIGNAL(pressed()), this, SLOT(c_pressed()));
    connect(ui->invertButton, SIGNAL(pressed()), this, SLOT(invert_pressed()));
    connect(ui->percentButton, SIGNAL(pressed()), this, SLOT(percent_pressed()));
    connect(ui->dotButton, SIGNAL(pressed()), this, SLOT(dot_pressed()));
    connect(ui->dotButton, SIGNAL(released()), this, SLOT(dot_released()));
    connect(ui->clearButton, SIGNAL(released()), this, SLOT(animate()));
    connect(ui->invertButton, SIGNAL(released()), this, SLOT(animate()));
    connect(ui->percentButton, SIGNAL(released()), this, SLOT(animate()));
}

MainWindow::~MainWindow()
{

    delete ui;
}
void MainWindow::invert_animation_mathButton(QString styleSheet){
    ui->divideButton->setStyleSheet(styleSheet);
    ui->multiplyButton->setStyleSheet(styleSheet);
    ui->addButton->setStyleSheet(styleSheet);
    ui->subButton->setStyleSheet(styleSheet);
}
void MainWindow::c_pressed(){
    QString styleSheet = "QPushButton {background-color: #ff9601; color: #ffffff; font: 17pt \"Helvetica\"; text-align: center; border-radius:27px;}";
    invert_animation_mathButton(styleSheet);
    styleSheet = "background-color: #dadada;color: #000000;font: 15pt \"Helvetica\";text-align: center;border-radius:27px;";
    ui->clearButton->setStyleSheet(styleSheet);
    styleSheet = "QPushButton {background-color: #ffffff; color: #ff9601; font: 17pt \"Helvetica\"; text-align: center; border-radius:27px;}";
    ui->inputField->setText("0");
    if(clear){
        clear_pressed();
    }else{
        ui->clearButton->setText("AC");
        clear = true;
        if(divTrigger)
             ui->divideButton->setStyleSheet(styleSheet);
        else if(mulTrigger)
            ui->multiplyButton->setStyleSheet(styleSheet);
        else if(addTrigger)
            ui->addButton->setStyleSheet(styleSheet);
        else if(subTrigger)
            ui->subButton->setStyleSheet(styleSheet);

    }

}
void MainWindow::number_pressed(){
    clear = false;
    QString styleSheet = "QPushButton {background-color: #ff9601; color: #ffffff; font: 17pt \"Helvetica\"; text-align: center; border-radius:27px;}";
    invert_animation_mathButton(styleSheet);

    QPushButton *button = (QPushButton *)sender();
    styleSheet = "background-color: #737373; color: #ffffff; font: 20pt \"Helvetica Light\"; text-align: center; border-radius:27px;";
    button->setStyleSheet(styleSheet);
    QString btnValue = button->text();
    if(btnValue.toDouble() != 0)
         ui->clearButton->setText("C");
    QString displayValue = ui->inputField->text();
    dot = false;
    for (QChar ch : displayValue) {
        if(ch == '.')
            dot = true;
    }

    if((displayValue.toDouble() == 0 && !dot) || ((divTrigger || mulTrigger || addTrigger || subTrigger) && (!once)) || equalPressed){
        ui->inputField->setText(btnValue);
        once = true;
        equalPressed = false;
    }
    else{
        ///double dValue = (displayValue + btnValue).toDouble();
        ///QString::number(dValue, 'g', 16)
        ui->inputField->setText(displayValue + btnValue);
    }

    numCounter++;


}

void MainWindow::mathButtonpressed(){
    //MainWindow::setCursor("Arrow")
    QString styleSheet = "QPushButton {background-color: #ff9601; color: #ffffff; font: 17pt \"Helvetica\"; text-align: center; border-radius:27px;}";
    invert_animation_mathButton(styleSheet);

    QPushButton *button = (QPushButton *)sender();
    QString opr = button->text();
    styleSheet = "QPushButton {background-color: #ffffff; color: #ff9601; font: 17pt \"Helvetica\"; text-align: center; border-radius:27px;}";
    button->setStyleSheet(styleSheet);
    if(numCounter >= 2){
        if(divTrigger || mulTrigger || addTrigger || subTrigger)
            equal_on_math();
        numCounter = 1;
    }
    if(opr == DIVISION_SYMBOL){
        divTrigger = true;
        mulTrigger = false;
        addTrigger = false;
        subTrigger = false;
        opreator = '/';
    }
    else if (opr == MULTIPLICATION_SYMBOL){
        mulTrigger = true;
        divTrigger = false;
        addTrigger = false;
        subTrigger = false;
        opreator = '*';
    }
    else if (opr == SUBSTRACTION_SYMBOL){

         subTrigger = true;
         addTrigger = false;
         divTrigger = false;
         mulTrigger = false;
         opreator = '-';
    }
    else{
        addTrigger = true;
        subTrigger = false;
        divTrigger = false;
        mulTrigger = false;
        opreator = '+';
    }
    calculatorValue = ui->inputField->text().toDouble();
    equalPressed = false;
    once = false;
    //ui->inputField->setText("");
}
void MainWindow::equal(){
    QString styleSheet = "background-color: #f9c792; color: #ffffff; font: 17pt \"Helvetica\"; text-align: center; border-radius:27px;";
    ui->equalsButton->setStyleSheet(styleSheet);
}
void MainWindow::equal_pressed(){
    QString styleSheet = "QPushButton {background-color: #ff9601; color: #ffffff; font: 17pt \"Helvetica\"; text-align: center; border-radius:27px;}";
    invert_animation_mathButton(styleSheet);
    result = 0;
    if(!equalPressed)
        secondValue = ui->inputField->text().toDouble();
    else{
        switch (opreator){
            case '+':
                addTrigger = true;
                break;
            case '-':
                subTrigger = true;
                break;
            case '/':
                divTrigger = true;
                break;
            case '*':
                mulTrigger = true;
                break;
        }
    }
    if(divTrigger)
        result = calculatorValue / secondValue;
    else if(mulTrigger)
        result = calculatorValue * secondValue;
    else if(addTrigger)
        result = calculatorValue + secondValue;
    else if(subTrigger)
        result = calculatorValue - secondValue;
    else
        result = ui->inputField->text().toDouble();

    if(fabs(result - secondValue) < 0.00001)
        same = true;
    else
        same = false;
    if(same)
        ui->inputField->setText("");

    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
    equalPressed = true;
    once = false;
    //calculatorValue = ui->inputField->text().toDouble();
    calculatorValue = result;

}
void MainWindow::equal_on_math(){
    double result, secondValue = ui->inputField->text().toDouble();
    if(divTrigger)
        result = calculatorValue / secondValue;
    else if(mulTrigger)
        result = calculatorValue * secondValue;
    else if(addTrigger)
        result = calculatorValue + secondValue;
    else if(subTrigger)
        result = calculatorValue - secondValue;
    else
        result = ui->inputField->text().toDouble();
    ui->inputField->setText(QString::number(result));
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
    //equalPressed = true;
}
void MainWindow::clear_pressed(){
    QString styleSheet = "QPushButton {background-color: #ff9601; color: #ffffff; font: 17pt \"Helvetica\"; text-align: center; border-radius:27px;}";
    invert_animation_mathButton(styleSheet);
    styleSheet = "background-color: #dadada;color: #000000;font: 15pt \"Helvetica\";text-align: center;border-radius:27px;";
    ui->clearButton->setStyleSheet(styleSheet);
    equalPressed = false;
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
    once = false;
    calculatorValue = 0;
    secondValue = 0;
    numCounter = 0;
    ui->inputField->setText(QString::number(calculatorValue));
}
void MainWindow::invert_pressed(){
    QString styleSheet = "background-color: #dadada;color: #000000;font: 15pt \"Helvetica\";text-align: center;border-radius:27px;";
    ui->invertButton->setStyleSheet(styleSheet);
    ui->inputField->setText(QString::number(ui->inputField->text().toDouble() * -1));
}
void MainWindow::percent_pressed(){
    QString styleSheet = "background-color: #dadada;color: #000000;font: 15pt \"Helvetica\";text-align: center;border-radius:27px;";
    ui->percentButton->setStyleSheet(styleSheet);
    ui->inputField->setText(QString::number(ui->inputField->text().toDouble() / 100));
}
void MainWindow::dot_pressed(){
    QString styleSheet = "background-color: #737373; color: #ffffff; font: 20pt \"Helvetica Light\"; text-align: center; border-radius:27px;";
    ui->dotButton->setStyleSheet(styleSheet);
    QString displayValue = ui->inputField->text();
    dot = false;
    for (QChar ch : displayValue) {
        if(ch == '.')
            dot = true;
    }
    if(!dot || !once){
        if((dot) || ((divTrigger || mulTrigger || addTrigger || subTrigger) && (!once)) || equalPressed){
            ui->inputField->setText("0.");
            once = true;
            equalPressed = false;
        }
        else
            ui->inputField->setText(ui->inputField->text() + ".");
    }

}
void MainWindow::dot_released(){
    QString styleSheet = "background-color: #333333; color: #ffffff; font: 20pt \"Helvetica Light\"; text-align: center; border-radius:27px;";
    ui->dotButton->setStyleSheet(styleSheet);
}
void MainWindow::number_released(){
    QPushButton *button = (QPushButton *)sender();
    QString styleSheet = "background-color: #333333;color: #ffffff;font: 20pt \"Helvetica Light\";text-align: center;border-radius:27px;";
    button->setStyleSheet(styleSheet);
}
void MainWindow::equal_released(){
    QPushButton *button = (QPushButton *)sender();
    QString styleSheet = "background-color: #ff9601; color: #ffffff; font: 17pt \"Helvetica\"; text-align: center; border-radius:27px;";
    button->setStyleSheet(styleSheet);
    ui->inputField->setText(QString::number(result));

}
void MainWindow::animate(){
    QPushButton *button = (QPushButton *)sender();
    QString styleSheet = "background-color: #a6a6a6;color: #000000;font: 15pt \"Helvetica\";text-align: center;border-radius:27px;";
    button->setStyleSheet(styleSheet);
}



