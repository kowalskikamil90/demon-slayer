#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QIcon>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    QVBoxLayout *menuLayout;
    QPushButton *startBtn;
    QPushButton *exitBtn;
    QLabel *title;
    QPixmap *titlePm;
    QIcon *startIc;
    QIcon *exitIc;

private slots:

    void switchToGameMode();
};

#endif // MAINWINDOW_H
