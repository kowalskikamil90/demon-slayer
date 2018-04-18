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

    QChar theMap[10][11];
    QVBoxLayout *gameMainLayout;
    QHBoxLayout *gameTipsLayout;
    QGridLayout *gameDisplayLayout;
    QPushButton *pixels[10][11];
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
};

#endif // GAMEWIDGET_H
