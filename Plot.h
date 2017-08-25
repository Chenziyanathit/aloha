#ifndef PLOT_H
#define PLOT_H
#include <itpp/itcomm.h>
#include <itpp/itstat.h>
using namespace std;
using namespace itpp;
#include "qwt_plot_curve.h"
#include"qwt_plot_grid.h"
#include "ui_mainwindow.h"
#include<QWidget>
#include<QPainter>
#include<QApplication>
//#include<qwt_legend.h>
#include<qwt_legend_item.h>
#include<qwt_symbol.h>
class Plot
{
public:
    Plot(Ui_MainWindow *ui);
    void Plot_data(vec g,vec s,vec ts);
    void Plot_data2(vec g,vec w);
private:
    Ui_MainWindow *gui;
    QwtPlotCurve curve;
    QwtPlotCurve curve1;
    QwtPlotCurve curve2;
    QwtPlotGrid grid;
   // QBrush brush;
  //  QwtSymbol symbol;

};

#endif // PLOT_H
