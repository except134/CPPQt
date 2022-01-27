#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "parsetext.h"
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_plainTextEdit_textChanged();

    void on_btnAdd_pressed();

    void on_btnDelete_pressed();

    void on_chkbOnlyIcons_stateChanged(int arg1);

    void on_btnUp_pressed();

    void on_btnDown_pressed();

private:
    Ui::MainWindow *ui;
    ParseText *parseText;
    QStandardItemModel *model;
};
#endif // MAINWINDOW_H
