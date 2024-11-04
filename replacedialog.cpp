#include "replacedialog.h"
#include "ui_replacedialog.h"
#include "QMessageBox"
ReplaceDialog::ReplaceDialog(QWidget *parent,QPlainTextEdit* textEdit)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    pTextEdit = textEdit;
    ui->rbDown->setChecked(true);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_btnFindNext_clicked()
{
    QString target = ui->FindTarget->text();//查询的目标字符串

    if(target==""||pTextEdit==nullptr)
        return;

    QString text = pTextEdit->toPlainText();//获取文本
    QTextCursor c = pTextEdit->textCursor();
    int index = -1;

    if(ui->rbDown->isChecked()){
        index = text.indexOf(target,c.position(),
                             ui->cbCaseSensitive->isChecked()?Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index>=0){
            c.setPosition(index);
            c.setPosition(index + target.length(),QTextCursor::KeepAnchor);//高亮

            pTextEdit->setTextCursor(c);

        }
    } else if(ui->rbUp->isChecked()) {
        index = text.lastIndexOf(target,c.position()-target.length()-1,
                                 ui->cbCaseSensitive->isChecked()?Qt::CaseSensitive : Qt::CaseInsensitive);
        if(index>=0){
            c.setPosition(index + target.length());
            c.setPosition(index,QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);

        }
    }
    if(index<0){
        QMessageBox msg(this);
        msg.setWindowTitle("记事本");
        msg.setText(QString("找不到")+target);
        msg.setWindowFlag(Qt::Drawer);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}


void ReplaceDialog::on_btnChange_clicked()
{
    QString target = ui->FindTarget->text();//查询的目标字符串
    QString to = ui->changeTarget->text();//替换的字符串

    if((pTextEdit!=nullptr)&&(target!="")&&(to!="")){
        QString selText =pTextEdit->textCursor().selectedText();
        if(selText==target){
            pTextEdit->insertPlainText(to);
        }
    }
    on_btnFindNext_clicked();
}


void ReplaceDialog::on_btnChangeAll_clicked()
{
    QString target = ui->FindTarget->text();//查询的目标字符串
    QString to = ui->changeTarget->text();//替换的字符串

    if((pTextEdit!=nullptr)&&(target!="")&&(to!="")){
        QString text = pTextEdit->toPlainText();

        text.replace(target,to,ui->cbCaseSensitive->isChecked()?Qt::CaseSensitive:Qt::CaseInsensitive);
        pTextEdit->clear();

        pTextEdit->insertPlainText(text);
    }
}


void ReplaceDialog::on_btnCancel_clicked()
{
    accept();
}

