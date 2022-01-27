#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    parseText = new ParseText();
    if (!parseText)
        close();
     model = new QStandardItemModel(this);
     ui->listView->setModel(model);

     model->appendRow(new QStandardItem(QIcon("./data/c++.png"),"C++"));
     model->appendRow(new QStandardItem(QIcon("./data/csharp.png"),"C#"));
     model->appendRow(new QStandardItem(QIcon("./data/java.png"),"Java"));
     model->appendRow(new QStandardItem(QIcon("./data/php.png"),"PHP"));
     model->appendRow(new QStandardItem(QIcon("./data/python.png"),"Python"));
     model->appendRow(new QStandardItem(QIcon("./data/javascript.png"),"JavaScript"));
}

MainWindow::~MainWindow()
{
    if (parseText) {
        delete parseText;
        parseText = nullptr;
    }

    delete ui;
}


void MainWindow::on_plainTextEdit_textChanged()
{
    QString str = ui->plainTextEdit->toPlainText();
    if (parseText->Change(str)) {
        ui->plainTextEdit->setPlainText(parseText->GetText());

        QTextCursor cursor = ui->plainTextEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->plainTextEdit->setTextCursor(cursor);
    }
}


void MainWindow::on_btnAdd_pressed()
{
    model->appendRow(new QStandardItem(QIcon("./data/default.png"), ui->edLangToAdd->text()));
}


void MainWindow::on_btnDelete_pressed()
{
    const QModelIndex index = ui->listView->selectionModel()->currentIndex();
    model->removeRow(index.row());
}


void MainWindow::on_chkbOnlyIcons_stateChanged(int arg1)
{
    if(arg1) {
        ui->listView->setViewMode(QListView::IconMode);
    } else {
        ui->listView->setViewMode(QListView::ListMode);
    }
}


void MainWindow::on_btnUp_pressed()
{
    int currRow = ui->listView->selectionModel()->currentIndex().row();
    if(currRow > 0 && ui->listView->selectionModel()->hasSelection()) {
        QStandardItem* item1 = model->takeItem(currRow - 1);
        QStandardItem* item2 = model->takeItem(currRow);
        model->removeRow(currRow);
        model->removeRow(currRow - 1);
        model->insertRow(currRow - 1, item2);
        model->insertRow(currRow, item1);
    }
}


void MainWindow::on_btnDown_pressed()
{
    int currRow = ui->listView->selectionModel()->currentIndex().row();
    if(currRow < model->rowCount() - 1 && ui->listView->selectionModel()->hasSelection()) {
        QStandardItem* item1 = model->takeItem(currRow + 1);
        QStandardItem* item2 = model->takeItem(currRow);
        model->removeRow(currRow + 1);
        model->removeRow(currRow);
        model->insertRow(currRow, item1);
        model->insertRow(currRow + 1, item2);
    }
}

