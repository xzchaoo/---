/********************************************************************************
** Form generated from reading UI file 'settingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QSpinBox *m_row;
    QLabel *label_3;
    QSpinBox *m_col;
    QLabel *label_4;
    QSpinBox *m_gameTime;
    QLabel *label_7;
    QSpinBox *m_iconTypes;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox;
    QSpinBox *m_openingShowId;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QCheckBox *m_continueHitNoTimeLimit;
    QCheckBox *m_continueHit;
    QLabel *label;
    QSpinBox *m_limitStep;
    QLabel *label_6;
    QSpinBox *m_continueHitInterval;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QCheckBox *m_playBGMOnStartup;
    QCheckBox *m_notMusicWhenHitFail;
    QCheckBox *m_mute;
    QCheckBox *m_noInformationWhenStop;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName(QStringLiteral("SettingDialog"));
        SettingDialog->resize(556, 209);
        verticalLayout = new QVBoxLayout(SettingDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox = new QGroupBox(SettingDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        m_row = new QSpinBox(groupBox);
        m_row->setObjectName(QStringLiteral("m_row"));
        m_row->setMinimum(4);
        m_row->setMaximum(20);
        m_row->setValue(10);

        gridLayout->addWidget(m_row, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        m_col = new QSpinBox(groupBox);
        m_col->setObjectName(QStringLiteral("m_col"));
        m_col->setMinimum(4);
        m_col->setMaximum(20);
        m_col->setValue(10);

        gridLayout->addWidget(m_col, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        m_gameTime = new QSpinBox(groupBox);
        m_gameTime->setObjectName(QStringLiteral("m_gameTime"));
        m_gameTime->setMinimum(10);
        m_gameTime->setMaximum(360);
        m_gameTime->setSingleStep(5);
        m_gameTime->setValue(60);

        gridLayout->addWidget(m_gameTime, 2, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        m_iconTypes = new QSpinBox(groupBox);
        m_iconTypes->setObjectName(QStringLiteral("m_iconTypes"));
        m_iconTypes->setMinimum(5);
        m_iconTypes->setMaximum(33);
        m_iconTypes->setValue(10);

        gridLayout->addWidget(m_iconTypes, 3, 1, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_8, 4, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_3->addWidget(checkBox);

        m_openingShowId = new QSpinBox(groupBox);
        m_openingShowId->setObjectName(QStringLiteral("m_openingShowId"));
        m_openingShowId->setMinimum(1);
        m_openingShowId->setMaximum(5);

        horizontalLayout_3->addWidget(m_openingShowId);


        gridLayout->addLayout(horizontalLayout_3, 4, 1, 1, 1);


        horizontalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(SettingDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        m_continueHitNoTimeLimit = new QCheckBox(groupBox_2);
        m_continueHitNoTimeLimit->setObjectName(QStringLiteral("m_continueHitNoTimeLimit"));

        gridLayout_3->addWidget(m_continueHitNoTimeLimit, 1, 0, 1, 2);

        m_continueHit = new QCheckBox(groupBox_2);
        m_continueHit->setObjectName(QStringLiteral("m_continueHit"));

        gridLayout_3->addWidget(m_continueHit, 0, 0, 1, 2);

        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 2, 0, 1, 1);

        m_limitStep = new QSpinBox(groupBox_2);
        m_limitStep->setObjectName(QStringLiteral("m_limitStep"));
        m_limitStep->setMinimum(3);
        m_limitStep->setMaximum(10);
        m_limitStep->setValue(3);

        gridLayout_3->addWidget(m_limitStep, 2, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_3->addWidget(label_6, 3, 0, 1, 1);

        m_continueHitInterval = new QSpinBox(groupBox_2);
        m_continueHitInterval->setObjectName(QStringLiteral("m_continueHitInterval"));
        m_continueHitInterval->setMinimum(100);
        m_continueHitInterval->setMaximum(20000);
        m_continueHitInterval->setSingleStep(100);
        m_continueHitInterval->setValue(10000);

        gridLayout_3->addWidget(m_continueHitInterval, 3, 1, 1, 1);


        horizontalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(SettingDialog);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        m_playBGMOnStartup = new QCheckBox(groupBox_3);
        m_playBGMOnStartup->setObjectName(QStringLiteral("m_playBGMOnStartup"));

        gridLayout_2->addWidget(m_playBGMOnStartup, 2, 0, 1, 1);

        m_notMusicWhenHitFail = new QCheckBox(groupBox_3);
        m_notMusicWhenHitFail->setObjectName(QStringLiteral("m_notMusicWhenHitFail"));

        gridLayout_2->addWidget(m_notMusicWhenHitFail, 0, 0, 1, 1);

        m_mute = new QCheckBox(groupBox_3);
        m_mute->setObjectName(QStringLiteral("m_mute"));

        gridLayout_2->addWidget(m_mute, 1, 0, 1, 1);

        m_noInformationWhenStop = new QCheckBox(groupBox_3);
        m_noInformationWhenStop->setObjectName(QStringLiteral("m_noInformationWhenStop"));

        gridLayout_2->addWidget(m_noInformationWhenStop, 3, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_5 = new QLabel(SettingDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        buttonBox = new QDialogButtonBox(SettingDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(SettingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QApplication::translate("SettingDialog", "\346\270\270\346\210\217\346\216\247\345\210\266\351\235\242\346\235\277", 0));
        groupBox->setTitle(QApplication::translate("SettingDialog", "\346\270\270\346\210\217\350\247\204\346\250\241", 0));
        label_2->setText(QApplication::translate("SettingDialog", "\350\241\214", 0));
        label_3->setText(QApplication::translate("SettingDialog", "\345\210\227", 0));
        label_4->setText(QApplication::translate("SettingDialog", "\346\270\270\346\210\217\346\227\266\351\227\264:", 0));
        m_gameTime->setSuffix(QApplication::translate("SettingDialog", "\347\247\222", 0));
        label_7->setText(QApplication::translate("SettingDialog", "\345\233\276\346\240\207\347\247\215\346\225\260", 0));
        label_8->setText(QApplication::translate("SettingDialog", "\345\274\200\345\234\272\345\212\250\347\224\273", 0));
        checkBox->setText(QApplication::translate("SettingDialog", "\351\232\217\346\234\272", 0));
        groupBox_2->setTitle(QApplication::translate("SettingDialog", "\345\212\237\350\203\275\350\256\276\347\275\256", 0));
        m_continueHitNoTimeLimit->setText(QApplication::translate("SettingDialog", "\350\277\236\345\207\273\346\227\240\346\227\266\351\225\277\351\231\220\345\210\266", 0));
#ifndef QT_NO_TOOLTIP
        m_continueHit->setToolTip(QApplication::translate("SettingDialog", "\345\205\201\350\256\270\346\214\201\347\273\255\350\277\236\345\207\273", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        m_continueHit->setStatusTip(QApplication::translate("SettingDialog", "\345\205\201\350\256\270\346\214\201\347\273\255\350\277\236\345\207\273", 0));
#endif // QT_NO_STATUSTIP
        m_continueHit->setText(QApplication::translate("SettingDialog", "\345\205\201\350\256\270\346\214\201\347\273\255\350\277\236\345\207\273", 0));
        label->setText(QApplication::translate("SettingDialog", "\346\234\200\345\244\232\347\233\264\347\272\277", 0));
        m_limitStep->setSuffix(QApplication::translate("SettingDialog", "\346\235\241", 0));
        label_6->setText(QApplication::translate("SettingDialog", "\350\277\236\345\207\273\351\227\264\351\232\224\346\227\266\351\227\264", 0));
        m_continueHitInterval->setSuffix(QApplication::translate("SettingDialog", "\346\257\253\347\247\222", 0));
        groupBox_3->setTitle(QApplication::translate("SettingDialog", "\345\205\266\344\273\226\350\256\276\347\275\256", 0));
        m_playBGMOnStartup->setText(QApplication::translate("SettingDialog", "\347\250\213\345\272\217\345\220\257\345\212\250\346\227\266\346\222\255\346\224\276\350\203\214\346\231\257\351\237\263\344\271\220", 0));
        m_notMusicWhenHitFail->setText(QApplication::translate("SettingDialog", "\350\277\236\345\207\273\345\244\261\350\264\245\346\227\266\344\270\215\345\217\221\345\207\272\345\243\260\351\237\263", 0));
        m_mute->setText(QApplication::translate("SettingDialog", "\351\235\231\351\237\263", 0));
        m_noInformationWhenStop->setText(QApplication::translate("SettingDialog", "\346\270\270\346\210\217\347\273\223\346\235\237\346\227\266\344\270\215\346\217\220\347\244\272", 0));
        label_5->setText(QApplication::translate("SettingDialog", "\345\217\213\346\203\205\346\217\220\347\244\272:\350\256\276\347\275\256\345\256\214\344\271\213\345\220\216\350\246\201\351\207\215\346\226\260\345\274\200\345\247\213\346\270\270\346\210\217\346\211\215\344\274\232\347\224\237\346\225\210\345\223\246.", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
