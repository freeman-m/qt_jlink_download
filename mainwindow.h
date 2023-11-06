#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QDateTime>
#include <QSettings>
#include <QFileDialog>
#include <QFile>
#include <QCloseEvent>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void slot_infoShowHandle(QString info);     // jlink消息显示槽函数

    void on_btn_download_clicked();

    void on_btn_reset_clicked();

    void on_btn_disconnect_clicked();

    void on_btn_openfile_clicked();

private:
    Ui::MainWindow *ui;

    // 配置文件对象
    QSettings *settings;

    QTimer *timer_burn;

    QString target_file_path;

    void save_windows_parm();
    void read_windows_parm();
};

#endif // MAINWINDOW_H
