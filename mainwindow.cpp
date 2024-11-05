#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QTextStream"
#include "QColorDialog"
#include "QFontDialog"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textChanged = false;
    on_actionNew_triggered();

    statusLabel.setMaximumWidth(180);
    statusLabel.setText("lenth:"+QString::number(0)+"  lines:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCussorLabel.setMaximumWidth(180);
    statusCussorLabel.setText("lenth:"+QString::number(0)+"  Col:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCussorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText("周志刚");
    ui->statusbar->addPermanentWidget(author);

    ui->actionCopy->setEnabled(false);
    ui->actionBack->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionRecover->setEnabled(false);
    ui->actionPut->setEnabled(false);

    QPlainTextEdit::LineWrapMode mode = ui->textEdit->lineWrapMode();

    if(mode == QTextEdit::NoWrap){
        ui->textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);

        ui->actionAutoNextLine->setCheckable(false);
    } else {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionAutoNextLine->setCheckable(true);
    }

    ui->actionToolBar->setChecked(true);
    ui->actionStausBar->setChecked(true);
    on_actionShowLine_triggered(false);
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
    SearchDialog dlg(this,ui->textEdit);
    dlg.exec();
}


void MainWindow::on_actionExchange_triggered()
{
    ReplaceDialog dlg(this,ui->textEdit);
    dlg.exec();
}


void MainWindow::on_actionNew_triggered()
{
    if(!userEditConfirmed()){
        return ;
    }
    filePath = "";
    ui->textEdit->clear();
    this->setWindowTitle(tr("新建文本文件 - 编辑器"));

    textChanged = false;
}


void MainWindow::on_actionOpen_triggered()
{
    if(!userEditConfirmed()){
        return ;
    }

    QString filename = QFileDialog::getOpenFileName(this,"打开文件",".",tr("Text files (*.txt) ;; All (*.*)"));
    QFile file(filename);

    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this,"..","打开文件失败");
        return;
    }

    filePath = filename;

    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->insertPlainText(text);
    file.close();

    this->setWindowTitle(QFileInfo(filename).absolutePath());

    textChanged = false;
}


void MainWindow::on_actionSave_triggered()
{
    if(filePath==""){
        QString filename = QFileDialog::getSaveFileName(this,"保存文件",".",
                                                        tr("Text files (*.txt) "));
        QFile file(filename);
        if(!file.open(QFile::WriteOnly|QFile::Text)){
            QMessageBox::warning(this,"..","打开保存文件失败");
            return;
        }
        file.close();
        filePath=filename;
    }

    QFile file(filePath);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"..","打开保存文件失败");
        return;
    }


    QTextStream out(&file);
    QString text = ui ->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absolutePath());

    textChanged = false;
}


void MainWindow::on_actionSaveNew_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,"保存文件",".",
                                                    tr("Text files (*.txt) "));
    QFile file(filename);
    if(!file.open(QFile::WriteOnly|QFile::Text)){
        QMessageBox::warning(this,"..","打开保存文件失败");
        return;
    }

    filePath = filename;

    QTextStream out(&file);
    QString text = ui ->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absolutePath());
}


void MainWindow::on_textEdit_textChanged()
{
    if(!textChanged){
        this->setWindowTitle("*" + this->windowTitle());
        textChanged = true;
    }
    statusLabel.setText("lenth:"+QString::number(ui->textEdit->toPlainText().length())+
                        "  lines:"+
                        QString::number(ui->textEdit->document()->lineCount()));
}

bool MainWindow::userEditConfirmed()
{

    if(textChanged){
        QString path = (filePath != "")? filePath : "无标题.txt";
        QMessageBox msg(this);

        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("...");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否将更改内容保存到\n")+"\""+filePath+ "\" ?" );
        msg.setStandardButtons(QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        int r = msg.exec();
        switch (r) {
        case QMessageBox::Yes:
            on_actionSave_triggered();
            break;
        case QMessageBox::No:
            textChanged = false;
            break;
        case QMessageBox::Cancel:
            return false;
        }
    }
    return true;
}

//撤销
void MainWindow::on_actionBack_triggered()
{
    ui->textEdit->undo();
}

//恢复
void MainWindow::on_actionRecover_triggered()
{
    ui->textEdit->redo();
}

//剪切
void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
    ui->actionPut->setEnabled(true);
}

//复制
void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
    ui->actionPut->setEnabled(true);
}

//粘贴
void MainWindow::on_actionPut_triggered()
{
    ui->textEdit->paste();
}

//复制键与剪切使能设置
void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
}

//恢复键使能设置
void MainWindow::on_textEdit_redoAvailable(bool b)
{
    ui->actionRecover->setEnabled(b);
}

//撤销键使能设置
void MainWindow::on_textEdit_undoAvailable(bool b)
{
    ui->actionBack->setEnabled(b);
}

//字体颜色
void MainWindow::on_actionFontColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black,this,"选择颜色");
    if(color.isValid()){
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit {color:%1}").arg(color.name()));
    }
}

//
void MainWindow::on_actEditBgColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black,this,"选择颜色");
    if(color.isValid()){
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit {background-color:%1}").arg(color.name()));
    }
}


void MainWindow::on_actBgColor_triggered()
{

}


void MainWindow::on_actionAutoNextLine_triggered()
{
    QPlainTextEdit::LineWrapMode mode = ui->textEdit->lineWrapMode();

    if(mode == QTextEdit::NoWrap){
        ui->textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);

        ui->actionAutoNextLine->setCheckable(true);
    } else {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionAutoNextLine->setCheckable(false);
    }
}


void MainWindow::on_actionFont_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok,this);

    if(ok)
        ui->textEdit->setFont(font);
}


void MainWindow::on_actionToolBar_triggered()
{
    bool visable = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visable);
    ui->actionToolBar->setChecked(!visable);
}


void MainWindow::on_actionStausBar_triggered()
{
    bool visable = ui->statusbar->isVisible();
    ui->statusbar->setVisible(!visable);
    ui->actionStausBar->setChecked(!visable);
}

//全选
void MainWindow::on_actionAllChoose_triggered()
{
    ui->textEdit->selectAll();
}


void MainWindow::on_actionExit_triggered()
{
    if(userEditConfirmed()){
        exit(0);
    }
}


void MainWindow::on_textEdit_cursorPositionChanged()
{
    int col = 0;
    int ln = 0;
    int flag =-1;
    int pos=ui->textEdit->textCursor().position();
    QString text = ui->textEdit->toPlainText();

    for(int i=0;i<pos;i++){
        if(text[i]=='\n'){
            ln++;
            flag=i;
        }
    }
    flag++;
    col = pos-flag;
    statusLabel.setText("lenth:"+QString::number(ln+1)+
                        "  lines:"+
                        QString::number(col+1));
}


void MainWindow::on_actionShowLine_triggered(bool checked)
{
    ui->textEdit->hideLineNumberArea(!checked);
}

