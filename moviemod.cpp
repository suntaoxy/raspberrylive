#include "moviemod.h"
#include <QLayout>
#include <QDir>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include "makeshell.h"
#include<QApplication>
Moviemod::Moviemod(QWidget *parent) : QWidget(parent)
{
    websitelabel=new QLabel(tr("网址"));
    websitetext=new QLineEdit("rtmp://js.live-send.acg.tv/live-js/");
    streamlabel=new QLabel(tr("推流码"));
    streamtext=new QLineEdit("?streamname=live_956714_5294207&key=a47f28b34b8809026e8e93e75adca602");
    okbtn=new QPushButton;
    okbtn->setText(tr("开始直播"));
    closebtn=new QPushButton;
    closebtn->setText(tr("停止直播"));
    choosemoive=new QPushButton;
    choosemoive->setText(tr("选择电影"));
    moviename=new QLineEdit;
    choosesrt=new QPushButton;
    choosesrt->setText(tr("选择字幕"));
    srt_name=new QLineEdit;

 //   fswatcher = new QFileSystemWatcher(this);


    QGridLayout* mainlayout=new QGridLayout(this);
    QHBoxLayout* btnlayout=new QHBoxLayout;
    btnlayout->addStretch(1);
    btnlayout->addWidget(okbtn);
    btnlayout->addWidget(closebtn);
    mainlayout->setMargin(10);
    mainlayout->setSpacing(6);
    mainlayout->addWidget(websitelabel,0,0);
    mainlayout->addWidget(websitetext,0,1);
    mainlayout->addWidget(streamlabel,1,0);
    mainlayout->addWidget(streamtext,1,1);
    mainlayout->addWidget(choosemoive,2,0);
    mainlayout->addWidget(moviename,2,1);
    mainlayout->addWidget(choosesrt,3,0);
    mainlayout->addWidget(srt_name,3,1);
    mainlayout->addLayout(btnlayout,4,0,1,2);
    process_0 = new QProcess(this);
    connect(okbtn,SIGNAL(clicked()),this,SLOT(mkandexcute_shell()));
    connect(choosemoive,SIGNAL(clicked()),this,SLOT(showfile()));
    connect(closebtn,SIGNAL(clicked()),process_0,SLOT(kill()));
    connect(choosesrt,SIGNAL(clicked(bool)),this,SLOT(showsrt()));

    connect(&fswatcher,SIGNAL(directoryChanged(QString)),this,SLOT(setsrt(QString)));


}

void Moviemod::showfile()
{
    QString path_of_video =QFileDialog::getOpenFileName(this,tr("选择电影文件"),"/");
    moviename->setText(path_of_video);
}


void Moviemod::showsrt()
{
    QString path_of_video =QFileDialog::getOpenFileName(this,tr("选择srt字幕文件"),moviename->text());
    srt_name->setText(path_of_video);
}

void Moviemod::mkandexcute_shell()
{
    QString rtmp = websitetext->text()+streamtext->text();
    creat_srt_shell(moviename->text(),rtmp,srt_name->text());
#if defined(Q_OS_WIN32)
    QString pathofshell = QDir::currentPath() + "/raspliveshell.bat" ;
    qDebug() << pathofshell;
    process_0->start("cmd.exe",QStringList() << "/c" << pathofshell);

#elif defined(Q_OS_LINUX)
    QString pathofshell = "sh "+QDir::currentPath() + "/raspliveshell.sh" ;
    qDebug() << pathofshell;
    process_0->start(pathofshell);
#endif


}

void Moviemod::downsrt()
{
    if(moviename->text().isEmpty())
        return;

    QString path_movie=moviename->text();
    QFileInfo mvinfo(path_movie);
    fswatcher.addPath(mvinfo.absolutePath());
    qDebug()<<mvinfo.absolutePath();

#if defined(Q_OS_LINUX)
    QString shell = "python3 "+QApplication::applicationDirPath()+"/getsrt.py "+path_movie;
    process_0->start(shell);
#elif defined(Q_OS_WIN32)
    QString shell = QApplication::applicationDirPath()+"/getsrt.py "+path_movie;
    qDebug()<<shell;
    process_0->start("cmd.exe",QStringList() << "/c" << shell);
#endif

}

void Moviemod::setsrt(QString path)
{
  //  qDebug()<<path;

    QDir mvdir(path);
    QStringList str_list;
    str_list<<"*";
    QFileInfoList filelist=mvdir.entryInfoList(str_list,QDir::Files,QDir::Name);
    foreach(QFileInfo finfo, filelist)
    {
        if(finfo.suffix()=="srt")
        {
            QString shell="ffmpeg -i "+finfo.absoluteFilePath()+" newname.ass";
            #if defined(Q_QS_LINUX)
            process_0->start(shell);
            #elif defined(Q_OS_WIN32)
            qDebug()<<shell;
            process_0->start("cmd.exe",QStringList() << "/c" << shell);
            #endif
            break;
        }

    }
    foreach(QFileInfo finfo, filelist)
    {
        if(finfo.suffix()=="ass"||finfo.suffix()=="srt")
        {
            srt_name->setText(finfo.absoluteFilePath());
            break;
        }
    }
}


Moviemod::~Moviemod()
{

}
