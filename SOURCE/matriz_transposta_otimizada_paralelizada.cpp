#include <cmath>
#include <iostream>
#include <chrono>
#include <omp.h>
#include <vector>
#include <algorithm>
//#include<conio>
#include <math.h>

using namespace std;

void fill_row(vector<int> & row)
{
    generate(row.begin(), row.end(), [](){ return rand() % 100; });
}

void fill_matrix(vector<vector<int>> & matrix)
{
    for_each(matrix.begin(), matrix.end(), fill_row);
}

vector<vector<int>> transpose(vector<vector<int>> &matrix)
{
    if (matrix.size() == 0)
        return matrix;

    vector<vector<int> > trans_vec(matrix[0].size(), vector<int>());
    #pragma omp parallel
    {
        int i, j, id, lnthreads;
        lnthreads = omp_get_num_threads();
        id = omp_get_thread_num();

        for (i = 0; i < matrix.size(); i++)
        {
            #pragma omp for schedule(static) nowait
            for (j = 0; j < matrix[i].size(); j++)
            {
                trans_vec[j].push_back(matrix[i][j]);
            }
        }
    }
    return trans_vec;
}

void printMatrix(vector<vector<int>> &m){
    cout << "\n";
    for(int i=0;i<m.size();i++){
        for(int j=0;j<m[i].size();j++)
            cout<<m[i][j] << " ";
        cout<<endl;
    }
}

int main(int argc, char *argv[ ]){

    if(argc != 3){
        cout << "Inicie o número de dimensão da matriz e o número de threads.\nEx: nome_do_binario 10 1 (Matriz 10000 x 10000 e 1 thread)." << "\n";
        return 0;
    }
    cout << argv[0] << " " << argv[1] << " " << argv[2] << " ";
    long N = atoi(argv[1]);
    int num_threads = atoi(argv[2]);
    cout << "Número de Threads: " << num_threads << "\n";
    omp_set_num_threads(num_threads);
    auto t1 = std::chrono::high_resolution_clock::now();
    vector<vector<int>> matrix (N, vector<int>(N, 0));
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = (std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count());
    auto duration_total = duration;
    cout << "Tempo de alocacao(" << N << "x" << N << " = 0): " << float(duration)/1000000 << "\n";

    t1 = std::chrono::high_resolution_clock::now();
    fill_matrix(matrix);
    t2 = std::chrono::high_resolution_clock::now();
    duration = (std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count());
    duration_total += duration;
    cout << "Tempo de preenchimento: " << float(duration)/1000000 << "\n";


    t1 = std::chrono::high_resolution_clock::now();
    vector<vector<int>> matrix_transpose = transpose(matrix);
    t2 = std::chrono::high_resolution_clock::now();
    duration = (std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count());
    duration_total += duration;
    cout << "Tempo de calculo: " << float(duration)/1000000 << "\n";

    cout << "Tempo de execucao total: " << float(duration_total)/1000000 << "\n";

    //printMatrix(matrix);
    //printMatrix(matrix_transpose);

    return 0;

}
