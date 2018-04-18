#include "menuwidget.h"
#include <QApplication>
#include <QPainter>

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    _menuLayout(new QVBoxLayout),
    _startBtn(new QPushButton),
    _exitBtn(new QPushButton),
    _title(new QLabel)
{
    /* Load pictures.
     * This is Qt-specific syntax for paths.
     * Images are stored in application executable
     * and are listed in images.qrc file */
    _titlePm = new QPixmap(":/images/title.png");
    _startIc = new QIcon(":/images/start.png");
    _exitIc = new QIcon(":/images/exit.png");

    /* Setup of the layout in MENU mode */
    _title->setBaseSize(300, 100);
    _title->setPixmap(*_titlePm);
    _title->setStyleSheet("background-color: green");

    _startBtn->setBaseSize(300, 100);
    _startBtn->setIcon(*_startIc);
    _startBtn->setIconSize(QSize(300, 100));
    _startBtn->setStyleSheet("background-color: green");

    _exitBtn->setBaseSize(300, 100);
    _exitBtn->setIcon(*_exitIc);
    _exitBtn->setIconSize(QSize(300, 100));
    _exitBtn->setStyleSheet("background-color: green");

    _menuLayout->addWidget(_title);
    _menuLayout->addStretch(1);
    _menuLayout->addWidget(_startBtn);
    _menuLayout->addWidget(_exitBtn);
    _menuLayout->addStretch(1);

    _menuLayout->setAlignment(_title, Qt::AlignHCenter);
    _menuLayout->setAlignment(_startBtn, Qt::AlignHCenter);
    _menuLayout->setAlignment(_exitBtn, Qt::AlignHCenter);

    this->setStyleSheet("background:rgb(88, 88, 88)");

    this->setLayout(_menuLayout);

    /* Logics of the menu */

    // Start the game when "START" button is clicked
    connect(_startBtn, SIGNAL(clicked()), this->parent(), SLOT(switchToGameMode()));

    // Exit app when the "EXIT" button is clicked
    connect(_exitBtn, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
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
