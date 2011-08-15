/********************************************************************************
** Form generated from reading UI file 'myVlcPlayer.ui'
**
** Created: Mon Aug 15 15:22:40 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYVLCPLAYER_H
#define UI_MYVLCPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_myVlcPlayerDlg
{
public:
    QPushButton *btnStart;
    QPushButton *btnStop;
    QSlider *sliderVol;

    void setupUi(QWidget *myVlcPlayerDlg)
    {
        if (myVlcPlayerDlg->objectName().isEmpty())
            myVlcPlayerDlg->setObjectName(QString::fromUtf8("myVlcPlayerDlg"));
        myVlcPlayerDlg->resize(690, 407);
        btnStart = new QPushButton(myVlcPlayerDlg);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(70, 160, 92, 27));
        btnStop = new QPushButton(myVlcPlayerDlg);
        btnStop->setObjectName(QString::fromUtf8("btnStop"));
        btnStop->setGeometry(QRect(70, 240, 92, 27));
        sliderVol = new QSlider(myVlcPlayerDlg);
        sliderVol->setObjectName(QString::fromUtf8("sliderVol"));
        sliderVol->setGeometry(QRect(70, 320, 160, 19));
        sliderVol->setMaximum(200);
        sliderVol->setOrientation(Qt::Horizontal);

        retranslateUi(myVlcPlayerDlg);

        QMetaObject::connectSlotsByName(myVlcPlayerDlg);
    } // setupUi

    void retranslateUi(QWidget *myVlcPlayerDlg)
    {
        myVlcPlayerDlg->setWindowTitle(QApplication::translate("myVlcPlayerDlg", "Form", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("myVlcPlayerDlg", "Start-Audio", 0, QApplication::UnicodeUTF8));
        btnStop->setText(QApplication::translate("myVlcPlayerDlg", "Stop-Audio", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class myVlcPlayerDlg: public Ui_myVlcPlayerDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYVLCPLAYER_H
