#ifndef CESHI_H
#define CESHI_H

#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QProcess>

class Ceshi : public QWidget
{
    Q_OBJECT

public:
    Ceshi(QWidget *parent = 0);
    QString path_srt;
    ~Ceshi();
  //  QString get_path();
private:
    QLabel* websitelabel;
    QLabel* streamlabel;
    QLineEdit* websitetext;
    QLineEdit* streamtext;
    QPushButton* okbtn;
    QPushButton* closebtn;
    QPushButton* choosepath;
    QLineEdit* pathname;
    QProcess* process_0;
  //  QDir* dir;

private slots:
    void mkandexcute_shell();
//    void closed_shell();
    void showfile();

};

#endif // CESHI_H
