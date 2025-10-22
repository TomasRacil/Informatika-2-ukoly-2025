#include <iostream>
#include <ctime>


void TiskniPole(int** pole,int radky, int sloupce)
{
    for(int i=0;i<radky;i++)
    {
        for(int j=0;j<sloupce;j++)       
        {
            std::cout<<pole[i][j]<<" "; 
        }
        std::cout<<std::endl;
    }
}


int main()
{
    int radky, sloupce;
    std::cin>>radky;      
    std::cin>>sloupce;    

    int** matice_1=nullptr;  
    matice_1=new int*[radky];

    int** matice_2=nullptr;
    matice_2=new int*[radky];
    
    int** soucet=nullptr;
    soucet=new int*[radky];
    
    std::srand(std::time(0));
    
    std::cout<<std::endl;
    std::cout<<"Matice 1:"<<std::endl;
    for(int i=0;i<radky;i++)
    {
        matice_1[i]=new int[sloupce];
        for(int j=0;j<sloupce;++j)
        {
            matice_1[i][j]=std::rand()%10;
        }
    }
    TiskniPole (matice_1,radky,sloupce);
    std::cout<<std::endl;

    std::cout<<"Matice 2:"<<std::endl;
    for(int i=0;i<radky;i++)
    {
        matice_2[i]=new int[sloupce];
        for(int j=0;j<sloupce;++j)
        {
            matice_2[i][j]=std::rand()%10;
        }
    }
    TiskniPole (matice_2,radky,sloupce);
    std::cout<<std::endl;

    std::cout<<"Soucet matic:"<<std::endl;
    for(int i=0;i<radky;i++)
    {
        soucet[i]=new int[sloupce];
        for(int j=0;j<sloupce;++j)
        {
            soucet[i][j]=matice_1[i][j]+matice_2[i][j];
        }
    }
    TiskniPole (soucet,radky,sloupce);
    std::cout<<std::endl;

    return 0;
}


