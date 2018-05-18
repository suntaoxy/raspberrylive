#ifndef LIVEMAINWIN_H
#define LIVEMAINWIN_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include "ceshi.h"

class Livemainwin : public QMainWindow
{
    Q_OBJECT
public:
    explicit Livemainwin(QWidget *parent = 0);
    void createAction();
    void createMenu();
    void createToolBar();

private:
    Ceshi* excutool;
    QMenu* fileMenu;
//    QMenu* about;
//    QMenu* test1;
//    QMenu* test2;
    QAction* displayjindu;
//    QAction* displaynow_tvnum;
//    QAction* disallinfo;
    QToolBar* jinduToolBar;


signals:

public slots:
};

#endif // LIVEMAINWIN_H
