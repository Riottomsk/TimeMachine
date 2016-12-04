 #pragma once

#include <timebarconstants.h>

#include <ctime>

#include <QWidget>
#include <QDateTimeEdit>

class TimeBar : public QWidget
{
    Q_OBJECT

public:
    explicit TimeBar(QDateTimeEdit *_fvtEdit, QWidget *parent = 0);
    QSize sizeHint() const Q_DECL_OVERRIDE;
    bool canRequestTime;
    QDateTimeEdit *fvtEdit;

signals:

    void sendMessageToStatusBar(QString message);
    void setPlayTime(qint32 requestTime);

protected:
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QWidget *mainWindow;

    int cursorX;
    qint32 playTime;
    bool cursorHover;
    bool drawSlider;
    QPoint tooltipPoint;

    //Параметры шкалы
    int widgetWidth;
    int scale = 0;
    int divValue;
    qint32 firstVisibleTime;
    qint32 lastVisibleTime;
    qint32 hoverTime;
    int minDivSignPeriod;

    //Параметры деления шкалы
    int divXPos;
    int divHeight;
    bool divSigned;
    qint32 unixtime;
    QDateTime tm;
    double mDivWidth;

    void drawDivSign(QPainter &painter, QString format);
    void updateFVT();

public slots:
    void setFVT(const QDateTime &datetime);
    void setSliderPosition(const qint32 playTime);
};
