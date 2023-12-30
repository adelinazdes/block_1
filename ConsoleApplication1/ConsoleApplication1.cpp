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

int grid_size = 101;//размер сетки
int T = 3000; //Заданный период времени 



void rashet(pipe myPipe, double parametr, vector<double>& current_layer, vector<double>& previous_layer) {

    // Суть - смещение предыдущего слоя и запись граничного условия
    for (size_t i = 1; i < current_layer.size(); i++)
    {
        current_layer[i] = previous_layer[i - 1];
    }
    current_layer[0] = parametr;

}



void excel(pipe myPipe, ring_buffer_t<vector<vector<double>>>& buffer, int i) {
    vector<vector<double>>& current_layer = buffer.current();
    if (i == 0) {
        ofstream outFile("plotnostsera.csv");
        outFile << "время,координиата,плотность, сера" << "\n";
        // Записать значения текущего слоя в файл
        for (size_t j = 0; j < current_layer[0].size(); j++) {
            outFile << i * myPipe.dt << "," << j * myPipe.dx << "," << current_layer[0][j] << "," << current_layer[1][j] << "\n";
        }
        outFile.close();
    }
    else {
        ofstream outFile("plotnostsera.csv", ios::app);
        // Записать значения текущего слоя в файл
        for (size_t j = 0; j < current_layer[0].size(); j++) {
            outFile << i * myPipe.dt << "," << j * myPipe.dx << "," << current_layer[0][j] << "," << current_layer[1][j] << "\n";
        }
        outFile.close();
    }
}




int main()
{
    pipe myPipe;
    myPipe.L = 100000;
    myPipe.V = 1;


    myPipe.dx = myPipe.L / (grid_size - 1);
    myPipe.dt = myPipe.dx / myPipe.V; //условие Куранта
    myPipe.N = (T / myPipe.dt);

    znachenia ro;
    ro.massiv = vector<double>(myPipe.N);
    ro.massiv = { 850,860,890 }; //значения плотности на входе трубы
    ro.nachalo = 950;

    znachenia sera;
    sera.massiv = vector<double>(myPipe.N);
    sera.massiv = { 0.01, 0.02, 0.03 }; //значения серы на входе трубы


    vector<double> odin(grid_size);
    ring_buffer_t<vector<vector<double>>> buffer(2, { odin, odin });


    for (size_t i = 0; i < myPipe.N; i++) {
        rashet(myPipe, ro.massiv[i], buffer.current()[0], buffer.previous()[0]);
        rashet(myPipe, sera.massiv[i], buffer.current()[1], buffer.previous()[1]);

        excel(myPipe, buffer, i);
        buffer.advance(1);
    }


}