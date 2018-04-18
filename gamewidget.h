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

signals:

protected:
    void keyPressEvent(QKeyEvent* event);

private slots:
    void spawnDemon();

private:

    struct Position {
        int x, y;
    };

    QVBoxLayout *gameMainLayout;
    QHBoxLayout *gameTipsLayout;
    QGridLayout *gameDisplayLayout;

    // These two fileds hold the map and units together
    QPushButton *pixelsBtn[ROWS][COLS];
    QChar pixelsDesc[ROWS][COLS];

    QLabel *gameScripture;
    QPushButton *exitToMenu;
    QLabel *tips;
    QLabel *arrows;
    QLabel *scoreLbl;
    QPixmap *arrowsPm;

    //Vector for scriptures loaded from file
    QVector<QString> scriptureVec;

    int numOfDemons;
    QSet<int> availSpawns;
    GameWidget::Position paulsPos;

    static bool gameStarted;
    static QTimer *timer;

    int getSpawn();
    int pickScriptureIndex();
    void updateSpawns(int x, int y);
};

#endif // GAMEWIDGET_H
