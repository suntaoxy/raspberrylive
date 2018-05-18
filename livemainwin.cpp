#include "livemainwin.h"

Livemainwin::Livemainwin(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("树莓派直播工具"));
    setGeometry(500,100,400,200);
    excutool =new Ceshi(this);
    setCentralWidget(excutool);
    startlive = new QToolButton;
    startlive->setIcon(QIcon("pig.png"));



    createAction();
     createMenu();
    createToolBar();

}


void Livemainwin::createAction()
{
   displayjindu = new QAction(QIcon("jindu.png"),tr("显示进度"),this);
   displayjindu->setShortcut(tr("Ctrl+I"));
   displayjindu->setStatusTip(tr("显示总播放进度"));

   displaynow_tvnum = new QAction(QIcon("png1.png"),tr("显示集数"),this);
   disallinfo = new QAction(QIcon("png2.png"),tr("其他信息"),this);


}

void Livemainwin::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("进度"));
    fileMenu->addAction(displayjindu);
    fileMenu->addAction(displaynow_tvnum);
    about = menuBar()->addMenu(tr("关于"));
    about->addAction(displayjindu);
    about->addAction(disallinfo);


}

void Livemainwin::createToolBar()
{
    jinduToolBar = addToolBar("jindu");
    jinduToolBar->addAction(displayjindu);
    jinduToolBar->addAction(disallinfo);
}
Livemainwin::~Livemainwin()
{

}


