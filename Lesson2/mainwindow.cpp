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

     compModel = new QStandardItemModel(this);
     ui->tblvComps->setModel(compModel);

     compModel->setHorizontalHeaderItem(0,new QStandardItem(QString("№")));
     compModel->setHorizontalHeaderItem(1,new QStandardItem(QString("Имя компьютера")));
     compModel->setHorizontalHeaderItem(2,new QStandardItem(QString("IP адрес")));
     compModel->setHorizontalHeaderItem(3,new QStandardItem(QString("MAC адрес")));

     QList<QStandardItem*>list;
     list.append(new QStandardItem("1"));
     list.append(new QStandardItem("comp1"));
     list.append(new QStandardItem("127.0.0.1"));
     list.append(new QStandardItem("00-D8-61-D9-00-CF"));
     compModel->appendRow(list);
     list.clear();
     list.append(new QStandardItem("2"));
     list.append(new QStandardItem("comp2"));
     list.append(new QStandardItem("10.0.0.1"));
     list.append(new QStandardItem("00-D9-61-D9-00-CF"));
     compModel->appendRow(list);
     list.clear();
     list.append(new QStandardItem("3"));
     list.append(new QStandardItem("comp3"));
     list.append(new QStandardItem("10.1.0.1"));
     list.append(new QStandardItem("00-D9-71-D9-00-CF"));
     compModel->appendRow(list);
     list.clear();
     list.append(new QStandardItem("4"));
     list.append(new QStandardItem("comp4"));
     list.append(new QStandardItem("10.1.1.1"));
     list.append(new QStandardItem("00-D9-91-D9-00-CF"));
     compModel->appendRow(list);
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


void MainWindow::on_btnFillColor_pressed()
{
    QModelIndexList lst = ui->tblvComps->selectionModel()->selectedRows();

    for(auto i : lst) {
        int ii = i.model()->columnCount();
        for(int j = 0; j < ii; j++) {
            QStandardItem* item = compModel->item(i.row(), j);
            item->setBackground(QBrush(Qt::GlobalColor::green));
        }
    }

}

