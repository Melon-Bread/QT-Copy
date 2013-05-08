#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

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
    void on_btnCopy_clicked();

    void on_btnSrcFile_clicked();

    void on_btnCopyDir_clicked();

    void copyCompleted(int exitCode, QProcess::ExitStatus);

private:
    Ui::MainWindow *ui;
    QProcess* cp; // Creates a object that will perform our command

};

#endif // MAINWINDOW_H
