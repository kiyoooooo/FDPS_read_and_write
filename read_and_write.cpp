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
    /*アングル*/
    uint32_t angle_pair[2][3];
    uint32_t angle_type[2];
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

    /*座標の読み込みを行う．*/
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
        std::cout << delete_str << std::endl;
    }
    //ファイルの読み込み
    ParticleInfo temp_info;
    while (ifs0 >> temp_info.id >> temp_info.type >> temp_info.posx >> temp_info.posy >> temp_info.posz)
    {
        PI.push_back(temp_info);
    }


    /*
    std::ifstream ifs1("../input/" + argv[2]);
    if (!ifs1)
    {
        std::cerr << "error1" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::ifstream ifs2("../input/" + argv[3]);
    if (!ifs2)
    {
        std::cerr << "error2" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::ifstream ifs3("../input/" + argv[4]);
    if (!ifs3)
    {
        std::cerr << "error3" << std::endl;
        std::exit(EXIT_FAILURE);
    }*/

    return 0;
}