#include "widget.h"
#include "ui_widget.h"
#include "converttool.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString s = ConvertTool::getInstance().IPToCode("1092.168.2.3",11010,2);
    qDebug()<<s;
    qDebug()<<ConvertTool::getInstance().CodeToIP(s);
}

Widget::~Widget()
{
    delete ui;
}
