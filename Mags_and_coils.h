#pragma once
#include <cstdio>
#include <iostream>
#include <math.h>
#include <cmath>
#include <vecters.h>
#include <Gas.h>
#include <vector>
#include <queue>

using namespace std;


#define π 3.14159265358979323846
#define μ (1.25663706 / 1000000 )




typedef struct FlowCell
{
	double flow;
	double derivative_plus;
	double derivative_minus;
	FlowCell(): flow(0), derivative_plus(0), derivative_minus(0){

	}
	

} FlowCell;

class FlowMap {
	int size_x;
	double diametr;

	vector<FlowCell> minus;
	vector<FlowCell> plus;

	FlowMap() {};
	FlowMap(int size_x,double diametr) : size_x(size_x), minus(size_x), plus(size_x), diametr(diametr) {};
	
	FlowCell& operator [](int x) {
		if (x >= 0) {
			return (plus[round(x)]);
		}
		else {
			return (minus[-round(x)]);
		}
	}
	double operator [](double x) {
		if (x >= 0) {
			int tmp = round(x);
			double dx = x - tmp;
			if (dx >= 0) {
				return (plus[tmp].flow + plus[tmp].derivative_plus * dx);
			}
			else {
				return (plus[tmp].flow + plus[tmp].derivative_minus * dx);
			}
		}
		else { 
			int tmp = round(x);
			double dx = x - tmp;
			if (dx >= 0) {
				return (minus[tmp].flow + minus[tmp].derivative_plus * dx);
			}
			else {
				return (minus[tmp].flow + minus[tmp].derivative_minus * dx);
			} 
		}
	}

	void set_derivatives() {
		for (int i = -size_x + 1; i++; i < size_x) {

			if (i > (-size_x + 1))
				(*this)[i].derivative_minus = (*this)[i - 1].flow - (*this)[i].flow;
			else (*this)[i].derivative_minus = 0;

			if (i < (size_x - 1))
				(*this)[i].derivative_plus = (*this)[i + 1].flow - (*this)[i].flow;
			else (*this)[i].derivative_plus = 0;
	
		}
	}
};


typedef struct FieldCell
{
	Vecter Mag_vec;
	vector<Vecter> jacobian_plus;
	vector<Vecter> jacobian_minus;
	FieldCell() : jacobian_plus(3), jacobian_minus(3) {

	}
	FieldCell operator +(FieldCell cell) {
		FieldCell tmp = *this;
		tmp.Mag_vec += cell.Mag_vec;
		for (unsigned int i = 0; i < 3; i++) {
			tmp.jacobian_plus[i] += cell.jacobian_plus[i];
			tmp.jacobian_minus[i] += cell.jacobian_minus[i];
		}
		return tmp;
	}
	void show()
	{
		cout << Mag_vec.x_proj << "	" << Mag_vec.y_proj << "	" << Mag_vec.z_proj << endl;
	}

} FieldCell;
class Field_2D {
public:
	void *magnit;

	vector<vector<FieldCell>> cells;

	int size_x, size_y;

	double mult;

	Field_2D() {};

	Field_2D(size_t size_x, size_t size_y):
	size_x(size_x),
	size_y(size_y), 
	cells(size_x, vector<FieldCell>(size_y)) 
	{}

	void show_field(int cherez_n);

	double Flow_X_flat(double distance, int diametr);
};




class FullFieldLine {			// Класс для удобства использования отрицательных значений в [][]. И ТОЛЬКО ДЛЯ ЭТОГО!!! НЕ ВНИКАТЬ, ОПАСНО!!!
public:
	vector<FieldCell> up;		// Вверх по у > 0 
	vector<FieldCell> down;	// Вниз по y < 0 
	int size_y;
	FieldCell& operator [](int y) {
		if (abs(y) < size_y) {
			if (y >= 0) {
				return (up[y]);
			}
			else {
				return (down[-y]);
			}
		}
		else {
			
			return (*this)[sign(y)*(size_y - 1)];
		}
	}
	FullFieldLine() {};
	FullFieldLine(int size_y): up(size_y), down(size_y), size_y(size_y) {}
};

class FullField {
public:
	Vecter center_coord;
	void* magnit;
	int size_x, size_y;		// Размеры поля от центра координат в сторону по х и по у

	vector<FullFieldLine> left;	// Наше поле, разбитое на линии по х < 0.
	vector<FullFieldLine> right;	// Наше поле, разбитое на линии по х > 0.

	FullFieldLine& operator [] (int x)
	{
		if (abs(x) < size_x) {
			if (x >= 0) {
				return (right[x]);
			}
			else {
				return (left[-x]);
			}
		}
		else {
			return (*this)[sign(x)*(size_x - 1)];
		}
	};

	FullField() {};

	FullField(Field_2D Quater_mag_field, Vecter center) :
		size_x(Quater_mag_field.size_x),
		size_y(Quater_mag_field.size_y),
		center_coord(center),
		left(Quater_mag_field.size_x, FullFieldLine(size_y)),
		right(Quater_mag_field.size_x, FullFieldLine(size_y)) {
		for (int x = 0; x++; x < Quater_mag_field.size_x) {
			for (int y = 0; y++; y < Quater_mag_field.size_y) {
				right[x].up[y].Mag_vec = Quater_mag_field.cells[x][y].Mag_vec;

				right[x].down[y].Mag_vec = Quater_mag_field.cells[x][y].Mag_vec;
				right[x].down[y].Mag_vec.y_proj = -Quater_mag_field.cells[x][y].Mag_vec.y_proj;

				left[x].down[y].Mag_vec = Quater_mag_field.cells[x][y].Mag_vec;

				left[x].up[y].Mag_vec = -right[x].down[y].Mag_vec;
			}
		}
		set_jacobians();
	}

	FullField(int size_x, int size_y) :
		size_x(size_x),
		size_y(size_y),
		left(size_x, size_y),
		right(size_x, size_y)
	{
		for (int i = 0; i < size_x; i++) {
			for (int k = 0; k < size_y; k++) {
				right[i].up[k].Mag_vec.set(sign(i), sign(k), 0);
				left[i].up[k].Mag_vec.set(-sign(i), sign(k), 0);
				left[i].down[k].Mag_vec.set(-sign(i), -sign(k), 0);
				right[i].down[k].Mag_vec.set(sign(i), -sign(k), 0);
			}
		};
	};

	void set_jacobians() {
		for (int x = -size_x + 1; x <= size_x - 1; x++) {
			for (int y = (size_y - 1); y >= -size_y + 1; y--) {
				if ((x + 1) < size_x) {
					(*this)[x][y].jacobian_plus[0] = -(*this)[x][y].Mag_vec + (*this)[x + 1][y].Mag_vec;
				}
				else {
					(*this)[x][y].jacobian_plus[0].set(0, 0, 0);
				}
				if ((y + 1) < size_y) {
					(*this)[x][y].jacobian_plus[1] = -(*this)[x][y].Mag_vec + (*this)[x][y + 1].Mag_vec;
				}
				else {
					(*this)[x][y].jacobian_plus[1].set(0, 0, 0);
				}
				if ((x - 1) > -size_x) {
					(*this)[x][y].jacobian_minus[0] = -(*this)[x][y].Mag_vec + (*this)[x - 1][y].Mag_vec;
				}
				else {
					(*this)[x][y].jacobian_minus[0].set(0, 0, 0);
				}
				if ((y - 1) > -size_y) {
					(*this)[x][y].jacobian_minus[1] = -(*this)[x][y].Mag_vec + (*this)[x][y - 1].Mag_vec;
				}
				else {
					(*this)[x][y].jacobian_minus[1].set(0, 0, 0);
				}
				
			}
		}
	}

	FullField operator + (FullField Field2) {
		double tmp_x, tmp_y;
		tmp_x =  (min(size_x + center_coord.x_proj, Field2.size_x + Field2.center_coord.x_proj) -
			max(- size_x + center_coord.x_proj, - Field2.size_x + Field2.center_coord.x_proj)) / 2;
		if (tmp_x < 0) {
			cerr << "FIELD IS NOT ENOUGH BY X AND WE GET MINUS-SIZES ";
			exit(1);
		}
		tmp_y =  (min(size_y + center_coord.y_proj, Field2.size_y + Field2.center_coord.y_proj) -
			max(- size_y + center_coord.y_proj, - Field2.size_y + Field2.center_coord.y_proj)) / 2;
		if (tmp_y < 0) {
			cerr << "FIELD IS NOT ENOUGH BY Y AND WE GET MINUS-COORDINATES ";
			exit(1);
		}
		FullField tmp(abs(trunc(tmp_x)) , abs(trunc(tmp_y)) );
		tmp.center_coord.x_proj = min(size_x + center_coord.x_proj, Field2.size_x + Field2.center_coord.x_proj) - tmp_x;

		tmp.center_coord.y_proj = min(center_coord.y_proj + size_y, Field2.center_coord.y_proj + Field2.size_y) - tmp_y;

		Vecter relative_coord = -center_coord + tmp.center_coord;
		double relative_x = relative_coord.x_proj;
		double relative_y = relative_coord.y_proj;

		Vecter relative_coord2 = -Field2.center_coord + tmp.center_coord;
		double relative_x2 = relative_coord2.x_proj;
		double relative_y2 = relative_coord2.y_proj;
		for (int _x = -tmp_x + 1; _x < tmp_x; _x++) {
			for (int _y = -tmp_y + 1; _y < tmp_y; _y++) {

				double local_x = relative_x + _x;
				double local_y = relative_y + _y;
				double dx = local_x - round(local_x);
				double dy = local_y - round(local_y);

				double local_x2 = relative_x2 + _x;
				double local_y2 = relative_y2 + _y;
				double dx2 = local_x2 - round(local_x2);
				double dy2 = local_y2 - round(local_y2);
			
				tmp[_x][_y] = approx((*this)[lround(local_x)][lround(local_y)], dx, dy) +
					approx(Field2[lround(local_x2)][lround(local_y2)], dx2, dy2);
			}
		}//AHTUNG!!! 
		set_jacobians();
		return tmp;
	}

	void show_field(int cherez_n) {
		int n = cherez_n;
		cout.width(3);
		cout.precision(3);
		cout.fill('0');
		cout.left;
		cout.fixed;
		cout << " X projection: " << endl << endl;
		for (int x = -size_x / n + 1; x <= size_x / n - 1; x++) {
			cout << endl;
			for (int y = (size_y / n - 1); y >= -size_y / n + 1; y--) {
				/*if ((n*x < ((Magnet*)magnit)->height / 2) && (n*y == ((Magnet*)magnit)->diametr / 2))
					cout << "  III    ";
				else*/
				cout << (*this)[n*x][n*y].Mag_vec.x_proj << "  ";
			}
		}
		cout << endl << endl << endl << " Y projection: " << endl << endl;
		for (int x = -size_x / n + 1; x <= size_x / n - 1; x++) {
			cout << endl;
			for (int y = (size_y / n - 1); y >= -size_y / n + 1; y--) {
				/*if ((n*x < ((Magnet*)magnit)->height / 2) && (n*y == ((Magnet*)magnit)->diametr / 2))
					cout << "  III    ";
				else*/
				cout << (*this)[n*x][n*y].Mag_vec.y_proj << "  ";
			}
		}
	}

	double Flow_X_flat(double distance, int diametr);
};

class Magnet {


public:

	double diametr;
	double radius;
	double height;

	double diametr_SI;
	double height_SI;
	double convert_to_SI;

	Vecter position;
	Vecter position_SI;
	Vecter force_on;
	//Vecter direction;
	//Vecter speed;


	Field_2D Quater_mag_field;
	FullField Mag_field;
	Magnet();
	Magnet(int destiny_of_mag_pixels, double _diametr,
		double _height, Vecter _position);
	void show_field(int cherez_n);
};

class PermanentMagnet: public Magnet {

	double strength;		
				

public:

	int sight;
	double weight;

	Vecter speed_SI;
	Vecter speed;
	Vecter accel;
	
	Gas* left;
	Gas* right;

	PermanentMagnet();

	PermanentMagnet(int destiny_of_mag_pixels, double _strength, double _diametr, double _weight,
		double _height, Vecter _position, Vecter _speed, int _sight);

	void relocate(double dtime);

	void Set_Field2D_Conf(int prec_H, int prec_R, int _size_x, int _size_y);

	Vecter Mag_Mag_Force(PermanentMagnet mag, int H_prec);
};

class ElectroMagnet : public Magnet {

	double flow[2];

	int turns;

public:

	double current;
	double voltage;
	double resist;

	ElectroMagnet();

	ElectroMagnet(int destiny_of_mag_pixels, double _current, double _diametr,
		double _height, Vecter _position, int _turns);

	void Set_Field2D_Conf(int prec_R, int _size_x, int _size_y); /* USE FIELD MULTIPLYIER (CURRENT) TO CALCULATE REAL FIELD*/ /*FOR NORMAL PRECISION MANY TURNS NEEDED*/

	double flow_X_from_mag(Magnet& magnit);

	double set_voltage(double dtime);

	Vecter Force_from_coil(PermanentMagnet mag);
};

class CoilSystem {

	int coil_num;

	vector<ElectroMagnet*> coils;

	vector<vector<double>> inductive_coupling;

	CoilSystem();
	CoilSystem(int num_of_coils, ElectroMagnet coil1, ...):
		coil_num(num_of_coils),
		inductive_coupling(num_of_coils, vector<double>(num_of_coils)),
		coils(num_of_coils){

	}

	int set_coupling() {	// returns 1 if coupling calculated correctly, else 0
		for (int i = 0; i < coil_num; i++) {
			for (int k = i + 1; k < coil_num; k++) {
				inductive_coupling[i][k] = coils[i]->flow_X_from_mag(*(coils[k]));
			}
		}
	}

	void update(double dtime);
};


double Flow_X_flat(Magnet mag, double distance, int diametr);

double Flow_X_flat(Field_2D field, double distance, int diametr);


