/********************************************************************************
** Form generated from reading UI file 'kabtrak.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KABTRAK_H
#define UI_KABTRAK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Kabtrak
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QFormLayout *formLayout;
    QPushButton *pushButton;

    void setupUi(QMainWindow *Kabtrak)
    {
        if (Kabtrak->objectName().isEmpty())
            Kabtrak->setObjectName(QStringLiteral("Kabtrak"));
        Kabtrak->resize(1230, 581);
        QFont font;
        font.setFamily(QStringLiteral("Century Gothic"));
        font.setPointSize(9);
        Kabtrak->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("../../../GitHub/kabTRAK/mtd_Icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Kabtrak->setWindowIcon(icon);
        Kabtrak->setStyleSheet(QStringLiteral("background-color: rgb(37, 37, 37);"));
        centralWidget = new QWidget(Kabtrak);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(0);
        formLayout->setVerticalSpacing(0);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        formLayout->setWidget(0, QFormLayout::FieldRole, pushButton);


        horizontalLayout->addLayout(formLayout);

        Kabtrak->setCentralWidget(centralWidget);

        retranslateUi(Kabtrak);

        QMetaObject::connectSlotsByName(Kabtrak);
    } // setupUi

    void retranslateUi(QMainWindow *Kabtrak)
    {
        Kabtrak->setWindowTitle(QApplication::translate("Kabtrak", "Kabtrak", 0));
        pushButton->setText(QApplication::translate("Kabtrak", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class Kabtrak: public Ui_Kabtrak {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KABTRAK_H
