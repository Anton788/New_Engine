#pragma once
#include <iostream>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <math.h>
#include <vecters.h>
#include <Gas.h>
using namespace std;


#define π 3.14159265358979323846
#define μ (1.25663706 / 1000000 )
typedef struct Field_cell
{
	vecter Mag_vec;

} Field_cell;

typedef struct Field_2D
{
	void *magnit;
	Field_cell **cells;
	int size_x, size_y;
	double mult;
}
Field_2D;

typedef struct Magnet
{
	double strength, diametr, radius, weight, height;
	double diametr_SI, height_SI, convert_to_SI;
	
	vecter position, position_SI, speed, speed_SI, accel, force_on;
	Field_2D Mag_field;
	vecter direction;
	Gas* left;
	Gas* right;
	int sight;
	void relocate(double dtime)
	{
		accel = force_on * (1 / weight);
		speed.y_proj = accel.y_proj = speed.z_proj = accel.z_proj = 0;
		position = position + speed*dtime + accel*(dtime*dtime / 2)*convert_to_SI;
		speed = speed + accel*dtime*convert_to_SI;

		speed_SI = speed / convert_to_SI;
		position_SI = position / convert_to_SI;
		
	}
	Magnet()
	{

		cout << "Coordinates of centre: ";
		cin >> position.x_proj >> position.y_proj >> position.z_proj;
		cout << "Speed vector: ";
		cin >> speed.x_proj >> speed.y_proj >> speed.z_proj;
		cout << "Magnit's weight: ";
		cin >> weight;
		cout << "Density of mag pixels: ";
		cin >> convert_to_SI;
		cout << "Height: ";
		cin >> height_SI;
		height = height_SI*convert_to_SI;
		cout << "Diametr: ";
		cin >> diametr_SI;
		diametr = diametr_SI*convert_to_SI;
		//cout << "Magnet's vector of +";
		//cin >>  direction.x_proj >>  direction.y_proj >>  direction.z_proj;
		direction.x_proj = direction.y_proj = direction.z_proj =
			force_on.x_proj = force_on.x_proj = force_on.x_proj =
			accel.x_proj = accel.y_proj = accel.y_proj = 0;

		cout << "Magnet strength: ";
		cin >> strength;
		cout << "Sight to X axis(1 or -1): ";
		cin >> sight;
		Mag_field.magnit = this;
		radius=diametr/2;
	}
	Magnet(int destiny_of_mag_pixels)
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
	}
	Magnet(int destiny_of_mag_pixels, double _strength, double _diametr, double _weight,
		double _height, vecter _position, vecter _speed, int _sight)
	{
		convert_to_SI = destiny_of_mag_pixels;
		position_SI = _position;
		position = _position*convert_to_SI;
		speed_SI = _speed;
		speed = _speed*convert_to_SI;
		weight = _weight;
		direction.x_proj = direction.y_proj = direction.z_proj =
		force_on.x_proj = force_on.x_proj = force_on.x_proj =
		accel.x_proj = accel.y_proj = accel.y_proj = 0;

	
		height_SI = _height;
		height = height_SI*convert_to_SI;
		
		diametr_SI = _diametr;
		diametr = diametr_SI*convert_to_SI;
		
		
		strength = _strength / convert_to_SI / 4 / π;
		sight = _sight;
		radius=diametr/2;
	}
	void show_field(int cherez_n)
	{
		int n = cherez_n;
		cout.width(3);
		cout.precision(3);
		cout.fill('0');
		cout.left;
		cout.fixed;
		cout << " X projection: " << endl << endl;
		for (int x = Mag_field.size_x / n - 1; x >= 0; x--)
		{
			cout << endl;
			for (int y = (Mag_field.size_y / n - 1); y >= 0; y--)
			{

				if ((n*x < height / 2) && (n*y == diametr / 2))
					cout << "  III    ";
				else
					cout << Mag_field.cells[n*x][n*y].Mag_vec.x_proj << "  ";
			}
		}
		cout << endl << endl << endl << " Y projection: " << endl << endl;
		for (int x = Mag_field.size_x / n - 1; x >= 0; x--)
		{
			cout << endl;
			for (int y = (Mag_field.size_y / n - 1); y >= 0; y--)
			{

				if ((n*x < height / 2) && (n*y == diametr / 2))
					cout << "  III    ";
				else
					cout << Mag_field.cells[n*x][n*y].Mag_vec.y_proj << "  ";
			}
		}
	}
	void Set_Field2D_Conf()
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
		//return F;
	}
	void Set_Field2D_Conf(int prec_H, int prec_R, int _size_x, int _size_y)
	{
		int x, y, z, h, angle;
		double len;
		
		cout << "X size of field: " << _size_x << endl;
		Mag_field.size_x = _size_x;
		cout << "Y size of field: " << _size_y << endl;
		Mag_field.size_y = _size_y;
		Mag_field.magnit = this;
		Mag_field.mult = 1;
		Mag_field.cells = (Field_cell**)malloc((Mag_field.size_x ) * sizeof(Field_cell*));
		for (int x = 0; x < (Mag_field.size_x ); x++)
		{
			Mag_field.cells[x] = (Field_cell*)malloc((Mag_field.size_y ) * sizeof(Field_cell));
			for (y = 0; y < Mag_field.size_y; y++)
			{
				Mag_field.cells[x][y].Mag_vec.set(0, 0, 0);
				
			}
		}
		
		vecter radius, tmp, koltso, cur, koltso_rot, cur_rot;
		koltso.set(0, diametr / 2, 0);
		cur.set(0, 0, (strength / prec_H * height) * (π * diametr / prec_R));
		double dheight = height / prec_H / 2 ;
		double dang = 2 * π / prec_R;
		
		for (angle = 0; angle < prec_R; angle++)
		{
			koltso_rot = Vec_Rotate_X(koltso, dang * angle);
			cur_rot = Vec_Rotate_X(cur, dang * angle);
			for (h = -prec_H; h < prec_H; h++)
			{
				koltso_rot.x_proj = (h + 0.5) * dheight;
				for (x = 0; x < Mag_field.size_x; x++)
				{
					for (y = 0; y < Mag_field.size_y; y++)
					{
						tmp.set(x, y, 0);
						radius = tmp - koltso_rot;
						len = radius.len();
						Mag_field.cells[x][y].Mag_vec += ((radius * cur_rot)* (1 / (len * len * len)));
					}
				}
			}

		}

		for (x = 0; x < Mag_field.size_x; x++)
		{
			for (y = 0; y < Mag_field.size_y; y++)
			{
			//	Mag_field.cells[x][y].Mag_vec.z_proj = 0;
				Mag_field.cells[x][y].Mag_vec = Mag_field.cells[x][y].Mag_vec * sight * μ * convert_to_SI;

			}
		}
		cout << "Field configuration is installed  " << endl;
		//return F;
	}
	vecter Mag_Mag_F(Magnet mag, int H_prec)
	{
	//	vecter force;
	//	vecter cur;
	//	force.set(0, 0, 0);
	//	cur.set(0, 0, (strength / H_prec * height * π * diametr));
	//	double dist = abs((position - mag.position).x_proj);
		//double dheight = height / H_prec;
		//if (ceil((height / 2 + abs((position - mag.position).x_proj))) < mag.Mag_field.size_x)
		//	for (int i = -H_prec / 2; i <= H_prec / 2; i++)
		//	{
			//	if ((i * dheight + (position - mag.position).x_proj) >= 0)
			//	{
			//		force += (cur * (mag.Mag_field.cells[lround(i * dheight + dist)]
			//				[lround(diametr / 2)].Mag_vec));
			//	}
			//	else
			//	{
			//		force -= (cur * (mag.Mag_field.cells[lround(i * dheight + dist)]
			//				[lround(diametr / 2)].Mag_vec));
			//	}
			//}

	//	return (force / convert_to_SI);




		vecter force(0, 0, 0), dforce1(0, 0, 0), dforce2(0, 0, 0);
		vecter cur;
		int _x;
		double tmp;
		cur.set(0, 0, (strength / H_prec * height * π * diametr));
		double dist = (position - mag.position).x_proj;
		double dheight = height / H_prec ;
		if (ceil(height / 2 + abs(dist)) < mag.Mag_field.size_x)
			for (int i = -H_prec  / 2; i <= H_prec  / 2; i++)
			{
				_x = lround(floor(abs(i * dheight + dist))) + 1;
				tmp = abs(i * dheight + dist);
				if ((i * dheight + dist) >= 0)
				{
					dforce1.x_proj = (cur*(mag.Mag_field.cells[_x]
						[lround(radius)].Mag_vec)).x_proj;
					dforce2.x_proj = (cur*(mag.Mag_field.cells[_x - 1 ]
						[lround(radius)].Mag_vec)).x_proj;
					force.x_proj += dforce2.x_proj*(_x - tmp) + dforce1.x_proj*(1 - (_x - tmp));
					
				}
				else
				{
					dforce1.x_proj = (cur*(mag.Mag_field.cells[_x]
						[lround(radius)].Mag_vec)).x_proj;
					dforce2.x_proj = (cur*(mag.Mag_field.cells[_x - 1]
						[lround(radius)].Mag_vec)).x_proj;
					force.x_proj -= (dforce2.x_proj*(_x - tmp) + dforce1.x_proj*(1 - (_x - tmp)));
					
				}
			}

		return (force / convert_to_SI);
	}


}
Magnet;

double Flow_X_flat(Magnet mag, double distance, int D)
{
	int x, y;
	double tmp = 0;
	double prm, f1, f2;
	x =  floor(fabs(distance) + 1) ;
	

	if (x < mag.Mag_field.size_x)
	{

		for (y = 1; y <=  D; y++)
		{
			if (!((x <= mag.height / 2) && (((y / 2) == mag.diametr / 2 ) || (((y - 1) / 2) == mag.diametr / 2 ))))
			{
				prm = (mag.Mag_field.cells[x][y / 2].Mag_vec.x_proj + (mag.Mag_field.cells[x][(y - 1) / 2].Mag_vec.x_proj) / 2);
				tmp += prm * π * (y * y -
					(y - 1) * (y - 1)) / 4;
			}
			else tmp += 0;
		}
		f1 = tmp;
		tmp = 0;
		for (y = 1; y <= D; y++)
		{
			if (!((x - 1 <= mag.height / 2) && (((y / 2) == mag.diametr / 2 ) || (((y - 1) / 2) == mag.diametr / 2 ))))
			{
				prm = (mag.Mag_field.cells[x - 1][y / 2].Mag_vec.x_proj + (mag.Mag_field.cells[x - 1][(y - 1) / 2].Mag_vec.x_proj) / 2);
				tmp += prm * π * (y * y  -
					 (y - 1) * (y - 1))/4 ;
			}
			else tmp += 0;
		}
		f2 = tmp;
		tmp = f2*(x - distance) + f1*(1 - (x - distance));
		return tmp;
	}
	else
		return 0;
}

typedef struct Coil
{
	double diametr, radius, height, flow[2], current, voltage, resist;
	double diametr_SI, height_SI, convert_to_SI;
	vecter position,position_SI, force_on;
	Field_2D Mag_field;
	int turns;
	vecter direction;
	Coil()
	{

		cout << "Coordinates of centre: ";
		cin >> position.x_proj >> position.y_proj >> position.z_proj;
		cout << "Density of mag pixels: ";
		cin >> convert_to_SI;
		cout << "Height: ";
		cin >> height_SI;
		height = height_SI*convert_to_SI;
		cout << "Diametr: ";
		cin >> diametr_SI;
		diametr = diametr_SI*convert_to_SI;
		cout << "Number of turns: ";
		cin >> turns;
		radius = diametr / 2;
		current = voltage = flow[1] = flow[0] = direction.x_proj
			= direction.y_proj = direction.z_proj = resist =
			force_on.x_proj = force_on.x_proj = force_on.x_proj = 0;

	}
	Coil(int turns_num, int destiny_of_mag_pixels)
	{
		
	
	convert_to_SI = destiny_of_mag_pixels;

		current = voltage = flow[1] = flow[0] = direction.x_proj
			= direction.y_proj = direction.z_proj = resist =
			force_on.x_proj = force_on.x_proj = force_on.x_proj = 0;

		cout << "Height: ";
		cin >> height_SI;
		height = height_SI*convert_to_SI;
		cout << "Diametr: ";
		cin >> diametr_SI;
		diametr = diametr_SI*convert_to_SI;
		turns = turns_num;
		radius = diametr / 2;

	}
	Coil(int destiny_of_mag_pixels, double _current, double _diametr, 
		double _height, vecter _position, int _turns)
	{
		convert_to_SI = destiny_of_mag_pixels;
		position_SI = _position;
		position = _position*convert_to_SI;
		current = _current;
		height_SI = _height;
		height = height_SI*convert_to_SI;

		diametr_SI = _diametr;
		diametr = diametr_SI*convert_to_SI;
		turns = _turns;
		radius = diametr / 2;
		
	}
	double flow_X_from_mag(Magnet& magnit)
	{
		double tmp = 0, ll, ttmp = (double) height / turns;
		for (int i = -turns / 2; i <= turns / 2; i++)
		{
			ll = (magnit.position - position).x_proj + ttmp * (i + 0.5);
			tmp += Flow_X_flat(magnit, fabs(ll), diametr);
		}
		return (tmp / convert_to_SI / convert_to_SI);
	}
	vecter F_from_coil(Magnet mag)
	{
		vecter force(0, 0, 0), dforce1(0, 0, 0), dforce2(0, 0, 0);
		vecter cur;
		int _x;
		double tmp;
		cur.set(0, 0, (current * π * diametr));
		double dist = (position - mag.position).x_proj;
		double dheight = height / turns;
		if (ceil(height / 2 + abs(dist)) < mag.Mag_field.size_x)
			for (int i = -turns / 2; i <= turns / 2; i++)
			{
				_x = lround(floor(abs(i * dheight + dist))) + 1;
				tmp = abs(i * dheight + dist);
				if ((i * dheight + dist) >= 0)
				{
					dforce1.x_proj = (cur*(mag.Mag_field.cells[_x]
						[lround(radius)].Mag_vec)).x_proj;
					dforce2.x_proj = (cur*(mag.Mag_field.cells[_x - 1 ]
						[lround(radius)].Mag_vec)).x_proj;
					force.x_proj += dforce2.x_proj*(_x - tmp) + dforce1.x_proj*(1 - (_x - tmp));
					
				}
				else
				{
					dforce1.x_proj = (cur*(mag.Mag_field.cells[_x]
						[lround(radius)].Mag_vec)).x_proj;
					dforce2.x_proj = (cur*(mag.Mag_field.cells[_x - 1]
						[lround(radius)].Mag_vec)).x_proj;
					force.x_proj -= (dforce2.x_proj*(_x - tmp) + dforce1.x_proj*(1 - (_x - tmp)));
					
				}
			}

		return (force / convert_to_SI);
	}
}
Coil;
