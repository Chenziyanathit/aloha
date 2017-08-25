#include"net_topo_para.h"

Topo::Topo()
{
   // struct pos_xyz new_posxyz[100]={0,0,0,0};
}
void Topo::Position(double r, double n, double h)
{
    double ms;
    char filename[]="topo_file";
    //ms=4*r;
   // struct pos_xyz new_posxyz[100];
    new_posxyz=new struct pos_xyz[int(n)];
    for(int i=0;i<100;i++)
    {
        new_posxyz[i].number=-1;
        new_posxyz[i].x=-1;
        new_posxyz[i].y=-1;
        new_posxyz[i].z=-1;
        new_posxyz[i].distance=0;
        new_posxyz[i].power_=0;

    }
    vec ms_out1;
    ms_out1.set_size(r-1);

    for(int i=1;i<r;i++)
    {
        double temp;
        temp=sqrt(pow(r,2)-pow(i,2));
        Fix(temp,0);
        ms_out1.set(i-1,temp);
       // ms_out1.push_back(temp);

       // cout<<ms_out1<<" ";
    }
//    cout<<endl;
 //   cout<<ms_out1<<endl;

    ms_out1=floor(ms_out1);
 //   cout<<ms_out1<<endl;
    ms=4*r+4*sum(ms_out1);
 //   cout<<ms<<endl;
    mat posxy(n,3);
    //posxy.set_size(n,3,false);
    posxy.zeros();
    //cout<<posxy<<endl;

    //cout<<xx<<endl;
     bool map_pos[100][100]={false};
    /*
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<map_pos[i][j]<<" ";
        }
        cout<<endl;
    }
    */

    int sum_in=0;
   // new_posxyz=new struct pos_xyz[int(n)];
    ofstream fout(filename);
    while(sum_in<n)
    {

            int xx_int;
            int yy_int;
            int zz_int;
           double xx=random_seeds.random_01();
           xx=int(r*xx)*sign(sin(2*pi*random_seeds.random_01()));
         //  cout<<xx<<" ";
           double yy=random_seeds.random_01();
           yy=int(r*yy)*sign(cos(2*pi*random_seeds.random_01()));
           double zz=random_seeds.random_01();
           zz=int(r*zz)*sign(cos(2*pi*random_seeds.random_01()));
         //  cout<<yy<<" "<<endl;
           xx_int=xx;
           yy_int=yy;
           zz_int=zz;
           if((xx*xx+yy*yy+zz*zz)<=r*r&&(xx!=0||yy!=0||zz!=0)&&map_pos[xx_int][yy_int]==false)
            {
              map_pos[xx_int][yy_int]=true;
              new_posxyz[sum_in].number=sum_in;
              new_posxyz[sum_in].x=xx_int;
              new_posxyz[sum_in].y=yy_int;
              new_posxyz[sum_in].z=zz_int;
              //fout<<"the number is: "<<sum_in<<",x="<<xx_int<<",y="<<yy_int<<",z="<<0<<endl;
              fout<<sum_in<<","<<xx_int<<","<<yy_int<<","<<zz_int<<endl;
             // fout.close();
              sum_in++;
            }

    }
    fout.close();
    //cout<<sum_in<<endl;
/*
    for(int i=0;i<n;i++)
    {

        cout<<new_posxyz[i].x<<" "<<new_posxyz[i].y<<endl;


    }
*/

}
