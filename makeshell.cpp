#include "makeshell.h"
#include<QFile>
#include<QFileDialog>
#include<QTextStream>
#include<QtDebug>
#include<QDir>
#include<ceshi.h>

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

void creat_srt_shell(QString pwd,QString rtmp,QString path_srt)
{
    QStringList str_list;
    str_list<<"*";
    QDir diry(pwd);
    QFileInfoList filelist=diry.entryInfoList(str_list,QDir::Files,QDir::Name);
    QFile file("raspliveshell.sh");
    if(file.open(QIODevice::ReadWrite|QIODevice::Truncate))
    {
        QString ffmpeg_order_fore =" ffmpeg -re -i ";
        QString ffmpeg_order_mid ="-vf subtitles="+path_srt+" -acodec aac -b:a 128k -f flv ";
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


