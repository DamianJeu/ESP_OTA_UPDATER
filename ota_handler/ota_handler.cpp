#include "ota_handler.h"

Ota_handler::Ota_handler(QObject *parent)
    : QObject{parent}
{}

qint8 Ota_handler::send_start_ota(quint64 fileSize)
{
    QByteArray pkg;
    QDataStream stream(&pkg, QIODevice::WriteOnly);

    QString data = QString("%1").arg(static_cast<quint8>(ota_state::OTA_DATA_CMD), 2, 16, QLatin1Char('0')).toUpper()
                   + ", file size: " + QString::number(fileSize);

    pkg.append(data.toUtf8());

    qDebug() << "file size from send_start_ota: " << pkg;

    if (pkg.isEmpty())
    {
        qDebug() << "Ota_handler, Error: empty pkg";
        return static_cast<quint8>(-1);
    }

    emit send_data_pkg(pkg);

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
