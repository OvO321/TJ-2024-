/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *ensureButton;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *textInput;
    QPushButton *exportTableButton;
    QFrame *graph;
    QPushButton *exportPhotoButton;
    QTableWidget *encoderTable;
    QLabel *label_2;
    QTableWidget *keyWordTable;
    QPushButton *importTextButton;
    QPushButton *deleteButton;
    QPushButton *addButton;
    QPushButton *clearButton;
    QComboBox *randomComboBox;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(919, 635);
        ensureButton = new QPushButton(Widget);
        ensureButton->setObjectName("ensureButton");
        ensureButton->setGeometry(QRect(250, 480, 81, 21));
        ensureButton->setCheckable(true);
        ensureButton->setAutoExclusive(true);
        label_3 = new QLabel(Widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(460, 446, 71, 20));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 430, 51, 16));
        textInput = new QLineEdit(Widget);
        textInput->setObjectName("textInput");
        textInput->setGeometry(QRect(20, 450, 421, 20));
        exportTableButton = new QPushButton(Widget);
        exportTableButton->setObjectName("exportTableButton");
        exportTableButton->setGeometry(QRect(840, 570, 61, 31));
        graph = new QFrame(Widget);
        graph->setObjectName("graph");
        graph->setGeometry(QRect(20, 10, 881, 411));
        graph->setFrameShape(QFrame::Box);
        graph->setFrameShadow(QFrame::Raised);
        exportPhotoButton = new QPushButton(Widget);
        exportPhotoButton->setObjectName("exportPhotoButton");
        exportPhotoButton->setGeometry(QRect(840, 490, 61, 31));
        encoderTable = new QTableWidget(Widget);
        encoderTable->setObjectName("encoderTable");
        encoderTable->setGeometry(QRect(460, 470, 361, 151));
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 510, 71, 16));
        keyWordTable = new QTableWidget(Widget);
        keyWordTable->setObjectName("keyWordTable");
        keyWordTable->setGeometry(QRect(20, 540, 421, 81));
        importTextButton = new QPushButton(Widget);
        importTextButton->setObjectName("importTextButton");
        importTextButton->setGeometry(QRect(140, 480, 71, 21));
        deleteButton = new QPushButton(Widget);
        deleteButton->setObjectName("deleteButton");
        deleteButton->setGeometry(QRect(410, 510, 31, 20));
        addButton = new QPushButton(Widget);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(360, 510, 31, 20));
        clearButton = new QPushButton(Widget);
        clearButton->setObjectName("clearButton");
        clearButton->setGeometry(QRect(360, 480, 80, 21));
        randomComboBox = new QComboBox(Widget);
        randomComboBox->addItem(QString());
        randomComboBox->addItem(QString());
        randomComboBox->addItem(QString());
        randomComboBox->addItem(QString());
        randomComboBox->setObjectName("randomComboBox");
        randomComboBox->setGeometry(QRect(20, 480, 91, 22));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\345\223\210\345\244\253\346\233\274\346\240\221", nullptr));
        ensureButton->setText(QCoreApplication::translate("Widget", "\347\241\256\350\256\244\347\224\237\346\210\220", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\345\205\263\351\224\256\345\255\227\347\274\226\347\240\201\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\226\207\346\234\254\350\276\223\345\205\245\357\274\232", nullptr));
        exportTableButton->setText(QCoreApplication::translate("Widget", "\345\257\274\345\207\272\350\241\250\346\240\274", nullptr));
        exportPhotoButton->setText(QCoreApplication::translate("Widget", "\345\257\274\345\207\272\345\233\276\347\211\207", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\345\205\263\351\224\256\345\255\227\345\210\227\350\241\250\357\274\232", nullptr));
        importTextButton->setText(QCoreApplication::translate("Widget", "\345\257\274\345\205\245\346\226\207\346\234\254", nullptr));
        deleteButton->setText(QCoreApplication::translate("Widget", "-", nullptr));
        addButton->setText(QCoreApplication::translate("Widget", "+", nullptr));
        clearButton->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
        randomComboBox->setItemText(0, QCoreApplication::translate("Widget", "\351\232\217\346\234\272\345\255\227\347\254\246\344\270\262", nullptr));
        randomComboBox->setItemText(1, QCoreApplication::translate("Widget", "\351\232\217\346\234\272\346\225\260\345\255\227", nullptr));
        randomComboBox->setItemText(2, QCoreApplication::translate("Widget", "\351\232\217\346\234\272\345\255\227\346\257\215", nullptr));
        randomComboBox->setItemText(3, QCoreApplication::translate("Widget", "\351\232\217\346\234\272\346\261\211\345\255\227", nullptr));

    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
