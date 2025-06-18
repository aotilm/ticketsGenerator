/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_4;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *seriesEdit;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *priceEdit;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *countEdit;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *addTicketsBtb;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_3;
    QListView *ticketsListView;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *generateFileBtn;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(700, 370);
        MainWindow->setMinimumSize(QSize(700, 370));
        MainWindow->setMaximumSize(QSize(700, 370));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout_4 = new QGridLayout(centralwidget);
        gridLayout_4->setObjectName("gridLayout_4");
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        groupBox_4->setMaximumSize(QSize(300, 300));
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setObjectName("gridLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox_3 = new QGroupBox(groupBox_4);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setMaximumSize(QSize(270, 50));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label = new QLabel(groupBox_3);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_3->addWidget(label);

        seriesEdit = new QLineEdit(groupBox_3);
        seriesEdit->setObjectName("seriesEdit");
        seriesEdit->setMinimumSize(QSize(50, 20));
        seriesEdit->setMaximumSize(QSize(100, 20));

        horizontalLayout_3->addWidget(seriesEdit);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox = new QGroupBox(groupBox_4);
        groupBox->setObjectName("groupBox");
        groupBox->setMaximumSize(QSize(270, 16777215));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_2->addWidget(label_2);

        priceEdit = new QLineEdit(groupBox);
        priceEdit->setObjectName("priceEdit");
        priceEdit->setMinimumSize(QSize(50, 20));
        priceEdit->setMaximumSize(QSize(100, 20));

        horizontalLayout_2->addWidget(priceEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");
        label_3->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        label_3->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout->addWidget(label_3);

        countEdit = new QLineEdit(groupBox);
        countEdit->setObjectName("countEdit");
        countEdit->setMinimumSize(QSize(50, 20));
        countEdit->setMaximumSize(QSize(100, 20));
        countEdit->setInputMethodHints(Qt::InputMethodHint::ImhDigitsOnly);

        horizontalLayout->addWidget(countEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer = new QSpacerItem(168, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        addTicketsBtb = new QPushButton(groupBox);
        addTicketsBtb->setObjectName("addTicketsBtb");
        addTicketsBtb->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(addTicketsBtb);


        verticalLayout->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(groupBox);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(1, 1, 1, 1);
        scrollArea = new QScrollArea(groupBox_2);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 366, 264));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_3->setObjectName("gridLayout_3");
        ticketsListView = new QListView(scrollAreaWidgetContents);
        ticketsListView->setObjectName("ticketsListView");
        ticketsListView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

        gridLayout_3->addWidget(ticketsListView, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);


        gridLayout_4->addWidget(groupBox_2, 0, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalSpacer_2 = new QSpacerItem(518, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        generateFileBtn = new QPushButton(centralwidget);
        generateFileBtn->setObjectName("generateFileBtn");

        horizontalLayout_5->addWidget(generateFileBtn);


        gridLayout_4->addLayout(horizontalLayout_5, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\224\320\260\320\275\321\226 \320\277\321\200\320\276 \320\272\320\262\320\270\321\202\320\276\320\272", nullptr));
        groupBox_3->setTitle(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\320\241\320\265\321\200\321\226\321\217 \320\272\320\262\320\270\321\202\320\272\321\226\320\262", nullptr));
        groupBox->setTitle(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\246\321\226\320\275\320\260 \321\201\320\265\321\200\321\226\321\227, \320\263\321\200\320\275.", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\232-\321\201\321\202\321\214 \320\272\320\262\320\270\321\202\320\272\321\226\320\262, \321\210\321\202.", nullptr));
        addTicketsBtb->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\264\320\260\321\202\320\270", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\262\320\276\321\200\320\265\320\275\321\226 \320\272\320\262\320\270\321\202\320\272\320\270", nullptr));
        generateFileBtn->setText(QCoreApplication::translate("MainWindow", "\320\227\320\263\320\265\320\275\320\265\321\200\321\203\320\262\320\260\321\202\320\270 \320\272\320\262\320\270\321\202\320\272\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
