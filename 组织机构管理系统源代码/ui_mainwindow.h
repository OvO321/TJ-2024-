/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QDockWidget *dockWidget_4;
    QWidget *dockWidgetContents_4;
    QPushButton *depButton_1;
    QPushButton *depButton_2;
    QPushButton *depButton_3;
    QPushButton *depButton_4;
    QPushButton *depButton_5;
    QPushButton *depButton_6;
    QPushButton *depButton_7;
    QPushButton *depButton_8;
    QPushButton *depButton_9;
    QPushButton *depButton_10;
    QLabel *canvasWidthLabel;
    QSpinBox *widthSpinBox;
    QLabel *canvasHeightLabel;
    QSpinBox *heightSpinBox;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(714, 556);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 714, 25));
        MainWindow->setMenuBar(menubar);
        dockWidget_4 = new QDockWidget(MainWindow);
        dockWidget_4->setObjectName("dockWidget_4");
        dockWidget_4->setMinimumSize(QSize(106, 45));
        dockWidget_4->setMaximumSize(QSize(106, 524287));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName("dockWidgetContents_4");
        depButton_1 = new QPushButton(dockWidgetContents_4);
        depButton_1->setObjectName("depButton_1");
        depButton_1->setGeometry(QRect(10, 30, 41, 41));
        depButton_1->setCheckable(true);
        depButton_1->setChecked(true);
        depButton_1->setAutoExclusive(true);
        depButton_2 = new QPushButton(dockWidgetContents_4);
        depButton_2->setObjectName("depButton_2");
        depButton_2->setGeometry(QRect(60, 30, 41, 41));
        depButton_2->setCheckable(true);
        depButton_2->setAutoExclusive(true);
        depButton_3 = new QPushButton(dockWidgetContents_4);
        depButton_3->setObjectName("depButton_3");
        depButton_3->setGeometry(QRect(10, 90, 41, 41));
        depButton_3->setCheckable(true);
        depButton_3->setAutoExclusive(true);
        depButton_4 = new QPushButton(dockWidgetContents_4);
        depButton_4->setObjectName("depButton_4");
        depButton_4->setGeometry(QRect(60, 90, 41, 41));
        depButton_4->setCheckable(true);
        depButton_4->setAutoExclusive(true);
        depButton_5 = new QPushButton(dockWidgetContents_4);
        depButton_5->setObjectName("depButton_5");
        depButton_5->setGeometry(QRect(10, 150, 41, 41));
        depButton_5->setCheckable(true);
        depButton_5->setAutoExclusive(true);
        depButton_6 = new QPushButton(dockWidgetContents_4);
        depButton_6->setObjectName("depButton_6");
        depButton_6->setGeometry(QRect(60, 150, 41, 41));
        depButton_6->setStyleSheet(QString::fromUtf8(""));
        depButton_6->setCheckable(true);
        depButton_6->setAutoExclusive(true);
        depButton_7 = new QPushButton(dockWidgetContents_4);
        depButton_7->setObjectName("depButton_7");
        depButton_7->setGeometry(QRect(10, 210, 41, 41));
        depButton_7->setStyleSheet(QString::fromUtf8(""));
        depButton_7->setCheckable(true);
        depButton_7->setAutoExclusive(true);
        depButton_8 = new QPushButton(dockWidgetContents_4);
        depButton_8->setObjectName("depButton_8");
        depButton_8->setGeometry(QRect(60, 210, 41, 41));
        depButton_8->setCheckable(true);
        depButton_8->setAutoExclusive(true);
        depButton_9 = new QPushButton(dockWidgetContents_4);
        depButton_9->setObjectName("depButton_9");
        depButton_9->setGeometry(QRect(10, 270, 41, 41));
        depButton_9->setStyleSheet(QString::fromUtf8(""));
        depButton_9->setCheckable(true);
        depButton_9->setAutoExclusive(true);
        depButton_10 = new QPushButton(dockWidgetContents_4);
        depButton_10->setObjectName("depButton_10");
        depButton_10->setGeometry(QRect(60, 270, 41, 41));
        depButton_10->setCheckable(true);
        depButton_10->setAutoExclusive(true);
        canvasWidthLabel = new QLabel(dockWidgetContents_4);
        canvasWidthLabel->setObjectName("canvasWidthLabel");
        canvasWidthLabel->setGeometry(QRect(10, 340, 91, 20));
        widthSpinBox = new QSpinBox(dockWidgetContents_4);
        widthSpinBox->setObjectName("widthSpinBox");
        widthSpinBox->setGeometry(QRect(10, 360, 81, 22));
        canvasHeightLabel = new QLabel(dockWidgetContents_4);
        canvasHeightLabel->setObjectName("canvasHeightLabel");
        canvasHeightLabel->setGeometry(QRect(10, 390, 91, 20));
        heightSpinBox = new QSpinBox(dockWidgetContents_4);
        heightSpinBox->setObjectName("heightSpinBox");
        heightSpinBox->setGeometry(QRect(10, 420, 81, 22));
        dockWidget_4->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_4);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        depButton_1->setText(QString());
        depButton_2->setText(QString());
        depButton_3->setText(QString());
        depButton_4->setText(QString());
        depButton_5->setText(QString());
        depButton_6->setText(QString());
        depButton_7->setText(QString());
        depButton_8->setText(QString());
        depButton_9->setText(QString());
        depButton_10->setText(QString());
        canvasWidthLabel->setText(QCoreApplication::translate("MainWindow", "Canvas Width:", nullptr));
        canvasHeightLabel->setText(QCoreApplication::translate("MainWindow", "Canvas Height:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
