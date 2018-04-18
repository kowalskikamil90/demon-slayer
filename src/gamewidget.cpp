#include "gamewidget.h"
#include <QString>
#include <QPalette>
#include <QTime>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>

// Global variable used for storing the game SCORE
unsigned int score;

// Initial position of the Paul
static int initPaulPosX = 5;
static int initPaulPosY = 5;

// T = TREE
// P = PATH
static QChar theInitialMap[ROWS][COLS]= {
                             {'T', 'P', 'P', 'P', 'T', 'T', 'T', 'P', 'P', 'P', 'T'},
                             {'T', 'P', 'T', 'P', 'P', 'P', 'P', 'P', 'T', 'P', 'T'},
                             {'T', 'P', 'T', 'T', 'P', 'T', 'T', 'P', 'P', 'P', 'P'},
                             {'P', 'P', 'P', 'P', 'P', 'P', 'T', 'T', 'T', 'T', 'P'},
                             {'P', 'T', 'T', 'P', 'T', 'P', 'P', 'P', 'T', 'P', 'P'},
                             {'P', 'P', 'T', 'T', 'T', 'P', 'T', 'P', 'T', 'P', 'T'},
                             {'P', 'P', 'P', 'P', 'T', 'P', 'T', 'P', 'T', 'P', 'P'},
                             {'T', 'P', 'T', 'P', 'P', 'P', 'T', 'P', 'P', 'P', 'P'},
                             {'T', 'P', 'T', 'P', 'T', 'P', 'P', 'P', 'P', 'T', 'T'},
                             {'T', 'P', 'P', 'P', 'T', 'T', 'T', 'P', 'P', 'P', 'T'},
                             };

// Maximum number of existing demons
#define MAX_DEMONS 5
// Timeout for spawning demons
#define SPAWN_TIMEOUT 3000 //unit is ms

// Static member inititialization
bool GameWidget::gameStarted(false);
QTimer* GameWidget::timer(new QTimer);

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
    /* Initialize random number generator.
     * This way we get diffrent numbers each time when the app is run. */
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
    for (int i=0; i<ROWS; i++)
    {
        for (int j=0; j<COLS; j++)
        {
            pixelsBtn[i][j] = new QPushButton();
            pixelsDesc[i][j] = theInitialMap[i][j];
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

    // Initially there is no demons on the map
    numOfDemons = 0;

    // Read in scriptures from the file
    QFile scriptures(":/scriptures/scriptures1.txt");
    if (scriptures.open(QIODevice::ReadOnly))
    {
       QTextStream in(&scriptures);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          scriptureVec.push_back(line);
       }
       scriptures.close();
    }

    /* Logics */

    // Setup timer callback for demons spawning, 5 seconds timeout interval
    connect(timer, SIGNAL(timeout()), this, SLOT(spawnDemon()));

    // Exit to menu when the "EXIT to menu" button is clicked
    connect(exitToMenu, SIGNAL(clicked()), this->parent(), SLOT(switchToMenuMode()));
}

void GameWidget::spawnDemon()
{

    if (numOfDemons < MAX_DEMONS && gameStarted)
    {
        QIcon demon(":/images/demon.png");
        QPushButton *pix;
        QChar *desc;

        switch (getSpawn()){

        case 0:
            pix = pixelsBtn[1][1];
            desc = &pixelsDesc[1][1];

            break;

        case 1:
            pix = pixelsBtn[7][1];
            desc = &pixelsDesc[7][1];

            break;

        case 2:
            pix = pixelsBtn[1][7];
            desc = &pixelsDesc[1][7];

            break;

        case 3:
            pix = pixelsBtn[7][5];
            desc = &pixelsDesc[7][5];

            break;

        case 4:
            pix = pixelsBtn[8][8];
            desc = &pixelsDesc[8][8];

            break;
        }

        pix->setIcon(demon);
        pix->setIconSize(QSize(60, 60));
        numOfDemons++;
        *desc = 'D';
    }

}

int GameWidget::getSpawn()
{
    /* Get random position of a spawn.
     * At the beginning there is 5 available positions.*/

    int spawn;

    // Only one available position, nothing to shuffle
    if (availSpawns.size() == 1)
    {
        spawn = availSpawns.toList().at(0);
        availSpawns.remove(0);
    }

    // Randomly choose the position for a demon
    else
    {
        int randomNum =  (qrand() % 10) + availSpawns.size();
        int numCycles = randomNum / availSpawns.size();
        randomNum = randomNum - numCycles*availSpawns.size();
        spawn = availSpawns.toList().at(randomNum);
        availSpawns.remove(spawn);
    }

    return spawn;
}

int GameWidget::pickScriptureIndex()
{
    // Get random scripture index
    return  qrand() % scriptureVec.size();
}

void GameWidget::drawInitialMap()
{
    // Setup grid layout - the map

    QIcon tree(":/images/tree1.png");
    QIcon path(":/images/dryground.png");
    QIcon paul(":/images/paul.png");

    for (int i=0; i<ROWS; i++)
    {
        for (int j=0; j<COLS; j++)
        {
            QPushButton *pix = pixelsBtn[i][j];
            QChar *desc = &pixelsDesc[i][j];
            pix->setFocusPolicy(Qt::NoFocus);
            pix->setFixedSize(60, 60);

            // Setup (A)postle Paul initial position and Icon
            if (i == initPaulPosX && j == initPaulPosY)
            {
                pix->setIcon(paul);
                paulsPos.x = i;
                paulsPos.y = j;
                *desc = 'P'; //No need to distinguish Path From Apostle here
            }

            // Setup (T)rees Icons
            else if (theInitialMap[i][j] == 'T')
            {
                pix->setIcon(tree);
                *desc = 'T';
            }

            // Setup (P)aths Icons
            else if (theInitialMap[i][j] == 'P')
            {
                pix->setIcon(path);
                *desc = 'P';
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
}

void GameWidget::start()
{
    gameStarted = true;
    timer->start(SPAWN_TIMEOUT);
}

void GameWidget::stop()
{
    gameStarted = false;
    timer->stop();
}

void GameWidget::keyPressEvent(QKeyEvent* event)
{
    QIcon path(":/images/dryground.png");
    QIcon paul(":/images/paul.png");
    int x = paulsPos.x;
    int y = paulsPos.y;
    bool encounteredDemon = false;

    switch (event->key())
    {
    case Qt::Key_Left:
        if (y > 0)
        {
            if (pixelsDesc[x][y-1] == 'P' || pixelsDesc[x][y-1] == 'D')
            {
                // Encounter with a demon
                if (pixelsDesc[x][y-1] == 'D')
                {
                    numOfDemons--;
                    score++;
                    scoreLbl->setText(QString("SCORE: ") + QString::number(score));
                    updateSpawns(x, y-1);
                    encounteredDemon = true;
                }

                // Set ground icon where Paul was
                pixelsBtn[x][y]->setIcon(path);
                pixelsBtn[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                pixelsBtn[x][y-1]->setIcon(paul);
                pixelsBtn[x][y-1]->setIconSize(QSize(60, 60));

                // Set new Paul's position
                paulsPos.y = y-1;

                // Set pixel to (P)ath
                pixelsDesc[x][y-1] = 'P';
            }
        }
        break;

    case Qt::Key_Up:
        if (x > 0)
        {
            if (pixelsDesc[x-1][y] == 'P' || pixelsDesc[x-1][y] == 'D')
            {
                // Encounter with a demon
                if (pixelsDesc[x-1][y] == 'D')
                {
                    numOfDemons--;
                    score++;
                    scoreLbl->setText(QString("SCORE: ") + QString::number(score));
                    updateSpawns(x-1, y);
                    encounteredDemon = true;
                }

                // Set ground icon where Paul was
                pixelsBtn[x][y]->setIcon(path);
                pixelsBtn[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                pixelsBtn[x-1][y]->setIcon(paul);
                pixelsBtn[x-1][y]->setIconSize(QSize(60, 60));

                // Set new Paul's position
                paulsPos.x = x-1;

                // Set pixel to (P)ath
                pixelsDesc[x-1][y] = 'P';
            }
        }

        break;

    case Qt::Key_Down:
        if (x < ROWS-1)
        {
            if (pixelsDesc[x+1][y] == 'P' || pixelsDesc[x+1][y] == 'D')
            {
                // Encounter with a demon
                if (pixelsDesc[x+1][y] == 'D')
                {
                    numOfDemons--;
                    score++;
                    scoreLbl->setText(QString("SCORE: ") + QString::number(score));
                    updateSpawns(x+1, y);
                    encounteredDemon = true;
                }

                // Set ground icon where Paul was
                pixelsBtn[x][y]->setIcon(path);
                pixelsBtn[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                pixelsBtn[x+1][y]->setIcon(paul);
                pixelsBtn[x+1][y]->setIconSize(QSize(60, 60));

                // Set nes Paul's position
                paulsPos.x = x+1;

                // Set pixel to (P)ath
                pixelsDesc[x+1][y] = 'P';
            }
        }

        break;

    case Qt::Key_Right:
        if (y < COLS-1)
        {
            if (pixelsDesc[x][y+1] == 'P' || pixelsDesc[x][y+1] == 'D')
            {
                // Encounter with a demon
                if (pixelsDesc[x][y+1] == 'D')
                {
                    numOfDemons--;
                    score++;
                    scoreLbl->setText(QString("SCORE: ") + QString::number(score));
                    updateSpawns(x, y+1);
                    encounteredDemon = true;
                }

                // Set ground icon where Paul was
                pixelsBtn[x][y]->setIcon(path);
                pixelsBtn[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                pixelsBtn[x][y+1]->setIcon(paul);
                pixelsBtn[x][y+1]->setIconSize(QSize(60, 60));

                // Set new Paul's position
                paulsPos.y = y+1;

                // Set pixel to (P)ath
                pixelsDesc[x][y+1] = 'P';
            }
        }

        break;
    }

    // If demon was encountered, change te scripture taht is displayed
    if (encounteredDemon) gameScripture->setText(scriptureVec[pickScriptureIndex()]);
}

void GameWidget::updateSpawns(int x, int y)
{
    if (x == 1 && y ==1) availSpawns.insert(0);
    else if(x == 7 && y == 1) availSpawns.insert(1);
    else if(x == 1 && y == 7) availSpawns.insert(2);
    else if(x == 7 && y == 5) availSpawns.insert(3);
    else if(x == 8 && y == 8) availSpawns.insert(4);
}
