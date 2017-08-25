#include"channel_para.h"
Channel::Channel()
{

}
void Channel::set_value()
{
    Dtime=0.3;
    bit_rate=512e3;
    sym_rate=256e3;
    packet_length=128;
    alfa=3;
    sigma=6;
    r=100;
    shadow=randn(1,100);
    char filename[]="shadow";
    ofstream fout(filename);
    fout<<shadow<<endl;
    fout.close();
    tcn=10;
    mcn=30;
    spend=10000;
    delaytime=0.3;
    Ttime=packet_length/sym_rate;
    bxy.x=0;
    bxy.y=0;
    bxy.z=5;
    Mnum=100;
    mpow=pow(10,(mcn/10))*pow(sqrt(r*r+bxy.z*bxy.z),alfa);
    STANDBY=0;
    TRANSMIT=1;
    COLLISION=2;

}

void Channel::start_loop(Topo *to_topo)
{
    double g=0.1;
    traffic_curve.set_size(20);
    traffic_curve.zeros();
    ts_curve.set_size(20);
    ts_curve.zeros();
    S.set_size(20);
    S.zeros();
    W.set_size(20);
    W.zeros();
    int now_number=0;
    for(g=0.1;g<2.1;g=g+0.1)
    {
        Tint=-Ttime/log(1-g/Mnum);
        Rint=Tint;
        Splen=0;
        Spnum=0;
        Tplen=0;
        Wtime=0;
        now_time=slot_aloha(-1);
        int max_power_index=-1;
        double max_power=0;
        double cn=0;
#if SHOW_DETAILED==1
        cout<<"now_time="<<now_time<<endl;
#endif
        int num_of_run=0;
        int collision=0;
        flag1=0;
        flag2=0;
        flag3=0;
        next_time=0;

       while(1)
        {
           next_time=slot_aloha(now_time);
           num_of_run++;
#if SHOW_DETAILED==1
            //运行次数
            cout<<"运行次数:"<<num_of_run<<endl;

            cout<<"传输成功包个数:Spnum="<<Spnum<<endl;
            cout<<"现在时刻:Now time="<<now_time<<endl;
#endif
            if(Spnum>=spend)
              break;
            find_idx_2.clear();
            for(int i=0;i<Mnum;i++)
            {
                if(Mstate(i)==TRANSMIT||Mstate(i)==COLLISION)//找到状态为发送或碰撞的终端，这些终端互相干扰，需要计算信干比
                {
                    find_idx_2.push_back(i);
                }
            }
            if(find_idx_2.size()>1)
                {
                    collision++;
                    vec power_total;
                    power_total.set_size(find_idx_2.size());
                    power_total.zeros();
                //    cout<<"find the statement is transmit and collision together ";
                    for(int i=0;i<find_idx_2.size();i++)
                    {

                       to_topo->new_posxyz[find_idx_2[i]].distance=distance_of(to_topo->new_posxyz[find_idx_2[i]].x,to_topo->new_posxyz[find_idx_2[i]].y,to_topo->new_posxyz[find_idx_2[i]].z);

                             to_topo->new_posxyz[find_idx_2[i]].power_=mpow*pow(to_topo->new_posxyz[find_idx_2[i]].distance,-alfa)*pow(10,sigma/10*shadow(find_idx_2[i]));
                             power_total(i)=to_topo->new_posxyz[find_idx_2[i]].power_;
                             if(power_total(i)>max_power)
                             {
                                 max_power=power_total(i);
                                 max_power_index=find_idx_2[i];//找出最大功率者,最大功率值
                             }

                    }
                //   cout<<"the total power is "<<power_total<<endl;
                //   cout<<"the max power index is"<<max_power_index<<endl;
                 //  cout<<"the Mstate(max_power_index) is"<<Mstate(max_power_index)<<endl;
                    if(Mstate(max_power_index)==TRANSMIT)
                    {
                        if(find_idx_2.size()==1)
                        {   //cout<<"flag1"<<endl;
                            cn=10*log10(max_power);
                        }
                        else
                        {   //cout<<"flag2"<<endl;
                            cn=10*log10(max_power/sum(power_total)+1);
                        }
                        for(int i=0;i<find_idx_2.size();i++)
                        {
                            Mstate(find_idx_2[i])=COLLISION;//all set to COLLISION
                          //  cout<<"all set to collision"<<Mstate<<endl;
                        }
                        if(cn>=tcn)
                        {
                            Mstate(max_power_index)=TRANSMIT;//send success
                           // cout<<"send success"<<endl;
                        }
                    }
                    else
                    {
                        for(int i=0;i<find_idx_2.size();i++)
                        {
                            Mstate(find_idx_2[i])=COLLISION;
                         //   cout<<"both collision"<<Mstate<<endl;
                        }
                    }


                }

                now_time=next_time;            

        }
    double traffic=Tplen/sym_rate/now_time;
//#if SHOW_DETAILED
   // cout<<"Splen="<<Splen<<"now_time="<<now_time<<endl;
//    cout<<"data1  "<<now_time<<endl;
//    cout<<"data2  "<<Splen/sym_rate<<endl;
//#endif
    S(now_number)=Splen/sym_rate/now_time;
    traffic_curve(now_number)=traffic;
    ts_curve(now_number)=theorys(traffic,Dtime);
    W(now_number)=Wtime/spend*sym_rate/packet_length;
    cout<<"traffic is: "<<traffic<<"   ";
    cout<<"S is: "<<S(now_number)<<"    ";
    cout<<"Ts is: "<<ts_curve(now_number)<<endl;
    cout<<"Now_time: "<<now_time<<"  ";
    cout<<"运行次数为:"<<num_of_run<<"  ";
    cout<<"碰撞次数为:"<<collision<<" ";
    cout<<"Tplen is:"<<Tplen<<endl;

    cout<<"flag1="<<flag1<<" flag2="<<flag2<<" flag3="<<flag3<<endl;
    cout<<"Wtime="<<Wtime<<endl;

    cout<<endl;
    now_number++;
    }
  //  cout<<traffic_curve<<endl;
  //  cout<<ts_curve<<endl;
 //   cout<<S<<endl;
    cout<<W<<endl;
}

///////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
double Channel::slot_aloha(double now_time)
{
    /////the below is for first calculate////////
  //  char filename_mtime[]="mtime";
   // ofstream fout(filename_mtime);
    if(now_time<0)
    {
#if SHOW_DETAILED==1
        cout<<"初始化 mtime"<<endl;
#endif
        char filename_mtime[]="mtime";
         ofstream fout(filename_mtime);
        slot=packet_length/sym_rate;

        mgtime.set_size(Mnum);
        mgtime.zeros();
        mtime.set_size(Mnum);
        mtime.zeros();

        for(int i=0;i<mgtime.length();i++)
        {
            mgtime(i)=-Tint*log(1-random_seeds.random_01());
            mtime(i)=(floor(mgtime(i)/slot)+1)*slot;
        }
        Mstate=zeros(1,Mnum);
        Mplen.set_size(Mnum);
        for(int i=0;i<Mnum;i++)
        {
            Mplen(i)=packet_length;
        }
        fout<<mtime<<endl;
        fout.close();
        next_time=min(mtime);
        return next_time;

    }
    /////////for second to the end//////////////
   // cout<<"mtime is"<<mtime<<endl;
   // cout<<"mstate is"<<Mstate<<endl;
   // int flag=-1;
  //  int idx=-1;
  //  vector<int> find_idx;
    find_idx.clear();
    idx=-1;
    for(int i=0;i<Mnum;i++)
    {
      //  cout<<"###i="<<i<<"mtime(i)="<<mtime(i)<<"Mstate(i)"<<Mstate(i)<<endl;
        if(mtime(i)==now_time&&Mstate(i)==TRANSMIT)//has found the terminal which transmission succeeded
        {
           // cout<<"##find"<<endl;
            idx=i;
           find_idx.push_back(idx);
        }
    }
    if(find_idx.size()>0)
    {
        flag1++;
      //  cout<<"find_idx.size()="<<find_idx.size()<<endl;
     //   cout<<"finding of terminal which transmission succeeded"<<endl;
#if SHOW_DETAILED==1
        cout<<"FLag1:has found the terminal which transmission succeeded"<<endl;
#endif
        Spnum++;
        Wtime=Wtime+now_time;
        for(int i=0;i<find_idx.size();i++)
        {
        //Spnum++;
        Splen=Splen+Mplen(find_idx[i]);
        Wtime=Wtime-mgtime(find_idx[i]);
        Mstate(find_idx[i])=STANDBY;
        mgtime(find_idx[i])=now_time-Tint*log(1-random_seeds.random_01());
        //mgtime(find_idx[i])=now_time-Tint*log(0.5);
        mtime(find_idx[i])=(floor(mgtime(find_idx[i])/slot)+1)*slot;
        }
    }
    /////clear/////////
    find_idx.clear();
    idx=-1;
     /////clear/////////
    for(int i=0;i<Mnum;i++)
    {
        if(mtime(i)==now_time&&Mstate(i)==COLLISION)//find the terminal which transmit failed
        {
#if SHOW_DETAILED==1
            cout<<"find the terminal"<<i<<" which transmit failed"<<endl;
#endif
            idx=i;
            find_idx.push_back(idx);
        }
    }
    if(find_idx.size()>0)
    {
        flag2++;
        #if SHOW_DETAILED==1
        cout<<"Flag2:find the terminal which transmit failed"<<endl;
        #endif
      //  cout<<"find_idx.size()="<<find_idx.size()<<endl;
     //   cout<<"finding of the terminal which transmission failed"<<endl;
        for(int i=0;i<find_idx.size();i++)
        {
            Mstate(find_idx[i])=STANDBY;
            mtime(find_idx[i])=now_time-Rint*log(1-random_seeds.random_01());
            //mtime(find_idx[i])=now_time-Rint*log(0.5);
            mtime(find_idx[i])=(floor(mtime(find_idx[i])/slot)+1)*slot;
        }
    }
    /////clear/////////
    find_idx.clear();
    idx=-1;
     /////clear/////////
    for(int i=0;i<Mnum;i++)
    {
        if(mtime(i)==now_time)
        {
            idx=i;
            find_idx.push_back(idx);
        }
    }
    if(find_idx.size()>0)
    {
        flag3++;
        #if SHOW_DETAILED==1
        cout<<"Flag3:finding the terminal which transmission start"<<endl;
#endif
        for(int i=0;i<find_idx.size();i++)
        {

            Mstate(find_idx[i])=TRANSMIT;
            mtime(find_idx[i])=now_time+Mplen(find_idx[i])/sym_rate;

            mtime(find_idx[i])=(itpp::round(mtime(find_idx[i])/slot))*slot;
            Tplen=Tplen+(Mplen(find_idx[i]));

        }
    }
    /////clear/////////
    find_idx.clear();
    idx=-1;
     /////clear/////////
    next_time=min(mtime);
   // cout<<"next_time="<<next_time<<endl;
    return next_time;
}
double Channel::distance_of(int x, int y, int z)
{
    return sqrt(x*x+y*y+abs(z*z-25));
}
double Channel::theorys(double traffic, double Dtime)
{

    return traffic*exp(-traffic);
}
