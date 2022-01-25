#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <limits>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

static bool IsEqual(double left, double right, double eps = std::numeric_limits<double>::epsilon())
{
   return qAbs(left - right) < eps;
}

void MainWindow::on_btnTask1Calc_pressed()
{
    double a = ui->edA->text().toDouble();
    double b = ui->edB->text().toDouble();
    double c = ui->edC->text().toDouble();

    double discriminant = b * b - 4 * a * c;

    double x1{};
    double x2{};

    if (discriminant < 0.0) {
        ui->edTask1Result->setText("Действительных корней уравнения не существует.");
    } else if(IsEqual(0.0, a)) {
        if (IsEqual(0.0, b)) {
            if (IsEqual(0.0, c)) {
                ui->edTask1Result->setText("Существует бесконечное множество решений.");
             } else {
                ui->edTask1Result->setText("Действительных корней уравнения не существует.");
            }
        } else {
            x1 = -c/b;
            ui->edTask1Result->setText("x1 = x2 = " + QString::number(x1));
        }
    } else {
        double discriminantSqrt = qSqrt(discriminant);
        if (IsEqual(0.0, b)) {
            x1 = discriminantSqrt / (2 * a);
            ui->edTask1Result->setText("x1 = x2 = " + QString::number(x1));
        } else if(IsEqual(0.0, discriminant)) {
            x1 = -(b / (2 * a));
            ui->edTask1Result->setText("x1 = x2 = " + QString::number(x1));
        } else {
            x1 = (-b + discriminantSqrt) / (2 * a);
            x2 = (-b - discriminantSqrt) / (2 * a);
            ui->edTask1Result->setText("x1 = " + QString::number(x1) + ", x2 = " + QString::number(x2));
        }
    }
}

void MainWindow::on_edTask1Result_textChanged(const QString &arg1)
{
    if(arg1.startsWith("x1")) {
        ui->edTask1Result->setStyleSheet("#edTask1Result { color: black;}");
    } else {
        ui->edTask1Result->setStyleSheet("#edTask1Result { color: red;}");
    }
}


void MainWindow::on_btnTask2Calc_pressed()
{
    double a = ui->edTriA->text().toDouble();
    double b = ui->edTriB->text().toDouble();
    double angle = ui->edAngle->text().toDouble();

    if(ui->rbDegree->isChecked())
        angle = qDegreesToRadians(angle);

    double c = qSqrt(a * a + b * b - 2 * a * b * qCos(angle));

    ui->edTask2Result->setText("Сторона C = " + QString::number(c));
}

void MainWindow::on_btnAddHtmlToText1_pressed()
{
    ui->pteText1->appendHtml("<font color='red'>Hello HTML!</font>");
}


void MainWindow::on_btnAppendText1ToText2_pressed()
{
    ui->pteText2->appendHtml(ui->pteText1->document()->toHtml());
}


void MainWindow::on_btnReplaceText1ToText2_2_pressed()
{
    ui->pteText2->clear();
    ui->pteText2->appendHtml(ui->pteText1->document()->toHtml());
}

