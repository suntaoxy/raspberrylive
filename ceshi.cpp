#include "ceshi.h"
#include <QLayout>
#include <QDir>
#include <QProcess>
#include <QDebug>
#include "makeshell.h"

Ceshi::Ceshi(QWidget *parent)
    : QWidget(parent)
{
  // setWindowTitle(tr("raspberry-livetool"));
  // setGeometry(500,100,400,200);
    websitelabel=new QLabel(tr("网址"));
    websitetext=new QLineEdit("rtmp://js.live-send.acg.tv/live-js/");
    streamlabel=new QLabel(tr("推流码"));
    streamtext=new QLineEdit("?streamname=live_956714_5294207&key=a47f28b34b8809026e8e93e75adca602");
    okbtn=new QPushButton;
    okbtn->setText(tr("开始直播"));
    closebtn=new QPushButton;
    closebtn->setText(tr("停止直播"));
    choosepath=new QPushButton;
    choosepath->setText(tr("选择路径"));
    pathname=new QLineEdit;


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
    mainlayout->addWidget(choosepath,2,0);
    mainlayout->addWidget(pathname,2,1);
    mainlayout->addLayout(btnlayout,3,0,1,2);
    process_0 = new QProcess(this);
    connect(okbtn,SIGNAL(clicked()),this,SLOT(mkandexcute_shell()));
    connect(choosepath,SIGNAL(clicked()),this,SLOT(showfile()));
    connect(closebtn,SIGNAL(clicked()),process_0,SLOT(kill()));


}

void Ceshi::mkandexcute_shell()
{
    QString rtmp = websitetext->text()+streamtext->text();

    creat_shell(pathname->text(),rtmp);

    QString pathofshell = "sh " + QDir::currentPath() + "/raspliveshell.sh" ;

   // qDebug() << pathofshell;
    process_0->start(pathofshell);
}
void Ceshi::showfile()
{
    QString path_of_video =QFileDialog::getExistingDirectory(this,tr("选择视频文件所在目录"),"/");
    pathname->setText(path_of_video);
}
/*void Ceshi::closed_shell()
{
    process_0->kill();
    delete process_0;
}
*/




Ceshi::~Ceshi()
{

}
