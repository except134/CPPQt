#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMath>

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
    void on_btnTask1Calc_pressed();

    void on_edTask1Result_textChanged(const QString &arg1);

    void on_btnTask2Calc_pressed();

    void on_btnAddHtmlToText1_pressed();

    void on_btnAppendText1ToText2_pressed();

    void on_btnReplaceText1ToText2_2_pressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
