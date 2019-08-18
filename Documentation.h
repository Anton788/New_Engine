#pragma once
#include <cstdio>
#include <iostream>
#include <math.h>
#include <vecters.h>
#include <Gas.h>
#include <vector>
//Документация для изменение под ООП


//Начнём с Mags_and_coils

typedef struct Field_cell
{
	vecter Mag_vec;

} Field_cell;

//Тк Field_cell пока тривиально, рассмотрим сразу 

class Field_2D { // двумерная сетка магнитного поля 
public:
	void *magnit;
	// указатель на магнит используется, чтоб извне узнавать, к чему относится поле, лучше оставить public

	vector<vector<Field_cell>> cells;
	// собственно, сам двумерный массив клеток поля

	int size_x, size_y; // размеры поля, можно сделать const, но чтение извне нужно для проверок перекрытия

	double mult;		// пока не задействован, сотрите нафиг

	Field_2D() {};		// конструктор по умолчанию бессмысленен, но пусть будет, ибо так учили и VS ругается

	Field_2D(size_t size_x, size_t size_y) :	// нормальный конструтктор
		size_x(size_x),
		size_y(size_y),
		cells(size_x, vector<Field_cell>(size_y))
	{}

	void show_field(int cherez_n);		
	// метод показа поля в консоль (выводит сетку поля, показывая значение проекций в ккаждой N-ой клетке)
	double Flow_X_flat(double distance, int diametr);
	// рассчитывает поток вектора поля сквозь круг диаметром diametr перпендикулярный оси магнита 
	// на расстоянии distance от начала отсчёта в условных единицах
};


// теперь рассмотрим класс-прародитель Electromagnet, родитель Magnet и Coil (постоянного магнита и катушки)

class Electromagnet {

public:

	double diametr;			// диаметр, очевидно в процессе работы двигателя измениться не может
	double radius;			// предыдущее пополам
	double height;			// аналогично
	/* Предыдущие три параметра const, diametr используется при расчёте в условных единицах Flow_X_flat */

	double convert_to_SI;	//convert_to_SI является const и используется везде, где необходимо переводо из условных единиц в СИ
	double diametr_SI;		// то же, но в СИ
	double height_SI;		// то же, но в СИ
	/* Предыдущие три параметра const, но они используются газом (площадь поршня следует из  diametr_SI,
	 из height_SI следует объём камер сгорания), а также поток магнитного поля в единицах СИ Flow_X_flat
	 считается отталкиваясь от диаметра. Их ни с чем не перепутаешь, следует оставить в public, но const
	 */
	vecter position;		// Позиция в условных единицах, используется при расчёте в условных единицах Flow_X_flat 
	// и расчёте сил взаимодействий
	vecter position_SI;		// Позиция в единицах СИ, испольуется почти везде извне
	vecter force_on;		// Сила, действующая на магнит. Для упрощения вычислений, чтобы можно было вручную 
	// вносить корректировки (дополнительные силы, например трение) а так же упрощать вычисления по третьему закону Ньютна
	/* Предыдущие три параметра можно изменять извне, чтобы в дальнейшем можно было симулировать отклонения от симметрии
	и тестировать алгоритмы стабилизации*/
	Field_2D Mag_field;		// Магнитное поле является константным, но его нужно рассчитывать, а также можно приравнивать,
	//для упрощения вычислений. Более того, в теории может изменятьсяот внешних условий, но слабо, так что пренебрежём этим

	//Конструкторы
	Electromagnet();
	Electromagnet(int destiny_of_mag_pixels, double _diametr,
		double _height, vecter _position); // судьба, потому что опечатка, но больше нигде не фигурирует и не будет, оставьте прикола ради))0)
	void show_field(int cherez_n);	// тот же показ поля в командную строку через N клеток
};
 
// Теперь сыновьи классы
class Magnet : public Electromagnet {

	
	

public:

	vecter speed;			// Скорость в условных единицах используется в search_position.h
	vecter accel;			// Ускорение в условных единицах используется в search_position.h
	double strength;		// Коэрцетивная сила магнита. В ходе работы двигателя const, извне использется при расчёте
							// силы взаимодействия между разными магнитами с разной силой


	int sight;				// Сторона, которой повёрнут магнит (+-1). Const. Извне может читаться для суммирования силы
	double weight;			// Вес магнита. Const. Оставьте в public. Тупо ведь, магнит есть, а веса нет  иначе.

	vecter speed_SI;		// Скорость в СИ. Опять же, доступ извне для тестов и алгоритмов балансировки,
							// а так же крайне наглядно следить за ней во время тестов 
							// (ловить баги физики, чтоб на сверхсветовую ничто не вышло).

	

	Gas* left;				// Опять же желательно оставить в public для расширения функционала в 
	Gas* right;				// main, и будет использоваться извне в алгоритмах балансировки. 


	// Конструкторы
	Magnet();

	Magnet(int destiny_of_mag_pixels, double _strength, double _diametr, double _weight,
		double _height, vecter _position, vecter _speed, int _sight);

	void relocate(double dtime);	// измененин скорости и положения магнита через время dtime

	void Set_Field2D_Conf(int prec_H, int prec_R, int _size_x, int _size_y);	
	/* Рассчитывает магнитное поле по БСВ размером size_x на size_y в условных единицах и привязывает его к магниту. 
	Параметры int prec_H, int prec_R в этом методе являются точность вычисления поля.
	Численно – prec_R является числом углов в правильном многоугольнике, которым мы приближаем круглый виток, 
	а prec_H – удвоенным количеством витков с током, на который магнит разбивается.*/

	vecter Mag_Mag_Force(Magnet mag, int H_prec);
	/* Рассчитывает силу взаимодействия двух магнитов с точностью H_prec по горизонтали.
	R_prec не нужно благодаря симметрии*/
};

class Coil : public Electromagnet {

	double flow[2];			// Поток магнитного поля сквозь катушку сейчас и в предыдущий момент времени

	int turns;				// Количество витков в катушке. Const.

public:

	double current;			// Ток в катушке. Изменяется и считывается внешними алгоритмами контролля двигателя
	double voltage;			// Напряжение, полученное с помощью индукции. Также обязано считываться извне для управления
	double resist;			// Электрическое сопротивление, вообще говоря, не константа, хоть и слабо изменяется от температуры. Но до этих рассчётов далеко.
							// Пока для удобства нихай останется так, для удобства алгоритмов управления

	// Конструкторы
	Coil();

	Coil(int destiny_of_mag_pixels, double _current, double _diametr,
		double _height, vecter _position, int _turns);


	void Set_Field2D_Conf(int prec_R, int _size_x, int _size_y); /* USE FIELD MULTIPLYIER (CURRENT) TO CALCULATE REAL FIELD*/ /*FOR NORMAL PRECISION MANY TURNS NEEDED*/

	double flow_X_from_mag(Electromagnet& magnit);	// Поток поля сквозь всю катушку (с учётом количества витков) от магнита
												
	double set_voltage(double dtime);				// Рассчитывает напряжение с помощью магнитного потока

	vecter Force_from_coil(Magnet mag);				// Сила взаимодействия катушки с магнитом

};


// Следующие функции для расчёта потока магнитного поля, как вы заметили, юзаются в катушках
double Flow_X_flat(Electromagnet mag, double distance, int diametr);

double Flow_X_flat(Field_2D field, double distance, int diametr);

// Теперь следует сказать пару слов о том что в main
/*В main тупо создаются все действующие объекты с их позициями и прочими характеристиками, устанавливается,
кто с кем и как взаимодействует путём задания силы, действующейна объекты, а так же
устанавливается промежуток времени dtime, то есть итерационная точность по времени. Далее следует бесконечный "игровой" цикл
с промежутком по модельному времени dtime, в котором проводятся и повторяются все дальнейшие расчёты 
и выводится на экран в виде графики так быстро, как могут.
Очевидно, первым делом в main записываются сами объекты, такие как Coil-ы и Magnet-ы. Следующий шаг -- обсчёт их полей
Set_Field2D_Conf. В случае, если объекты одинаковы, для упрощения следует приравнять их магнитные поля. 
Устанавливается нулевое время time = 0, далее идёт графон, не лезь, оно тебя сожрёт.
После графона как раз начинается игровой цикл, в котором происходит в сё в следующем порядке: */
while (!glfwWindowShouldClose(window))
	{
		time += dtime;		// Обновление времени
		clock1++;			//для графона

		glfwPollEvents();	//для графона

		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);	//для графона
		glClear(GL_COLOR_BUFFER_BIT);			//для графона


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

// Это вручную записанное выражение для силы, действующей на магнит:
mag_left.force_on.x_proj = S1.Force_from_coil(mag_left).x_proj + S2.Force_from_coil(mag_left).x_proj +
mag_right.Mag_Mag_Force(mag_left, 100).x_proj - mag_right_static.Mag_Mag_Force(mag_left, 100).x_proj +
mag_left_static.Mag_Mag_Force(mag_left, 100).x_proj -
0 * mag_left.speed_SI.x_proj + gas_left.Force() - gas_centr.Force(); 

//Вывод данных может быть в любом месте:
mag_right.force_on.x_proj = -mag_left.force_on.x_proj;
cout << "Phase L:" << gas_left.phase << " Phase C:" << gas_centr.phase
<< " L Temp:" << gas_left.T - 273 << "  C Temp: " << gas_centr.T - 273
<< " L sp" << mag_left.speed_SI.x_proj << endl;


// relocating pistons:  // Перемещаются только два поршня, остальные объекты статичны.
mag_right.relocate(dtime / 1000);
mag_left.relocate(dtime / 1000);

// resetting gases:		// Обновление газов
gas_left.GasFullUpdate(dtime / 1000,
	S_porsh * abs(-0.8 - mag_left.position_SI.x_proj + mag_left.height_SI / 2), abs(mag_left.speed_SI.x_proj));
gas_centr.GasFullUpdate(dtime / 1000,
	2 * S_porsh * abs(-mag_left.position_SI.x_proj + mag_left.height_SI / 2), abs(mag_left.speed_SI.x_proj));




// resetting positions:	// Обновление положений центров графических объектов на экране
mag1.centr.x_proj = mag_left.position_SI.x_proj;
mag2.centr.x_proj = mag_right.position_SI.x_proj;




// graph object's relocating:	// Обновление массивов точек объетов и графиков на экране
mag1.reloc();
mag2.reloc();

if (clock1 % 100 == 0)
{
	EDS.reloc(S1.current / 10000 / 2);
}






// Drawing:			// Отрисовка этого всего

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



