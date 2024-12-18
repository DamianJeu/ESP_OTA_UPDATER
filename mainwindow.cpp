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
    ota_handler = new Ota_handler(this);

    connect(client, &Client::connectedToServer, this, [this](){
        ui->labelConnectionStatusInfo->setText("Connected");
        ui->labelConnectionStatusInfo->setStyleSheet("QLabel { background-color : green; }");
        isConnected = true;
    });

    connect(client, &Client::disconnectedFromServer, this, [this](){
        ui->labelConnectionStatusInfo->setText("Disconnected");
        ui->labelConnectionStatusInfo->setStyleSheet("");
        isConnected = false;
    });

    connect(fileDialog,&FileDialog::fileLoaded, this, [this](quint64 fileSize){
        ui->labelBinSizeInfo->setText(QString::number(qCeil(fileSize/1024)));
        this->fileSize = fileSize;
    });

    connect(client, &Client::dataReceived, this, [this](const QByteArray &data){
        ui->textBrowserRawData->append(data.toHex());
    });

    connect(ota_handler, &Ota_handler::send_data_pkg, client, &Client::sendDataToServer);
    connect(client, &Client::dataReceived, ota_handler, &Ota_handler::on_data_received);
    connect(ota_handler, &Ota_handler::send_prepare_chunk, fileDialog, &FileDialog::read_bytes_from);
    connect(fileDialog, &FileDialog::sendData, ota_handler, &Ota_handler::on_send_data_chunk);

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
    if(fileSize && isConnected && !ui->lineEditDeviceID->text().isEmpty())
    {

        ota_handler->send_start_ota(fileSize);
        ota_handler->set_device_id(ui->lineEditDeviceID->text());

    }
    else
    {
        qDebug()<<"File size or connection status is not valid" << "File size: " << fileSize << ", Connection status: " << isConnected;

    }
}

