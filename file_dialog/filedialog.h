#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QObject>
#include <QLabel>
#include <QFileDialog>
#include <QIODevice>
#include <QTextStream>
#include <QFile>
#include <QList>
#include <QScopedPointer>


/**
 * @class FileDialog
 * @brief Handling system files.
 *
 * Allows to open a txt file and handle it for the simulator's needs
 */
class FileDialog : public QObject
{
    Q_OBJECT
public:
    explicit FileDialog(QObject *parent = nullptr);

    ~FileDialog();

public slots:
    void openFolderDialog();
    qint8 read_bytes_from(quint64 from, quint64 to);

signals:

    void fileLoaded(quint64 fileSize);
    void sendData(QByteArray dataChunk);

private:
    QString filePath;
    QByteArray m_data;
    quint64 m_fileSize;

    void openFile();

};

#endif // FILEDIALOG_H
