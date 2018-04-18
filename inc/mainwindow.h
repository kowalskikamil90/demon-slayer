#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "menuwidget.h"
#include "gamewidget.h"
#include <QStackedWidget>
#include <QDialog>

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    /* Stacked widget for switching modes */
    QStackedWidget *_stackWidged;

    /* Widget containing all menu screen items */
    MenuWidget *_menuWidget;

    /* Widget containing all menu screen items */
    GameWidget *_gameWidget;

private slots:

    void switchToGameMode();
    void switchToMenuMode();
};

#endif // MAINWINDOW_H
