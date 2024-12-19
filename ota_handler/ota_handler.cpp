#include "ota_handler.h"
#include "../json_parser/json_parser.h"
#include <QDataStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

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
    json->setCommand(static_cast<int>(ota_state::OTA_INIT_CMD));
    json->setJsonMessage(data);

    //json->createJsonFile();

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

void Ota_handler::set_device_id(const QString &device_id)
{
    m_deviceID = device_id;
}

void Ota_handler::on_data_received(const QByteArray &data)
{

    QString dataStr = QString::fromUtf8(data);

    std::cout<<"\n\n\n"<<dataStr.toStdString()<<std::endl;

    QByteArray jsonBytes = dataStr.toUtf8();

    QJsonParseError parseError;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonBytes, &parseError);

    if (parseError.error != QJsonParseError::NoError)
    {
        qDebug() << "Error parsing JSON:" << parseError.errorString();
        return;
    }

    if (!jsonDoc.isObject())
    {
        qDebug()<<"is not object!";
        return;
    }

    QString jsonStr = jsonDoc["id"].toString();

    //check if device id and type matches
    if(m_deviceID != jsonStr && (jsonDoc["type"].toString() != "OTA"))
    {
        qDebug()<<"Device ID does not match!";
        return;
    }

    parse_data(jsonDoc);

    qDebug()<<"is object! id: "<<jsonStr;

}

void Ota_handler::on_send_data_chunk(const QByteArray &data)
{
    QByteArray pkg;
    QJsonObject json;

    json["id"] = m_deviceID;
    json["type"] = "OTA";
    json["command"] = static_cast<int>(ota_state::OTA_DATA_CMD);
    json["binary"] = QString::fromLatin1(data.toBase64());

    pkg = QJsonDocument(json).toJson();

    emit send_data_pkg(pkg);
}

void Ota_handler::prepare_data_chunk(quint64 from, quint64 to)
{
    emit send_prepare_chunk(from, to);
}

void Ota_handler::on_get_data_cmd(const QJsonDocument &data)
{
    qint64 start = data["startRange"].toInteger();
    qint64 end = data["endRange"].toInteger();

    prepare_data_chunk(start, end);
}

void Ota_handler::parse_data(const QJsonDocument &data)
{
    quint8 command = data["command"].toInt();

    switch (command)
    {
    case static_cast<int>(ota_state::OTA_DATA_CMD):
        qDebug()<<"OTA_DATA_CMD";
        break;

    case static_cast<int>(ota_state::OTA_FINISH_CMD):
        qDebug()<<"OTA_FINISH_CMD";
        break;

    case static_cast<int>(ota_state::OTA_CANCEL_CMD):
        qDebug()<<"OTA_CANCEL_CMD";
        break;

    case static_cast<int>(ota_state::OTA_GET_DATA_CMD):
        qDebug()<<"OTA_GET_DATA_CMD";
        on_get_data_cmd(data);
        break;

    case static_cast<int>(ota_state::OTA_SUCCESS_CMD):
        qDebug()<<"OTA_SUCCESS_CMD";
        break;

    default:
        break;

    }
}
