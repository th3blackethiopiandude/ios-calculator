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

    void number_pressed();
    void number_released();
    void mathButtonpressed();
    void equal();
    void equal_pressed();
    void equal_released();
    void equal_on_math();
    void c_pressed();
    void clear_pressed();
    void invert_pressed();
    void percent_pressed();
    void animate();
    void dot_pressed();
    void dot_released();
    void invert_animation_mathButton(QString styleSheet);


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
