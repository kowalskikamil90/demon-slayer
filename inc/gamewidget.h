#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QSet>
#include <QVector>
#include <QChar>
#include <QTimer>

extern unsigned int score;

// Size of a map
const int ROWS = 10;
const int COLS = 11;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    void drawInitialMap();
    static void start();
    static void stop();

protected:
    void keyPressEvent(QKeyEvent* event);

private slots:
    void spawnDemon();

private:

    struct Position {
        int x, y;
    };

    QVBoxLayout *_gameMainLayout;
    QHBoxLayout *_gameTipsLayout;
    QGridLayout *_gameDisplayLayout;

    // These two fileds hold the map and units together
    QPushButton *_pixelsBtn[ROWS][COLS];
    QChar _pixelsDesc[ROWS][COLS];

    QLabel *_gameScripture;
    QPushButton *_exitToMenu;
    QLabel *_tips;
    QLabel *_arrows;
    QLabel *_scoreLbl;
    QPixmap *_arrowsPm;

    //Vector for scriptures loaded from file
    QVector<QString> _scriptureVec;

    int _numOfDemons;
    QSet<int> _availSpawns;
    GameWidget::Position _paulsPos;

    static bool _gameStarted;
    static QTimer *_timer;

    int getSpawn();
    int pickScriptureIndex();
    void updateSpawns(int x, int y);
};

#endif // GAMEWIDGET_H
