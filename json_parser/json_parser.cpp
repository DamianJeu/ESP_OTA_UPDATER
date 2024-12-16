#include "json_parser.h"
#include <QStringList>
#include <QJsonDocument>


JsonParser::JsonParser(QObject *parent)
    : QObject{parent}
{

}

JsonParser::~JsonParser()
{
    qDebug()<<"JsonParser destroyed..";
}

QJsonObject JsonParser::createJsonFile()
{
    QJsonObject json;

    json["id"] = m_headerID;
    json["type"] = m_headerType;
    json["command"] = m_command;
    json["message"] = m_jsonMessage;

    m_json = json;

    emit jsonFileCreated(json);

    qDebug()<<"Json file created.." << m_json;

    return json;
}

QString JsonParser::headerID() const
{
    return m_headerID;
}

void JsonParser::setHeaderID(const QString &newHeaderID)
{
    m_headerID = newHeaderID;
}

QString JsonParser::headerType() const
{
    return m_headerType;
}

void JsonParser::setHeaderType(const QString &newHeaderType)
{
    m_headerType = newHeaderType;
}

void JsonParser::setJsonMessage(const QString &newJsonMessage)
{
    m_jsonMessage = newJsonMessage;
}

QString JsonParser::jsonMessage() const
{
    return m_jsonMessage;
}

QString JsonParser::command() const
{
    return m_command;
}

void JsonParser::setCommand(const QString &newCommand)
{
    m_command = newCommand;
}






