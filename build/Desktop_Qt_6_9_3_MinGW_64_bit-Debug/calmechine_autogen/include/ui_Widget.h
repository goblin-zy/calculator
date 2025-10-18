/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *btnQuit;
    QLabel *labTitle;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *labX;
    QLineEdit *leX;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labResult;
    QTextEdit *teResult;
    QWidget *widget2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labLeftPoly;
    QLineEdit *leLeftPoly;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labRightPoly;
    QLineEdit *leRightPoly;
    QWidget *widget3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *btnAdd;
    QPushButton *btnSub;
    QPushButton *btnCalcX;
    QPushButton *btnReset;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        btnQuit = new QPushButton(Widget);
        btnQuit->setObjectName("btnQuit");
        btnQuit->setGeometry(QRect(500, 280, 91, 51));
        labTitle = new QLabel(Widget);
        labTitle->setObjectName("labTitle");
        labTitle->setGeometry(QRect(280, 30, 211, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(16);
        font.setBold(true);
        labTitle->setFont(font);
        widget = new QWidget(Widget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(20, 210, 301, 31));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        labX = new QLabel(widget);
        labX->setObjectName("labX");
        QFont font1;
        font1.setPointSize(12);
        labX->setFont(font1);

        horizontalLayout_3->addWidget(labX);

        leX = new QLineEdit(widget);
        leX->setObjectName("leX");

        horizontalLayout_3->addWidget(leX);

        widget1 = new QWidget(Widget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(20, 360, 771, 31));
        horizontalLayout_4 = new QHBoxLayout(widget1);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        labResult = new QLabel(widget1);
        labResult->setObjectName("labResult");
        labResult->setFont(font1);

        horizontalLayout_4->addWidget(labResult);

        teResult = new QTextEdit(widget1);
        teResult->setObjectName("teResult");
        teResult->setReadOnly(true);

        horizontalLayout_4->addWidget(teResult);

        widget2 = new QWidget(Widget);
        widget2->setObjectName("widget2");
        widget2->setGeometry(QRect(20, 110, 771, 72));
        verticalLayout = new QVBoxLayout(widget2);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        labLeftPoly = new QLabel(widget2);
        labLeftPoly->setObjectName("labLeftPoly");
        labLeftPoly->setMinimumSize(QSize(0, 0));
        labLeftPoly->setFont(font1);

        horizontalLayout->addWidget(labLeftPoly);

        leLeftPoly = new QLineEdit(widget2);
        leLeftPoly->setObjectName("leLeftPoly");
        leLeftPoly->setMinimumSize(QSize(280, 30));

        horizontalLayout->addWidget(leLeftPoly);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        labRightPoly = new QLabel(widget2);
        labRightPoly->setObjectName("labRightPoly");
        labRightPoly->setFont(font1);

        horizontalLayout_2->addWidget(labRightPoly);

        leRightPoly = new QLineEdit(widget2);
        leRightPoly->setObjectName("leRightPoly");
        leRightPoly->setMinimumSize(QSize(280, 30));

        horizontalLayout_2->addWidget(leRightPoly);


        verticalLayout->addLayout(horizontalLayout_2);

        widget3 = new QWidget(Widget);
        widget3->setObjectName("widget3");
        widget3->setGeometry(QRect(20, 280, 361, 51));
        horizontalLayout_5 = new QHBoxLayout(widget3);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        btnAdd = new QPushButton(widget3);
        btnAdd->setObjectName("btnAdd");

        horizontalLayout_5->addWidget(btnAdd);

        btnSub = new QPushButton(widget3);
        btnSub->setObjectName("btnSub");

        horizontalLayout_5->addWidget(btnSub);

        btnCalcX = new QPushButton(widget3);
        btnCalcX->setObjectName("btnCalcX");

        horizontalLayout_5->addWidget(btnCalcX);

        btnReset = new QPushButton(widget3);
        btnReset->setObjectName("btnReset");

        horizontalLayout_5->addWidget(btnReset);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        btnQuit->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
        labTitle->setText(QCoreApplication::translate("Widget", "\344\270\200\345\205\203\347\250\200\347\226\217\345\244\232\351\241\271\345\274\217\350\256\241\347\256\227\345\231\250", nullptr));
        labX->setText(QCoreApplication::translate("Widget", "\350\257\267\350\276\223\345\205\245x\345\200\274\357\274\232", nullptr));
        leX->setInputMask(QString());
        leX->setPlaceholderText(QCoreApplication::translate("Widget", "\344\276\213\357\274\2322.5 /-1 / 0\357\274\210\346\224\257\346\214\201\345\260\217\346\225\260\357\274\211", nullptr));
        labResult->setText(QCoreApplication::translate("Widget", "\350\277\220\347\256\227\347\273\223\346\236\234\357\274\232", nullptr));
        teResult->setPlaceholderText(QCoreApplication::translate("Widget", "\350\277\220\347\256\227\347\273\223\346\236\234\345\260\206\346\230\276\347\244\272\345\234\250\350\277\231\351\207\214...", nullptr));
        labLeftPoly->setText(QCoreApplication::translate("Widget", "\345\267\246\346\223\215\344\275\234\346\225\260\357\274\232", nullptr));
        leLeftPoly->setPlaceholderText(QCoreApplication::translate("Widget", "\344\276\213\357\274\2323 2 3 5 1 -1 0\357\274\2102x\302\263+5x-1\357\274\211", nullptr));
        labRightPoly->setText(QCoreApplication::translate("Widget", "\345\217\263\346\223\215\344\275\234\346\225\260\357\274\232", nullptr));
        leRightPoly->setPlaceholderText(QCoreApplication::translate("Widget", "\344\276\213\357\274\2322 1 2 -3 0\357\274\210x\302\262-3\357\274\211", nullptr));
        btnAdd->setText(QCoreApplication::translate("Widget", "\345\212\240\346\263\225\357\274\210+\357\274\211", nullptr));
        btnSub->setText(QCoreApplication::translate("Widget", "\345\207\217\346\263\225\357\274\210-\357\274\211", nullptr));
        btnCalcX->setText(QCoreApplication::translate("Widget", "\344\273\243\345\205\245x\350\256\241\347\256\227", nullptr));
        btnReset->setText(QCoreApplication::translate("Widget", "\351\207\215\346\226\260\345\274\200\345\247\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
