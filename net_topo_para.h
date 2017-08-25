#ifndef NET_TOPO_PARA_H
#define NET_TOPO_PARA_H
#include <itpp/itcomm.h>
#include <itpp/itstat.h>
#include <itpp/itbase.h>
#include <itpp/itfixed.h>
#include<itpp/base/random.h>
#include<fstream>

//extern struct pos_xyz

//extern struct pos_xyz new_posxyz[100];
using namespace std;
using namespace itpp;
class Topo
{
public:
    double r;
    double x;
    double y;
    double z;
    double tcn;
    int Mnum;
    int mcn;
    //Mat poxsy;
    Topo();
    void Position(double r,double n,double h);
    Random_Generator random_seeds;
    struct pos_xyz
    {
        int number;
        int x;
        int y;
        int z;
        double distance;
        double power_;
    };
    struct pos_xyz *new_posxyz;


};


#endif // NET_TOP_PARA_H
