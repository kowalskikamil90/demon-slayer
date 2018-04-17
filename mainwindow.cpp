#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent),
      stackWidged(new QStackedWidget(this)),
      menuWidget(new MenuWidget(this)),
      gameWidget(new GameWidget(this))
{
    // Set initial position
    this->setGeometry(500, 100, 700, 700);

    // Set the size to be fixed, nonchangable
    this->setFixedSize(QSize(700, 700));

    // Set the background color as dark grey
    this->setStyleSheet("background:rgb(88, 88, 88)");

    stackWidged->addWidget(menuWidget);
    stackWidged->addWidget(gameWidget);
    stackWidged->setCurrentWidget(menuWidget);

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

    stackWidged->setCurrentWidget(gameWidget);

    gameWidget->drawInitialMap();

    // Start game
    GameWidget::start();
}

void MainWindow::switchToMenuMode()
{
    // Reset the score
    score = 0;

    // Set the background color as dark grey
    this->setStyleSheet("background:rgb(88, 88, 88)");

    stackWidged->setCurrentWidget(menuWidget);

    // Stop game
    GameWidget::stop();
}
