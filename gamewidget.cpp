#include "gamewidget.h"
#include <QString>

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    gameMainLayout(new QVBoxLayout),
    gameTipsLayout(new QHBoxLayout),
    gameDisplayLayout(new QGridLayout),
    gameScripture(new QLabel),
    exitToMenu(new QPushButton),
    tips(new QLabel),
    arrows(new QLabel)
{
    // Setup tips layout
    tips->setText("Use arrow keys to walk");

    arrowsPm = new QPixmap(":/images/arrows.png");
    arrows->setPixmap(*arrowsPm);
    arrows->setFixedSize(100, 40);

    exitToMenu->setText("Exit to menu");
    gameTipsLayout->addWidget(tips);
    gameTipsLayout->addWidget(arrows);
    gameTipsLayout->addStretch(1);
    gameTipsLayout->addWidget(exitToMenu);

    // Setup grid layout - the map
    int rows = 10;
    int cols = 11;

    // T = TREE
    // P = PATH
    QString map[10][11] = {
        {"T", "P", "P", "P", "T", "T", "T", "P", "P", "P", "T"},
        {"T", "P", "T", "P", "P", "P", "P", "P", "T", "P", "T"},
        {"T", "P", "T", "T", "P", "T", "T", "P", "P", "P", "P"},
        {"P", "P", "P", "P", "P", "P", "T", "T", "T", "T", "P"},
        {"P", "T", "T", "P", "T", "P", "P", "P", "T", "P", "P"},
        {"P", "P", "T", "T", "T", "P", "T", "P", "T", "P", "T"},
        {"P", "P", "P", "P", "T", "P", "T", "P", "T", "P", "P"},
        {"T", "P", "T", "P", "P", "P", "T", "P", "P", "P", "P"},
        {"T", "P", "T", "P", "T", "P", "P", "P", "P", "T", "T"},
        {"T", "P", "P", "P", "T", "T", "T", "P", "P", "P", "T"},
    };
    QIcon tree(":/images/tree1.png");
    QIcon path(":/images/dryground.png");

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            QPushButton *pix = new QPushButton();
            pix->setFixedSize(60, 60);
            if (map[i][j] == "T")
            {
                pix->setIcon(tree);
            }
            else if (map[i][j] == "P")
            {
                pix->setIcon(path);
            }

            pix->setIconSize(QSize(60, 60));
            gameDisplayLayout->addWidget(pix, i, j);
        }
    }
    gameDisplayLayout->setSpacing(1);

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
