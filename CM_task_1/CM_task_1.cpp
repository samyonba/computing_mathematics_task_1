#include <iostream>
#include "Gauss.h"

using namespace std;

int main()
{
    vector<vector<double>> data = get_input_matrix();    

    size_t swap_lines_counter = 0;
    make_triangled_matrix(data, swap_lines_counter);
    cout << endl << "Triangled matrix:" << endl;
    print_matrix(data);
    
    vector<double> x;
    double determinant = get_triangled_matrix_determinant(data, swap_lines_counter, x);

    cout << endl << "X: ";
    for (auto value : x)
    {
        cout << value << " ";
    }
    cout << endl << "Determinant: " << determinant << endl;

    vector<double> residual;
    get_residual(data, x, residual);
    cout << "Residual: ";
    for (double value : residual)
    {
        cout << value << " ";
    }
    cout << endl;
}
