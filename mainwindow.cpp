#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileDialog = new FileDialog(this);

    client = new Client(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonSearchBin_clicked()
{

    fileDialog->openFolderDialog();


}





void MainWindow::on_pushButtonLocalHost_clicked()
{


    client->setHost(QHostAddress::LocalHost);
    client->setPort(1234);

    ui->lineEditIpAddress->setText(client->host().toString());
    ui->spinBoxPort->setValue(client->port());

}

