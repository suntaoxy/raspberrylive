#ifndef MOVIEMOD_H
#define MOVIEMOD_H
#include <QWidget>
#include <QMainWindow>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QProcess>


class Moviemod : public QWidget
{
    Q_OBJECT
public:
    explicit Moviemod(QWidget *parent = nullptr);
    ~Moviemod();
    QString path_srt;
private:
    QLabel* websitelabel;
    QLabel* streamlabel;
    QLineEdit* websitetext;
    QLineEdit* streamtext;
    QPushButton* okbtn;
    QPushButton* closebtn;
    QPushButton* choosemoive;
    QLineEdit* moviename;
    QPushButton* choosesrt;
    QLineEdit* srt_name;

    QProcess* process_0;


signals:

public slots:

    void mkandexcute_shell();
    void showfile();
    void showsrt();
};

#endif // MOVIEMOD_H
