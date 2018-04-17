#include "gamewidget.h"
#include <QString>
#include <QPalette>
#include <QTimer>
#include <QTime>
#include <QRandomGenerator>

// Global variable used for storing the game SCORE
int score;

// Maximum number of existing demons
#define MAX_DEMONS 5

// Static member inititialization
bool GameWidget::gameStarted(false);

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
    // Initialize random number generator
    QTime time = QTime::currentTime();
    qsrand(static_cast<unsigned int> (time.msec()));

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

    // Initialize map grid pixels
    int rows = 10;
    int cols = 11;
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols; j++)
        {
            QPushButton *pix = new QPushButton();
            pixels[i][j] = pix;
        }
    }
    drawInitialMap();

    // Setup scripture label
    gameScripture->setText("I am the way, the truth and the life.");
    gameScripture->setAlignment(Qt::AlignHCenter);
    gameScripture->setFixedSize(QSize(690, 150));

    //Setup main vertical layout
    gameMainLayout->addLayout(gameTipsLayout);
    gameMainLayout->addLayout(gameDisplayLayout);
    gameMainLayout->addWidget(gameScripture);

    setLayout(gameMainLayout);

    // Setup timer for demons spawning, 5 seconds timeout interval
    numOfDemons = 0;

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(spawnDemon()));
    timer->start(4000);

    /* Logics */

    // Exit to menu when the "EXIT to menu" button is clicked
    connect(exitToMenu, SIGNAL(clicked()), this->parent(), SLOT(switchToMenuMode()));
}

void GameWidget::spawnDemon()
{
    if (numOfDemons < MAX_DEMONS && gameStarted)
    {
        QIcon demon(":/images/demon.png");
        QPushButton *pix;

        switch (getSpawn()){

        case 0:
            pix = pixels[1][1];
            break;

        case 1:
            pix = pixels[7][1];
            break;

        case 2:
            pix = pixels[1][7];
            break;

        case 3:
            pix = pixels[7][5];
            break;

        case 4:
            pix = pixels[8][8];
            break;
        }

        pix->setIcon(demon);
        pix->setIconSize(QSize(60, 60));
        numOfDemons++;
    }
}

int GameWidget::getSpawn()
{
    int spawn;

    if (availSpawns.size() == 1)
    {
        spawn = availSpawns.at(0);
        availSpawns.remove(0);
    }
    else
    {
        int randomNum =  (qrand() % 10) + availSpawns.size();
        int numCycles = randomNum / availSpawns.size();
        randomNum = randomNum - numCycles*availSpawns.size();
        spawn = availSpawns.at(randomNum);
        availSpawns.remove(randomNum);
    }

    return spawn;
}

void GameWidget::drawInitialMap()
{
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
            QPushButton *pix = pixels[i][j];
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

    // Reset number of demons
    numOfDemons = 0;

    // Setup available spawn positions
    availSpawns.clear();
    availSpawns.push_back(0);
    availSpawns.push_back(1);
    availSpawns.push_back(2);
    availSpawns.push_back(3);
    availSpawns.push_back(4);
}

void GameWidget::start()
{
    gameStarted = true;
}

void GameWidget::stop()
{
    gameStarted = false;
}
