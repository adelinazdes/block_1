// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <vector>

using namespace std;
int main()
{
    struct pipe
    {
        double L, dx, dt, V;
    };

    pipe myPipe;
    myPipe.L = 100000;
    myPipe.V = 1.5;
    int n = 101;
    int T = 7000;    //Заданный период времени 
    double ro_n = 850;
    double ro_k = 860;
    myPipe.dx = myPipe.L / (n - 1);
    myPipe.dt = myPipe.dx / myPipe.V;    //условие Куранта
    int N = (T / myPipe.dt);

    vector<double> ro_0(N);
    ro_0 = { 850, 870, 860, 860, 860,860, 860, 860, 860, 860 };
    ofstream outFile1("massiv2.csv");
    outFile1 << "время,координата,плотность" << "\n";
    vector<double> ro_1(n);
    for (int k = 0; k < n; k++) {
        ro_1[k] = ro_n;
    }
    vector<double> ro_2(n);
    for (int i = 0; i < N; i++) {
        ro_2[0] = ro_0[i];
        for (int i = 1; i < n; i++) {
            ro_2[i] = ro_1[i - 1];
        }
        ro_1 = ro_2;
        for (int j = 0; j < n; j++) {
            outFile1 << i * myPipe.dt << "," << j * myPipe.dx << "," << ro_2[j] << "\n";
        }

    }

    outFile1.close();

    //апвапимвпаив

    vector<float> sera_0(N);//сера по партиям 
    sera_0 = { 0.01, 0.02, 0.03, 0.04, 0.05,0.06, 0.07, 0.08, 0.09, 0.01 };
    ofstream outFile2("sera2.csv");
    outFile2 << "время,координата,сера" << "\n";
    vector<float> sera_1(n);
    for (int k = 0; k < n; k++) {
        sera_1[k] = 0.01;
    }
    vector<float> sera_2(n);
    for (int i = 0; i < N; i++) {
        sera_2[0] = sera_0[i];
        for (int i = 1; i < n; i++) {
            sera_2[i] = sera_1[i - 1];
        }
        sera_1 = sera_2;
        for (int j = 0; j < n; j++) {
            outFile2 << myPipe.dt * i << "," << myPipe.dx * j << "," << sera_2[j] << "\n";
        }
    }
    outFile2.close();
}
