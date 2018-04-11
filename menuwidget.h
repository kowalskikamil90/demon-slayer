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

signals:

public slots:

private:
    QVBoxLayout *menuLayout;
    QPushButton *startBtn;
    QPushButton *exitBtn;
    QLabel *title;
    QPixmap *titlePm;
    QIcon *startIc;
    QIcon *exitIc;
};

#endif // MENUWIDGET_H
