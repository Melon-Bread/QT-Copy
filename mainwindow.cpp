#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QProcess"
#include "QMessageBox"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cp = new QProcess(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSrcFile_clicked()
{
    // Makes a open file dialog come up
    QString srcFile = QFileDialog::getOpenFileName(this, tr("Select Source File"), QString(), tr("All Files *.*"));

    // Takes the file location of the file selected from dialog and feeds it to first text box.
    ui->leditSource->setText(srcFile);
}

void MainWindow::on_btnCopyDir_clicked()
{
    // Makes a mondified  file dialog come up that onll lets you select a directory
    QString copyDir = QFileDialog::getExistingDirectory(this, tr("Copy Location"), QString(), QFileDialog::ShowDirsOnly);

    // Takes the new directory of the file selected from dialog and feeds it to second text box.
    ui->leditCopy->setText(copyDir);
}

void MainWindow::on_btnCopy_clicked()
{      
    // Connects our copy proccess to our copyCompleted event
    connect(cp, SIGNAL(finished(int, QProcess::ExitStatus)), this,
            SLOT(copyCompleted(int, QProcess::ExitStatus)));
    
    QString copyCommand;
    
    // Checks if the user is running Windows and sets the propper copy command
    #ifdef W_WS_WIN32
    copyCommand = "copy ";
    #else
    // Set the proper copy command for Linux, OSX, etc.
    copyCommand = "cp ";
    #endif
    

    // Performs the command: "cp '/your/source/file.txt' '/your/copy/location'"
    cp->start(copyCommand + ui->leditSource->text() + " " + ui->leditCopy->text());
    
    // Freezes our UI untill the proccess is complete
    cp->waitForFinished(-1);

}

void MainWindow::copyCompleted(int exitCode, QProcess::ExitStatus)
{

    QMessageBox confirmation;
    if(exitCode == 0)
    {
    // Throws up a confirmation if their proccess went all right 
    confirmation.setIcon(QMessageBox::Information);
    confirmation.setText("Copy Completed!");
    }

    else
    {
        // Throws up a warning messege if something does not go right
        confirmation.setIcon(QMessageBox::Warning);
        confirmation.setText("Copy Failed!");
    }
    confirmation.exec();
}



