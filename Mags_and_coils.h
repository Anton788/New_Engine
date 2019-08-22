#pragma once
#include <cstdio>
#include <iostream>
#include <math.h>
#include <vecters.h>
#include <Gas.h>
#include <vector>

using namespace std;


#define π 3.14159265358979323846
#define μ (1.25663706 / 1000000 )
typedef struct Field_cell
{
	vecter Mag_vec;
	vector<vecter> jacobian;
	Field_cell() : jacobian(3) {

	}
	Field_cell operator +(Field_cell & cell) {
		Field_cell tmp = *this;
		tmp.Mag_vec += cell.Mag_vec;
		for (unsigned int i = 0; i < 3; i++) {
			tmp.jacobian[i] += cell.jacobian[i];
		}
		return tmp;
	}
	void show()
	{
		cout << Mag_vec.x_proj << "	" << Mag_vec.y_proj << "	" << Mag_vec.z_proj << endl;
	}
	
} Field_cell;

Field_cell approx(Field_cell first, Field_cell cells[4], double dx, double dy) {
	Field_cell tmp = first;
	tmp.Mag_vec += first.jacobian[0] * dx + first.jacobian[1] * dy;
	for (int i = 0; i < 3; i++) {
		if ((dx > 0) && (dy > 0)) {
			tmp.jacobian[i] = (1 - dx) * first.jacobian[i] + dx * cells[0].jacobian[i];
		}
		if ((dx < 0) && (dy > 0)) {
			tmp.jacobian[i] = (1 - dx) * first.jacobian[i] + dx * cells[1].jacobian[i];
		}
		if ((dx < 0) && (dy < 0)) {
			tmp.jacobian[i] = (1 - dx) * first.jacobian[i] + dx * cells[2].jacobian[i];
		}
		if ((dx > 0) && (dy < 0)) {
			tmp.jacobian[i] = (1 - dx) * first.jacobian[i] + dx * cells[3].jacobian[i];
		}
		
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

class Full_Field_Line {
public:
	vector<Field_cell> up;
	vector<Field_cell> down;
	Field_cell& operator [](int y) {
		if (y > 0) {
			return (up[y]);
		}
		else {
			return (down[-y]);
		}
	}
	/*vecter operator [](double y) {
		if (y > 0) {
			return (up[y].Mag_vec);
		}
		else {
			return (down[-y].Mag_vec);
		}
	}*/
	Full_Field_Line() {};
	Full_Field_Line(int size_y) :up(size_y), down(size_y) {}
};

class Full_Field {
public:
	vecter center_coord;

	int size_x, size_y;

	vector<Full_Field_Line> left;
	vector<Full_Field_Line> right;

	Full_Field_Line& operator [] (int x)
	{
		if (x >= 0) {
			return (right[x]);
		}
		else {
			return (left[-x]);
		}
	};
	Full_Field() {};
	Full_Field(Electromagnet magnet) :
		size_x(magnet.Mag_field.size_x),
		size_y(magnet.Mag_field.size_y),
		center_coord(magnet.position),
		left(magnet.Mag_field.size_x, Full_Field_Line(size_y)),
		right(magnet.Mag_field.size_x, Full_Field_Line(size_y)) {
		for (int x = 0; x++; x < magnet.Mag_field.size_x) {
			for (int y = 0; y++; y < magnet.Mag_field.size_y) {
				right[x].up[y].Mag_vec = magnet.Mag_field.cells[x][y].Mag_vec;

				right[x].down[y].Mag_vec = magnet.Mag_field.cells[x][y].Mag_vec;
				right[x].down[y].Mag_vec.y_proj = -magnet.Mag_field.cells[x][y].Mag_vec.y_proj;

				left[x].down[y].Mag_vec = magnet.Mag_field.cells[x][y].Mag_vec;

				left[x].up[y].Mag_vec = -right[x].down[y].Mag_vec;
			}
		}
	}
	Full_Field(int size_x, int size_y) :
		size_x(size_x),
		size_y(size_y),
		left(size_x, size_y),
		right(size_x, size_y)
	{
		for (int i = 0; i < size_x; i++) {
			for (int k = 0; k < size_y; k++) {
				right[i].up[k].Mag_vec.set(1, 1, 0);
				left[i].up[k].Mag_vec.set(-1, 1, 0);
				left[i].down[k].Mag_vec.set(-1, -1, 0);
				right[i].down[k].Mag_vec.set(1, -1, 0);
			}
		};
	};
	Full_Field &operator + (Full_Field Field2) {
		int tmp_x, tmp_y;
		tmp_x = (size_x + Field2.size_x + abs(center_coord.x_proj - Field2.center_coord.x_proj)) / 2;
		tmp_y = (size_y + Field2.size_y + abs(center_coord.y_proj - Field2.center_coord.y_proj)) / 2;
		Full_Field tmp(tmp_x, tmp_y);
		tmp.center_coord.x_proj = min(center_coord.x_proj + size_x, Field2.center_coord.x_proj + Field2.size_x) - tmp_x;
		tmp.center_coord.y_proj = min(center_coord.y_proj + size_y, Field2.center_coord.y_proj + Field2.size_y) - tmp_y;
		for (int _x = -tmp_x + 1; _x < tmp_x; _x++) {
			for (int _y = -tmp_y + 1; _y < tmp_y; _y++) {
				tmp[_x][_y] = (*this)[ -center_coord.x_proj + tmp.center_coord.x_proj + _x][-center_coord.y_proj + tmp.center_coord.y_proj + _y] +
					Field2[-Field2.center_coord.x_proj + tmp.center_coord.x_proj + _x][-Field2.center_coord.y_proj + tmp.center_coord.y_proj + _y];
			}
		}//APROX SUKAAAAAAA!HHH!UG!GY!TYGTY!GU!U!UY!G!G!GG!UG!UGIY!GIYT!TYU !DYTCdrRYDY R@RD !@D Y Yut @# @#H VV@ T YDCV  #uV#H#$gh

	}
};

class Electromagnet {

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
	Electromagnet();
	Electromagnet(int destiny_of_mag_pixels, double _diametr,
		double _height, vecter _position);
	void show_field(int cherez_n);
};

class Magnet : public Electromagnet {

	double strength;		
				

public:

	int sight;
	double weight;

	vecter speed_SI;
	vecter speed;
	vecter accel;
	
	Gas* left;
	Gas* right;

	Magnet();

	Magnet(int destiny_of_mag_pixels, double _strength, double _diametr, double _weight,
		double _height, vecter _position, vecter _speed, int _sight);
	 
	void show_field(int cherez_n);

	void relocate(double dtime);

	void Set_Field2D_Conf(int prec_H, int prec_R, int _size_x, int _size_y);

	vecter Mag_Mag_Force(Magnet mag, int H_prec);
};

class Coil : public Electromagnet {

	double flow[2];

	int turns;

public:

	double current;
	double voltage;
	double resist;

	Coil();

	Coil(int destiny_of_mag_pixels, double _current, double _diametr,
		double _height, vecter _position, int _turns);

	void Set_Field2D_Conf(int prec_R, int _size_x, int _size_y); /* USE FIELD MULTIPLYIER (CURRENT) TO CALCULATE REAL FIELD*/ /*FOR NORMAL PRECISION MANY TURNS NEEDED*/

	double flow_X_from_mag(Electromagnet& magnit);

	double set_voltage(double dtime);

	vecter Force_from_coil(Magnet mag);
};

class Coil_System {

	int coil_num;

	vector<Coil*> coils;

	vector<vector<double>> inductive_coupling;

	Coil_System();
	Coil_System(int num_of_coils, Coil coil1, ...);

	int set_coupling();		// returns 1 if coupling calculated correctly, else 0

	void update(double dtime);
};



double Flow_X_flat(Electromagnet mag, double distance, int diametr);

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