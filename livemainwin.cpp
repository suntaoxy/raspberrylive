#include "livemainwin.h"
#include "makeshell.h"
#include<QFile>
#include<QFileDialog>
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

   addsrt = new QAction(QIcon("addsrt.png"),tr("添加字幕"),this);
   addsrt->setStatusTip(tr("可添加UTF-8编码的srt字幕"));
   connect(addsrt,SIGNAL(triggered(bool)),this,SLOT(choose_srt()));


}

void Livemainwin::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("进度"));
    fileMenu->addAction(displayjindu);
    fileMenu->addAction(displaynow_tvnum);

    subtitleMenu = menuBar()->addMenu(tr("字幕"));
    subtitleMenu->addAction(addsrt);

    aboutMenu = menuBar()->addMenu(tr("关于"));
    aboutMenu->addAction(disallinfo);

}

void Livemainwin::createToolBar()
{
    jinduToolBar = addToolBar("jindu");
    jinduToolBar->addAction(displayjindu);
    jinduToolBar->addAction(disallinfo);
}


void Livemainwin::choose_srt()
{
    QString path_of_srt =QFileDialog::getOpenFileName(this,tr("选择字幕文件"),"/");
    excutool->path_srt=path_of_srt;
}



Livemainwin::~Livemainwin()
{

}


