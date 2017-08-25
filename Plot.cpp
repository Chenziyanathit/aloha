#include"Plot.h"
Plot::Plot(Ui_MainWindow *ui)
{
    gui=ui;
    curve.attach(gui->qwtPlot);
    curve1.attach(gui->qwtPlot);
    curve2.attach(gui->qwtPlot_2);
    //brush.setColor(Qt::GlobalColor(QColor::yellow()));
 //   legend.setItemMode(QwtLegendItem::checked(true));

    gui->qwtPlot->setTitle("Throughput of Slotted ALOHA system");
    gui->qwtPlot->setAxisTitle(QwtPlot::yLeft, "Throughput       (normalization)");
    gui->qwtPlot->setAxisTitle(QwtPlot::xBottom,"Traffic(Simulation result)       (normalization)");

    gui->qwtPlot->setAxisScale(QwtPlot::yLeft,0,0.5,0);
    gui->qwtPlot->setAxisScale(QwtPlot::xBottom,0,2,0);
    gui->qwtPlot_2->setTitle("Average Delay time of Slotted ALOHA system");
    gui->qwtPlot_2->setAxisTitle(QwtPlot::yLeft, "Average Delay time(packet)");
    gui->qwtPlot_2->setAxisTitle(QwtPlot::xBottom,"Traffic(Simulation result)       (normalization)");
  //  brush.setColor(QColor(Qt::green));
   // brush.setStyle(Qt::BrushStyle);
   // brush.setStyle();
 //   gui->qwtPlot->insertLegend(legend,QwtPlot::RightLegend,-1.0);
   // grid.attach(gui->qwtPlot);
   // grid.enableY(true);
   // grid.enableX(true);
    //grid.setMajPen(QPen(QColor(Qt::red)));





  //  grid.setMajPen(QPen(QColor(Qt::red)));

    gui->qwtPlot->replot();
    gui->qwtPlot_2->replot();

}
void Plot::Plot_data(vec g, vec s,vec ts)
{
    double x[g.size()];
    double y[g.size()];
    double y1[g.size()];
    for(int i=0;i<g.size();i++)
    {
        x[i]=g(i);
        y[i]=s(i);
        y1[i]=ts(i);
    }

    curve.setData(x,y,g.size());
    curve1.setData(x,y1,g.size());
    curve.setStyle(QwtPlotCurve::NoCurve);
    curve.setSymbol(QwtSymbol(QwtSymbol::XCross,QBrush(),QPen(Qt::red),QSize(10,10)));
    //curve.setPaintAttribute(QwtPlotCurve::);
    //curve.setPen(QPen(QBrush));

    curve1.setPen(QPen(QColor(Qt::blue)));
   // curve1.setPen(QPen());
    curve1.setStyle(QwtPlotCurve::Lines);
  //  curve1.setPen(QPen(QBrush(brush),0.6,Qt::PenStyle(Qt::SolidLine),Qt::PenCapStyle(Qt::SquareCap),Qt::PenJoinStyle(Qt::BevelJoin)));
   // curve1.setPen(Qpen)

    gui->qwtPlot->replot();
}
void Plot::Plot_data2(vec g, vec w)
{

    double x[g.size()];
    double y[g.size()];
    for(int i=0;i<g.size();i++)
    {
        x[i]=g(i);
        y[i]=w(i);
    }
    curve2.setData(x,y,g.size());
    //curve2.setPen();
    //curve2.setPen(QPen(Qt::PenStyle(QwtPlotCurve::Dots)));
    //curve2.setStyle(QwtPlotCurve::NoCurve);
   // curve2.setSymbol(QwtSymbol(QwtSymbol::XCross,QBrush(QColor(Qt::blue),Qt::BrushStyle(Qt::SolidLine)),QPen(Qt::red),QSize(10,10)));
    gui->qwtPlot_2->replot();

}
