#ifndef MAINTABSTYLE_H
#define MAINTABSTYLE_H

#include <QProxyStyle>
#include <QPainter>
#include <QStyleOptionTab>


class MainTabStyle:public QProxyStyle
{
public:
    QSize sizeFromContents(ContentsType type, const QStyleOption *option,
                           const QSize &size, const QWidget *widget) const
    {
        QSize tabsize = QProxyStyle::sizeFromContents(type, option, size, widget);
        if (type == QStyle::CT_TabBarTab) {
            tabsize.transpose();
            tabsize.rwidth() = 90; // 设置每个tabBar中item的大小
            tabsize.rheight() = 44;//设置高度
        }
        return tabsize;
    }
    void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
    {
        if (element == CE_TabBarTabLabel)
        {//如果元件是TabBarTabLabel
            if (const QStyleOptionTab *tab = qstyleoption_cast<const QStyleOptionTab *>(option)) {
                QRect allRect = tab->rect;//获取tab矩形框
                if (tab->state & QStyle::State_Selected) {
                    painter->save();
                    painter->setPen(0x89cfff);//设置颜色
                    painter->setBrush(QBrush(0x89cfff));//设置Brush颜色
                    painter->drawRect(allRect.adjusted(6, 6, 6, -6));//这里调整高亮
                    painter->restore();//恢复
                }
                QTextOption option;//这里设置文本样式
                option.setAlignment(Qt::AlignCenter);//设置对其方式。居中对齐
                if (tab->state & QStyle::State_Selected) {
                    painter->setPen(0xf8fcff);//设置颜色
                }
                else {
                    painter->setPen(0x5d5d5d);
                }
                painter->drawText(allRect, tab->text, option);//绘制文本
                return;
            }
        }
        if (element == CE_TabBarTab) {
            QProxyStyle::drawControl(element, option, painter, widget);

        }
    }
};

#endif // MAINTABSTYLE_H
