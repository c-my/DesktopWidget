#ifndef MAINTABSTYLE_H
#define MAINTABSTYLE_H

#include <QProxyStyle>
#include <QPainter>
#include <QStyleOptionTab>


class MainTabStyle:public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
                           const QSize &size, const QWidget *widget) const;
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;
};
#endif // MAINTABSTYLE_H
