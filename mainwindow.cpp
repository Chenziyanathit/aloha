#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    plot=new Plot(ui);
    channel=new Channel();
    channel->set_value();
      topo=new Topo(); 
      topo->Position(100,100,0);    
      channel->start_loop(topo);
     plot->Plot_data(channel->traffic_curve,channel->S,channel->ts_curve);
     plot->Plot_data2(channel->traffic_curve,channel->W);



}

MainWindow::~MainWindow()
{
    delete ui;
    delete plot;
    delete channel;
    delete topo;
}
