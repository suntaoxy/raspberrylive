#include "makeshell.h"
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QtDebug>
#include<QDir>


void creat_shell(QString pwd,QString rtmp)
{
    QStringList str_list;
    str_list<<"*";
    QDir diry(pwd);
    QFileInfoList filelist=diry.entryInfoList(str_list,QDir::Files,QDir::Name);
    QFile file("raspliveshell.sh");
    if(file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        QString ffmpeg_order_fore =" ffmpeg -re -i ";
        QString ffmpeg_order_mid =" -vcodec copy -acodec aac -b:a 128k -f flv ";
        QTextStream writeinshell(&file);
        writeinshell<<"#!/bin/bash"<<left<<endl;
        writeinshell<<"while true"<<left<<endl;
        writeinshell<<"do"<<left<<endl;
        foreach (QFileInfo finfo, filelist)
        {
            if(finfo.suffix()=="mp4"||finfo.suffix()=="mkv")
            {
                writeinshell<<ffmpeg_order_fore + "\"" + finfo.filePath()+"\"" +ffmpeg_order_mid
                +" \"" + rtmp +"\" "<<left<<endl;
            }


        }
        writeinshell<<"done"<<left<<endl;



    }
}

void creat_srt_shell(QString path_movie,QString rtmp,QString path_srt)
{

    QFileInfo filemovie=QFileInfo(path_movie);  //文件信息类
    QFileInfo filesrt=QFileInfo(path_srt);
#if defined(Q_OS_WIN32)
    QFile file("raspliveshell.bat");
#elif defined(Q_OS_LINUX)
    QFile file("raspliveshell.sh");
#endif
    if(file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
     #if defined(Q_OS_WIN32)
        QString ffmpeg_order_fore =" ffmpeg -re -i ";
        QString ffmpeg_order_mid;
        if(filesrt.suffix()=="ass")
        {
            ffmpeg_order_mid =" -vf \"ass="+filesrt.fileName()+"\" -vcodec h264 -acodec aac -b:a 128k -f flv ";
        }
        else
        {
            ffmpeg_order_mid =" -vf subtitles="+filesrt.fileName()+" -vcodec h264 -acodec aac -b:a 128k -f flv ";
        }

        QTextStream writeinshell(&file);
        writeinshell<<"cd /d "+ filemovie.absolutePath()+"\r\n"<<left;
        writeinshell<<ffmpeg_order_fore + "\"" +filemovie.fileName()+"\"" +ffmpeg_order_mid+" \"" + rtmp +"\" \r\n"<<left;
        writeinshell<<"pause"<<left<<endl;
     #elif defined(Q_OS_LINUX)
        QString ffmpeg_order_fore =" ffmpeg -re -i ";
        QString ffmpeg_order_mid;
        if(filesrt.suffix()=="ass")
        {
            ffmpeg_order_mid =" -vf \"ass="+filesrt.fileName()+"\" -vcodec h264 -acodec aac -b:a 128k -f flv ";
        }
        else
        {
            ffmpeg_order_mid =" -vf subtitles="+filesrt.fileName()+" -vcodec h264 -acodec aac -b:a 128k -f flv ";
        }

        QTextStream writeinshell(&file);
        writeinshell<<"#!/bin/bash"<<left<<endl;
        writeinshell<<"while true"<<left<<endl;
        writeinshell<<"do"<<left<<endl;
        writeinshell<<"cd "+ filemovie.absolutePath()<<left<<endl;
        writeinshell<<ffmpeg_order_fore + "\"" +filemovie.fileName()+"\"" +ffmpeg_order_mid+" \"" + rtmp +"\" "<<left<<endl;
        writeinshell<<"done"<<left<<endl;
     #endif

    }

}


