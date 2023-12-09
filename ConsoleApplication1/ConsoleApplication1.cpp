#include <string.h>
#include <stdio.h>
#include <clocale>
#include <iomanip>
#include <iostream>
#include <vector>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <fixed/fixed.h>
#include <pde_solvers/pde_solvers.h>

using namespace std;

struct znachenia
{
    vector<double> massiv;
};

struct pipe
{
    double L, dx, dt, V;
};

int grid_size = 101;
int T = 7000; //Заданный период времени 

int main()
{
    pipe myPipe;
    myPipe.L = 100000;
    myPipe.V = 1.5;

    double ro_n = 850;
    double ro_k = 860;
    myPipe.dx = myPipe.L / (grid_size - 1);
    myPipe.dt = myPipe.dx / myPipe.V; //условие Куранта
    int N = (T / myPipe.dt);

    znachenia ro;
    ro.massiv = vector<double>(N);
    ro.massiv = { 850, 870, 860, 860, 860,860, 860, 860, 860, 860 }; //значения плотности на входе трубы

    znachenia sera;
    sera.massiv = vector<double>(N);
    sera.massiv = { 0.01, 0.02, 0.03, 0.04, 0.05,0.06, 0.07, 0.08, 0.09, 0.01 }; //значения серы на входе трубы

    
}

void rashet(pipe myPipe, znachenia ro, znachenia sera) {
    vector<double> initial_layer(grid_size, ro.massiv[0]);
    // initial_layer - слой, значениями из которого проинициализируются все слои буфера
    ring_buffer_t<vector<double>> buffer(2, initial_layer);

    for (double time = 0; time < T; time += myPipe.dt)
    {
        // Получение ссылок на текущий и предыдущий слои буфера
        vector<double>& previous_layer = buffer.previous();
        vector<double>& current_layer = buffer.current();

        // Расчет методом характеристик
        // Суть - смещение предыдущего слоя и запись граничного условия
        for (size_t i = 1; i < current_layer.size(); i++)
        {
            current_layer[i] = previous_layer[i - 1];
        }
        current_layer[0] = ro.massiv[0];

        // Слой current_layer на следующем шаге должен стать предыдущим. 
        // Для этого сместим индекс текущего слоя в буфере на единицу
        buffer.advance(+1);
        
    }
}


void excel(pipe myPipe, znachenia ro, znachenia sera) {
    ofstream outFile("ddddddddddddddddd.csv");
    outFile << "время,координата,плотность" << "\n";
    vector<double> znachenia(grid_size);
    for (int j = 0; j < grid_size; j++) {
        outFile << j * myPipe.dt << "," << j * myPipe.dx << "," << znachenia[j] << "\n";
    }
    outFile.close();
}
