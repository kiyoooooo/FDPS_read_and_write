#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <random>
#include <string.h>      //文字列の代入に使う
#include <bits/stdc++.h> //piの利用で必要(M_PI)

class ParticleInfo
{
public:
    uint32_t id;
    uint32_t type;
    /*position*/
    double posx;
    double posy;
    double posz;
    /*velocity*/
    double velx;
    double vely;
    double velz;
    /*結合*/
    uint32_t bond_pair[2];
    uint32_t bond_type[2];
    uint32_t nbond = 0;
    /*アングル*/
    uint32_t angle_pair[2][3];
    uint32_t angle_type[2];
    uint32_t nangle = 0;
};

int main(int argc, char *argv[])
{
    std::vector<ParticleInfo> pinfo;
    ParticleInfo temp_info;
    /*
    
    
    
    
    座標の読み込みを行う．*/
    std::ifstream ifs0(argv[1]);
    if (!ifs0)
    {
        std::cerr << "error0" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    //いらないはじめの3行を捨てる．
    std::string delete_str[3];
    for (uint32_t i = 0; i < 3; i++)
    {
        std::getline(ifs0, delete_str[i]);
    }
    //ファイルの読み込み　粒子番号,粒子種は0から開始する．
    while (ifs0 >> temp_info.id >> temp_info.type >> temp_info.posx >> temp_info.posy >> temp_info.posz)
    {
        temp_info.id--;
        temp_info.type--;
        pinfo.push_back(temp_info);
    }
    ifs0.close();
    /*
    
    
    
    
    速度の読み込みを行う．*/
    std::ifstream ifs1(argv[2]);
    if (!ifs1)
    {
        std::cerr << "error1" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    //ファイルの読み込み
    while (ifs1 >> temp_info.id >> temp_info.velx >> temp_info.vely >> temp_info.velz)
    {
        temp_info.id--;
        pinfo.at(temp_info.id).velx = temp_info.velx;
        pinfo.at(temp_info.id).vely = temp_info.vely;
        pinfo.at(temp_info.id).velz = temp_info.velz;
    }
    ifs1.close();
    /*
    
    
    
    
    ボンド情報の読み込みを行う．粒子番号や，ボンド相手の粒子番号とボンド種が−1されていることに注意する．*/
    std::ifstream ifs2(argv[3]);
    if (!ifs2)
    {
        std::cerr << "error2" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    //ファイルの読み込み
    while (ifs2 >> temp_info.bond_pair[0] >> temp_info.bond_pair[1] >> temp_info.bond_type[0])
    {
        int i = temp_info.bond_pair[0] - 1;
        int j = temp_info.bond_pair[1] - 1;
        temp_info.bond_type[0]--;
        pinfo.at(i).bond_pair[pinfo.at(i).nbond] = j;
        pinfo.at(i).bond_type[pinfo.at(i).nbond] = temp_info.bond_type[0];
        pinfo.at(i).nbond++;

        pinfo.at(j).bond_pair[pinfo.at(j).nbond] = i;
        pinfo.at(j).bond_type[pinfo.at(j).nbond] = temp_info.bond_type[0];
        pinfo.at(j).nbond++;
    }
    ifs2.close();
    /*//bond情報をファイルに書き出す際に便利な書き方．
    for (int i = 0; i < 10; i++)
    {
        //"&&"条件で，pinfo.at(i).nbond == 1のときに重複して出力してしまうのを防ぐ．
        if (pinfo.at(i).nbond == 1 && pinfo.at(i).id < pinfo.at(i).bond_pair[0])
        {
            std::cout << pinfo.at(i).id + 1 << " " << pinfo.at(i).bond_pair[0] + 1 << " " << pinfo.at(i).bond_type[0] + 1 << std::endl;
        }
        else if (pinfo.at(i).nbond == 2)
        {
            std::cout << pinfo.at(i).id + 1 << " " << pinfo.at(i).bond_pair[1] + 1 << " " << pinfo.at(i).bond_type[0] + 1 << std::endl;
        }
    }*/
    /*
    
    
    
    
    アングル情報の読み込みを行う．粒子番号や，アングル相手の粒子番号とアングル種が−1されていることに注意する．*/
    std::ifstream ifs3(argv[4]);
    if (!ifs3)
    {
        std::cerr << "error3" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    //ファイルの読み込み
    while (ifs3 >> temp_info.angle_pair[0][0] >> temp_info.angle_pair[0][1] >> temp_info.angle_pair[0][2] >> temp_info.angle_type[0])
    {
        int i = temp_info.angle_pair[0][0] - 1;
        int j = temp_info.angle_pair[0][1] - 1;
        int k = temp_info.angle_pair[0][2] - 1;
        temp_info.angle_type[0]--;
        pinfo.at(i).angle_pair[pinfo.at(i).nangle][0] = i;
        pinfo.at(i).angle_pair[pinfo.at(i).nangle][1] = j;
        pinfo.at(i).angle_pair[pinfo.at(i).nangle][2] = k;
        pinfo.at(i).angle_type[pinfo.at(i).nangle] = temp_info.angle_type[0];
        pinfo.at(i).nangle++;

        pinfo.at(j).angle_pair[pinfo.at(j).nangle][0] = i;
        pinfo.at(j).angle_pair[pinfo.at(j).nangle][1] = j;
        pinfo.at(j).angle_pair[pinfo.at(j).nangle][2] = k;
        pinfo.at(j).angle_type[pinfo.at(j).nangle] = temp_info.angle_type[0];
        pinfo.at(j).nangle++;

        pinfo.at(k).angle_pair[pinfo.at(k).nangle][0] = i;
        pinfo.at(k).angle_pair[pinfo.at(k).nangle][1] = j;
        pinfo.at(k).angle_pair[pinfo.at(k).nangle][2] = k;
        pinfo.at(k).angle_type[pinfo.at(k).nangle] = temp_info.angle_type[0];
        pinfo.at(k).nangle++;
    }
    ifs3.close();
    /*//アングル情報をファイルに書き出す際に便利な書き方．
    for (int i = 0; i < 10; i++)
    {
        if (pinfo.at(i).nangle == 1)
        {
            std::cout << pinfo.at(i).angle_pair[0][0] + 1 << " " << pinfo.at(i).angle_pair[0][1] + 1 << " " << pinfo.at(i).angle_pair[0][2] + 1 << " " << pinfo.at(i).angle_type[0] + 1 << std::endl;
        }
    }*/
    /*
    
    
    
    
    出力ファイルを生成する．*/
    //open file
    //pos_file
    FILE *fpo0;
    fpo0 = fopen("../output/initial_pos_lipid.cdv", "w");
    if (fpo0 == NULL)
    {
        printf("ERROR_initial_pos_lipid.cdv\n");
        return -1;
    }
    for (int i = 0; i < 3; i++)
    {
        fprintf(fpo0, "%s \n", delete_str[i].c_str());
    }
    for (int i = 0; i < pinfo.size(); i++)
    {
        fprintf(fpo0, "%d %d   %lf   %lf   %lf \n",
                pinfo.at(i).id + 1,
                pinfo.at(i).type + 1,
                pinfo.at(i).posx,
                pinfo.at(i).posy,
                pinfo.at(i).posz);
    }
    /*





    */
    //vel_file
    FILE *fpo1;
    fpo1 = fopen("../output/initial_vel_lipid.cdv", "w");
    if (fpo1 == NULL)
    {
        printf("ERROR_initial_vel_lipid.cdv\n");
        return -1;
    }
        for (int i = 0; i < pinfo.size(); i++)
    {
        fprintf(fpo1, "%d   %lf   %lf   %lf \n",
                pinfo.at(i).id + 1,
                pinfo.at(i).velx,
                pinfo.at(i).vely,
                pinfo.at(i).velz);
    }
    /*





    */
    //bond_fileここからはofstream記法で出力する．
    std::ofstream fpo2("../output/bond_info.cdv", std::ios::out);
    for (int i = 0; i < pinfo.size(); i++)
    {
        //"&&"条件で，pinfo.at(i).nbond == 1のときに重複して出力してしまうのを防ぐ．
        if (pinfo.at(i).nbond == 1 && pinfo.at(i).id < pinfo.at(i).bond_pair[0])
        {
            fpo2 << pinfo.at(i).id + 1 << "   " << pinfo.at(i).bond_pair[0] + 1 << "   " << pinfo.at(i).bond_type[0] + 1 << std::endl;
        }
        else if (pinfo.at(i).nbond == 2)
        {
            fpo2 << pinfo.at(i).id + 1 << "   " << pinfo.at(i).bond_pair[1] + 1 << "   " << pinfo.at(i).bond_type[0] + 1 << std::endl;
        }
    }
    /*





    */
    //angle_file
    FILE *fpo3;
    fpo3 = fopen("../output/angle_info.cdv", "w");
    if (fpo3 == NULL)
    {
        printf("ERROR_angle_info.cdv\n");
        return -1;
    }
    return 0;
}