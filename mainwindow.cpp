#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h".h"
#include "replacedialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    statusLabel.setMaximumWidth(150);
    statusLabel.setText("lenth:"+QString::number(0)+"  lines:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCussorLabel.setMaximumWidth(150);
    statusCussorLabel.setText("lenth:"+QString::number(0)+"  Col:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCussorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText("周志刚");
    ui->statusbar->addPermanentWidget(author);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionSeach_triggered()
{
    SearchDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionExchange_triggered()
{
    ReplaceDialog dlg;
    dlg.exec();
}

