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
#include <QChar>

extern int score;

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
    QPushButton *pixelsBtn[10][11];
    QChar pixelsDesc[10][11];

    QLabel *gameScripture;
    QPushButton *exitToMenu;
    QLabel *tips;
    QLabel *arrows;
    QLabel *scoreLbl;
    QPixmap *arrowsPm;

    int numOfDemons;
    QSet<int> availSpawns;
    QSet<int> positionedDemons;
    GameWidget::Position paulsPos;

    static bool gameStarted;

    int getSpawn();
    void updateSpawns(int x, int y);
};

#endif // GAMEWIDGET_H
