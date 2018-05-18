#include "livemainwin.h"

Livemainwin::Livemainwin(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("树莓派直播工具"));
    setGeometry(500,100,400,200);
    excutool =new Ceshi(this);
    setCentralWidget(excutool);
    createMenu();
    createAction();
    createToolBar();

}


void Livemainwin::createAction()
{
   displayjindu = new QAction(QIcon("jindu.png"),tr("显示进度"),this);
   displayjindu->setShortcut(tr("Ctrl+I"));
   displayjindu->setStatusTip(tr("显示总播放进度"));
}

void Livemainwin::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("进度"));
    fileMenu->addAction(displayjindu);


}

void Livemainwin::createToolBar()
{
    jinduToolBar = addToolBar("jindu");
    jinduToolBar->addAction(displayjindu);
}


