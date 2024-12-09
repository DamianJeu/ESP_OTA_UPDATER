#ifndef OTA_HANDLER_H
#define OTA_HANDLER_H

#include <QObject>
#include "../tcp_client/client.h"


enum class ota_state
{
    OTA_INFO,
    DOWNLOADING,
    FINISH,
};

class ota_handler : public QObject
{
    Q_OBJECT
public:
    explicit ota_handler(QObject *parent = nullptr);

signals:

  void send_data_pkg(QByteArray data);



public slots:

    quint8 send_start_ota();
    quint8 send_stop_ota();
    quint8 send_pkg(QByteArray pkg);

    void on_data_received(const QByteArray &data);



private:




};

#endif // OTA_HANDLER_H
