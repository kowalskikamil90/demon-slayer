#include "menuwidget.h"
#include <QApplication>
#include <QPainter>

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    menuLayout(new QVBoxLayout),
    startBtn(new QPushButton),
    exitBtn(new QPushButton),
    title(new QLabel)
{
    /* Load pictures.
     * This is Qt-specific syntax for paths.
     * Images are stored in application executable
     * and are listed in images.qrc file */
    titlePm = new QPixmap(":/images/title.png");
    startIc = new QIcon(":/images/start.png");
    exitIc = new QIcon(":/images/exit.png");

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

void MenuWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    //Paint the cross symbol
    QPainter painter(this);
    painter.fillRect(340, 140, 20, 170, QColor(150, 30, 30));
    painter.fillRect(300, 180, 100, 20, QColor(150, 30, 30));
    painter.fillRect(345, 145, 10, 160, QColor(0, 0, 0));
    painter.fillRect(305, 185, 90, 10, QColor(0, 0, 0));
}
