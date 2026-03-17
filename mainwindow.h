#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int getBatteryLevel();  // заглушка, потом заменить

private:
    Ui::MainWindow *ui;

private:
    void updateBatteryIndicator(QProgressBar *bar, int value);
};
#endif // MAINWINDOW_H
