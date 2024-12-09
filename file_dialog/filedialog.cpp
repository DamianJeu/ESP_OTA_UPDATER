#include "filedialog.h"

/**
 * @brief Constructor FileDialog class.
 */
FileDialog::FileDialog(QObject *parent)
    : QObject{parent}
{



}

/**
 * @brief Deconstructor FileDialog class.
 */
FileDialog::~FileDialog()
{
    qDebug() << "File dialog destroyed!";
}

/**
 * @brief Opens a dialog window to choose a file.
 *
 * Opens a dialog window to choose a file.
 */
void FileDialog::openFolderDialog()
{
    QString path = QFileDialog::getOpenFileName(nullptr, tr("Wybierz plik"), "/home",tr("Text files (*.bin)"));

    if (!path.isEmpty())
    {
        filePath=path;
        qDebug () << "Folder path: " << filePath;
        openFile();
    }
}

qint8 FileDialog::read_bytes_from(quint64 from, quint64 to)
{

    if (from >= m_fileSize || to >= m_fileSize)
    {
        qDebug() << "Invalid range!";
        return -1;
    }

    QByteArray dataChunk = m_data.mid(from, to - from + 1);

    emit sendData(dataChunk);

    return 0;
}

/**
 * @brief Opens a file.
 *
 * Opens a file and reads it line by line.
 */
void FileDialog::openFile()
{
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open file!";
        return;
    }


    m_fileSize = file.size();

    m_data = file.readAll();

    emit fileLoaded(m_fileSize);

    qDebug()<< "File size: " << m_fileSize << " bytes. \n" << m_data;



    file.close();
    qDebug() << "File closed!";

}


