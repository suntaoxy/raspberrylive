#ifndef LIVEMAINWIN_H
#define LIVEMAINWIN_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QToolButton>
#include "ceshi.h"
#include "moviemod.h"

class Livemainwin : public QMainWindow
{
    Q_OBJECT
public:
     Livemainwin(QWidget *parent = 0);
    ~Livemainwin();
    void createAction();
    void createMenu();
    void createToolBar();

private:
    Ceshi* excutool;
    Moviemod* movie_excutool;

    QMenu* fileMenu;
    QMenu* aboutMenu;
    QMenu* subtitleMenu;
//    QMenu* test1;
//    QMenu* test2;
    QAction* displayjindu;
    QAction* displaynow_tvnum;
    QAction* disallinfo;
    QAction* turn_movie_mod;
    QAction* turn_tv_mod;
    QAction* about_author;
    QAction* download_srt;
    QToolBar* jinduToolBar;
    QToolBar* srtToolBar;


signals:

public slots:
    void turntv();
    void turnmovie();
    void showauthor();

};

#endif // LIVEMAINWIN_H
