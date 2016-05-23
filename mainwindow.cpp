#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QString>
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        QTimer *timer;
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()),
              this, SLOT(StatusUpdate()));
        timer->start(10000);
    StatusUpdate();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::StatusUpdate(){
    pid_t nginx = system("pidof -s nginx");
    pid_t mysqld = system("pidof -s mysqld");
    pid_t php5fpm = system("pidof -s php5-fpm");
    if(nginx != 256)
        ui->label_3->setText("Running");
    else
        ui->label_3->setText("Not Running");
    if(mysqld != 256)
        ui->label_5->setText("Running");
    else
        ui->label_5->setText("Not Running");
    if(php5fpm != 256)
        ui->label_7->setText("Running");
    else
        ui->label_7->setText("Not Running");
}

void MainWindow::bash(QString command)
{
    QProcess *p = new QProcess( this );

    if (p)
    {
      p->setEnvironment( QProcess::systemEnvironment() );
      p->setProcessChannelMode( QProcess::MergedChannels );

      p->start( command );
      p->waitForStarted();

      connect( p, SIGNAL(readyReadStandardOutput()), this, SLOT(ReadOut()) );
      connect( p, SIGNAL(readyReadStandardError()), this, SLOT(ReadErr()) );
    }

}

void MainWindow::ReadOut(){
    QProcess *p = dynamic_cast<QProcess *>( sender() );

    if (p){
        ui->textBrowser->append( p->readAllStandardOutput() );
    }
}
void MainWindow::ReadErr(){
    QProcess *p = dynamic_cast<QProcess *>( sender() );

    if (p){
        ui->textBrowser->append( p->readAllStandardError() );
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    bash("service nginx restart");
}

void MainWindow::on_mysql_clicked()
{
    bash("service mysql restart");
}

void MainWindow::on_php5_clicked()
{
    bash("service php5-fpm restart");
}

void MainWindow::on_pushButton_clicked()
{
    bash("service nginx restart");
    bash("service mysql restart");
    bash("service php5-fpm restart");

}

void MainWindow::on_pushButton_2_clicked()
{
    bash("service nginx stop");
    bash("service mysql stop");
    bash("service php5-fpm stop");
}

void MainWindow::on_pushButton_3_clicked()
{
    StatusUpdate();
}
