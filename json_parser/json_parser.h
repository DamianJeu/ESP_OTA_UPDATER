#ifndef CRUSHJSON_H
#define CRUSHJSON_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>

class JsonParser : public QObject
{
    Q_OBJECT
public:
    explicit JsonParser(QObject *parent = nullptr);
    ~JsonParser();

    QString headerID() const;
    void setHeaderID(const QString &newHeaderID);

    QString headerType() const;
    void setHeaderType(const QString &newHeaderType);

    QString command() const;
    void setCommand(const QString & newCommand);

    QString jsonMessage() const;
    void setJsonMessage(const QString &newJsonSize);



public slots:

    QJsonObject createJsonFile();


signals:

    emit void jsonFileCreated(QJsonObject &json);
    emit void jsonErrorLog(QString &error);

private:

QString m_headerID;
QString m_headerType;
QString m_jsonMessage;
QString m_command;


QJsonObject m_json;

};

#endif // CRUSHJSON_H