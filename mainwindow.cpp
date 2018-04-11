#include "mainwindow.h"

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
    this->setGeometry(500, 100, 700, 700);

    title->setBaseSize(300, 100);
    title->setPixmap(*titlePm);

    startBtn->setBaseSize(300, 100);
    startBtn->setIcon(*startIc);
    startBtn->setIconSize(QSize(300, 100));

    exitBtn->setBaseSize(300, 100);
    exitBtn->setIcon(*exitIc);
    exitBtn->setIconSize(QSize(300, 100));

    menuLayout->addStretch(1);
    menuLayout->addWidget(title);
    menuLayout->addStretch(1);
    menuLayout->addWidget(startBtn);
    menuLayout->addWidget(exitBtn);
    menuLayout->setAlignment(title, Qt::AlignHCenter);
    menuLayout->setAlignment(startBtn, Qt::AlignHCenter);
    menuLayout->setAlignment(exitBtn, Qt::AlignHCenter);
    menuLayout->addStretch(1);

    setLayout(menuLayout);

}

MainWindow::~MainWindow()
{
    delete titlePm;
    delete startIc;
    delete exitIc;
}
