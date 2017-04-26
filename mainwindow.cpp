#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "question1.h"
#include "question2.h"
#include "question3.h"
#include "question4.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->edit_q2_input, SIGNAL(textChanged(const QString &)), this, SLOT(calculateArea(const QString &)));
    connect(ui->button_parse, SIGNAL(released()), this, SLOT(handleParse()));

    // First Question

    ui->label_q1_answer->setText("Result: " + QString::number(Question1::getSum(1000)));


    // Third Question
    Question3 q3 = Question3::getInstance();
    std::string strTotal = q3.getAllFibo(1000);

    ui->text_q3_answer->setText("Result: " + QString(QString::fromStdString(strTotal)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * * Handle the change in radius edit box
 *
 */
void MainWindow::calculateArea(const QString &newR)
{
    // Second Question
    QString strInputR = newR;
    double dInputR = strInputR.toDouble();

    double dArea = Question2::getArea(dInputR);
    ui->label_q2_answer->setText("Result: " + QString::number(dArea));
}

/*
 * * Handle button click of parse
 *
 */
void MainWindow::handleParse()
{
    Question4 q4 = Question4::getInstance();
    q4.parse("D:\\qttest\\", "D:\\qttest1\\");
    //q4.parse(ui->edit_q4_inputfile->text(), ui->edit_q4_outputfile->text());
}
