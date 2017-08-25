#ifndef CHANNEL_PARA_H
#define CHANNEL_PARA_H
#include <itpp/itcomm.h>
#include <itpp/itstat.h>
#include<itpp/base/random.h>
#include <itpp/itfixed.h>
#include"net_topo_para.h"
#include<fstream>
//#include"mainwindow.h"
//#include"saloha.h"
#define SHOW_DETAILED 0
using namespace std;
using namespace itpp;
class Channel
{
public:
    Channel();
    void set_value();
    double bit_rate;
    double sym_rate;
    int packet_length;
    double alfa;
    double sigma;
    double tcn;
    double mcn;
    mat shadow;
    double r;
    int spend;
    double delaytime;
    double Ttime;
    long double mpow;
    double Tint;
    double Mnum;
    double Rint;
    double Dtime;
    int Spnum;//成功传输包的个数
    int Splen;//成功传输包的符号数
    int Tplen;//发送的符号数
    double Wtime;//等待时间
    double now_time;
    double next_time;
    double slot;
    int flag1;
    int flag2;
    int flag3;
    vec mgtime;
    vec mtime;
    vec Mstate;
    vec Mplen;
    int STANDBY;
    int TRANSMIT;
    int COLLISION;
    vector<int> find_idx;
    vector<int> find_idx_2;
    vector<double> power_;
    int idx;
    struct AP
    {
        int x;
        int y;
        int z;
    };
    AP bxy;
    void start_loop(Topo *to_topo);
    double slot_aloha(double now_time);
    Random_Generator random_seeds;
    double distance_of(int x,int y,int z);
    Topo *to_topo;
    vec traffic_curve;
    vec ts_curve;
    vec S;
    vec W;
    double theorys(double traffic,double Dtime);



};

#endif // CHANNEL_PARA_H
