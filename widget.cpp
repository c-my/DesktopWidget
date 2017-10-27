#include "widget.h"
#include "ui_widget.h"
#include <QDesktopWidget>
#include <windows.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);//设置窗口置顶
    this->setFixedSize(500,300);
    //获取屏幕的宽高
    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect deskRect = desktopWidget->availableGeometry();
    deskHeight = deskRect.height();
    deskWidth  = deskRect.width();
    //边缘隐藏定时器
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(hideUpdata()));
    timer->start(10);
    tabWidget = new QTabWidget(this);
    tabWidget->setTabPosition(QTabWidget::West);
    QLabel *label1 = new QLabel(tr("新分组中的内容"));
    QLabel *label2 = new QLabel(tr("新新分组中的内容"));
    tabWidget->addTab(label1, tr("新分组"));
    tabWidget->addTab(label2, tr("新新分组"));
    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(tabWidget);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::hideUpdata()
{
    static bool isHide = false;
    if(!isHide)
    {
        //获取鼠标的位置
        POINT pt;
        GetCursorPos(&pt);
        int x = pt.x;
        int y = pt.y;
        //设置边缘隐藏的参数
        int hideSpeed = 20;//每次更新移动的量
        int leftRemain = 20;
        int rightRemain = 20;
        int topRemain = 20;
        //获取窗口尺寸
        int widgetHeight = this->frameGeometry().height();
        int widgetWidth = this->frameGeometry().width();
        if(x>=this->x() && x<=this->x()+widgetWidth && y>=this->y() && y<=this->y()+widgetHeight)
        {
            switch(HidePos)
            {
            case NONE:
                break;
            case LEFT:
                if(this->x()<0-hideSpeed)
                    this->move(this->x()+hideSpeed, this->y());
                else
                    HidePos = NONE;
                break;
            case RIGHT:
                if(this->x()+widgetWidth>deskWidth+hideSpeed)
                    this->move(this->x()-hideSpeed, this->y());
                else
                    HidePos = NONE;
                break;
            case TOP:
                if(this->y()<0)
                    this->move(this->x(),this->y()+hideSpeed);
                else
                    HidePos = NONE;
                break;
            }
        }
        else//鼠标不在界面中
        {
            if(this->x()<=0)//贴在了屏幕左侧
            {
                if(this->x() > -widgetWidth+leftRemain)
                    this->move(this->x()-hideSpeed,this->y());
                else
                    HidePos = LEFT;
            }
            else if(this->x()>=deskWidth-widgetWidth)//贴在了屏幕右侧
            {
                if(this->x() < deskWidth-rightRemain)
                    this->move(this->x()+hideSpeed,this->y());
                else
                    HidePos = RIGHT;
            }
            else if(this->y() <= 0)//贴在了屏幕顶部
            {
                if(this->y()+widgetHeight>topRemain)
                    this->move(this->x(),this->y()-hideSpeed);
                else
                    HidePos = TOP;
            }
        }
    }
}
