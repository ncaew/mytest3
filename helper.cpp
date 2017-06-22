#include "helper.h"
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QDateTime>
#include <QDebug>
#include <QTranslator>

Helper::Helper()
{
    mImage_1_1 = QImage(":/rc/1-1.png");
    mImage_1_2 = QImage(":/rc/1-2.png");
    mImage_1_3 = QImage(":/rc/1-3.png");
    mImage_1_4 = QImage(":/rc/1-4.png");
    mImage_1_5 = QImage(":/rc/1-5.png");
    mImage_1_6 = QImage(":/rc/1-6.png");
    mImage_1_7 = QImage(":/rc/1-7.png");

    rectBtn_1_1_lockIn = QRect(800-183,0,800,238);
    rectBtn_1_1_lockOut = QRect(800-183,239,800,480);
    rectBtn_1_2_locking = QRect(800-183,0,800,480);
    rectBtn_1_7_locked = rectBtn_1_2_locking;
    QPoint pointKeypad[12];
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<3;j++)
        {
            pointKeypad[i*3+j].setX(595+76*j);
            pointKeypad[i*3+j].setY( 98+88*i);
        }
    }
    for(int i=0;i<12;i++)
    {
        qDebug()<<pointKeypad[i];
        rectBtn_1_3_Keypad[i].setX(pointKeypad[i].x()-30);
        rectBtn_1_3_Keypad[i].setY(pointKeypad[i].y()-30);
        rectBtn_1_3_Keypad[i].setWidth(60);
        rectBtn_1_3_Keypad[i].setHeight(60);
        qDebug()<<rectBtn_1_3_Keypad[i];
        bBtnPressed_1_3_Keypad[i] = false;
    }

    bBtnPressed_1_1_lockIn = false;
    bBtnPressed_1_1_lockOut = false;
    bBtnPressed_1_2_locking = false;
    bBtnPressed_1_7_locked = false;

    colorBtnPressedMask = QColor(255,255,255,255*3/100);
    fontClock.setFamily("Digital-7");
    fontClock.setPixelSize(128);
    penClock.setColor(QColor("#B5C0D3"));
    penClock.setWidth(1);
    fontDate.setFamily("Noto Sans CJK SC");
    fontDate.setPixelSize(28);
    penDate.setColor(QColor("#8994A6"));
    penDate.setWidth(1);
    fontPsw.setFamily("Noto Sans CJK SC");
    fontPsw.setPixelSize(62);
    penPsw.setColor(QColor("#56BACA"));
    penPsw.setWidth(1);
}

void Helper::clearBtnPressed()
{
    for(int i=0;i<12;i++)
    {
        bBtnPressed_1_3_Keypad[i] = false;
    }
    bBtnPressed_1_1_lockIn = false;
    bBtnPressed_1_1_lockOut = false;
    bBtnPressed_1_2_locking = false;
    bBtnPressed_1_7_locked = false;
}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    Q_UNUSED(event);
    Q_UNUSED(elapsed);
    painter->save();

    painter->restore();
}

void Helper::paint_1_1(QPainter *painter, QPaintEvent *event)
{
    Q_UNUSED(event);
    QDateTime dtCurrent = QDateTime::currentDateTime();
    QString strDate = dtCurrent.toString("yyyy/M/dd");
    QString strTime = dtCurrent.toString("HH:mm:ss");
    QString strWeek;
    switch( QDate::currentDate().dayOfWeek() )
    {
    case 1:
        strWeek = QObject::tr("星期一");
        break;
    case 2:
        strWeek = QObject::tr("星期二");
        break;
    case 3:
        strWeek = QObject::tr("星期三");
        break;
    case 4:
        strWeek = QObject::tr("星期四");
        break;
    case 5:
        strWeek = QObject::tr("星期五");
        break;
    case 6:
        strWeek = QObject::tr("星期六");
        break;
    case 7:
        strWeek = QObject::tr("星期日 ");
        break;
    default:
        qDebug()<<"something is wrong: "<<__FUNCTION__<<__LINE__;
        break;
    }

    int x=150;
    int y=120;
    QImage image(mImage_1_1);
    QPainter painterImage;
    painterImage.begin(&image);
    painterImage.setPen(penClock);
    painterImage.setFont(fontClock);
    painterImage.drawText(x,y+fontClock.pixelSize(),strTime);
    painterImage.setPen(penDate);
    painterImage.setFont(fontDate);
    painterImage.drawText(x+fontClock.pixelSize()/2-20,y+22+fontClock.pixelSize()+fontDate.pixelSize(),strDate+" "+strWeek);
    if(bBtnPressed_1_1_lockIn)
        painterImage.fillRect(rectBtn_1_1_lockIn,colorBtnPressedMask);
    if(bBtnPressed_1_1_lockOut)
        painterImage.fillRect(rectBtn_1_1_lockOut,colorBtnPressedMask);
    painterImage.end();
    painter->drawImage(0,0,image);
}

void Helper::paint_1_2(QPainter *painter, QPaintEvent *event, int nSeconds)
{
    Q_UNUSED(event);
    QImage image(mImage_1_2);
    QPainter painterImage;
    painterImage.begin(&image);
    painterImage.setPen(penClock);
    painterImage.setFont(fontClock);
    painterImage.drawText(QRect(220,130,128,128),Qt::AlignRight,QString::number(nSeconds));
    painterImage.setPen(penDate);
    painterImage.setFont(fontDate);
    if(bBtnPressed_1_2_locking)
        painterImage.fillRect(rectBtn_1_2_locking,colorBtnPressedMask);
    painterImage.end();
    painter->drawImage(0,0,image);
}

void Helper::paint_1_3(QPainter *painter, QPaintEvent *event, int nSeconds, int nLength)
{
    Q_UNUSED(event);
    QImage image(mImage_1_3);
    QPainter painterImage;
    painterImage.begin(&image);
    painterImage.setPen(penClock);
    painterImage.setFont(fontClock);
    painterImage.drawText(QRect(200,260,128,128),Qt::AlignRight,QString::number(nSeconds));
    painterImage.setPen(penPsw);
    painterImage.setFont(fontPsw);
    painterImage.drawText(122,170,QString("*  ").repeated(nLength));
    for(int i=0;i<12;i++)
    {
        if(bBtnPressed_1_3_Keypad[i])
        {
            painterImage.fillRect(rectBtn_1_3_Keypad[i],colorBtnPressedMask);
        }
    }
    painterImage.end();
    painter->drawImage(0,0,image);
}

void Helper::paint_1_4(QPainter *painter, QPaintEvent *event)
{
    Q_UNUSED(event);
    QImage image(mImage_1_4);
    QPainter painterImage;
    painterImage.begin(&image);
    painterImage.setPen(penClock);
    painterImage.setFont(fontClock);
    //painterImage.drawText(x,y+fontClock.pixelSize(),strTime);
    painterImage.setPen(penDate);
    painterImage.setFont(fontDate);
    //painterImage.drawText(x+fontClock.pixelSize()/2-20,y+22+fontClock.pixelSize()+fontDate.pixelSize(),strDate+" "+strWeek);
    painterImage.end();
    painter->drawImage(0,0,image);
}

void Helper::paint_1_5(QPainter *painter, QPaintEvent *event)
{
    Q_UNUSED(event);
    QImage image(mImage_1_5);
    QPainter painterImage;
    painterImage.begin(&image);
    painterImage.setPen(penClock);
    painterImage.setFont(fontClock);
    //painterImage.drawText(x,y+fontClock.pixelSize(),strTime);
    painterImage.setPen(penDate);
    painterImage.setFont(fontDate);
    //painterImage.drawText(x+fontClock.pixelSize()/2-20,y+22+fontClock.pixelSize()+fontDate.pixelSize(),strDate+" "+strWeek);
    painterImage.end();
    painter->drawImage(0,0,image);
}

void Helper::paint_1_6(QPainter *painter, QPaintEvent *event)
{
    Q_UNUSED(event);
    QImage image(mImage_1_6);
    QPainter painterImage;
    painterImage.begin(&image);
    painterImage.setPen(penClock);
    painterImage.setFont(fontClock);
    //painterImage.drawText(x,y+fontClock.pixelSize(),strTime);
    painterImage.setPen(penDate);
    painterImage.setFont(fontDate);
    //painterImage.drawText(x+fontClock.pixelSize()/2-20,y+22+fontClock.pixelSize()+fontDate.pixelSize(),strDate+" "+strWeek);
    painterImage.end();
    painter->drawImage(0,0,image);
}

void Helper::paint_1_7(QPainter *painter, QPaintEvent *event)
{
    Q_UNUSED(event);
    QImage image(mImage_1_7);
    QPainter painterImage;
    painterImage.begin(&image);
    if(bBtnPressed_1_7_locked)
        painterImage.fillRect(rectBtn_1_7_locked,colorBtnPressedMask);
    painterImage.end();
    painter->drawImage(0,0,image);
}
