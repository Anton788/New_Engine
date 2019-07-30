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

} Field_cell;

class Field_2D {
public:
	void *magnit;
	vector<vector<Field_cell>> cells;
	//Field_cell **cells;
	int size_x, size_y;
	double mult;
	Field_2D() {};
	Field_2D(size_t size_x, size_t size_y):
	size_x(size_x),
	size_y(size_y), 
	cells(size_x, vector<Field_cell>(size_y)) 
	{}
};

struct Magnet
{
	double strength, diametr, radius, weight, height;
	double diametr_SI, height_SI, convert_to_SI;
	
	vecter position, position_SI, speed, speed_SI, accel, force_on;
	Field_2D Mag_field;
	vecter direction;
	Gas* left;
	Gas* right;
	int sight;
	void relocate(double dtime);
	Magnet();
	/*Magnet(int destiny_of_mag_pixels)
	{
		convert_to_SI = destiny_of_mag_pixels;
		position.x_proj = position.y_proj = position.z_proj = speed.x_proj =
			speed.y_proj = speed.z_proj = weight =
			direction.x_proj = direction.y_proj = direction.z_proj =
			force_on.x_proj = force_on.x_proj = force_on.x_proj =
			accel.x_proj = accel.y_proj = accel.y_proj = 0;
		cout << "Height: ";
		cin >> height_SI;
		height = height_SI*convert_to_SI;
		cout << "Diametr: ";
		cin >> diametr_SI;
		diametr = diametr_SI*convert_to_SI;
		cout << "Magnet strength: ";
		cin >> strength;
		strength = strength / convert_to_SI / 4 / π;
		cout << "Sight to X axis(1 or -1): ";
		cin >> sight;
		Mag_field.magnit = this;
		radius=diametr/2;
	}*/
	Magnet(int destiny_of_mag_pixels, double _strength, double _diametr, double _weight,
		double _height, vecter _position, vecter _speed, int _sight);
	void show_field(int cherez_n);
	/*void Set_Field2D_Conf()
	{
		int x, y, z, h, angle, prec_H, prec_R;
		double len;
		cout << "Height precision:";
		cin >> prec_H;
		cout << "Radial precision:";
		cin >> prec_R;
		cout << "X size of field: ";
		cin >> Mag_field.size_x;
		cout << "Y size of field: ";
		cin >> Mag_field.size_y;
		Mag_field.magnit = this;
		Mag_field.mult = 1;
		Mag_field.cells = (Field_cell**)malloc((Mag_field.size_x ) * sizeof(Field_cell*));
		for (int i = 0; i < (Mag_field.size_x ); i++)
		{
			Mag_field.cells[i] = (Field_cell*)malloc((Mag_field.size_y ) * sizeof(Field_cell));
		}
		vecter radius, tmp, koltso, cur;
		koltso.set(0, diametr / 2, 0);
		cur.set(0, 0, (strength / prec_H * height) * (π * diametr / prec_R));
		for (x = 0; x < Mag_field.size_x; x++)
		{
			for (y = 0; y < Mag_field.size_y; y++)
			{
				tmp.set(x, y, 0);
				Mag_field.cells[x][y].Mag_vec.set(0, 0, 0);
				for (h = -prec_H / 2; h < prec_H / 2; h++)
				{
					koltso.x_proj = h * height / prec_H;
					for (angle = 0; angle < prec_R; angle++)
					{
						radius = tmp - Vec_Rotate_X(koltso, π * 2 / prec_R * angle);
						len = radius.len();
						Mag_field.cells[x][y].Mag_vec += ((radius * Vec_Rotate_X(cur, π * 2 / prec_R * angle))* (1 / len / len / len));
					}
				}
				Mag_field.cells[x][y].Mag_vec = Mag_field.cells[x][y].Mag_vec*sight*μ*convert_to_SI;
				Mag_field.cells[x][y].Mag_vec.z_proj = 0;
			}
		}
		cout << "Field configuration is installed  " << endl;
		
	}*/
	void Set_Field2D_Conf(int prec_H, int prec_R, int _size_x, int _size_y);
	vecter Mag_Mag_F(Magnet mag, int H_prec);

};

double Flow_X_flat(Magnet mag, double distance, int D);

struct Coil
{
	double diametr, radius, height, flow[2], current, voltage, resist;
	double diametr_SI, height_SI, convert_to_SI;
	vecter position,position_SI, force_on;
	Field_2D Mag_field;
	int turns;
	vecter direction;
	Coil();
	Coil(int destiny_of_mag_pixels, double _current, double _diametr,
		double _height, vecter _position, int _turns);
	double flow_X_from_mag(Magnet& magnit);
	vecter F_from_coil(Magnet mag);
};
