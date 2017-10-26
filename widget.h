#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void hideUpdata();

private:
    Ui::Widget *ui;
    int deskHeight;
    int deskWidth;
    enum HIDEPOS{NONE,TOP,LEFT,RIGHT}HidePos;
};

#endif // WIDGET_H
