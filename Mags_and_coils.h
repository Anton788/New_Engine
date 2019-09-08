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


typedef struct Field_cell
{
	vecter Mag_vec;
	vector<vecter> jacobian_plus;
	vector<vecter> jacobian_minus;
	Field_cell() : jacobian_plus(3), jacobian_minus(3) {

	}
	Field_cell operator +(Field_cell cell) {
		Field_cell tmp = *this;
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
	
} Field_cell;

typedef struct Flow_cell
{
	double flow;
	double derivative_plus;
	double derivative_minus;
	Flow_cell(): flow(0), derivative_plus(0), derivative_minus(0){

	}
	

} Flow_cell;

class Flow_map {
	int size_x;
	double diametr;

	vector<Flow_cell> minus;
	vector<Flow_cell> plus;

	Flow_map() {};
	Flow_map(int size_x,double diametr) : size_x(size_x), minus(size_x), plus(size_x), diametr(diametr) {};
	
	Flow_cell& operator [](int x) {
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


inline Field_cell approx(Field_cell& first, double dx, double dy) {
	Field_cell tmp = first;
	
	if (dx > 0) {
		if (dy > 0) {
			tmp.Mag_vec += first.jacobian_plus[0] * fabs(dx) + first.jacobian_plus[1] * fabs(dy);
		}
		else {
			tmp.Mag_vec += first.jacobian_plus[0] * fabs(dx) + first.jacobian_minus[1] * fabs(dy);
		}
	}
	else if (dy > 0) {
		tmp.Mag_vec += first.jacobian_minus[0] * fabs(dx) + first.jacobian_plus[1] * fabs(dy);
	}
	else {
		tmp.Mag_vec += first.jacobian_minus[0] * fabs(dx) + first.jacobian_minus[1] * fabs(dy);
	}
		
	return tmp;
}


class Field_2D {
public:
	void *magnit;

	vector<vector<Field_cell>> cells;

	int size_x, size_y;

	double mult;

	Field_2D() {};

	Field_2D(size_t size_x, size_t size_y):
	size_x(size_x),
	size_y(size_y), 
	cells(size_x, vector<Field_cell>(size_y)) 
	{}

	void show_field(int cherez_n);

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

	vecter position;
	vecter position_SI;
	vecter force_on;
	//vecter direction;
	//vecter speed;
	

	Field_2D Mag_field;
	Full_Field Full_mag_field;
	Magnet();
	Magnet(int destiny_of_mag_pixels, double _diametr,
		double _height, vecter _position);
	void show_field(int cherez_n);
};
//Приём!Ты тут?

class Full_Field_Line {			// Класс для удобства использования отрицательных значений в [][]. И ТОЛЬКО ДЛЯ ЭТОГО!!! НЕ ВНИКАТЬ, ОПАСНО!!!
public:
	vector<Field_cell> up;		// Вверх по у > 0 
	vector<Field_cell> down;	// Вниз по y < 0 
	int size_y;
	Field_cell& operator [](int y) {
		if (abs(y) < size_y) {
			if (y > 0) {
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
	Full_Field_Line() {};
	Full_Field_Line(int size_y) :up(size_y), down(size_y), size_y(size_y) {}
};

class Full_Field {
public:
	vecter center_coord;
	void* magnit;
	int size_x, size_y;		// Размеры поля от центра координат в сторону по х и по у

	vector<Full_Field_Line> left;	// Наше поле, разбитое на линии по х < 0.
	vector<Full_Field_Line> right;	// Наше поле, разбитое на линии по х > 0.

	Full_Field_Line& operator [] (int x)
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
	Full_Field() {};
	Full_Field( Magnet mag) :
		size_x(mag.Mag_field.size_x),
		size_y(mag.Mag_field.size_y),
		center_coord(mag.position),
		left(mag.Mag_field.size_x, Full_Field_Line(size_y)),
		right(mag.Mag_field.size_x, Full_Field_Line(size_y)) {
		for (int x = 0; x++; x < mag.Mag_field.size_x) {
			for (int y = 0; y++; y < mag.Mag_field.size_y) {
				right[x].up[y].Mag_vec = mag.Mag_field.cells[x][y].Mag_vec;

				right[x].down[y].Mag_vec = mag.Mag_field.cells[x][y].Mag_vec;
				right[x].down[y].Mag_vec.y_proj = -mag.Mag_field.cells[x][y].Mag_vec.y_proj;

				left[x].down[y].Mag_vec = mag.Mag_field.cells[x][y].Mag_vec;

				left[x].up[y].Mag_vec = -right[x].down[y].Mag_vec;
			}
		}
		set_jacobians();
	}
	Full_Field(int size_x, int size_y) :
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
	Full_Field operator + (Full_Field Field2) {
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
		Full_Field tmp(abs(trunc(tmp_x)) , abs(trunc(tmp_y)) );
		tmp.center_coord.x_proj = min(size_x + center_coord.x_proj, Field2.size_x + Field2.center_coord.x_proj) - tmp_x;

		tmp.center_coord.y_proj = min(center_coord.y_proj + size_y, Field2.center_coord.y_proj + Field2.size_y) - tmp_y;

		vecter relative_coord = -center_coord + tmp.center_coord;
		double relative_x = relative_coord.x_proj;
		double relative_y = relative_coord.y_proj;

		vecter relative_coord2 = -Field2.center_coord + tmp.center_coord;
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



class Permanent_Magnet : public Magnet {

	double strength;		
				

public:

	int sight;
	double weight;

	vecter speed_SI;
	vecter speed;
	vecter accel;
	
	Gas* left;
	Gas* right;

	Permanent_Magnet();

	Permanent_Magnet(int destiny_of_mag_pixels, double _strength, double _diametr, double _weight,
		double _height, vecter _position, vecter _speed, int _sight);

	void relocate(double dtime);

	void Set_Field2D_Conf(int prec_H, int prec_R, int _size_x, int _size_y);

	vecter Mag_Mag_Force(Permanent_Magnet mag, int H_prec);
};

class Electromagnet : public Magnet {

	double flow[2];

	int turns;

public:

	double current;
	double voltage;
	double resist;

	Electromagnet();

	Electromagnet(int destiny_of_mag_pixels, double _current, double _diametr,
		double _height, vecter _position, int _turns);

	void Set_Field2D_Conf(int prec_R, int _size_x, int _size_y); /* USE FIELD MULTIPLYIER (CURRENT) TO CALCULATE REAL FIELD*/ /*FOR NORMAL PRECISION MANY TURNS NEEDED*/

	double flow_X_from_mag(Magnet& magnit);

	double set_voltage(double dtime);

	vecter Force_from_coil(Permanent_Magnet mag);
};

class Coil_System {

	int coil_num;

	vector<Electromagnet*> coils;

	vector<vector<double>> inductive_coupling;

	Coil_System();
	Coil_System(int num_of_coils, Electromagnet coil1, ...):
		coil_num(num_of_coils),
		inductive_coupling(num_of_coils, vector<double>(num_of_coils)),
		coils(num_of_coils){

	}

	int set_coupling() {	// returns 1 if coupling calculated correctly, else 0
		for (int i = 0; i < coil_num; i++) {
			for (int k = i + 1; k < coil_num; k++) {
				inductive_coupling[i][k] = coils[i]->flow_X_from_mag(*coils[k]);
			}
		}
	}

	void update(double dtime);
};



double Flow_X_flat(Magnet mag, double distance, int diametr);

double Flow_X_flat(Field_2D field, double distance, int diametr);



//struct Coil {
//	double diametr, radius, height, flow[2], current, voltage, resist;
//	double diametr_SI, height_SI, convert_to_SI;
//	vecter position, position_SI, force_on;
//	Field_2D Mag_field;
//	int turns;
//	vecter direction;
//	Coil();
//	Coil(int destiny_of_mag_pixels, double _current, double _diametr,
//		double _height, vecter _position, int _turns);
//	double flow_X_from_mag(Magnet& magnit);
//	vecter Force_from_coil(Magnet mag);
//};
//struct Magnet
//{
//	double strength, diametr, radius, weight, height;
//	double diametr_SI, height_SI, convert_to_SI;
//	
//	vecter position, position_SI, speed, speed_SI, accel, force_on;
//	Field_2D Mag_field;
//	vecter direction;
//	Gas* left;
//	Gas* right;
//	int sight;
//	void relocate(double dtime);
//	Magnet();
//	/*Magnet(int destiny_of_mag_pixels)
//	{
//		convert_to_SI = destiny_of_mag_pixels;
//		position.x_proj = position.y_proj = position.z_proj = speed.x_proj =
//			speed.y_proj = speed.z_proj = weight =
//			direction.x_proj = direction.y_proj = direction.z_proj =
//			force_on.x_proj = force_on.x_proj = force_on.x_proj =
//			accel.x_proj = accel.y_proj = accel.y_proj = 0;
//		cout << "Height: ";
//		cin >> height_SI;
//		height = height_SI*convert_to_SI;
//		cout << "Diametr: ";
//		cin >> diametr_SI;
//		diametr = diametr_SI*convert_to_SI;
//		cout << "Magnet strength: ";
//		cin >> strength;
//		strength = strength / convert_to_SI / 4 / π;
//		cout << "Sight to X axis(1 or -1): ";
//		cin >> sight;
//		Mag_field.magnit = this;
//		radius=diametr/2;
//	}*/
//	Magnet(int destiny_of_mag_pixels, double _strength, double _diametr, double _weight,
//		double _height, vecter _position, vecter _speed, int _sight);
//	void show_field(int cherez_n);
//	/*void Set_Field2D_Conf()
//	{
//		int x, y, z, h, angle, prec_H, prec_R;
//		double len;
//		cout << "Height precision:";
//		cin >> prec_H;
//		cout << "Radial precision:";
//		cin >> prec_R;
//		cout << "X size of field: ";
//		cin >> Mag_field.size_x;
//		cout << "Y size of field: ";
//		cin >> Mag_field.size_y;
//		Mag_field.magnit = this;
//		Mag_field.mult = 1;
//		Mag_field.cells = (Field_cell**)malloc((Mag_field.size_x ) * sizeof(Field_cell*));
//		for (int i = 0; i < (Mag_field.size_x ); i++)
//		{
//			Mag_field.cells[i] = (Field_cell*)malloc((Mag_field.size_y ) * sizeof(Field_cell));
//		}
//		vecter radius, tmp, koltso, cur;
//		koltso.set(0, diametr / 2, 0);
//		cur.set(0, 0, (strength / prec_H * height) * (π * diametr / prec_R));
//		for (x = 0; x < Mag_field.size_x; x++)
//		{
//			for (y = 0; y < Mag_field.size_y; y++)
//			{
//				tmp.set(x, y, 0);
//				Mag_field.cells[x][y].Mag_vec.set(0, 0, 0);
//				for (h = -prec_H / 2; h < prec_H / 2; h++)
//				{
//					koltso.x_proj = h * height / prec_H;
//					for (angle = 0; angle < prec_R; angle++)
//					{
//						radius = tmp - Vec_Rotate_X(koltso, π * 2 / prec_R * angle);
//						len = radius.len();
//						Mag_field.cells[x][y].Mag_vec += ((radius * Vec_Rotate_X(cur, π * 2 / prec_R * angle))* (1 / len / len / len));
//					}
//				}
//				Mag_field.cells[x][y].Mag_vec = Mag_field.cells[x][y].Mag_vec*sight*μ*convert_to_SI;
//				Mag_field.cells[x][y].Mag_vec.z_proj = 0;
//			}
//		}
//		cout << "Field configuration is installed  " << endl;
//		
//	}*/
//	void Set_Field2D_Conf(int prec_H, int prec_R, int _size_x, int _size_y);
//	vecter Mag_Mag_Force(Magnet mag, int H_prec);
//
//};