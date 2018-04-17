#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

extern int score;

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);

signals:

public slots:

private:

    QVBoxLayout *gameMainLayout;
    QHBoxLayout *gameTipsLayout;
    QGridLayout *gameDisplayLayout;
    QLabel *gameScripture;
    QPushButton *exitToMenu;
    QLabel *tips;
    QLabel *arrows;
    QLabel *scoreLbl;
    QPixmap *arrowsPm;
};

#endif // GAMEWIDGET_H
