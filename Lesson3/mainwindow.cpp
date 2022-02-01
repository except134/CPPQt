#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QResource>
#include <QFileDialog>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(":/Help.txt");
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        helpText = stream.readAll();
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnHelp_pressed()
{
    static bool helpOpened = false;
    static QString old{};

    if(helpOpened) {
        ui->textEdit->setPlainText(old);
        old.clear();
    } else {
        old = ui->textEdit->toPlainText();
        ui->textEdit->setPlainText(helpText);
    }

    helpOpened = !helpOpened;

    ui->textEdit->setReadOnly(helpOpened);
    ui->btnOpen->setEnabled(!helpOpened);
    ui->btnSave->setEnabled(!helpOpened);
}


void MainWindow::on_btnOpen_pressed()
{
    QFileDialog::Options options;
    //options |= QFileDialog::DontUseNativeDialog;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Выберите файл"),
                                   tr("./"),
                                   tr("All Files (*);;Text Files (*.txt)"),
                                   &selectedFilter,
                                   options);
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly)) {
            QTextStream stream(&file);
            ui->textEdit->setPlainText(stream.readAll());
            file.close();
        }
    }
}


void MainWindow::on_btnSave_pressed()
{
    QFileDialog::Options options;
    //options |= QFileDialog::DontUseNativeDialog;
    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(this,
                                   tr("Выберите файл"),
                                   tr("./"),
                                   tr("All Files (*);;Text Files (*.txt)"),
                                   &selectedFilter,
                                   options);
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)) {
            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            file.close();
        }
    }
}


void MainWindow::on_btnChooseHtml_pressed()
{
    QString textToParse;
    QFileDialog::Options options;
    //options |= QFileDialog::DontUseNativeDialog;
    QString selectedFilter;
    QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Выберите файл"),
                                   tr("./"),
                                   tr("All Files (*);;Text Files (*.html)"),
                                   &selectedFilter,
                                   options);
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly)) {
            QTextStream stream(&file);
            textToParse = stream.readAll();
            file.close();
        }
    }

    {
        QRegularExpression reg { "\"temp\":\"(.+)\",\"tempFeelsLike\":\"(.+)\",\"description\":\"(.+)\"" };
        QRegularExpressionMatch match { reg.match(textToParse) };
        QString w = "Температура: " + match.captured(1);
        ui->edWeather->setText(w);
    }

    {
        QRegularExpression reg { "\"type\":\"USD\",\"rate\":(.+)" };
        QRegularExpressionMatch match { reg.match(textToParse) };
        QString w = match.captured(1);
        w.truncate(w.indexOf(','));
        ui->edCurses->setText("Доллар: " +  w);
    }
}

