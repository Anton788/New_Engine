#pragma once
#include <cstdio>
#include <iostream>
#include <math.h>
#include <vecters.h>
#include <Gas.h>
#include <vector>
//������������ ��� ��������� ��� ���


//����� � Mags_and_coils

typedef struct Field_cell
{
	vecter Mag_vec;

} Field_cell;

//�� Field_cell ���� ����������, ���������� ����� 

class Field_2D { // ��������� ����� ���������� ���� 
public:
	void *magnit;
	// ��������� �� ������ ������������, ���� ����� ��������, � ���� ��������� ����, ����� �������� public

	vector<vector<Field_cell>> cells;
	// ����������, ��� ��������� ������ ������ ����

	int size_x, size_y; // ������� ����, ����� ������� const, �� ������ ����� ����� ��� �������� ����������

	double mult;		// ���� �� ������������, ������� �����

	Field_2D() {};		// ����������� �� ��������� ������������, �� ����� �����, ��� ��� ����� � VS ��������

	Field_2D(size_t size_x, size_t size_y) :	// ���������� ������������
		size_x(size_x),
		size_y(size_y),
		cells(size_x, vector<Field_cell>(size_y))
	{}

	void show_field(int cherez_n);		
	// ����� ������ ���� � ������� (������� ����� ����, ��������� �������� �������� � ������� N-�� ������)
	double Flow_X_flat(double distance, int diametr);
	// ������������ ����� ������� ���� ������ ���� ��������� diametr ���������������� ��� ������� 
	// �� ���������� distance �� ������ ������� � �������� ��������
};


// ������ ���������� �����-����������� Electromagnet, �������� Magnet � Coil (����������� ������� � �������)

class Electromagnet {

public:

	double diametr;			// �������, �������� � �������� ������ ��������� ���������� �� �����
	double radius;			// ���������� �������
	double height;			// ����������
	/* ���������� ��� ��������� const, diametr ������������ ��� ������� � �������� �������� Flow_X_flat */

	double convert_to_SI;	//convert_to_SI �������� const � ������������ �����, ��� ���������� �������� �� �������� ������ � ��
	double diametr_SI;		// �� ��, �� � ��
	double height_SI;		// �� ��, �� � ��
	/* ���������� ��� ��������� const, �� ��� ������������ ����� (������� ������ ������� ��  diametr_SI,
	 �� height_SI ������� ����� ����� ��������), � ����� ����� ���������� ���� � �������� �� Flow_X_flat
	 ��������� ������������ �� ��������. �� �� � ��� �� �����������, ������� �������� � public, �� const
	 */
	vecter position;		// ������� � �������� ��������, ������������ ��� ������� � �������� �������� Flow_X_flat 
	// � ������� ��� ��������������
	vecter position_SI;		// ������� � �������� ��, ����������� ����� ����� �����
	vecter force_on;		// ����, ����������� �� ������. ��� ��������� ����������, ����� ����� ���� ������� 
	// ������� ������������� (�������������� ����, �������� ������) � ��� �� �������� ���������� �� �������� ������ ������
	/* ���������� ��� ��������� ����� �������� �����, ����� � ���������� ����� ���� ������������ ���������� �� ���������
	� ����������� ��������� ������������*/
	Field_2D Mag_field;		// ��������� ���� �������� �����������, �� ��� ����� ������������, � ����� ����� ������������,
	//��� ��������� ����������. ����� ����, � ������ ����� ������������ ������� �������, �� �����, ��� ��� ���������� ����

	//������������
	Electromagnet();
	Electromagnet(int destiny_of_mag_pixels, double _diametr,
		double _height, vecter _position); // ������, ������ ��� ��������, �� ������ ����� �� ���������� � �� �����, �������� ������� ����))0)
	void show_field(int cherez_n);	// ��� �� ����� ���� � ��������� ������ ����� N ������
};
 
// ������ ������� ������
class Magnet : public Electromagnet {

	
	

public:

	vecter speed;			// �������� � �������� �������� ������������ � search_position.h
	vecter accel;			// ��������� � �������� �������� ������������ � search_position.h
	double strength;		// ������������ ���� �������. � ���� ������ ��������� const, ����� ����������� ��� �������
							// ���� �������������� ����� ������� ��������� � ������ �����


	int sight;				// �������, ������� ������� ������ (+-1). Const. ����� ����� �������� ��� ������������ ����
	double weight;			// ��� �������. Const. �������� � public. ���� ����, ������ ����, � ���� ���  �����.

	vecter speed_SI;		// �������� � ��. ����� ��, ������ ����� ��� ������ � ���������� ������������,
							// � ��� �� ������ �������� ������� �� ��� �� ����� ������ 
							// (������ ���� ������, ���� �� ������������� ����� �� �����).

	

	Gas* left;				// ����� �� ���������� �������� � public ��� ���������� ����������� � 
	Gas* right;				// main, � ����� �������������� ����� � ���������� ������������. 


	// ������������
	Magnet();

	Magnet(int destiny_of_mag_pixels, double _strength, double _diametr, double _weight,
		double _height, vecter _position, vecter _speed, int _sight);

	void relocate(double dtime);	// ��������� �������� � ��������� ������� ����� ����� dtime

	void Set_Field2D_Conf(int prec_H, int prec_R, int _size_x, int _size_y);	
	/* ������������ ��������� ���� �� ��� �������� size_x �� size_y � �������� �������� � ����������� ��� � �������. 
	��������� int prec_H, int prec_R � ���� ������ �������� �������� ���������� ����.
	�������� � prec_R �������� ������ ����� � ���������� ��������������, ������� �� ���������� ������� �����, 
	� prec_H � ��������� ����������� ������ � �����, �� ������� ������ �����������.*/

	vecter Mag_Mag_Force(Magnet mag, int H_prec);
	/* ������������ ���� �������������� ���� �������� � ��������� H_prec �� �����������.
	R_prec �� ����� ��������� ���������*/
};

class Coil : public Electromagnet {

	double flow[2];			// ����� ���������� ���� ������ ������� ������ � � ���������� ������ �������

	int turns;				// ���������� ������ � �������. Const.

public:

	double current;			// ��� � �������. ���������� � ����������� �������� ����������� ��������� ���������
	double voltage;			// ����������, ���������� � ������� ��������. ����� ������� ����������� ����� ��� ����������
	double resist;			// ������������� �������������, ������ ������, �� ���������, ���� � ����� ���������� �� �����������. �� �� ���� ��������� ������.
							// ���� ��� �������� ����� ��������� ���, ��� �������� ���������� ����������

	// ������������
	Coil();

	Coil(int destiny_of_mag_pixels, double _current, double _diametr,
		double _height, vecter _position, int _turns);


	void Set_Field2D_Conf(int prec_R, int _size_x, int _size_y); /* USE FIELD MULTIPLYIER (CURRENT) TO CALCULATE REAL FIELD*/ /*FOR NORMAL PRECISION MANY TURNS NEEDED*/

	double flow_X_from_mag(Electromagnet& magnit);	// ����� ���� ������ ��� ������� (� ������ ���������� ������) �� �������
												
	double set_voltage(double dtime);				// ������������ ���������� � ������� ���������� ������

	vecter Force_from_coil(Magnet mag);				// ���� �������������� ������� � ��������

};


// ��������� ������� ��� ������� ������ ���������� ����, ��� �� ��������, ������� � ��������
double Flow_X_flat(Electromagnet mag, double distance, int diametr);

double Flow_X_flat(Field_2D field, double distance, int diametr);

// ������ ������� ������� ���� ���� � ��� ��� � main
/*� main ���� ��������� ��� ����������� ������� � �� ��������� � ������� ����������������, ���������������,
��� � ��� � ��� ��������������� ���� ������� ����, ������������� �������, � ��� ��
��������������� ���������� ������� dtime, �� ���� ������������ �������� �� �������. ����� ������� ����������� "�������" ����
� ����������� �� ���������� ������� dtime, � ������� ���������� � ����������� ��� ���������� ������� 
� ��������� �� ����� � ���� ������� ��� ������, ��� �����.
��������, ������ ����� � main ������������ ���� �������, ����� ��� Coil-� � Magnet-�. ��������� ��� -- ������ �� �����
Set_Field2D_Conf. � ������, ���� ������� ���������, ��� ��������� ������� ���������� �� ��������� ����. 
��������������� ������� ����� time = 0, ����� ��� ������, �� ����, ��� ���� �����.
����� ������� ��� ��� ���������� ������� ����, � ������� ���������� � � � ��������� �������: */
while (!glfwWindowShouldClose(window))
	{
		time += dtime;		// ���������� �������
		clock1++;			//��� �������

		glfwPollEvents();	//��� �������

		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//��� �������
		glClear(GL_COLOR_BUFFER_BIT);			//��� �������


		// Resetting currents in coils
		c2 = S1.flow_X_from_mag(mag_left) - S1.flow_X_from_mag(mag_right);
		S1.current = (c2 - c1) * 100000 / 1.5;
		S2.current = S1.current;
		c1 = c2;
		E += 2 * S1.current * S1.current / 100000 * 1.5;
		if (clock1 < 5)
			E = 0;


		//if ((gas_left.phase == 4) && (dddddd == 0))
		//{
		//	gas_left.P = 1.1 * Patm;
		//}
		//if ((gas_left.phase != 4) && (dddddd == 0))
		//{
		//	dddddd = 1;
		//}
		//*if ((gas_centr.phase == 4) && (abs(mag_left.speed_SI.x_proj) > 10))
		//{
		//	gas_centr.P =  gas_left.P;
		//}*/

		//// resetting forces  

// ��� ������� ���������� ��������� ��� ����, ����������� �� ������:
mag_left.force_on.x_proj = S1.Force_from_coil(mag_left).x_proj + S2.Force_from_coil(mag_left).x_proj +
mag_right.Mag_Mag_Force(mag_left, 100).x_proj - mag_right_static.Mag_Mag_Force(mag_left, 100).x_proj +
mag_left_static.Mag_Mag_Force(mag_left, 100).x_proj -
0 * mag_left.speed_SI.x_proj + gas_left.Force() - gas_centr.Force(); 

//����� ������ ����� ���� � ����� �����:
mag_right.force_on.x_proj = -mag_left.force_on.x_proj;
cout << "Phase L:" << gas_left.phase << " Phase C:" << gas_centr.phase
<< " L Temp:" << gas_left.T - 273 << "  C Temp: " << gas_centr.T - 273
<< " L sp" << mag_left.speed_SI.x_proj << endl;


// relocating pistons:  // ������������ ������ ��� ������, ��������� ������� ��������.
mag_right.relocate(dtime / 1000);
mag_left.relocate(dtime / 1000);

// resetting gases:		// ���������� �����
gas_left.GasFullUpdate(dtime / 1000,
	S_porsh * abs(-0.8 - mag_left.position_SI.x_proj + mag_left.height_SI / 2), abs(mag_left.speed_SI.x_proj));
gas_centr.GasFullUpdate(dtime / 1000,
	2 * S_porsh * abs(-mag_left.position_SI.x_proj + mag_left.height_SI / 2), abs(mag_left.speed_SI.x_proj));




// resetting positions:	// ���������� ��������� ������� ����������� �������� �� ������
mag1.centr.x_proj = mag_left.position_SI.x_proj;
mag2.centr.x_proj = mag_right.position_SI.x_proj;




// graph object's relocating:	// ���������� �������� ����� ������� � �������� �� ������
mag1.reloc();
mag2.reloc();

if (clock1 % 100 == 0)
{
	EDS.reloc(S1.current / 10000 / 2);
}






// Drawing:			// ��������� ����� �����

coil1.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
coil2.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
background.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
mag1.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
mag2.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
magleft_static.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
magright_static.draw(GL_TRIANGLE_FAN, VBO, VAO, ourShader);
EDS.draw(VBO, VAO);
glfwSwapBuffers(window);

}



