#include <iostream>
#include "Gauss.h"

using namespace std;

int main()
{
    // реализовать ввод из файла
    setlocale(LC_ALL, "Russian");
    cout << "Введите размерность матрицы - n:" << endl;
    vector<vector<double>> data = get_input_matrix();    

    size_t swap_lines_counter = 0;
    make_triangled_matrix(data, swap_lines_counter);
    cout << endl << "Треугольная матрица:" << endl;
    print_matrix(data);
    
    vector<double> x;
    double determinant = get_triangled_matrix_determinant(data, swap_lines_counter, x);

    cout << endl << "Вектор X: ";
    for (auto value : x)
    {
        cout << value << " ";
    }
    cout << endl << endl << "Определитель: " << determinant << endl;

    vector<double> residual;
    get_residual(data, x, residual);
    cout << endl << "Невязки: ";
    for (double value : residual)
    {
        cout << value << " ";
    }
    cout << endl;
}
