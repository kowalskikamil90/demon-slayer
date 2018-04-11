#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
      stackWidged(new QStackedWidget(this)),
      menuWidget(new MenuWidget(this)),
      gameWidget(new GameWidget(this))
{
    this->setGeometry(500, 100, 700, 700);

    stackWidged->addWidget(menuWidget);
    stackWidged->addWidget(gameWidget);
    stackWidged->setCurrentWidget(menuWidget);

}

MainWindow::~MainWindow()
{

}

void MainWindow::switchToGameMode()
{
    stackWidged->setCurrentWidget(gameWidget);
}

void MainWindow::switchToMenuMode()
{
    stackWidged->setCurrentWidget(menuWidget);
}
