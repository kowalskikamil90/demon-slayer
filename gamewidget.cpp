#include "gamewidget.h"
#include <QString>
#include <QPalette>

int score;

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    gameMainLayout(new QVBoxLayout),
    gameTipsLayout(new QHBoxLayout),
    gameDisplayLayout(new QGridLayout),
    gameScripture(new QLabel),
    exitToMenu(new QPushButton),
    tips(new QLabel),
    arrows(new QLabel),
    scoreLbl(new QLabel)
{
    // Initial score
    score = 0;

    // Setup tips layout
    tips->setText("Use arrow keys to walk");

    // Arrows picture
    arrowsPm = new QPixmap(":/images/arrows.png");
    arrows->setPixmap(*arrowsPm);
    arrows->setFixedSize(100, 40);

    // SCORE label
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::green);
    QFont font = scoreLbl->font();
    font.setBold(true);
    font.setPointSize(20);
    scoreLbl->setText(QString("SCORE: ") + QString::number(score));
    scoreLbl->setPalette(palette);
    scoreLbl->setFont(font);

    // Exit button
    exitToMenu->setText("Exit to menu");
    exitToMenu->setFocusPolicy(Qt::NoFocus);

    // Entire tips layout
    gameTipsLayout->addWidget(tips);
    gameTipsLayout->addWidget(arrows);
    gameTipsLayout->addStretch(1);
    gameTipsLayout->addWidget(scoreLbl);
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
    QIcon paul(":/images/paul.png");

    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            QPushButton *pix = new QPushButton();
            pix->setFocusPolicy(Qt::NoFocus);
            pix->setFixedSize(60, 60);
            // Setup Paul
            if (i == 5 && j == 5)
            {
                pix->setIcon(paul);
            }
            // Trees
            else if (map[i][j] == "T")
            {
                pix->setIcon(tree);
            }
            // Paths
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
