#pragma once
#include <vector>
#include <optional>
#include <string>

using namespace std;

vector<vector<double>> get_input_matrix(); // n строк, m столбцов дополненной матрицы (со столбцом B)
optional<vector<vector<double>>> get_file_matrix(const string& path);
vector<vector<double>> get_input();

void print_matrix(const vector<vector<double>>& data);

void make_triangled_matrix(vector<vector<double>>& data, size_t& swap_lines_counter);

double get_triangled_matrix_determinant(const vector<vector<double>>& data, const size_t& swap_lines_counter, vector<double>& x);

void get_residual(const vector<vector<double>>& data, const vector<double>& x, vector<double>& residual);
