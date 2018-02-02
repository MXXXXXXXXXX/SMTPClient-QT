#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    }

    void MainWindow::sendMail()
    {
        Smtp* smtp = new Smtp(ui->username->text(), ui->password->text(), ui->server->text(), ui->port->text().toInt());
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


        smtp->sendMail(ui->username->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
    }

    void MainWindow::mailSent(QString status)
    {
        if(status == "Message sent")
            QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
        ui->msg->clear();
        ui->subject->clear();
    }

    MainWindow::~MainWindow()
    {
        qDebug() << "delete ui";
        delete ui;
    }
