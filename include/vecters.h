#pragma once
typedef struct vecter
{
	double x_proj, y_proj, z_proj;
	vecter()
	{
		x_proj = 0;
		y_proj = 0;
		z_proj = 0;
	}
	vecter(double x, double y, double z)
	{
		x_proj = x;
		y_proj = y;
		z_proj = z;
	}
	inline double len()
	{
		return sqrt(x_proj*x_proj + y_proj*y_proj + z_proj*z_proj);
	}
	void set(double x, double y, double z)
	{
		x_proj = x;
		y_proj = y;
		z_proj = z;
	}
	inline vecter Rotate_X(double angle)
	{
		vecter tmp;
		tmp.x_proj = x_proj;
		tmp.y_proj = y_proj*cos(angle) - z_proj*sin(angle);
		tmp.z_proj = y_proj*sin(angle) + z_proj*cos(angle);
		return tmp;
	}
	inline vecter Rotate_Y(double angle)
	{
		vecter tmp;
		
		tmp.y_proj = y_proj;
		tmp.x_proj = x_proj*cos(angle) + z_proj*sin(angle);
		tmp.z_proj = -x_proj*sin(angle) + z_proj*cos(angle);
		return tmp;
	}
	inline vecter Rotate_Z(double angle)
	{
		vecter tmp;
		
		tmp.z_proj = z_proj;
		tmp.y_proj = x_proj*sin(angle) + y_proj*cos(angle); 
		tmp.x_proj = x_proj*cos(angle) - y_proj*sin(angle);
		return tmp;
	}
	vecter Rotate(double angle_x, double angle_y, double angle_z)
	{
		return this->Rotate_X(angle_x).Rotate_Y(angle_y).Rotate_Z(angle_z);
	}
} vecter;


inline vecter operator * (vecter a, vecter b)
{
	vecter tmp;
	tmp.x_proj = (a.y_proj * b.z_proj) - (a.z_proj * b.y_proj);
	tmp.y_proj = (a.z_proj * b.x_proj) - (a.x_proj * b.z_proj);
	tmp.z_proj = (a.x_proj * b.y_proj) - (a.y_proj * b.x_proj);
	return tmp;
}
inline vecter operator + (vecter a, vecter b)
{
	vecter tmp;
	tmp.x_proj = a.x_proj + b.x_proj;
	tmp.y_proj = a.y_proj + b.y_proj;
	tmp.z_proj = a.z_proj + b.z_proj;
	return tmp;
}
inline vecter operator - (vecter a, vecter b)
{
	vecter tmp;
	tmp.x_proj = a.x_proj - b.x_proj;
	tmp.y_proj = a.y_proj - b.y_proj;
	tmp.z_proj = a.z_proj - b.z_proj;
	return tmp;
}
inline vecter operator *(vecter a, double b)
{
	vecter tmp;
	tmp.x_proj = a.x_proj * b;
	tmp.y_proj = a.y_proj * b;
	tmp.z_proj = a.z_proj * b;
	return tmp;
}
inline vecter operator /(vecter a, double b)
{
	vecter tmp;
	tmp.x_proj = a.x_proj / b;
	tmp.y_proj = a.y_proj / b;
	tmp.z_proj = a.z_proj / b;
	return tmp;
}
inline vecter operator *(double b, vecter a)
{
	vecter tmp;
	tmp.x_proj = a.x_proj * b;
	tmp.y_proj = a.y_proj * b;
	tmp.z_proj = a.z_proj * b;
	return tmp;
}
inline vecter&  operator *=(vecter &a, const double b)
{

	vecter tmp;
	tmp.x_proj = a.x_proj * b;
	tmp.y_proj = a.y_proj * b;
	tmp.z_proj = a.z_proj * b;
	a = tmp;
	return a;
	
}
inline vecter&  operator /=(vecter &a, const double b)
{

	vecter tmp;
	tmp.x_proj = a.x_proj / b;
	tmp.y_proj = a.y_proj / b;
	tmp.z_proj = a.z_proj / b;
	a = tmp;
	return a;

}
inline double operator & (vecter a, vecter b)
{
	double tmp;
	tmp = a.x_proj * b.x_proj + a.y_proj * b.y_proj + a.z_proj * b.z_proj;
	return tmp;
}
inline vecter&  operator += (vecter &a, vecter b)
{
	vecter tmp;
	tmp.x_proj = a.x_proj + b.x_proj;
	tmp.y_proj = a.y_proj + b.y_proj;
	tmp.z_proj = a.z_proj + b.z_proj;
	a = tmp;
	return a;
}

inline vecter&  operator *= (vecter &a, vecter b)
{
	vecter tmp;
	tmp = a;
	tmp.x_proj = (a.y_proj * b.z_proj) - (a.z_proj * b.y_proj);
	tmp.y_proj = (a.z_proj * b.x_proj) - (a.x_proj * b.z_proj);
	tmp.z_proj = (a.x_proj * b.y_proj) - (a.y_proj * b.x_proj);
	a = tmp;

}
inline  vecter& operator -= (vecter &a, const vecter b)
{
	vecter tmp;
	tmp.x_proj = a.x_proj - b.x_proj;
	tmp.y_proj = a.y_proj - b.y_proj;
	tmp.z_proj = a.z_proj - b.z_proj;
	a = tmp;
	return a;
}
inline vecter Vec_Rotate_X(vecter vec, double angle)
{
	
	vecter tmp;
	tmp.x_proj = vec.x_proj;
	tmp.y_proj = vec.y_proj*cos(angle) - vec.z_proj*sin(angle);
	tmp.z_proj = vec.y_proj*sin(angle) + vec.z_proj*cos(angle);
	return tmp;
}
inline vecter& operator -(vecter vec)
{
 vecter tmp(0,0,0);
tmp-=vec;
return tmp;
}

short sign(double x)
{
	if (x > 0) { return 1; }
	else if (x = 0) { return 0; }
			else return -1;
}