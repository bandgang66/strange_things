#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <mutex> 


using namespace std;
random_device Rand;

/*
    Дано
    -----------------------
    пчелы - n
    медведь - 1
    горшок мёда - 1
    вместимость горшка - N
    ======================

    НАЧАЛЬНЫЕ ДАННЫЕ
    -----------------------
    горшок - пустой
    медведь - спит
    =======================

    УСЛОВИЯ
    -----------------------
    пока горшок не полный - медведь спит
    когда горшок полный - медведь сьедает весь мёд(проснулся, сьел, уснул)
    пчела собирает по одному глотку меда и кладет в горшок
    пчела которая приности последнюю порцию будит медведя
*/



void game_world_animation(int n,int N);

int main(int argc,char* argv[])
{   
    int n=Rand()%10;
    int N=Rand()%100+50;
    game_world_animation(n,N);
    return 0;
}


void game_world_animation(int n,int N)
{
    int honey_count_flower=N;
    int honey_count_pot=0;
    char iks      = 'x';
    char stick    = '|';
    char tire     = '-';
    char d_tire   = '_';
    char slash    = '/';
    char b_slash  = '\\';
    char bee_take = 'z';    //обозначение пчелы когда летит за мёдом
    char bee_give = 'k';    //обозначение пчелы когда летит сдавать мёд в горшок
    char honey_in_pot    = 'e';
    int bee_line[10]     = {0,1,2,3,4,5,6,7,8,9}; //0-9
    int bee_poz_take[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}; //7-18 (начальное 12)
    int bee_poz_give[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    
    for(int i=0;i<n;++i)
    {
        bee_poz_take[i]=Rand()%13+7;

    }
    

    while(true)
    {
        system("clear");

        for(int i=0;i<10;++i)
        {
            for(int j=0;j<40;++j)
            {
/*поле 'х'*/    if(     (i==0&&j==0)  ||(i==2&&j==0) ||(i==1&&j==1)  ||(i==0&&j==2) ||(i==2&&j==2))
                    cout<<iks;
/*поле '|'*/    else if((i==3&&j==1)  ||(i==4&&j==1) ||(i==5&&j==1)  ||(i==6&&j==1) ||(i==7&&j==1) ||
                        (i==8&&j==1)  ||(i==9&&j==1) ||(i==6&&j==20) ||(i==7&&j==20)||(i==6&&j==28)||
                        (i==7&&j==28) ||(i==1&&j==31)||(i==1&&j==32) ||(i==1&&j==38)||(i==1&&j==39)||
                        (i==3&&j==33) ||(i==4&&j==33)||(i==3&&j==37) ||(i==4&&j==37))
                    cout<<stick;
/*поле '-'*/    else if((i==7&&j==3)  ||(i==7&&j==4) ||(i==9&&j==22) ||(i==9&&j==23)||(i==9&&j==24)||
                        (i==9&&j==25) ||(i==9&&j==26)||(i==5&&j==35))
                    cout<<tire;
/*поле '_'*/    else if((i==4&&j==3)  ||(i==4&&j==4) ||(i==3&&j==21) ||(i==1&&j==22)||(i==3&&j==22)||
                        (i==1&&j==23) ||(i==3&&j==23)||(i==1&&j==24) ||(i==3&&j==24)||(i==1&&j==25)||
                        (i==3&&j==25) ||(i==1&&j==26)||(i==3&&j==26) ||(i==3&&j==27)||(i==1&&j==34)||
                        (i==1&&j==35) ||(i==1&&j==36))
                    cout<<d_tire;
/*поле '/'*/    else if((i==5&&j==2)  ||(i==6&&j==5) ||(i==3&&j==20) ||(i==2&&j==21)||(i==5&&j==21)||
                        (i==4&&j==22) ||(i==8&&j==27)||(i==0&&j==31) ||(i==2&&j==32)||(i==2&&j==33)||
                        (i==5&&j==36) ||(i==0&&j==38)||(i==2&&j==39))
                    cout<<slash;
/*поле '\'*/    else if((i==6&&j==2)  ||(i==5&&j==5) ||(i==8&&j==21) ||(i==4&&j==26)||(i==2&&j==27)||
                        (i==5&&j==27) ||(i==3&&j==28)||(i==2&&j==31) ||(i==0&&j==32)||(i==5&&j==34)||
                        (i==2&&j==37) ||(i==2&&j==38)||(i==0&&j==39))
                    cout<<b_slash;    
/*1-я пчелка*/  else if(i==bee_line[0]&&j==bee_poz_take[0])
                    cout<<bee_take;
                else if(i==bee_line[0]&&j==bee_poz_give[0])
                    cout<<bee_give;
/*2-я пчелка*/  else if(i==bee_line[1]&&j==bee_poz_take[1])
                    cout<<bee_take;
                else if(i==bee_line[1]&&j==bee_poz_give[1])
                    cout<<bee_give;
/*3-я пчелка*/  else if(i==bee_line[2]&&j==bee_poz_take[2])
                    cout<<bee_take;
                else if(i==bee_line[2]&&j==bee_poz_give[2])
                    cout<<bee_give;
/*4-я пчелка*/  else if(i==bee_line[3]&&j==bee_poz_take[3])
                    cout<<bee_take;
                else if(i==bee_line[3]&&j==bee_poz_give[3])
                    cout<<bee_give;
/*5-я пчелка*/  else if(i==bee_line[4]&&j==bee_poz_take[4])
                    cout<<bee_take;
                else if(i==bee_line[4]&&j==bee_poz_give[4])
                    cout<<bee_give;
/*6-я пчелка*/  else if(i==bee_line[5]&&j==bee_poz_take[5])
                    cout<<bee_take;
                else if(i==bee_line[5]&&j==bee_poz_give[5])
                    cout<<bee_give;
/*7-я пчелка*/  else if(i==bee_line[6]&&j==bee_poz_take[6])
                    cout<<bee_take;
                else if(i==bee_line[6]&&j==bee_poz_give[6])
                    cout<<bee_give;
/*8-я пчелка*/  else if(i==bee_line[7]&&j==bee_poz_take[7])
                    cout<<bee_take;
                else if(i==bee_line[7]&&j==bee_poz_give[7])
                    cout<<bee_give;
/*9-я пчелка*/  else if(i==bee_line[8]&&j==bee_poz_take[8])
                    cout<<bee_take;
                else if(i==bee_line[8]&&j==bee_poz_give[8])
                    cout<<bee_give;
/*10-я пчелка*/ else if(i==bee_line[9]&&j==bee_poz_take[9])
                    cout<<bee_take;
                else if(i==bee_line[9]&&j==bee_poz_give[9])
                    cout<<bee_give;
/*мёд в горшке*/else if((i==8&&j==22)||(i==8&&j==23)||(i==8&&j==24)||(i==8&&j==25)||(i==8&&j==26))
/*15%*/                    {
                        if(honey_count_pot>(0.15*N))
                            cout<<honey_in_pot;
                        else
                            cout<<" ";
                    }
/*30%*/         else if((i==7&&j==21)||(i==7&&j==22)||(i==7&&j==23)||(i==7&&j==24)||(i==7&&j==25)||(i==7&&j==26)||(i==7&&j==27))
                    {
                        if(honey_count_pot>0.3*N)
                            cout<<honey_in_pot;
                        else
                            cout<<" ";
                    }
/*45%*/         else if((i==6&&j==21)||(i==6&&j==22)||(i==6&&j==23)||(i==6&&j==24)||(i==6&&j==25)||(i==6&&j==26)||(i==6&&j==27))
                    {
                        if(honey_count_pot>(0.45*N))
                            cout<<honey_in_pot;
                        else
                            cout<<" ";
                    }
/*60%*/         else if((i==5&&j==22)||(i==5&&j==23)||(i==5&&j==24)||(i==5&&j==25)||(i==5&&j==26))
                    {
                        if(honey_count_pot>(0.6*N))
                            cout<<honey_in_pot;
                        else
                            cout<<" ";
                    }
/*75%*/         else if((i==4&&j==23)||(i==4&&j==24)||(i==4&&j==25))
                    {
                        if(honey_count_pot>(0.75*N))
                            cout<<honey_in_pot;
                        else
                            cout<<" ";
                    }
/*90%*/         else if((i==2&&j==22)||(i==2&&j==23)||(i==2&&j==24)||(i==2&&j==25)||(i==2&&j==26))
                    {
                        if(honey_count_pot>(0.9*N))
                            cout<<honey_in_pot;
                        else
                            cout<<" ";
                    }
/*медведь */    else if((i==3&&j==34)||(i==3&&j==36))
/*сьедает */        {
/*мёд*/                 if(honey_count_pot!=(N-1))
                        {
                            cout<<tire;
                        }
                        else if(honey_count_pot==(N-1))
                        {
                            cout<<'O'; //медведь просыпается
                        }
                    }
                else
                    cout<<" ";
           
            }

        cout<<endl;

        }


        

        for(int i=0;i<n;++i)         // механизм сбора мёда
        {
            if(honey_count_flower!=0)   //если мёд в цветке закончился то пчелы перестают двигаться к нему
            {
                if(bee_poz_take[i]>6&&bee_poz_take[i]!=-1) //если пчела(состояние взять мёд больше поля 6, это граница у цветка)
                {                                          //и она не -1, значит она активна
                    --bee_poz_take[i];                     //летит к цветку меняя положение на 1 влево
                }
                else if(bee_poz_take[i]==6) //иначе если она равна 6(граница цветка) надо взять мёд
                {                           
                    --honey_count_flower;  // -1 количества мёда в цветке(но еще не прибавляем горшку)
                    bee_poz_take[i] = -1;   //состояние "взять мёд" засыпает
                    bee_poz_give[i] = 6;    //просыпается состояние "отнести мёд"
                }
            }
            if(honey_count_pot!=N)   //если мёд в горшке полный просыпается медведь и жрёт мёд
            {
                if(bee_poz_give[i]<19&&bee_poz_give[i]!=-1)//если состояние отнести мёд меньше 19(граница горшка) 
                {                                          //и активно (-1 это состояние сна)
                    ++bee_poz_give[i];                      //то меняем позицию на +1 вправо(летим к горшку)
                }
                else if(bee_poz_give[i]==19)    //иначе, если долетели до границы(19)
                {   
                    ++honey_count_pot;          //отдаем мёд в горшок
                    bee_poz_give[i] = -1;       //состояние отдать мёд спит
                    bee_poz_take[i] = 19;       //состояние взять мёд проснулось
                }
            }
        }
        

        cout<<"honey in flower : "<<honey_count_flower<<endl;
        cout<<"honey in pot : "<<honey_count_pot<<endl;
        this_thread::sleep_for(chrono::milliseconds(10));

        

        if(honey_count_flower==0&&honey_count_pot==N)
        {
            this_thread::sleep_for(chrono::milliseconds(2000));
            honey_count_flower=N;
            honey_count_pot=0;
        }

    }
    
}

