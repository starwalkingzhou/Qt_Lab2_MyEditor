#include "searchdialog.h"
#include "ui_searchdialog.h"
#include "QMessageBox"
SearchDialog::SearchDialog(QWidget *parent,QPlainTextEdit* textEdit)
    : QDialog(parent)
    , ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    pTextEdit = textEdit;
    ui->rbDown->setChecked(true);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_btnFindNext_clicked()
{
    QString target = ui->seachText->text();//查询的目标字符串

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


void SearchDialog::on_btnCancel_clicked()
{
    accept();
}

