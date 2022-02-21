#pragma once
#include <vector>

using namespace std;

vector<vector<double>> get_input_matrix(); // n �����, m �������� ����������� ������� (�� �������� B)

void print_matrix(const vector<vector<double>>& data);

void make_triangled_matrix(vector<vector<double>>& data, size_t& swap_lines_counter);

double get_triangled_matrix_determinant(const vector<vector<double>>& data, const size_t& swap_lines_counter, vector<double>& x);

void get_residual(const vector<vector<double>>& data, const vector<double>& x, vector<double>& residual);





