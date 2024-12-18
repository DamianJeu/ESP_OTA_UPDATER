#ifndef OTA_HANDLER_H
#define OTA_HANDLER_H

#include <QObject>
#include "../tcp_client/client.h"


enum class ota_state
{
    OTA_INIT_CMD=0x10,
    OTA_DATA_CMD=0x21,
    OTA_FINISH_CMD=0x32,
    OTA_CANCEL_CMD=0x43,
    OTA_GET_DATA_CMD=0x54,
    OTA_SUCCESS_CMD=0x65,
};

class Ota_handler : public QObject
{
    Q_OBJECT
public:
    explicit Ota_handler(QObject *parent = nullptr);

signals:

    void send_data_pkg(QByteArray data);
    void send_prepare_chunk(quint64 from, quint64 to);



public slots:

    qint8 send_start_ota(quint64 fileSize);
    qint8 send_stop_ota();
    qint8 send_pkg(ota_state cmd, QByteArray pkg);

    void set_device_id(const QString &device_id);

    void on_data_received(const QByteArray &data);

    void on_send_data_chunk(const QByteArray &data);

private:

    bool autoSendPkg = false;

    void parse_data(const QJsonDocument &data);
    void prepare_data_chunk(quint64 from, quint64 to);
    void on_get_data_cmd(const QJsonDocument &data);


    QString m_deviceID;

};

#endif // OTA_HANDLER_H
