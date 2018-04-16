#include "gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    gameMainLayout(new QVBoxLayout),
    gameTipsLayout(new QHBoxLayout),
    gameDisplayLayout(new QGridLayout),
    gameScripture(new QLabel),
    exitToMenu(new QPushButton),
    tips(new QLabel)
{
    // Setup tips layout
    tips->setText("Use arrow keys to walk");
    exitToMenu->setText("Exit to menu");
    gameTipsLayout->addWidget(tips);
    gameTipsLayout->addStretch(1);
    gameTipsLayout->addWidget(exitToMenu);

    // Setup grid layout - the map
    int rows = 42;
    int cols = 45;

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            QPushButton *pix = new QPushButton();
            pix->setFixedSize(15, 15);
            gameDisplayLayout->addWidget(pix, i, j);
        }
    }
    gameDisplayLayout->setSpacing(0);

    // Setup scripture label
    gameScripture->setText("I am the way, the truth and the life.");
    gameScripture->setAlignment(Qt::AlignHCenter);
    gameScripture->setFixedSize(QSize(690, 150));

    //Setup main vertical layout
    gameMainLayout->addLayout(gameTipsLayout);
    gameMainLayout->addLayout(gameDisplayLayout);
    gameMainLayout->addWidget(gameScripture);

    setLayout(gameMainLayout);

    /* Logics */

    // Exit to menu when the "EXIT to menu" button is clicked
    connect(exitToMenu, SIGNAL(clicked()), this->parent(), SLOT(switchToMenuMode()));

}
