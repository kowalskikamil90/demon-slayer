#include "mainwindow.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent),
      menuLayout(new QVBoxLayout(this)),
      startBtn(new QPushButton(this)),
      exitBtn(new QPushButton(this)),
      title(new QLabel(this)),
      titlePm(new QPixmap("/home/binarek/github/demon-slayer/images/title.png")),
      startIc(new QIcon("/home/binarek/github/demon-slayer/images/start.png")),
      exitIc(new QIcon("/home/binarek/github/demon-slayer/images/exit.png"))
{
    /* Setup of the layout in MENU mode */

    this->setGeometry(500, 100, 700, 700);

    title->setBaseSize(300, 100);
    title->setPixmap(*titlePm);
    title->setStyleSheet("background-color: green");

    startBtn->setBaseSize(300, 100);
    startBtn->setIcon(*startIc);
    startBtn->setIconSize(QSize(300, 100));
    startBtn->setStyleSheet("background-color: green");

    exitBtn->setBaseSize(300, 100);
    exitBtn->setIcon(*exitIc);
    exitBtn->setIconSize(QSize(300, 100));
    exitBtn->setStyleSheet("background-color: green");

    menuLayout->addStretch(1);
    menuLayout->addWidget(title);
    menuLayout->addStretch(1);
    menuLayout->addWidget(startBtn);
    menuLayout->addWidget(exitBtn);
    menuLayout->setAlignment(title, Qt::AlignHCenter);
    menuLayout->setAlignment(startBtn, Qt::AlignHCenter);
    menuLayout->setAlignment(exitBtn, Qt::AlignHCenter);
    menuLayout->addStretch(1);

    this->setStyleSheet("background:rgb(90, 90, 90)");

    setLayout(menuLayout);

    /* Logics of the menu */

    // Start the game when "START" button is clicked
    connect(startBtn, SIGNAL(clicked()), this, SLOT(switchToGameMode()));

    // Exit app when the "EXIT" button is clicked
    connect(exitBtn, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));

}

MainWindow::~MainWindow()
{
    delete titlePm;
    delete startIc;
    delete exitIc;
}

void MainWindow::switchToGameMode()
{
    startBtn->setVisible(false);
    exitBtn->setVisible(false);
    title->setVisible(false);
    //menuLayout->set
}
