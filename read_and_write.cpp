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

    //open file
    //pos_file
    FILE *fpo0;
    fpo0 = fopen("../output/initial_pos_lipid.cdv", "a");
    if (fpo0 == NULL)
    {
        printf("ERROR_initial_pos_lipid.cdv\n");
        return -1;
    }

    //vel_file
    FILE *fpo1;
    fpo1 = fopen("../output/initial_vel_lipid.cdv", "a");
    if (fpo1 == NULL)
    {
        printf("ERROR_initial_vel_lipid.cdv\n");
        return -1;
    }

    //bond_file
    FILE *fpo2;
    fpo2 = fopen("../output/bond_info.cdv", "a");
    if (fpo2 == NULL)
    {
        printf("ERROR_bond_info.cdv\n");
        return -1;
    }

    //angle_file
    FILE *fpo3;
    fpo3 = fopen("../output/angle_info.cdv", "a");
    if (fpo3 == NULL)
    {
        printf("ERROR_angle_info.cdv\n");
        return -1;
    }

    std::vector<ParticleInfo> PI;
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
    for (uint32_t i = 0; i < 3; i++)
    {
        std::string delete_str;
        std::getline(ifs0, delete_str);
    }
    //ファイルの読み込み
    while (ifs0 >> temp_info.id >> temp_info.type >> temp_info.posx >> temp_info.posy >> temp_info.posz)
    {
        PI.push_back(temp_info);
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
        PI.at(temp_info.id).velx = temp_info.velx;
        PI.at(temp_info.id).vely = temp_info.vely;
        PI.at(temp_info.id).velz = temp_info.velz;
    }
    ifs1.close();
    /*
    
    
    
    
    ボンド情報の読み込みを行う．*/
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
        PI.at(i).bond_pair[PI.at(i).nbond] = j;
        PI.at(i).bond_type[PI.at(i).nbond] = temp_info.bond_type[0];
        PI.at(i).nbond++;

        PI.at(j).bond_pair[PI.at(j).nbond] = i;
        PI.at(j).bond_type[PI.at(j).nbond] = temp_info.bond_type[0];
        PI.at(j).nbond++;
    }
    ifs1.close();
    for (int i = 0; i < 10; i++)
    {
        std::cout << PI.at(i).bond_pair[0] + 1 << " " << PI.at(i).bond_pair[1] + 1 << std::endl;
    }

    /*
    
    
    
    
    アングル情報の読み込みを行う．*/

    std::ifstream ifs3("../input/" + argv[4]);
    if (!ifs3)
    {
        std::cerr << "error3" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    //ファイルの読み込み
    while (ifs2 >> temp_info.bond_pair[0] >> temp_info.bond_pair[1] >> temp_info.bond_type[0])
    {
        int i = temp_info.bond_pair[0] - 1;
        int j = temp_info.bond_pair[1] - 1;
        PI.at(i).bond_pair[PI.at(i).nbond] = j;
        PI.at(i).bond_type[PI.at(i).nbond] = temp_info.bond_type[0];
        PI.at(i).nbond++;

        PI.at(j).bond_pair[PI.at(j).nbond] = i;
        PI.at(j).bond_type[PI.at(j).nbond] = temp_info.bond_type[0];
        PI.at(j).nbond++;
    }
    ifs1.close();
    for (int i = 0; i < 10; i++)
    {
        std::cout << PI.at(i).bond_pair[0] + 1 << " " << PI.at(i).bond_pair[1] + 1 << std::endl;
    }
    return 0;
}