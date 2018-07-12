#include "livemainwin.h"
#include "makeshell.h"
#include<QFile>
#include<QFileDialog>
#include<QMessageBox>
#include<memory>

Livemainwin::Livemainwin(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("树莓派直播工具"));
    setGeometry(500,100,400,200);
    excutool =new Ceshi(this);
    movie_excutool=new Moviemod(this);
    setCentralWidget(movie_excutool);
    setWindowIcon(QIcon(":icon/icon/live.png"));

    createAction();
    createMenu();
    createToolBar();

}


void Livemainwin::createAction()
{
   displayjindu = new QAction(QIcon("jindu.png"),tr("显示进度"),this);
   displayjindu->setShortcut(tr("Ctrl+I"));
   displayjindu->setStatusTip(tr("显示播放进度"));

   displaynow_tvnum = new QAction(QIcon("png1.png"),tr("显示集数"),this);

   turn_movie_mod = new QAction(QIcon(":/icon/icon/film.png"),tr("电影模式"),this);
   turn_movie_mod->setStatusTip(tr("播放单个电影文件"));
   connect(turn_movie_mod,SIGNAL(triggered(bool)),this,SLOT(turnmovie()));

   turn_tv_mod = new QAction(QIcon(":/icon/icon/tv.png"),tr("电视剧模式"),this);
   turn_movie_mod->setStatusTip(tr("播放多集电视剧"));
   connect(turn_tv_mod,SIGNAL(triggered(bool)),this,SLOT(turntv()));

   about_author = new QAction(tr("关于作者"),this);
   about_author->setStatusTip(tr("关于作者"));
   connect(about_author,SIGNAL(triggered(bool)),this,SLOT(showauthor()));

   download_srt = new QAction(QIcon(":/icon/icon/down.png"),tr("下载字幕"),this);
   download_srt->setStatusTip(tr("下载匹配的字幕文件"));
   connect(download_srt,SIGNAL(triggered(bool)),movie_excutool,SLOT(downsrt()));

}

void Livemainwin::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("进度"));
    fileMenu->addAction(displayjindu);
    fileMenu->addAction(displaynow_tvnum);

    subtitleMenu = menuBar()->addMenu(tr("字幕模式"));
    subtitleMenu->addAction(turn_movie_mod);
    subtitleMenu->addAction(turn_tv_mod);
    subtitleMenu->addAction(download_srt);

    aboutMenu = menuBar()->addMenu(tr("关于"));
    aboutMenu->addAction(about_author);

}

void Livemainwin::createToolBar()
{
    jinduToolBar = addToolBar("mod");
    jinduToolBar->addAction(turn_movie_mod);
    jinduToolBar->addAction(turn_tv_mod);

    srtToolBar = addToolBar("zimu");
    srtToolBar->addAction(download_srt);
}

void Livemainwin::turnmovie()
{
   // movie_excutool =new Moviemod(this);
    centralWidget()->setParent(0);
    setCentralWidget(movie_excutool);

}

void Livemainwin::turntv()
{
 //   excutool =new Ceshi(this);
    centralWidget()->setParent(0);
    setCentralWidget(excutool);

}

void Livemainwin::showauthor()
{
    QMessageBox::about(this,tr("作者"),tr("美国的华莱士"));
    return;
}



Livemainwin::~Livemainwin()
{

}


