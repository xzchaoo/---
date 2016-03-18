/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *startGameAction;
    QAction *actionDev_save_layers;
    QAction *stopGameAction;
    QAction *settingDialog;
    QAction *testFindCanGo;
    QAction *testMouseClick;
    QAction *autoLink;
    QAction *restartGameAction;
    QAction *guideAction;
    QAction *aboutAction;
    QAction *saveViewAction;
    QAction *saveAction;
    QAction *restoreAction;
    QAction *awardToolAction;
    QAction *defaultIconAction;
    QWidget *centralWidget;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_4;
    QMenu *m_guanqiaMenu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(891, 519);
        MainWindow->setContextMenuPolicy(Qt::NoContextMenu);
        startGameAction = new QAction(MainWindow);
        startGameAction->setObjectName(QStringLiteral("startGameAction"));
        actionDev_save_layers = new QAction(MainWindow);
        actionDev_save_layers->setObjectName(QStringLiteral("actionDev_save_layers"));
        actionDev_save_layers->setVisible(true);
        stopGameAction = new QAction(MainWindow);
        stopGameAction->setObjectName(QStringLiteral("stopGameAction"));
        settingDialog = new QAction(MainWindow);
        settingDialog->setObjectName(QStringLiteral("settingDialog"));
        testFindCanGo = new QAction(MainWindow);
        testFindCanGo->setObjectName(QStringLiteral("testFindCanGo"));
        testMouseClick = new QAction(MainWindow);
        testMouseClick->setObjectName(QStringLiteral("testMouseClick"));
        autoLink = new QAction(MainWindow);
        autoLink->setObjectName(QStringLiteral("autoLink"));
        restartGameAction = new QAction(MainWindow);
        restartGameAction->setObjectName(QStringLiteral("restartGameAction"));
        guideAction = new QAction(MainWindow);
        guideAction->setObjectName(QStringLiteral("guideAction"));
        aboutAction = new QAction(MainWindow);
        aboutAction->setObjectName(QStringLiteral("aboutAction"));
        saveViewAction = new QAction(MainWindow);
        saveViewAction->setObjectName(QStringLiteral("saveViewAction"));
        saveAction = new QAction(MainWindow);
        saveAction->setObjectName(QStringLiteral("saveAction"));
        restoreAction = new QAction(MainWindow);
        restoreAction->setObjectName(QStringLiteral("restoreAction"));
        awardToolAction = new QAction(MainWindow);
        awardToolAction->setObjectName(QStringLiteral("awardToolAction"));
        defaultIconAction = new QAction(MainWindow);
        defaultIconAction->setObjectName(QStringLiteral("defaultIconAction"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 891, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        m_guanqiaMenu = new QMenu(menuBar);
        m_guanqiaMenu->setObjectName(QStringLiteral("m_guanqiaMenu"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(m_guanqiaMenu->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(startGameAction);
        menu->addAction(restartGameAction);
        menu->addAction(stopGameAction);
        menu->addAction(saveViewAction);
        menu->addAction(saveAction);
        menu->addAction(restoreAction);
        menu_2->addAction(settingDialog);
        menu_4->addAction(guideAction);
        menu_4->addAction(aboutAction);
        menu_4->addAction(awardToolAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\350\277\236\350\277\236\347\234\213", 0));
        startGameAction->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", 0));
        actionDev_save_layers->setText(QApplication::translate("MainWindow", "dev_save_layers", 0));
        stopGameAction->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237\346\270\270\346\210\217", 0));
        settingDialog->setText(QApplication::translate("MainWindow", "\346\216\247\345\210\266\351\235\242\346\235\277", 0));
        testFindCanGo->setText(QApplication::translate("MainWindow", "\345\267\246\344\270\212\350\247\222\345\217\257\344\273\245\345\210\260\345\223\252\351\207\214", 0));
        testMouseClick->setText(QApplication::translate("MainWindow", "\351\274\240\346\240\207\347\226\257\347\213\202\347\202\271\345\207\273", 0));
        autoLink->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\350\277\236\345\207\273\350\213\245\345\271\262\345\257\271", 0));
        restartGameAction->setText(QApplication::translate("MainWindow", "\351\207\215\346\226\260\345\274\200\345\247\213", 0));
        guideAction->setText(QApplication::translate("MainWindow", "\346\270\270\346\210\217\346\214\207\345\215\227", 0));
        aboutAction->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0));
        saveViewAction->setText(QApplication::translate("MainWindow", "\346\210\252\345\233\276", 0));
        saveAction->setText(QApplication::translate("MainWindow", "\345\255\230\346\241\243", 0));
        restoreAction->setText(QApplication::translate("MainWindow", "\346\201\242\345\244\215\345\255\230\346\241\243", 0));
        awardToolAction->setText(QApplication::translate("MainWindow", "\346\261\202\347\202\271\351\201\223\345\205\267...", 0));
        defaultIconAction->setText(QApplication::translate("MainWindow", "\345\210\207\346\215\242\345\233\236\351\273\230\350\256\244\345\233\276\346\240\207\345\272\223", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\346\270\270\346\210\217", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\270\270\346\210\217\350\256\276\347\275\256", 0));
        menu_4->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", 0));
        m_guanqiaMenu->setTitle(QApplication::translate("MainWindow", "\345\205\263\345\215\241", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
