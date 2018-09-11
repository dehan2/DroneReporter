/********************************************************************************
** Form generated from reading UI file 'DroneReporter.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRONEREPORTER_H
#define UI_DRONEREPORTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DroneReporterClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTableView *tableView_main;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_open_port_file;
    QPushButton *pushButton_start_read_status;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DroneReporterClass)
    {
        if (DroneReporterClass->objectName().isEmpty())
            DroneReporterClass->setObjectName(QStringLiteral("DroneReporterClass"));
        DroneReporterClass->resize(1117, 647);
        centralWidget = new QWidget(DroneReporterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tableView_main = new QTableView(centralWidget);
        tableView_main->setObjectName(QStringLiteral("tableView_main"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView_main->sizePolicy().hasHeightForWidth());
        tableView_main->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(tableView_main);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMaximumSize(QSize(300, 16777215));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_open_port_file = new QPushButton(tab);
        pushButton_open_port_file->setObjectName(QStringLiteral("pushButton_open_port_file"));

        verticalLayout->addWidget(pushButton_open_port_file);

        pushButton_start_read_status = new QPushButton(tab);
        pushButton_start_read_status->setObjectName(QStringLiteral("pushButton_start_read_status"));

        verticalLayout->addWidget(pushButton_start_read_status);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tabWidget->addTab(tab, QString());

        horizontalLayout->addWidget(tabWidget);

        DroneReporterClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DroneReporterClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1117, 21));
        DroneReporterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DroneReporterClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DroneReporterClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DroneReporterClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DroneReporterClass->setStatusBar(statusBar);

        retranslateUi(DroneReporterClass);
        QObject::connect(pushButton_open_port_file, SIGNAL(clicked()), DroneReporterClass, SLOT(load_port_file()));
        QObject::connect(pushButton_start_read_status, SIGNAL(clicked()), DroneReporterClass, SLOT(start_read_status()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DroneReporterClass);
    } // setupUi

    void retranslateUi(QMainWindow *DroneReporterClass)
    {
        DroneReporterClass->setWindowTitle(QApplication::translate("DroneReporterClass", "DroneReporter", 0));
        pushButton_open_port_file->setText(QApplication::translate("DroneReporterClass", "Open Port File", 0));
        pushButton_start_read_status->setText(QApplication::translate("DroneReporterClass", "Read status", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("DroneReporterClass", "Control", 0));
    } // retranslateUi

};

namespace Ui {
    class DroneReporterClass: public Ui_DroneReporterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRONEREPORTER_H
