#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_btnHelp_pressed();

    void on_btnOpen_pressed();

    void on_btnSave_pressed();

    void on_btnChooseHtml_pressed();

private:
    Ui::MainWindow *ui;
    QString helpText;
};
#endif // MAINWINDOW_H
