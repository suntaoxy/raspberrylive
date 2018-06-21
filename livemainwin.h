#ifndef LIVEMAINWIN_H
#define LIVEMAINWIN_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QToolButton>
#include "ceshi.h"

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
    QMenu* fileMenu;
    QMenu* aboutMenu;
    QMenu* subtitleMenu;
//    QMenu* test1;
//    QMenu* test2;
    QAction* displayjindu;
    QAction* displaynow_tvnum;
    QAction* disallinfo;
    QAction* addsrt;
    QToolBar* jinduToolBar;
    QToolButton* startlive;


signals:

public slots:
    void choose_srt();
};

#endif // LIVEMAINWIN_H
