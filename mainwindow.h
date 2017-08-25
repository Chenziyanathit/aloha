#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<iostream>
#include <itpp/itcomm.h>
#include <itpp/itstat.h>
#include"net_topo_para.h"
#include"channel_para.h"
#include"Plot.h"
//#include"position.h"
//#include"saloha.h"

#include<fstream>
using namespace std;
using namespace itpp;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
     //SAloha *saloha;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Topo *topo;
    Channel *channel;
    Plot *plot;


};

#endif // MAINWINDOW_H
