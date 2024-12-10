#ifndef OTA_HANDLER_H
#define OTA_HANDLER_H

#include <QObject>
#include "../tcp_client/client.h"


enum class ota_state
{
    OTA_START_CMD=0x10,
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

public slots:

    qint8 send_start_ota(quint64 fileSize);
    qint8 send_stop_ota();
    qint8 send_pkg(ota_state cmd, QByteArray pkg);

    void on_data_received(const QByteArray &data);

private:

    bool autoSendPkg = false;

};

#endif // OTA_HANDLER_H
