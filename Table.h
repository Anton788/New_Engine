#pragma once
#include <vector>
using namespace std;

static int NUM_OF_ELEMENTS = 30;
static double MIN_SPEED_REACTION = 1e-10;

static vector<vector<double>> VANDERVAL_COEFF_A (NUM_OF_ELEMENTS, vector<double>(NUM_OF_ELEMENTS, 0));
static vector<vector<double>> REACTION_ENERGY   (NUM_OF_ELEMENTS, vector<double>(NUM_OF_ELEMENTS, 0));
static vector<vector<double>> ACTIVATION_ENERGY (NUM_OF_ELEMENTS, vector<double>(NUM_OF_ELEMENTS, 0));

static vector<vector<bool>>   IS_REACTION       (NUM_OF_ELEMENTS, vector<bool>(NUM_OF_ELEMENTS, 0));
// Булевская таблица, реагируют ли 2 элемента между собой

static vector<vector<pair<pair<int, int>, vector<pair<int, int>>>>> REACTION_EQUATIONS
(NUM_OF_ELEMENTS, vector<pair<pair<int, int>, vector<pair<int, int>>>>(NUM_OF_ELEMENTS)); // (stechiometrycal_indexes)
// Формат взаимодействия между любыми двумя элементами в реакции с N_ij выходными веществами.
// В элементе ячейки: 
// FIRST = Первая пара в ячейке выдает коэффициенты взаимодействия двух входных (по номерам в векторе (определен в SUBSTANCES)) элементов в реакции.
// SECOND = Vector пар с обозначениями: <номер вещества (определен в SUBSTANCES), коэффициент домножения в реакции(на выходе)>

static vector<vector<double>> LOCAL_REACTION_MULTIPLIER_INDEX(NUM_OF_ELEMENTS, vector<double>(NUM_OF_ELEMENTS, 0));
// Матрица множителей скорости реакции между двумя элеменами
// i_j-элмент считается по формуле:
// Nav * σ_ij * σ_ij * sqrt(8 * π * κ * (mol_mass[i] + mol_mass[j]) / (mol_mass[i] * mol_mass[j])), где
// σ_ij - это эффективная площадь столкновения молекул в реакции (табличные данные)

enum SUBSTANCES {
	VAKUUM = 0,
	H20 = 1,
	CO2 = 2,
	N2 = 3,
	H2 = 4,
	CH4 = 5,
	O2 = 6
};

//class FUEL_PROFILE
//{
//public:
//	vector<Substance> injection;
//	vector<Substance> products;
//	int inj_substances_count;
//	int product_substances_count;
//	int substances_count;
//	enum SUBSTANCES_NUMBERS {};
//	vector<vector<double>> VANDERVAL_COEFF_A;
//	vector<vector<double>> REACTION_ENERGY;
//	vector<vector<double>> ACTIVATION_ENERGY;
//	vector<vector<pair<pair<int, int>, vector<pair<int, int>>>>> REACTION_EQUATIONS;
//};



