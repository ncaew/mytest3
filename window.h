#ifndef WINDOW_H
#define WINDOW_H

#include "helper.h"
#include <QWidget>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private:
    int nFPS = 40; // refresh per second
    int nCountdownTimeout = 30 ; // countdown timeout seconds
    Helper mHelper;
    int nCurrentImage;
    QString strPsw;

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;

};


#endif
