#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

void izpis(int island[][80]){
    for(int i = 0; i < 50; i++)
    {
        for(int j = 0; j < 80; j++)
            std::cout << island[i][j];
        std::cout << std::endl;
    }
}

void seed(int island[][80]){
    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 80; j++)
            island[i][j] = (rand() % 100 < 55) ? 1 : 0;
}

int neighbour(int island[][80], int x, int y){
    int xm1 = x - 1;
    int xp1 = x + 1;
    int ym1 = y - 1;
    int yp1 = y + 1;
    int neighbours = 0;
    if(xm1 >= 0  && ym1 >= 0 && island[ym1][xm1] == 1) neighbours++;
    if(xm1 >= 0  && y >= 0 && island[y][xm1] == 1) neighbours++;
    if(xm1 >= 0  && yp1 < 50 && island[yp1][xm1] == 1) neighbours++;
    if(x >= 0  && ym1 >= 0 && island[ym1][x] == 1) neighbours++;
    if(x >= 0  && yp1 < 50 && island[yp1][x] == 1) neighbours++;
    if(xp1 < 80  && ym1 >= 0 && island[ym1][xp1] == 1) neighbours++;
    if(xp1 < 80  && y >= 0 && island[y][xp1] == 1) neighbours++;
    if(xp1 < 80  && yp1 < 50 && island[yp1][xp1] == 1) neighbours++;
    return neighbours;
}

void pass(int island[][80]){
    int island2[50][80];

    for(int i = 0; i < 50; i++)
        for(int j = 0; j < 80; j++)
            island2[i][j] = island[i][j];
    
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 80; j++){
            int n = neighbour(island2, j, i);
            if(n > 4){
                island[i][j] = 1;
            }
            else{
                island[i][j] = 0;
            }
        }
    }
}

void izpis2(int island[][80]){
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 80; j++)
            std::cout << neighbour(island, j, i);
        std::cout<<std::endl;
    }
}

int main(){
    srand(time(0));
    int island[50][80];
    
    seed(island);
    for(int i = 0; i < 5; i++)
    {
        pass(island);
    }
    izpis(island);
}