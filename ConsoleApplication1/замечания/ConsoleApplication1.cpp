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
    double nachalo;
};

struct pipe
{
    double L, dx, dt, V, N;
};

int grid_size = 101;
int T = 100000; //Заданный период времени 



void rashet(pipe myPipe, znachenia parametr, vector<double>& current_layer, vector<double>& previous_layer) {
    vector<double> initial_layer(parametr.massiv);
    // initial_layer - слой, значениями из которого проинициализируются все слои буфера

           // Расчет методом характеристик
        // Суть - смещение предыдущего слоя и запись граничного условия
    for (size_t i = 1; i < current_layer.size(); i++)
    {
        current_layer[i] = previous_layer[i - 1];
    }
    current_layer[0] = parametr.nachalo;


    // Слой current_layer на следующем шаге должен стать предыдущим. 
    // Для этого сместим индекс текущего слоя в буфере на единицу

}



void excel(pipe myPipe, vector<double>& current_layer, int i) {
    if (i == 0) {
        ofstream outFile("ddddddddddddddddd.csv");
        outFile << "время,координата,плотность, сера" << "\n";
        // Записать значения текущего слоя в файл
        for (size_t j = 0; j < current_layer.size(); j++) {
            outFile << i * myPipe.dt << "," << j * myPipe.dx << "," << current_layer[j] << "\n";
        }
        outFile.close();
    }

    else {

        ofstream outFile("ddddddddddddddddd.csv", ios::app);
        // Записать значения текущего слоя в файл
        for (size_t j = 0; j < current_layer.size(); j++) {
            outFile << i * myPipe.dt << "," << j * myPipe.dx << "," << current_layer[j] << "\n";
        }
        outFile.close();
    }





}
int main()
{



    pipe myPipe;
    myPipe.L = 100000;
    myPipe.V = 1.5;

    double ro_n = 850;
    double ro_k = 860;
    myPipe.dx = myPipe.L / (grid_size - 1);
    myPipe.dt = myPipe.dx / myPipe.V; //условие Куранта
    myPipe.N = (T / myPipe.dt);

    znachenia ro;
    ro.massiv = vector<double>(myPipe.N);
    ro.massiv = { 850 }; //значения плотности на входе трубы
    ro.nachalo = 950;

    znachenia sera;
    sera.massiv = vector<double>(myPipe.N);
    sera.massiv = { 0.01 }; //значения серы на входе трубы
    vector<double > odin(grid_size);
    ring_buffer_t<vector<double>> buffer(2, odin);

    for (size_t i = 0; i < myPipe.N; i++) {
        rashet(myPipe, ro, buffer.current(), buffer.previous());
        buffer.advance(1);
        excel(myPipe, buffer.current(), i);

    }




}