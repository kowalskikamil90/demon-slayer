#include "menuwidget.h"
#include <QApplication>

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    menuLayout(new QVBoxLayout),
    startBtn(new QPushButton),
    exitBtn(new QPushButton),
    title(new QLabel),
    titlePm(new QPixmap("/home/binarek/github/demon-slayer/images/title.png")),
    startIc(new QIcon("/home/binarek/github/demon-slayer/images/start.png")),
    exitIc(new QIcon("/home/binarek/github/demon-slayer/images/exit.png"))
{
    /* Setup of the layout in MENU mode */

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

    menuLayout->addWidget(title);
    menuLayout->addStretch(1);
    menuLayout->addWidget(startBtn);
    menuLayout->addWidget(exitBtn);
    menuLayout->addStretch(1);

    menuLayout->setAlignment(title, Qt::AlignHCenter);
    menuLayout->setAlignment(startBtn, Qt::AlignHCenter);
    menuLayout->setAlignment(exitBtn, Qt::AlignHCenter);

    this->setStyleSheet("background:rgb(88, 88, 88)");

    this->setLayout(menuLayout);

    /* Logics of the menu */

    // Start the game when "START" button is clicked
    connect(startBtn, SIGNAL(clicked()), this->parent(), SLOT(switchToGameMode()));

    // Exit app when the "EXIT" button is clicked
    connect(exitBtn, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
}
