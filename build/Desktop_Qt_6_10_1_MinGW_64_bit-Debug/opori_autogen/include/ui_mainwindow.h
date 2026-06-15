/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *lbl1;
    QLabel *label;
    QLabel *lbl_CurrentTime;
    QLabel *lbl_CurrentDate;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1920, 1080);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(1100, 727, 301, 251));
        pushButton->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"background-image: url(:/new/prefix1/Resources/Group 33.png);\n"
"background-repeat: no-repeat;\n"
"background-position: center;\n"
"border: none;\n"
"outline: none;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"background-image: url(:/new/prefix1/Resources/Group 33 (1).png);\n"
"background-repeat: no-repeat;\n"
"background-position: center;\n"
"border: none;\n"
"outline: none;\n"
"}\n"
"\n"
""));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setEnabled(true);
        pushButton_2->setGeometry(QRect(1510, 727, 301, 251));
        pushButton_2->setMouseTracking(false);
        pushButton_2->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"background-image: url(:/new/prefix1/Resources/Group 43.png);\n"
"background-repeat: no-repeat;\n"
"background-position: center;\n"
"border: none;\n"
"outline: none;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"background-image: url(:/new/prefix1/Resources/Group 43 (1).png);\n"
"background-repeat: no-repeat;\n"
"background-position: center;\n"
"border: none;\n"
"outline: none;\n"
"}\n"
"\n"
""));
        pushButton_2->setFlat(false);
        lbl1 = new QLabel(centralwidget);
        lbl1->setObjectName("lbl1");
        lbl1->setGeometry(QRect(990, 180, 211, 61));
        QFont font;
        font.setPointSize(22);
        lbl1->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 1920, 1080));
        label->setPixmap(QPixmap(QString::fromUtf8(":/new/prefix1/Resources/Frame 2.png")));
        lbl_CurrentTime = new QLabel(centralwidget);
        lbl_CurrentTime->setObjectName("lbl_CurrentTime");
        lbl_CurrentTime->setGeometry(QRect(1775, -5, 181, 81));
        QFont font1;
        font1.setPointSize(24);
        font1.setBold(true);
        lbl_CurrentTime->setFont(font1);
        lbl_CurrentDate = new QLabel(centralwidget);
        lbl_CurrentDate->setObjectName("lbl_CurrentDate");
        lbl_CurrentDate->setGeometry(QRect(1817, 42, 141, 51));
        QFont font2;
        font2.setPointSize(12);
        lbl_CurrentDate->setFont(font2);
        MainWindow->setCentralWidget(centralwidget);
        label->raise();
        pushButton->raise();
        pushButton_2->raise();
        lbl1->raise();
        lbl_CurrentTime->raise();
        lbl_CurrentDate->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1920, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        lbl1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label->setText(QString());
        lbl_CurrentTime->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        lbl_CurrentDate->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
