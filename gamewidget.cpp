#include "gamewidget.h"
#include <QString>
#include <QPalette>
#include <QTimer>
#include <QTime>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QDebug>

// Global variable used for storing the game SCORE
int score;

// Maximum number of existing demons
#define MAX_DEMONS 5

// Static member inititialization
bool GameWidget::gameStarted(false);

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    // T = TREE
    // P = PATH
    map({
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
    }),
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
    qsrand(static_cast<unsigned int>(time.msec()));

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
        spawn = availSpawns.toList().at(0);
        availSpawns.remove(0);
        positionedDemons.insert(0);
    }
    else
    {
        int randomNum =  (qrand() % 10) + availSpawns.size();
        int numCycles = randomNum / availSpawns.size();
        randomNum = randomNum - numCycles*availSpawns.size();
        spawn = availSpawns.toList().at(randomNum);
        availSpawns.remove(randomNum);
        positionedDemons.insert(randomNum);
    }

    return spawn;
}

void GameWidget::drawInitialMap()
{
    // Setup grid layout - the map
    int rows = 10;
    int cols = 11;

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
                paulsPos.x = i;
                paulsPos.y = j;
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
    availSpawns.insert(0);
    availSpawns.insert(1);
    availSpawns.insert(2);
    availSpawns.insert(3);
    availSpawns.insert(4);

    // No demons at the beginning
    positionedDemons.clear();
}

void GameWidget::start()
{
    gameStarted = true;
}

void GameWidget::stop()
{
    gameStarted = false;
}

void GameWidget::keyPressEvent(QKeyEvent* event)
{
    QIcon path(":/images/dryground.png");
    QIcon paul(":/images/paul.png");
    int x = paulsPos.x;
    int y = paulsPos.y;

    qDebug() << x << "," << y;

    switch (event->key())
    {
    case Qt::Key_Left:
        if (y>0)
        {
            qDebug() << "LEFT: " << *map[x, y-1];
            if (map[x, y-1] == QString("P"))
            {

                qDebug() << "LEFT: " << *map[x, y-1];

                // Set ground icon where Paul was
                pixels[x][y]->setIcon(path);
                pixels[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                pixels[x][y-1]->setIcon(paul);
                pixels[x][y-1]->setIconSize(QSize(60, 60));

                // Set new Paul's position
                paulsPos.y = y-1;
            }
        }
        break;

    case Qt::Key_Up:
        if (x>0)
        {
            if (map[x-1, y] == QString("P"))
            {
                // Set ground icon where Paul was
                pixels[x][y]->setIcon(path);
                pixels[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                pixels[x-1][y]->setIcon(paul);
                pixels[x-1][y]->setIconSize(QSize(60, 60));

                // Set new Paul's position
                paulsPos.x = x-1;
            }
        }

        break;

    case Qt::Key_Down:
        if (x<9)
        {
            if (map[x+1, y] == QString("P"))
            {
                // Set ground icon where Paul was
                pixels[x][y]->setIcon(path);
                pixels[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                pixels[x+1][y]->setIcon(paul);
                pixels[x+1][y]->setIconSize(QSize(60, 60));

                // Set nes Paul's position
                paulsPos.x = x+1;
            }
        }

        break;

    case Qt::Key_Right:
        if (y<10)
        {
            if (map[x, y+1] == QString("P"))
            {
                // Set ground icon where Paul was
                pixels[x][y]->setIcon(path);
                pixels[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                pixels[x][y+1]->setIcon(paul);
                pixels[x][y+1]->setIconSize(QSize(60, 60));

                // Set new Paul's position
                paulsPos.y = y+1;
            }
        }

        break;
    }
}
