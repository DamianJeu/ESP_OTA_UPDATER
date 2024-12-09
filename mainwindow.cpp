#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //my objects
    fileDialog = new FileDialog(this);
    client = new Client(this);

    connect(client, &Client::connectedToServer, this, [this](){
        ui->labelConnectionStatusInfo->setText("Connected");
        ui->labelConnectionStatusInfo->setStyleSheet("QLabel { background-color : green; }");
    });

    connect(client, &Client::disconnectedFromServer, this, [this](){
        ui->labelConnectionStatusInfo->setText("Disconnected");
        ui->labelConnectionStatusInfo->setStyleSheet("");
    });

    connect(fileDialog,&FileDialog::fileLoaded, this, [this](quint64 fileSize){
        ui->labelBinSizeInfo->setText(QString::number(fileSize));
    });
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


void MainWindow::on_pushButtonConnect_clicked()
{
    client->setHost(QHostAddress(ui->lineEditIpAddress->text()));
    client->setPort(ui->spinBoxPort->text().toUShort());
    client->connectToServer();
}


void MainWindow::on_pushButtonDisconnect_clicked()
{
    client->disconnectFromServer();
}





void MainWindow::on_pushButtonStartOta_clicked()
{

    QByteArray data;
    data.resize(1);
    data[0] = 0x3c;
    client->sendDataToServer(data);
}

