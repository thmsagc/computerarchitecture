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

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            trans_vec[j].push_back(matrix[i][j]);
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


int main(){
    long N = 10000;

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

