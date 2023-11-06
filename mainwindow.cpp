#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "jlink.h"


void MainWindow::save_windows_parm()
{
    qDebug("%s", __func__);
    settings->setValue("file_path", ui->lineEdit->text().trimmed());
}

void MainWindow::read_windows_parm()
{
    qDebug("%s", __func__);
    settings = new QSettings("setting.ini",QSettings::IniFormat);
    qDebug() << QCoreApplication::applicationDirPath();
    ui->lineEdit->setText(settings->value("file_path").toString());
    target_file_path = settings->value("file_path").toString();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    read_windows_parm();

    connect(&JlinkView::getInstance(), SIGNAL(sig_infoShowHandle(QString)),
            this, SLOT(slot_infoShowHandle(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_infoShowHandle(QString info)
{
    qDebug() << info;
    QDateTime timeCurrent = QDateTime::currentDateTime();
    QString timeStr = timeCurrent.toString("[yyyy-MM-dd hh:mm:ss.zzz]");

    QString str1 = timeStr + ":\n==>" + info + "\n";

    ui->textBrowser->append(str1);

    qDebug() << str1;
}

void MainWindow::on_btn_download_clicked()
{
    JlinkView::getInstance().jlinkLibLoadHandle();
    JlinkView::getInstance().jlinkConnectHandle();
    JlinkView::getInstance().jlinkResetFunc();
}

void MainWindow::on_btn_reset_clicked()
{
    JlinkView::getInstance().JlinkSetResetTypeFuncPtr(JLINKARM_RESET_TYPE_NORMAL);
    JlinkView::getInstance().JlinkResetFuncPtr();
}

void MainWindow::on_btn_disconnect_clicked()
{
    JlinkView::getInstance().jlinkdisconnectHandle();
}

void MainWindow::on_btn_openfile_clicked()
{
    QFileInfo fileinfo = QFileInfo(target_file_path);
    qDebug()<<"bin  absolutePath:" << fileinfo.absolutePath();
    QString tmp = QFileDialog::getOpenFileName(this,"选择bin文件", fileinfo.absolutePath(), "bin文件(*.bin)");
    if(tmp.isEmpty())
        return;
    target_file_path = tmp;
    qDebug() << "file path: " << target_file_path;

    ui->lineEdit->setText(target_file_path);
    save_windows_parm();
}
