

#include "stdafx.h"
#include <Mags_and_coils.h>
#include <mags_and_coils.cpp>


using namespace std;

int main() {
	vecter position(0.5, 0, 0);			// координата
	vecter speed(0, 0, 0);				// скорость
	int side = 1;						// полюс магнита по направлению x
	int density_of_mag_pixels = 200;	// плотность точек сетки поля (точек на метр)
	int coercitivity = 1000000;			// коэрцетивная сила -- сила магнита
	double diametr = 0.1;				// диаметр			
	double height = 0.1;				// высота
	double mass = 1;					// масса магнита
	Magnet magnit1(density_of_mag_pixels, coercitivity, diametr, mass, height, position, speed, side); // конструктор
	Magnet magnit2(density_of_mag_pixels, coercitivity, diametr, mass, height, -position, speed, -side); // конструктор

	int H_precision = 40;				// точность расчёта по высоте магнита -- количество слоёв в модели магнита из колец с током
	int R_precision = 80;				// точность расчёта по углу -- аппрокимация витка N-угольником
	int x_size = 200;					// колличество ячеек в сетке поля по горизонтали
	int y_size = 80;					// колличество ячеек поля во вертикали
	magnit1.Set_Field2D_Conf(H_precision, R_precision, x_size, y_size); // задание магнитного поля
	magnit2.Set_Field2D_Conf(H_precision, R_precision, x_size, y_size); // задание магнитного поля
	magnit1.show_field(20);				// показ поля в консоли
	vecter sensor_pos(0,0.2,0);
	if (search_position(sensor_pos,magnit1,magnit2) = position){
		cout<< "It is working nafig"<<endl;
	} else cout << "Vi ne ochen. Perepisivaite kod";
	getchar(); getchar();

}
