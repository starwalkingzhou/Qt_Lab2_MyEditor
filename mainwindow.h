#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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
    void on_actionAbout_triggered();

    void on_actionSeach_triggered();

    void on_actionExchange_triggered();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveNew_triggered();

    void on_textEdit_textChanged();

    void on_actionBack_triggered();

    void on_actionRecover_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPut_triggered();

    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_redoAvailable(bool b);

    void on_textEdit_undoAvailable(bool b);

    void on_actionFontColor_triggered();

    void on_actEditBgColor_triggered();

    void on_actBgColor_triggered();

    void on_actionAutoNextLine_triggered();

    void on_actionFont_triggered();

private:
    Ui::MainWindow *ui;

    QLabel statusCussorLabel;
    QLabel statusLabel;

    QString filePath;
    bool textChanged;

    bool userEditConfirmed();
};
#endif // MAINWINDOW_H
