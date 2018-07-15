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

struct Coords
{
  int x;
  int y;
  
  bool operator==(const Coords& c) const
  {
    if (this->x == c.x && this->y == c.y) return true;
    else return false;
  }
};

// These are potencial available spawn positions
Coords spawns[5] = { {1,1}, {7,1}, {1,7}, {7,5}, {8,8} };

// Maximum number of existing demons
#define MAX_DEMONS 5
// Timeout for spawning demons
#define SPAWN_TIMEOUT 3000 //unit is ms

// Static member inititialization
bool GameWidget::_gameStarted(false);
QTimer* GameWidget::_timer(new QTimer);

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    _gameMainLayout(new QVBoxLayout),
    _gameTipsLayout(new QHBoxLayout),
    _gameDisplayLayout(new QGridLayout),
    _gameScripture(new QLabel),
    _exitToMenu(new QPushButton),
    _tips(new QLabel),
    _arrows(new QLabel),
    _scoreLbl(new QLabel)
{
    /* Initialize random number generator.
     * This way we get diffrent numbers each time when the app is run. */
    QTime time = QTime::currentTime();
    qsrand(static_cast<unsigned int>(time.msec()));

    // Initial score
    score = 0;

    // Setup tips layout
    _tips->setText("Use arrow keys to walk");

    // Arrows picture
    _arrowsPm = new QPixmap(":/images/arrows.png");
    _arrows->setPixmap(*_arrowsPm);
    _arrows->setFixedSize(100, 40);

    // SCORE label
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::green);
    QFont font = _scoreLbl->font();
    font.setBold(true);
    font.setPointSize(20);
    _scoreLbl->setText(QString("SCORE: ") + QString::number(score));
    _scoreLbl->setPalette(palette);
    _scoreLbl->setFont(font);

    // Exit button
    _exitToMenu->setText("Exit to menu");
    _exitToMenu->setFocusPolicy(Qt::NoFocus);

    // Entire tips layout
    _gameTipsLayout->addWidget(_tips);
    _gameTipsLayout->addWidget(_arrows);
    _gameTipsLayout->addStretch(1);
    _gameTipsLayout->addWidget(_scoreLbl);
    _gameTipsLayout->addStretch(1);
    _gameTipsLayout->addWidget(_exitToMenu);

    // Initialize map grid pixels
    for (int i=0; i<ROWS; i++)
    {
        for (int j=0; j<COLS; j++)
        {
            _pixelsBtn[i][j] = new QPushButton();
            _pixelsDesc[i][j] = theInitialMap[i][j];
        }
    }
    drawInitialMap();

    // Setup scripture label
    _gameScripture->setText("I am the way, the truth and the life.");
    _gameScripture->setAlignment(Qt::AlignHCenter);
    _gameScripture->setFixedSize(QSize(690, 150));

    //Setup main vertical layout
    _gameMainLayout->addLayout(_gameTipsLayout);
    _gameMainLayout->addLayout(_gameDisplayLayout);
    _gameMainLayout->addWidget(_gameScripture);

    setLayout(_gameMainLayout);

    // Initially there is no demons on the map
    _numOfDemons = 0;

    // Read in scriptures from the file
    QFile scriptures(":/scriptures/scriptures1.txt");
    if (scriptures.open(QIODevice::ReadOnly))
    {
       QTextStream in(&scriptures);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          _scriptureVec.push_back(line);
       }
       scriptures.close();
    }

    /* Logics */

    // Setup timer callback for demons spawning, 5 seconds timeout interval
    connect(_timer, SIGNAL(timeout()), this, SLOT(spawnDemon()));

    // Exit to menu when the "EXIT to menu" button is clicked
    connect(_exitToMenu, SIGNAL(clicked()), this->parent(), SLOT(switchToMenuMode()));
}

void GameWidget::spawnDemon()
{

    if (_numOfDemons < MAX_DEMONS && _gameStarted)
    {
        QIcon demon(":/images/demon.png");
        QPushButton *pix;
        QChar *desc;
        Coords spawn;

        spawn = spawns[getSpawn()];
        pix = _pixelsBtn[spawn.x][spawn.y];
        desc = &_pixelsDesc[spawn.x][spawn.y];

        pix->setIcon(demon);
        pix->setIconSize(QSize(60, 60));
        _numOfDemons++;
        *desc = 'D';
    }

}

int GameWidget::getSpawn()
{
    /* Get random position of a spawn.
     * At the beginning there is 5 available positions.*/

    int spawn;

    // Only one available position, nothing to shuffle
    if (_availSpawns.size() == 1)
    {
        spawn = _availSpawns.toList().at(0);
        _availSpawns.remove(0);
    }

    // Randomly choose the position for a demon
    else
    {
        int randomNum =  (qrand() % 10) + _availSpawns.size();
        int numCycles = randomNum / _availSpawns.size();
        randomNum = randomNum - numCycles*_availSpawns.size();
        spawn = _availSpawns.toList().at(randomNum);
        _availSpawns.remove(spawn);
    }

    /* Returns number from 0 to 4, the index of a spawn position
     * depending on available spawn positions.*/
    return spawn;
}

int GameWidget::pickScriptureIndex()
{
    // Get random scripture index
    return  qrand() % _scriptureVec.size();
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
            QPushButton *pix = _pixelsBtn[i][j];
            QChar *desc = &_pixelsDesc[i][j];
            pix->setFocusPolicy(Qt::NoFocus);
            pix->setFixedSize(60, 60);

            // Setup (A)postle Paul initial position and Icon
            if (i == initPaulPosX && j == initPaulPosY)
            {
                pix->setIcon(paul);
                _paulsPos.x = i;
                _paulsPos.y = j;
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
            _gameDisplayLayout->addWidget(pix, i, j);
        }
    }
    _gameDisplayLayout->setSpacing(1);

    // Reset number of demons
    _numOfDemons = 0;

    // Setup available spawn positions
    _availSpawns.clear();
    _availSpawns.insert(0);
    _availSpawns.insert(1);
    _availSpawns.insert(2);
    _availSpawns.insert(3);
    _availSpawns.insert(4);
}

void GameWidget::start()
{
    _gameStarted = true;
    _timer->start(SPAWN_TIMEOUT);
}

void GameWidget::stop()
{
    _gameStarted = false;
    _timer->stop();
}

void GameWidget::keyPressEvent(QKeyEvent* event)
{
    QIcon path(":/images/dryground.png");
    QIcon paul(":/images/paul.png");
    int x = _paulsPos.x;
    int y = _paulsPos.y;
    bool encounteredDemon = false;

    switch (event->key())
    {
    case Qt::Key_Left:
        if (y > 0)
        {
            if (_pixelsDesc[x][y-1] == 'P' || _pixelsDesc[x][y-1] == 'D')
            {
                // Encounter with a demon
                if (_pixelsDesc[x][y-1] == 'D')
                {
                    _numOfDemons--;
                    score++;
                    _scoreLbl->setText(QString("SCORE: ") + QString::number(score));
                    updateSpawns(x, y-1);
                    encounteredDemon = true;
                }

                // Set ground icon where Paul was
                _pixelsBtn[x][y]->setIcon(path);
                _pixelsBtn[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                _pixelsBtn[x][y-1]->setIcon(paul);
                _pixelsBtn[x][y-1]->setIconSize(QSize(60, 60));

                // Set new Paul's position
                _paulsPos.y = y-1;

                // Set pixel to (P)ath
                _pixelsDesc[x][y-1] = 'P';
            }
        }
        break;

    case Qt::Key_Up:
        if (x > 0)
        {
            if (_pixelsDesc[x-1][y] == 'P' || _pixelsDesc[x-1][y] == 'D')
            {
                // Encounter with a demon
                if (_pixelsDesc[x-1][y] == 'D')
                {
                    _numOfDemons--;
                    score++;
                    _scoreLbl->setText(QString("SCORE: ") + QString::number(score));
                    updateSpawns(x-1, y);
                    encounteredDemon = true;
                }

                // Set ground icon where Paul was
                _pixelsBtn[x][y]->setIcon(path);
                _pixelsBtn[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                _pixelsBtn[x-1][y]->setIcon(paul);
                _pixelsBtn[x-1][y]->setIconSize(QSize(60, 60));

                // Set new Paul's position
                _paulsPos.x = x-1;

                // Set pixel to (P)ath
                _pixelsDesc[x-1][y] = 'P';
            }
        }

        break;

    case Qt::Key_Down:
        if (x < ROWS-1)
        {
            if (_pixelsDesc[x+1][y] == 'P' || _pixelsDesc[x+1][y] == 'D')
            {
                // Encounter with a demon
                if (_pixelsDesc[x+1][y] == 'D')
                {
                    _numOfDemons--;
                    score++;
                    _scoreLbl->setText(QString("SCORE: ") + QString::number(score));
                    updateSpawns(x+1, y);
                    encounteredDemon = true;
                }

                // Set ground icon where Paul was
                _pixelsBtn[x][y]->setIcon(path);
                _pixelsBtn[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                _pixelsBtn[x+1][y]->setIcon(paul);
                _pixelsBtn[x+1][y]->setIconSize(QSize(60, 60));

                // Set nes Paul's position
                _paulsPos.x = x+1;

                // Set pixel to (P)ath
                _pixelsDesc[x+1][y] = 'P';
            }
        }

        break;

    case Qt::Key_Right:
        if (y < COLS-1)
        {
            if (_pixelsDesc[x][y+1] == 'P' || _pixelsDesc[x][y+1] == 'D')
            {
                // Encounter with a demon
                if (_pixelsDesc[x][y+1] == 'D')
                {
                    _numOfDemons--;
                    score++;
                    _scoreLbl->setText(QString("SCORE: ") + QString::number(score));
                    updateSpawns(x, y+1);
                    encounteredDemon = true;
                }

                // Set ground icon where Paul was
                _pixelsBtn[x][y]->setIcon(path);
                _pixelsBtn[x][y]->setIconSize(QSize(60, 60));

                // Set Paul icon to the left
                _pixelsBtn[x][y+1]->setIcon(paul);
                _pixelsBtn[x][y+1]->setIconSize(QSize(60, 60));

                // Set new Paul's position
                _paulsPos.y = y+1;

                // Set pixel to (P)ath
                _pixelsDesc[x][y+1] = 'P';
            }
        }

        break;
    }

    // If demon was encountered, change te scripture taht is displayed
    if (encounteredDemon) _gameScripture->setText(_scriptureVec[pickScriptureIndex()]);
}

void GameWidget::updateSpawns(int x, int y)
{
    Coords spawn(x, y);
  
    for (int i = 0; i  sizeof(spawns)/sizeof(Coords); i++)
    {
       if (spawn == spawns[i]) 
       {
          _availSpawns.insert(i);
          break;
       }
    }
}
