#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
        connect(ui->Browse, SIGNAL(clicked()),this, SLOT(browse()));
    }

    void MainWindow::browse(){
        files.clear();

        QFileDialog dialog(this);
        dialog.setDirectory(QDir::homePath());
        dialog.setFileMode(QFileDialog::ExistingFiles);

        if(dialog.exec()){
            files = dialog.selectedFiles();
        }

        QString fileListString;
        foreach (QString file, files) {
            fileListString.append("\"" + QFileInfo(file).fileName() + "\"");
        }

        ui->file->setText(fileListString);
    }

    void MainWindow::sendMail()
    {
        Smtp* smtp = new Smtp(ui->username->text(), ui->password->text(), ui->server->text(), ui->port->text().toInt());
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        if(!files.empty())
            smtp->sendMail(ui->username->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(),files);
        else
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
