#include "pch.h"
#include <cstdio>
#include <iostream>
#include <math.h>
#include <vecters.h>
#include <Gas.h>
#include <vector>
#include <Mags_and_coils.h>

using namespace std;

Magnet::Magnet() {}

Magnet::Magnet(int destiny_of_mag_pixels, double _diametr,
	double _height, vecter _position) {

	convert_to_SI = destiny_of_mag_pixels;

	position_SI = _position;
	position = _position * convert_to_SI;

	force_on.x_proj = force_on.x_proj = force_on.x_proj = 0;

	height_SI = _height;
	height = height_SI * convert_to_SI;

	diametr_SI = _diametr;
	diametr = diametr_SI * convert_to_SI;

	radius = diametr / 2;
}


Permanent_Magnet::Permanent_Magnet() {

	cout << "Coordinates of centre: ";
	cin >> position.x_proj >> position.y_proj >> position.z_proj;
	cout << "Speed vector: ";
	cin >> speed.x_proj >> speed.y_proj >> speed.z_proj;
	cout << "Magnit's mass: ";
	cin >> weight;
	cout << "Density of mag pixels: ";
	cin >> convert_to_SI;
	cout << "Height: ";
	cin >> height_SI;
	height = height_SI * convert_to_SI;
	cout << "Diametr: ";
	cin >> diametr_SI;
	diametr = diametr_SI * convert_to_SI;
	//cout << "Magnet's vector of +";
	//cin >>  direction.x_proj >>  direction.y_proj >>  direction.z_proj;
	//direction.x_proj = direction.y_proj = direction.z_proj =
		force_on.x_proj = force_on.x_proj = force_on.x_proj =
		accel.x_proj = accel.y_proj = accel.y_proj = 0;

	cout << "Magnet strength: ";
	cin >> strength;
	cout << "Sight to X axis(1 or -1): ";
	cin >> sight;
	Mag_field.magnit = this;
	radius = diametr / 2;
}

Permanent_Magnet::Permanent_Magnet(int destiny_of_mag_pixels, double _strength, double _diametr, double _mass,
	double _height, vecter _position, vecter _speed, int _sight) : Magnet (
		destiny_of_mag_pixels,
		_diametr,
		_height,
		_position)

{
	convert_to_SI = destiny_of_mag_pixels;
	position_SI = _position;
	position = _position * convert_to_SI;
	speed_SI = _speed;
	speed = _speed * convert_to_SI;
	weight = _mass;
	//direction.x_proj = direction.y_proj = direction.z_proj =
	force_on.x_proj = force_on.x_proj = force_on.x_proj =
		accel.x_proj = accel.y_proj = accel.y_proj = 0;


	height_SI = _height;
	height = height_SI * convert_to_SI;

	diametr_SI = _diametr;
	diametr = diametr_SI * convert_to_SI;


	strength = _strength / convert_to_SI / 4 / π;
	sight = _sight;
	radius = diametr / 2;
}

void Permanent_Magnet::relocate(double dtime) {
	accel = force_on * (1 / weight);

	speed.y_proj = accel.y_proj = speed.z_proj = accel.z_proj = 0;

	position = position + speed * dtime + accel * (dtime * dtime / 2) * convert_to_SI;
	position_SI = position / convert_to_SI;

	speed = speed + accel * dtime * convert_to_SI;
	speed_SI = speed / convert_to_SI;
}

void Magnet::show_field(int cherez_n) {
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

void Permanent_Magnet::Set_Field2D_Conf(int prec_H, int prec_R, int _size_x, int _size_y)
{
	int x, y, z, h, angle;
	double len;

	Field_2D New_field(_size_x, _size_y);
	Mag_field = New_field;
	cout << "X size of field: " << _size_x << endl;
	Mag_field.size_x = _size_x;
	cout << "Y size of field: " << _size_y << endl;
	Mag_field.size_y = _size_y;
	Mag_field.magnit = this;
	Mag_field.mult = 1;
	vecter radius, tmp, koltso, cur, koltso_rot, cur_rot;
	koltso.set(0, diametr / 2, 0);
	cur.set(0, 0, (strength / prec_H * height) * (π * diametr / prec_R));
	double dheight = height / prec_H / 2;
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
}

vecter Permanent_Magnet::Mag_Mag_Force(Permanent_Magnet mag, int H_prec)
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
	double dheight = height / H_prec;
	if (ceil(height / 2 + abs(dist)) < mag.Mag_field.size_x)
		for (int i = -H_prec / 2; i <= H_prec / 2; i++)
		{
			_x = lround(floor(abs(i * dheight + dist))) + 1;
			tmp = abs(i * dheight + dist);
			if ((i * dheight + dist) >= 0)
			{
				dforce1.x_proj = (cur*(mag.Mag_field.cells[_x]
					[lround(radius)].Mag_vec)).x_proj;
				dforce2.x_proj = (cur*(mag.Mag_field.cells[_x - 1]
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


Electromagnet::Electromagnet()
{

	cout << "Coordinates of centre: ";
	cin >> position.x_proj >> position.y_proj >> position.z_proj;
	cout << "Density of mag pixels: ";
	cin >> convert_to_SI;
	cout << "Height: ";
	cin >> height_SI;
	height = height_SI * convert_to_SI;
	cout << "Diametr: ";
	cin >> diametr_SI;
	diametr = diametr_SI * convert_to_SI;
	cout << "Number of turns: ";
	cin >> turns;
	radius = diametr / 2;
	//direction.x_proj = direction.y_proj = direction.z_proj =
	current = voltage = flow[1] = flow[0]  = resist =
		force_on.x_proj = force_on.x_proj = force_on.x_proj = 0;

}

Electromagnet::Electromagnet(int destiny_of_mag_pixels, double _current, double _diametr,
	double _height, vecter _position, int _turns) : Magnet(
		destiny_of_mag_pixels,
		_diametr,
		_height,
		_position)
{
	current = _current;
	
	turns = _turns;

}

vecter Electromagnet::Force_from_coil(Permanent_Magnet mag)
{
	vecter force(0, 0, 0), dforce1(0, 0, 0), dforce2(0, 0, 0);
	vecter cur;
	int _x;
	double tmp;
	cur.set(0, 0, (current * π * diametr));
	double dist = (position - mag.position).x_proj;
	double dheight = height / turns;
	if (ceil(height / 2 + abs(dist)) < mag.Mag_field.size_x)
		for (double i = -turns / 2 + 0.5; i < turns / 2; i++)
		{
			_x = lround(floor(abs(i * dheight + dist))) + 1;
			tmp = abs(i * dheight + dist);
			if ((i * dheight + dist) >= 0)
			{
				dforce1.x_proj = (cur*(mag.Mag_field.cells[_x]
					[lround(radius)].Mag_vec)).x_proj;
				dforce2.x_proj = (cur*(mag.Mag_field.cells[_x - 1]
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

double Electromagnet::flow_X_from_mag(Magnet& magnit)
{
	double tmp = 0, ll, ttmp = (double)height / turns;
	for (int i = -turns / 2; i <= turns / 2; i++)
	{
		ll = (magnit.position - position).x_proj + ttmp * (i + 0.5);
		tmp += Flow_X_flat(magnit, fabs(ll), diametr);
	}
	return (tmp / convert_to_SI / convert_to_SI);
}

double Electromagnet::set_voltage(double dtime) {
	voltage = (flow[1] - flow[0]) / dtime;
	return voltage;
}

void Electromagnet::Set_Field2D_Conf(int prec_R, int _size_x, int _size_y) /* USE FIELD MULTIPLYIER (CURRENT) TO CALCULATE REAL FIELD*/{
	int x, y, z, angle;
	double len, h;

	Field_2D New_field(_size_x, _size_y);
	Mag_field = New_field;
	cout << "X size of field: " << _size_x << endl;
	Mag_field.size_x = _size_x;
	cout << "Y size of field: " << _size_y << endl;
	Mag_field.size_y = _size_y;
	Mag_field.magnit = this;
	Mag_field.mult = 1;
	vecter radius, tmp, koltso, cur, koltso_rot, cur_rot;
	koltso.set(0, diametr / 2, 0);
	cur.set(0, 0, (π * diametr / prec_R));
	double dheight = height / turns;
	double dang = 2 * π / prec_R;
	for (angle = 0; angle < prec_R; angle++)
	{
		koltso_rot = Vec_Rotate_X(koltso, dang * angle);
		cur_rot = Vec_Rotate_X(cur, dang * angle);
		for (h = -turns / 2 + 0.5; h < turns / 2; h++) ///AHTUNG!!!FOR NORMAL PRECISION A LOT OF TURNS NEEDED!!!
		{
			koltso_rot.x_proj = h * dheight;
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
			Mag_field.cells[x][y].Mag_vec = Mag_field.cells[x][y].Mag_vec * μ * convert_to_SI;

		}
	}
	cout << "Field configuration is installed  " << endl;
};


double Flow_X_flat(Magnet mag, double distance, int diametr)
{
	int x, y;
	double tmp = 0;
	double prm, f1, f2;
	x = floor(fabs(distance) + 1);


	if (x < mag.Mag_field.size_x)
	{

		for (y = 1; y <= diametr; y++) {
			if (!((x <= mag.height / 2) && (((y / 2) == mag.diametr / 2)
				|| (((y - 1) / 2) == mag.diametr / 2)))) {

				prm = (mag.Mag_field.cells[x][y / 2].Mag_vec.x_proj + (mag.Mag_field.cells[x][(y - 1) / 2].Mag_vec.x_proj) / 2);
				tmp += prm * π * (y * y - (y - 1) * (y - 1)) / 4;
			}
			else tmp += 0;
		}

		f1 = tmp;

		tmp = 0;

		for (y = 1; y <= diametr; y++) {
			if (!((x - 1 <= mag.height / 2) && (((y / 2) == mag.diametr / 2)
				|| (((y - 1) / 2) == mag.diametr / 2)))) {

				prm = (mag.Mag_field.cells[x - 1][y / 2].Mag_vec.x_proj + (mag.Mag_field.cells[x - 1][(y - 1) / 2].Mag_vec.x_proj) / 2);
				tmp += prm * π * (y * y - (y - 1) * (y - 1)) / 4;
			}
			else tmp += 0;
		}

		f2 = tmp;

		tmp = f2 * (x - distance) + f1 * (1 - (x - distance));

		return tmp;
	}
	else
		return 0;
}
// дописать градиент потока
double Flow_X_flat(Field_2D field, double distance, int diametr) /*AHTUNG!!!WITHOUT CHEKING INF*/ {
	int x, y;
	double tmp = 0;
	double prm, f1, f2;
	x = floor(fabs(distance) + 1);


	if (x < field.size_x)
	{
		for (y = 1; y <= diametr; y++) {
			prm = (field.cells[x][y / 2].Mag_vec.x_proj + (field.cells[x][(y - 1) / 2].Mag_vec.x_proj) / 2);
			tmp += prm * π * (y * y - (y - 1) * (y - 1)) / 4;
		}

		f1 = tmp;

		tmp = 0;

		for (y = 1; y <= diametr; y++) {
			prm = (field.cells[x - 1][y / 2].Mag_vec.x_proj + (field.cells[x - 1][(y - 1) / 2].Mag_vec.x_proj) / 2);
			tmp += prm * π * (y * y - (y - 1) * (y - 1)) / 4;
		}

		f2 = tmp;

		tmp = f2 * (x - distance) + f1 * (1 - (x - distance));

		return tmp;
	}
	else
		return 0;
}


double Field_2D::Flow_X_flat(double distance, int diametr) {

	int x, y;

	double tmp = 0;

	double prm, f1, f2;

	x = floor(fabs(distance) + 1);

	if (x < size_x) {
		for (y = 1; y <= diametr; y++) {
			prm = (cells[x][y / 2].Mag_vec.x_proj + (cells[x][(y - 1) / 2].Mag_vec.x_proj) / 2);
			tmp += prm * π * (y * y - (y - 1) * (y - 1)) / 4;
		}

		f1 = tmp;

		tmp = 0;

		for (y = 1; y <= diametr; y++) {
			prm = (cells[x - 1][y / 2].Mag_vec.x_proj + (cells[x - 1][(y - 1) / 2].Mag_vec.x_proj) / 2);
			tmp += prm * π * (y * y - (y - 1) * (y - 1)) / 4;
		}

		f2 = tmp;

		tmp = f2 * (x - distance) + f1 * (1 - (x - distance));

		return tmp;
	}
	else
		return 0;
}

void Field_2D::show_field(int cherez_n) {
	int n = cherez_n;
	cout.width(3);
	cout.precision(3);
	cout.fill('0');
	cout.left;
	cout.fixed;
	cout << " X projection: " << endl << endl;
	for (int x = size_x / n - 1; x >= 0; x--) {
		cout << endl;
		for (int y = (size_y / n - 1); y >= 0; y--) {
			/*if ((n*x < ((Magnet*)magnit)->height / 2) && (n*y == ((Magnet*)magnit)->diametr / 2))
				cout << "  III    ";
			else*/
			cout << cells[n*x][n*y].Mag_vec.x_proj << "  ";
		}
	}
	cout << endl << endl << endl << " Y projection: " << endl << endl;
	for (int x = size_x / n - 1; x >= 0; x--) {
		cout << endl;
		for (int y = (size_y / n - 1); y >= 0; y--) {
			/*if ((n*x < ((Magnet*)magnit)->height / 2) && (n*y == ((Magnet*)magnit)->diametr / 2))
				cout << "  III    ";
			else*/
			cout << cells[n*x][n*y].Mag_vec.y_proj << "  ";
		}
	}
}

void Coil_System::update(double dtime)
{
}
