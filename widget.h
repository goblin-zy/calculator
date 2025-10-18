#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "Node_Poly.h"  // 你的多项式类头文件

// 包含Qt设计界面自动生成的头文件
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void onBtnAddClicked();    // 加法槽函数
    void onBtnSubClicked();    // 减法槽函数
    void onBtnCalcXClicked();  // 计算x值槽函数
    void onBtnResetClicked();  // 重新开始槽函数
    void onBtnQuitClicked();   // 退出槽函数

private:
    Ui::Widget *ui;
    Polynomial resultPoly;     // 存储运算结果
    bool isFirstCalc = true;   // 首次计算标记

    // 辅助函数
    bool parsePolyInput(const QString &input, Polynomial &poly, QString &errMsg);  // 解析多项式输入
    void showPolyResult(const Polynomial &poly);  // 显示多项式结果
    void showXResult(double result);              // 显示x计算结果
    void initWidgetProps();                       // 控件属性初始化
};

#endif // WIDGET_H
