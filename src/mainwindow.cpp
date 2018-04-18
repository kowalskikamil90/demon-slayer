#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
      _stackWidged(new QStackedWidget(this)),
      _menuWidget(new MenuWidget(this)),
      _gameWidget(new GameWidget(this))
{
    // Set initial position
    this->setGeometry(500, 100, 700, 700);

    // Set the size to be fixed, nonchangable
    this->setFixedSize(QSize(700, 700));

    // Set the background color as dark grey
    this->setStyleSheet("background:rgb(88, 88, 88)");

    _stackWidged->addWidget(_menuWidget);
    _stackWidged->addWidget(_gameWidget);
    _stackWidged->setCurrentWidget(_menuWidget);

}

MainWindow::~MainWindow()
{

}

void MainWindow::switchToGameMode()
{
    // Reset the score
    score = 0;

    // Set the background color as light grey
    this->setStyleSheet("background:rgb(150, 150, 150)");

    _stackWidged->setCurrentWidget(_gameWidget);

    _gameWidget->drawInitialMap();

    // Start game
    GameWidget::start();
}

void MainWindow::switchToMenuMode()
{
    // Reset the score
    score = 0;

    // Set the background color as dark grey
    this->setStyleSheet("background:rgb(88, 88, 88)");

    _stackWidged->setCurrentWidget(_menuWidget);

    // Stop game
    GameWidget::stop();
}
