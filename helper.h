#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QDateTime>
#include <QDebug>

class Helper : public QObject
{
    Q_OBJECT

public:
    Helper();

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);
    void paint_1_1(QPainter *painter, QPaintEvent *event);
    void paint_1_2(QPainter *painter, QPaintEvent *event, int nSeconds);
    void paint_1_3(QPainter *painter, QPaintEvent *event, int nSeconds, int nLength);
    void paint_1_4(QPainter *painter, QPaintEvent *event);
    void paint_1_5(QPainter *painter, QPaintEvent *event);
    void paint_1_6(QPainter *painter, QPaintEvent *event);
    void paint_1_7(QPainter *painter, QPaintEvent *event);

    void clearBtnPressed();

    bool bBtnPressed_1_1_lockIn;
    bool bBtnPressed_1_1_lockOut;
    bool bBtnPressed_1_2_locking;
    bool bBtnPressed_1_3_Keypad[12];
    bool bBtnPressed_1_7_locked;

    QRect rectBtn_1_1_lockIn;
    QRect rectBtn_1_1_lockOut;
    QRect rectBtn_1_2_locking;
    QRect rectBtn_1_3_Keypad[12];
    QRect rectBtn_1_7_locked;

private:
    QImage mImage_1_1;
    QImage mImage_1_2;
    QImage mImage_1_3;
    QImage mImage_1_4;
    QImage mImage_1_5;
    QImage mImage_1_6;
    QImage mImage_1_7;

    QColor colorBtnPressedMask;
    QFont fontClock;
    QPen penClock;
    QFont fontDate;
    QPen penDate;
    QFont fontPsw;
    QPen penPsw;


};

#endif
