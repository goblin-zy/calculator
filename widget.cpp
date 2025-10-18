#include "Widget.h"
#include "ui_Widget.h"
#include <QMessageBox>
#include <QStringList>
#include <cmath>
#include <QDoubleValidator>  // 用于x值输入验证（可选，增强输入合法性）
#include<map>
using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initWidgetProps();  // 初始化控件属性

    // 信号与槽绑定（所有控件均用ui->访问）
    connect(ui->btnAdd, &QPushButton::clicked, this, &Widget::onBtnAddClicked);
    connect(ui->btnSub, &QPushButton::clicked, this, &Widget::onBtnSubClicked);
    connect(ui->btnCalcX, &QPushButton::clicked, this, &Widget::onBtnCalcXClicked);
    connect(ui->btnReset, &QPushButton::clicked, this, &Widget::onBtnResetClicked);
    connect(ui->btnQuit, &QPushButton::clicked, this, &Widget::onBtnQuitClicked);
}

Widget::~Widget()
{
    delete ui;  // 释放UI资源
}

// 控件属性初始化（含x值输入验证）
void Widget::initWidgetProps()
{
    // 1. 窗口属性
    this->setWindowTitle("一元稀疏多项式计算器（Widget版）");
    this->setFixedSize(800, 500);  // 固定窗口大小

    // 2. 输入框提示文本
   /* ui->leLeftPoly->setPlaceholderText("例：3 2 3 5 1 -1 0（表示2x³+5x-1）");
    ui->leRightPoly->setPlaceholderText("例：2 1 2 -3 0（表示x²-3）");
    ui->leX->setPlaceholderText("例：2.5 或 -1（支持小数）");*/

    // 3. x值输入验证（仅允许数字/小数/负号，双重保障）
    ui->leX->setValidator(new QDoubleValidator(-1e18, 1e18, 10, this));



    // 5. 初始状态：左操作数可编辑
    ui->leLeftPoly->setReadOnly(false);
}

// 完整解析多项式输入（复刻原代码逻辑，无修改）
bool Widget::parsePolyInput(const QString &input, Polynomial &poly, QString &errMsg)
{
    // 1. 分割输入字符串（过滤空字符）
    QStringList parts = input.split(" ", Qt::SkipEmptyParts);
    if (parts.isEmpty()) {
        errMsg = "输入不能为空！";
        return false;
    }

    // 2. 解析项数（非负整数）
    bool ok;
    int n = parts[0].toInt(&ok);
    if (!ok || n < 0) {
        errMsg = "项数必须是非负整数！（如0表示空多项式）";
        return false;
    }

    // 3. 校验参数数量（项数n需2n个系数指数对）
    if (parts.size() != 1 + 2 * n) {
        errMsg = QString("输入格式错误！项数为%1，需%2个系数指数对（当前输入%3个参数）")
                     .arg(n).arg(2*n).arg(parts.size() - 1);
        return false;
    }

    // 4. 解析系数和指数（新增：合并同类项，支持相同指数）  这里使用unordered_map是为了合并同类项，而map不能接收两个相同的键
    unordered_map<int, double> tempMap; // 临时存储，用于合并同类项（键：指数，值：系数和）
    for (int i = 0; i < n; ++i) {
        // 解析系数（支持小数/负数）
        double xishu = parts[1 + 2*i].toDouble(&ok);
        if (!ok) {
            errMsg = QString("第%1个系数不是有效数字！（如2.5、-3）").arg(i + 1);
            return false;
        }

        // 解析指数（必须是整数）
        int cishu = parts[2 + 2*i].toInt(&ok);
        if (!ok) {
            errMsg = QString("第%1个指数不是整数！（如3、-2）").arg(i + 1);
            return false;
        }

        // 核心修改：相同指数的系数累加（合并同类项）
        tempMap[cishu] += xishu; // 重点！不再是直接赋值，而是累加
    }

    //  过滤零系数项，并按指数降序排序（复用原map的排序特性）
    map<int, double, greater<int>> polyMap;
    for (auto &pair : tempMap) {
        if (pair.second != 0) { // 只保留系数非0的项
            polyMap[pair.first] = pair.second;
        }
    }

    // 5. 生成Node链表，构造Polynomial对象（复用原代码逻辑）
    Node* tempHead = new Node();
    tempHead->next = nullptr;
    Node* curr = tempHead;
    for (auto it = polyMap.begin(); it != polyMap.end(); ++it) {
        Node* newNode = new Node(it->second, it->first);
        curr->next = newNode;
        curr = curr->next;
    }

    // 6. 构造Polynomial（调用原代码构造函数，深拷贝）
    poly = Polynomial(tempHead);

    // 7. 释放临时链表（避免内存泄漏）
   /* Node* delTemp = tempHead;
    while (delTemp) {
        Node* tempDel = delTemp;
        delTemp = delTemp->next;
        delete tempDel;
    }*/ //不用释放，后续该Poly销毁时会释放

    return true;
}


void Widget::showPolyResult(const Polynomial &poly)
{
    QString resultStr;
    if (poly.head->next == nullptr) {
        // 空多项式：仅保留纯数字0，无多余字符（符合输入格式）
        resultStr = "✅ 多项式结果：0";
    } else {
        resultStr += "✅ 多项式结果：";
        resultStr += QString("%1").arg(poly.length);  // 项数（纯数字）
        Node* curr = poly.head->next;
        while (curr) {
            // 用空格分隔系数和指数，与输入格式保持一致（关键修复）
            resultStr += QString(" %1 %2").arg(curr->xishu).arg(curr->cishu);
            curr = curr->next;
        }
    }

    // 显示结果到文本框
    ui->teResult->setText(resultStr);

    // 连续计算：将结果填充到左操作数（只读）
    if (!isFirstCalc) {
        // 动态计算前缀长度（兼容特殊字符编码，避免固定索引错误）
        const QString prefix = "✅ 多项式结果：";
        int prefixLen = prefix.length();
        // 截取前缀后的内容，并去除首尾空格（避免多余空白影响解析）
        QString polyStr = resultStr.mid(prefixLen).trimmed();
        // 填充到左输入框
        ui->leLeftPoly->setText(polyStr);
        ui->leLeftPoly->setReadOnly(true);
    }
}

// 显示多项式结果（复用原代码格式）
/*void Widget::showPolyResult(const Polynomial &poly)
{
    QString resultStr;
    if (poly.head->next == nullptr) {
        resultStr = "✅ 多项式结果：";
    } else {
        resultStr += "✅ 多项式结果：";
        resultStr += QString("%1").arg(poly.length);
        Node* curr = poly.head->next;
        while (curr) {
            resultStr += QString(",%1,%2").arg(curr->xishu).arg(curr->cishu);
            curr = curr->next;
        }
    }

    // 显示到结果框
    ui->teResult->setText(resultStr);

    // 连续计算：左操作数设为上次结果（只读）
    if (!isFirstCalc) {
        QString polyStr = resultStr.mid(7);  // 去掉"✅ 多项式结果："前缀
        ui->leLeftPoly->setText(polyStr);
        ui->leLeftPoly->setReadOnly(true);
    }
}*/

// 显示x计算结果（追加显示，不覆盖多项式结果）
void Widget::showXResult(double result)
{
    QString xResultStr = QString("\n✅ 代入x计算结果：%1").arg(result, 0, 'f', 6);  // 保留6位小数
    ui->teResult->append(xResultStr);
}

// 加法槽函数（调用原代码operator+）
void Widget::onBtnAddClicked()
{

    //这个获取输入是给 原左操作数框
    // 获取当前左操作数（实时值）
    QString currentLeft = ui->leLeftPoly->text().trimmed();

    // 实时显示当前左操作数（覆盖旧内容，而非追加）
    if (currentLeft.isEmpty()) {
        ui->teCurrentLeft->setText("当前左操作数：（空）");
    } else {
        ui->teCurrentLeft->setText(QString("当前左操作数：%1").arg(currentLeft));
    }

    // 获取输入（ui->访问输入框）
    QString leftInput = ui->leLeftPoly->text().trimmed();
    QString rightInput = ui->leRightPoly->text().trimmed();

    // 解析输入
    Polynomial leftPoly, rightPoly;
    QString errMsg;
    if (!parsePolyInput(leftInput, leftPoly, errMsg)) {
        QMessageBox::warning(this, "❌ 输入错误（左操作数）", errMsg);
        return;
    }
    if (!parsePolyInput(rightInput, rightPoly, errMsg)) {
        QMessageBox::warning(this, "❌ 输入错误（右操作数）", errMsg);
        return;
    }

    // 执行加法（原代码逻辑）
    resultPoly = leftPoly + rightPoly;
    isFirstCalc = false;

    // 显示结果
    showPolyResult(resultPoly);
}

// 减法槽函数（调用原代码operator-）
void Widget::onBtnSubClicked()
{
    //这个获取输入是给 原左操作数框
    // 获取当前左操作数（实时值）
    QString currentLeft = ui->leLeftPoly->text().trimmed();

    // 实时显示当前左操作数（覆盖旧内容，而非追加）
    if (currentLeft.isEmpty()) {
        ui->teCurrentLeft->setText("当前左操作数：（空）");
    } else {
        ui->teCurrentLeft->setText(QString("当前左操作数：%1").arg(currentLeft));
    }

    // 获取输入（ui->访问输入框）
    QString leftInput = ui->leLeftPoly->text().trimmed();
    QString rightInput = ui->leRightPoly->text().trimmed();

    // 解析输入
    Polynomial leftPoly, rightPoly;
    QString errMsg;
    if (!parsePolyInput(leftInput, leftPoly, errMsg)) {
        QMessageBox::warning(this, "❌ 输入错误（左操作数）", errMsg);
        return;
    }
    if (!parsePolyInput(rightInput, rightPoly, errMsg)) {
        QMessageBox::warning(this, "❌ 输入错误（右操作数）", errMsg);
        return;
    }

    // 执行减法（原代码逻辑）
    resultPoly = leftPoly - rightPoly;
    isFirstCalc = false;

    // 显示结果
    showPolyResult(resultPoly);
}

// 计算x值槽函数（复用原代码x_cal逻辑）
void Widget::onBtnCalcXClicked()
{
    // 1. 校验是否有运算结果
    if (isFirstCalc && ui->leLeftPoly->text().isEmpty()) {
        QMessageBox::warning(this, "❌ 计算错误", "请先输入多项式并执行加减运算！");
        return;
    }

    // 2. 解析x值（ui->访问x输入框）
    QString xInput = ui->leX->text().trimmed();
    if (xInput.isEmpty()) {
        QMessageBox::warning(this, "❌ 输入错误", "请输入x的值！");
        return;
    }

    bool ok;
    double x = xInput.toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "❌ 输入错误（x值）", "x值必须是有效数字！（如2.5、-1）");
        return;
    }

    // 3. 校验负指数x=0（原代码逻辑）
    if (resultPoly.tail != resultPoly.head && resultPoly.tail->cishu < 0 && x == 0) {
        QMessageBox::warning(this, "❌ 计算错误", "存在负指数项，x=0无意义！");
        return;
    }

    // 4. 执行x计算（原代码逻辑）
    double answer = 0;
    Node* curr = resultPoly.head->next;
    while (curr) {
        answer += curr->xishu * pow(x, curr->cishu);
        curr = curr->next;
    }

    // 5. 显示x计算结果
    showXResult(answer);
}

// 重新开始槽函数（重置所有状态）
void Widget::onBtnResetClicked()
{
    //清空原左操作数文本框
     ui->teCurrentLeft->clear();

    // 1. 清空所有输入框（ui->访问控件）
    ui->leLeftPoly->clear();
    ui->leRightPoly->clear();
    ui->leX->clear();

    // 2. 清空结果框
    ui->teResult->clear();

    // 3. 重置状态
    ui->leLeftPoly->setReadOnly(false);  // 左操作数可编辑
    isFirstCalc = true;                  // 标记为首次计算
    resultPoly = Polynomial();           // 重置结果多项式（调用原代码默认构造）

    // 4. 提示用户
    QMessageBox::information(this, "ℹ️ 提示", "已重置所有状态，可重新输入多项式！");
}

// 退出槽函数（确认后关闭窗口）
void Widget::onBtnQuitClicked()
{
    // 弹出确认对话框
    int ret = QMessageBox::question(this, "❓ 确认退出", "是否要关闭计算器？",
                                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        this->close();  // 关闭窗口
    }
}
