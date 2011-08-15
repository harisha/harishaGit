#include "mainWindow.h"

mainWindow::mainWindow( QWidget * parent, Qt::WFlags f) : QMainWindow(parent, f)
{
    setupUi(this);
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(addClicked()));
}

void mainWindow::addClicked()
{

    if(edText->text() == "")    // If there is no text then exit this function
    {
        return;
    }
    lbMyList->addItem(edText->text()); // Add the text typed to the list
    edText->setText("");    // erase the text from the box they typed in
    edText->setFocus();    // set the focus back to the LineEdit from the button
}


