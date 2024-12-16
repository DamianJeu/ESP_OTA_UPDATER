#include "ota_handler.h"
#include "../json_parser/json_parser.h"
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>


Ota_handler::Ota_handler(QObject *parent)
    : QObject{parent}
{}

qint8 Ota_handler::send_start_ota(quint64 fileSize)
{
     QByteArray pkg;
     QDataStream stream(&pkg, QIODevice::WriteOnly);

     QString data = "file size: " + QString::number(fileSize);



    QString headerID = "WOT-31";

    JsonParser * json = new JsonParser();

    json->setHeaderID(headerID);
    json->setHeaderType("OTA");
    json->setCommand( QString::number(static_cast<int>(ota_state::OTA_INIT_CMD),16));
    json->setJsonMessage(data);

    json->createJsonFile();

    QJsonObject jsonObj = json->createJsonFile();

    pkg = QJsonDocument(jsonObj).toJson();

    emit send_data_pkg(pkg);

    delete json;



    return 0;
}


qint8 Ota_handler::send_stop_ota()
{
    return 0;
}

qint8 Ota_handler::send_pkg(ota_state cmd, QByteArray pkg)
{
    Q_UNUSED(cmd);
    Q_UNUSED(pkg);
    return 0;
}

void Ota_handler::on_data_received(const QByteArray &data)
{



    if(data.size())
    {
        switch(data.toHex().at(0))
        {

        case static_cast<int>(ota_state::OTA_GET_DATA_CMD):
        {
            QByteArray pkg;

            pkg.append(static_cast<int>(ota_state::OTA_DATA_CMD));
            pkg.append(data.mid(1));

            //[client]->[ota_handler]->send_pkg->[fileDialog]->getData->[client]->sendpkg

            emit send_data_pkg(pkg);

            break;
        }

        case static_cast<int>(ota_state::OTA_FINISH_CMD):
        {
            break;
        }

        case static_cast<int>(ota_state::OTA_CANCEL_CMD):
        {
            break;
        }



        default:
        {
            qDebug() << "Unknown command";
        }

        };
    }




    Q_UNUSED(data);
}
