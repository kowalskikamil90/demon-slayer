#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

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
};

#endif // GAMEWIDGET_H
