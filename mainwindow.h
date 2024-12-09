#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "file_dialog/filedialog.h"
#include "tcp_client/client.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButtonSearchBin_clicked();

    void on_pushButtonLocalHost_clicked();

private:
    Ui::MainWindow *ui;

    FileDialog *fileDialog;

    Client *client;
};
#endif // MAINWINDOW_H
