#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QIcon>
#include <QHBoxLayout>
#include <QGridLayout>

class MenuWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MenuWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent*);

private:
    QVBoxLayout *_menuLayout;
    QPushButton *_startBtn;
    QPushButton *_exitBtn;
    QLabel *_title;
    QPixmap *_titlePm;
    QIcon *_startIc;
    QIcon *_exitIc;
};

#endif // MENUWIDGET_H
