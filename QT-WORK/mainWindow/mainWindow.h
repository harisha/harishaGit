#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainWindow.h"

class mainWindow : public QMainWindow, public Ui::mainWindowDlg
{
Q_OBJECT
    public:
        mainWindow( QWidget * parent = 0, Qt::WFlags f = 0 );
    public slots:
        void addClicked();
};
#endif
