#include "Gauss.h"
#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <optional>
#include <string>
#include <sstream>

vector<vector<double>> get_input_matrix()
{
	vector<vector<double>> data;
	size_t n, m;
	cin >> n;
	m = n + 1;
	vector<double> line;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			double a;
			cin >> a;
			line.push_back(a);
		}
		data.push_back(line);
		line.clear();
	}
	return data;
}

optional<vector<vector<double>>> get_file_matrix(const string& path)
{
	ifstream file(path);
	if (!file)
	{
		cout << "Не удалось открыть файл" << endl;
		return {};
	}

	vector<vector<double>> data;
	size_t n, m;
	file >> n >> m;
	vector<double> line;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			double a;
			file >> a;
			line.push_back(a);
		}
		data.push_back(line);
		line.clear();
	}

	return data;
}

//vector<vector<double>> get_input()
//{
//	cout << "Введите \"c\", если желаете ввести данные с клавиатуры и \"f\", если данные поступят из файла" << endl;
//	char c;
//	cin >> c;
//	if (c == 'f')
//	{
//		cout << "Введите путь к файлу:" << endl;
//		string path;
//		cin >> path;
//		optional<vector<vector<double>>> opt_data = get_file_matrix(path);
//		if (!opt_data.has_value())
//		{
//
//		}
//	}
//	return vector<vector<double>>();
//}

void print_matrix(const vector<vector<double>>& data)
{
	size_t max_length = 0;
	
	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data[0].size() - 1; j++)
		{
			stringstream s_value;
			s_value << data[i][j];
			string current = s_value.str();
			
			if (current.length() > max_length)
			{
				max_length = current.length();
			}
			s_value.clear();
		}
	}

	for (size_t i = 0; i < data.size(); i++)
	{
		for (size_t j = 0; j < data[0].size() - 1; j++)
		{
			cout << setw(max_length + 1) << left << data[i][j];
		}
		cout << "| " << data[i][data[0].size() - 1];
		cout << endl;
	}
}

void make_triangled_matrix(vector<vector<double>>& data, size_t& swap_lines_counter)
{
	const size_t n = data.size();
	const size_t m = data[0].size();
	for (size_t j = 0; j < m-2; j++)
	{
		double column_max_value = abs(data[j][j]);
		size_t max_i_index = j;
		for (size_t i = j+1; i < n; i++)
		{
			if (abs(data[i][j]) > column_max_value)
			{
				column_max_value = abs(data[i][j]);
				max_i_index = i;
			}
		}
		if (max_i_index != j)
		{
			swap_lines_counter++;
			vector<double> max_line = data[max_i_index];
			data[max_i_index] = data[j];
			data[j] = max_line;
		}

		// на данном этапе имеем в текущем столбце максимальный по модулю элемент в позиции [j][j]
		/*print_matrix(data);
		cout << endl;*/

		if (data[j][j] == 0)
			continue;
		for (size_t i = j+1; i < n; i++)
		{
			double change_value = (-1.0) * data[i][j] / data[j][j];
			for (size_t k = 0; k < m; k++)
			{
				data[i][k] += change_value * data[j][k];
			}
		}
	}
}

double get_triangled_matrix_determinant(const vector<vector<double>>& data, const size_t& swap_lines_counter, vector<double>& x)
{
	const size_t n = data.size();
	const size_t m = data[0].size();

	x.resize(n, 0);
	for (int i = n-1; i >= 0; i--)
	{
		double right_value = data[i][m - 1]; // значение из столбца B
		for (size_t j = i + 1; j < m - 1; j++)
		{
			right_value -= data[i][j] * x[j];
		}
		//if (abs(right_value) < 0.000000000001)
		if (right_value == 0)
		{
			x[i] = 0;
			continue;
		}
		x[i] = right_value / data[i][i];
	}

	double determinant = pow(-1, swap_lines_counter);
	for (size_t i = 0; i < n; i++)
	{
		determinant *= data[i][i];
	}
	return determinant;
}

void get_residual(const vector<vector<double>>& data, const vector<double>& x, vector<double>& residual)
{
	const size_t n = data.size();
	const size_t m = data[0].size();

	for (size_t i = 0; i < n; i++)
	{
		double left = 0;
		for (size_t j = 0; j < m - 1; j++)
		{
			left += data[i][j] * x[j];
		}

		double right = data[i][m - 1];

		residual.push_back(right - left);
	}
}
