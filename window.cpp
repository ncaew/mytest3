#include "window.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QTimer>
#include <QPaintEvent>
#include <QDebug>

Window::Window()
{
    setWindowTitle(tr("2D Painting on Native and OpenGL Widgets"));
    this->resize(800,480);
    setFixedSize(800,480);
    //setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    //showFullScreen();
    //setWindowState(this->windowType() ^ Qt::Window);
    //setWindowState(this->windowState() ^ Qt::WindowFullScreen);
    //setWindowState(Qt::WindowFullScreen);

    nCurrentImage = 0;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(1000/nFPS);

}

void Window::animate()
{
    update();
}

void Window::paintEvent(QPaintEvent *event)
{
    static int nCountdown_1_2 = 0 ;
    static int nCountdown_1_3 = 0 ;

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    switch (nCurrentImage) {
    case 0:
        nCountdown_1_2 = nFPS * nCountdownTimeout;
        nCountdown_1_3 = nFPS * nCountdownTimeout;
        mHelper.paint_1_1(&painter,event);
        break;
    case 1:
        --nCountdown_1_2;
        if(nCountdown_1_2==0)
            nCurrentImage = 6;
        mHelper.paint_1_2(&painter,event,nCountdown_1_2/nFPS);
        break;
    case 2:
        --nCountdown_1_3;
        if(nCountdown_1_3==0)
        {
            nCurrentImage = 0;
            strPsw.clear();
        }
        mHelper.paint_1_3(&painter,event,nCountdown_1_3/nFPS,strPsw.length());
        break;
    case 3:
        mHelper.paint_1_4(&painter,event);
        break;
    case 4:
        mHelper.paint_1_5(&painter,event);
        break;
    case 5:
        mHelper.paint_1_6(&painter,event);
        break;
    case 6:
        mHelper.paint_1_7(&painter,event);
        break;
    default:
        painter.fillRect(event->rect(), QBrush(QColor(0, 0, 0)));
        break;
    }
    painter.end();
}

void Window::mouseReleaseEvent(QMouseEvent * event)
{
    qDebug()<<event;
    qDebug()<<"current image:"<<nCurrentImage;
    int i=0;
    switch (nCurrentImage) {
    case 0:
        if(  mHelper.rectBtn_1_1_lockOut.contains(event->pos()))
        {
            qDebug()<<"lock out";
            nCurrentImage = 1;
        }
        else if(  mHelper.rectBtn_1_1_lockIn.contains(event->pos()))
        {
            qDebug()<<"lock in";
            nCurrentImage = 6;
        }
        break;
    case 1:
        if(  mHelper.rectBtn_1_2_locking.contains(event->pos()))
        {
            qDebug()<<"unlock";
            nCurrentImage = 2;
        }
        break;
    case 2:
        for(i=0;i<12;i++)
        {
            if(  mHelper.rectBtn_1_3_Keypad[i].contains(event->pos()))
            {
                break;
            }
        }
        qDebug()<<QString::number(i);
        if(i==10)
        {
            if(strPsw.length()<6)
                strPsw += "0";
        }
        else if(i==9)
            strPsw.remove(strPsw.length()-1,1);
        else if(i==11)
            strPsw.clear();
        else if(i>=0 && i<=8)
        {
            if(strPsw.length()<6)
                strPsw += QString::number(i+1);
        }
        else
            Q_UNUSED(event);
        qDebug()<<"Password:"<<strPsw;
        if(strPsw.length()==6)
        {
            nCurrentImage = 0;
            strPsw.clear();
        }
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        if(  mHelper.rectBtn_1_7_locked.contains(event->pos()))
        {
            qDebug()<<"unlock";
            nCurrentImage = 2;
        }
        break;
    default:
        break;
    }
    mHelper.clearBtnPressed();
}

void Window::mousePressEvent(QMouseEvent * event)
{
    qDebug()<<event<<"current image:"<<nCurrentImage;
    int i=0;
    switch (nCurrentImage) {
    case 0:
        if(  mHelper.rectBtn_1_1_lockIn.contains(event->pos()))
        {
            qDebug()<<"lock in";
            mHelper.bBtnPressed_1_1_lockIn = true;
        }
        else if(  mHelper.rectBtn_1_1_lockOut.contains(event->pos()))
        {
            qDebug()<<"lock out";
            mHelper.bBtnPressed_1_1_lockOut = true;
        }
        break;
    case 1:
        if(  mHelper.rectBtn_1_2_locking.contains(event->pos()))
        {
            qDebug()<<"unlock";
            mHelper.bBtnPressed_1_2_locking = true;
        }
        break;
    case 2:
        for(i=0;i<12;i++)
        {
            if(  mHelper.rectBtn_1_3_Keypad[i].contains(event->pos()))
            {
                mHelper.bBtnPressed_1_3_Keypad[i] = true;
                break;
            }
        }
        qDebug()<<QString::number(i);
        if(i==10)
        {
            qDebug()<<"0";
        }
        else if(i==9)
            qDebug()<<"back";
        else if(i==11)
            qDebug()<<"del";
        else if(i>=0 && i<=8)
        {
            qDebug()<< QString::number(i+1);
        }
        else
            Q_UNUSED(event);
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        if(  mHelper.rectBtn_1_7_locked.contains(event->pos()))
        {
            qDebug()<<"unlock";
            mHelper.bBtnPressed_1_7_locked = true;
        }
        break;
    default:
        break;
    }

}
