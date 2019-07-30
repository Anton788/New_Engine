#pragma once
#include <cstdio>
#include <iostream>
#include <math.h>
#include <vecters.h>
#include <map>
#include <time.h>
#include "Table.h"
using namespace std;

#define π 3.14159265358979323846
#define PI 3.14159265358979323846
#define R 8.3144598
#define κ 1.38064852E-023
#define Nav 6.02214129E+023
#define Patm 100000
#define aem 1.660539040E-027

struct Substance {
	Substance(double adiabatical_index,
		long double molecular_mass,
		double molar_mass,
		double Van_der_Vaals_coeff_b,
		double Cv,
		double molecule_cross_section,
		bool active) :

		adiabatical_index(adiabatical_index),
		molecular_mass(molecular_mass),
		molar_mass(molar_mass),
		Van_der_Vaals_coeff_b(Van_der_Vaals_coeff_b),
		Cv(Cv),
		molecule_cross_section(molecule_cross_section),
		is_active(active),
		amount_of_substance(0),
		concentration(0), 
		injection_amount(0)
		{}

	const double adiabatical_index;
	const long double molecular_mass;

	const double molar_mass;
	const double Van_der_Vaals_coeff_b;

	const double Cv;
	double concentration;
	// double mols_amount; // unnecessary???

	double amount_of_substance;
	double injection_amount; //
	const double molecule_cross_section; // sigma
	bool is_active;
};

//struct H2O : public Substance {
//	H2O() : Substance(4 / 3, 18 * aem, 18, /*RANDOM*/ 7, 3 * R, /*RANDOM*/ 7) {}
//};
//
//struct CO2 : public Substance {
//	CO2() : Substance(7 / 5, 44 * aem, 44, /*RANDOM*/ 7, 2.5 * R, /*RANDOM*/ 7) {}
//};
//
//struct N2 : public Substance {
//	N2() : Substance(7 / 5, 28 * aem, 28, /*RANDOM*/ 7, 2.5 * R, /*RANDOM*/ 7) {}
//};
//
//struct H2 : public Substance {
//	H2() : Substance(7 / 5, 2 * aem, 2, /*RANDOM*/ 7, 2.5 * R, /*RANDOM*/ 7) {}
//};
//
//struct CH4 : public Substance {
//	CH4() : Substance(4 / 3, 16 * aem, 16, /*RANDOM*/ 7, 3 * R, /*RANDOM*/ 7) {}
//};



//INCORRECT DATA IN STRUCTURES !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

class Gas {
	// temp variables in order to get bigger operation efficiency
	vector<int> substances_numbers;
	map<int, Substance> composition;
	//vector<Substance*> composition;

	int number_of_substances;
	double time;					// temp time
	double TV_multiplication;		// T * (V-total_molecular_volume)^(R/Cv)
	double total_amount_of_gas;		// summ of ν[i] (total amount of gas in mols)
	double total_molecular_volume;	// summ of bVV[i] * ν[i]
	//ν2[4],						// squares of ν[i]
	double V2;						// squre of V
	double heat_quantity;			// tmp values
	//Eact,							// energy of reaction activation MATRIX - > ACTIVATION_ENERGY (table.h)
	vector<vector<double>> chemical_reaction_speed; // speed of reaction
	//γ[4],							// adiabatical coefficient

	vector<vector<double>> reaction_speed_index;			// constant of reaction speed (collision number)
	//vector<vector<double>> local_reaction_multiplier_index; //!!!! MATRIX -> LOCAL_REACTION_MULTIPLIER_INDEX (table.h)

	double total_Cv;				// total thermal captivity
	double average_Cv;			// average thermal captivity
	//long double mol_mass[4];		// mass of one molecule

	vector<bool> elements_in_gas;

 public:
		//μ[4],						// molar mass
		//aVV[4];					// a coefficient in Van-der-Vaals equation MATRIX -> VANDERVAL_COEFF_A (table.h)
		//bVV[4],					// b coefficient in Van-der-Vaals equation

		//double* stechiometrycal_indexes; //PIZDEC FOR EACH REACTION !!!! MATRIX -> REACTION_EQUATIONS (table.h)

		/* stechiometrycal coefficients in reaction
		for example, 2 * H2 + O2 - 2 * H20 = 0 */
		//Cv[4];					// molar thermal captivities const volume
		
	double P;				// Pressure
	double V;				// Volume
	double T;				// Temperature
			  //burn_energy,	// molar burning energy of the component MATRIX !!!!!!!!!!!!!!!!!!!!!!
			  //C[4],			// concentrations
			  //ν[4],			// amount of mols
	double	area_of_piston;		// sectional area (square) of the piston
	double	area_of_valve;		// sectional area (square) of out valve
	double	T_crit;				// Autoignition temperature //UNNECESSARY
	double	V_crit;				// kostil:(
	double	length_of_piston;	// 
		// InjQnu[4],			// amount of injecting moles
	double	injection_time;		// injecting time
		// σ,					// effective cross section of a molecule
	double	average_mol_mass;	// average molecule mass
	double	injection_temperature; // injecting gas temperature
	int counter, phase;

	// GAS HEREE

	//  loading fuel parametrs 
	//Gas(double* _μ, double* _aVV, double* _bVV, double* _cstech, double* _Cv,
	//	double _V, double _T, double _burnE, double* _ν, double _Eact,
	//	double _area_of_piston, double* _InjQnu, double _injection_time,double _Injtemp, double _σ,
	//	double _area_of_valve, double _T_crit, double _V_crit, int zero_phase)
	//{
	//	σ = _σ;
	//	burnE = _burnE;
	//	Eact = _Eact;
	//	V = _V;
	//	T = _T;
	//	injection_time = _injection_time;
	//	area_of_piston = _area_of_piston;
	//	area_of_valve = _area_of_valve;
	//	T_crit = _T_crit;
	//	V_crit = _V_crit;
	//	phase = zero_phase;
	//	injection_temperature = _Injtemp;
	//	for (int i = 0; i < 4; i++)
	//	{
	//		InjQnu[i] = _InjQnu[i];
	//		μ[i] = _μ[i];
	//		aVV[i] = _aVV[i];
	//		bVV[i] = _bVV[i];
	//		cstech[i] = _cstech[i];
	//		Cv[i] = _Cv[i];
	//		ν[i] = _ν[i];
	//		mol_mass[i] = aem * μ[i];
	//		//γ[i] = R / Cv[i];
	//	}
	//	reset_amount_of_gas();
	//	reset_total_molecular_volume();
	//	reset_total_Cv();
	//	reset_ν2();
	//	reset_Concs();
	//	reset_TV();
	//	counter = 0;
	//	time = 0;
	//	reset_Pressure_by_TV();
	//	cout << "Fuel is loaded" << endl;
	//}

	Gas(double _V, double _T, double _area_of_piston, double _injection_time, double _Injtemp,
		double _area_of_valve, double _V_crit, int start_phase, vector<int> _substances) :
		number_of_substances(_substances.size()),
		elements_in_gas(NUM_OF_ELEMENTS, false)
	{
		substances_numbers = _substances;
		V = _V;
		T = _T;
		injection_time = _injection_time;
		area_of_piston = _area_of_piston;
		area_of_valve = _area_of_valve;
		V_crit = _V_crit;
		phase = start_phase;
		injection_temperature = _Injtemp;
		typedef pair<int, Substance> sub_pair;

		elements_in_gas[0] = true;											  //VACUUM IN GAS (FOR 1-ELEMENT REACTIONS)
		composition.insert(sub_pair(VAKUUM, Substance(0, 0, 0, 0, 0, 0, 1))); //VACUUM IN GAS (FOR 1-ELEMENT REACTIONS)

		for (int i = 0; i < number_of_substances; i++) {

			elements_in_gas[_substances[i]] = true;

			if (_substances[i] == H20) {
				composition.insert(sub_pair(H20, Substance(4 / 3, 18 * aem, 18, /*RANDOM*/ 7, 3 * R, /*RANDOM*/ 7, 1)));
			} else if (_substances[i] == CO2) {
				composition.insert(sub_pair(CO2, Substance(7 / 5, 44 * aem, 44, /*RANDOM*/ 7, 2.5 * R, /*RANDOM*/ 7, 1)));
			} else if (_substances[i] == N2) {
				composition.insert(sub_pair(N2, Substance(7 / 5, 28 * aem, 28, /*RANDOM*/ 7, 2.5 * R, /*RANDOM*/ 7, 1)));
			} else if (_substances[i] == H2) {
				composition.insert(sub_pair(H2, Substance(7 / 5, 2 * aem, 2, /*RANDOM*/ 7, 2.5 * R, /*RANDOM*/ 7, 1)));
			} else if (_substances[i] == CH4) {
				composition.insert(sub_pair(CH4, Substance(4 / 3, 16 * aem, 16, /*RANDOM*/ 7, 3 * R, /*RANDOM*/ 7, 1)));
			} else if (_substances[i] == O2) {
				composition.insert(sub_pair(O2, Substance(7 / 5, 32 * aem, 32, /*RANDOM*/ 7, 2.5 * R, /*RANDOM*/ 7, 1)));
			}

			// INCORRECT DATA IN STRUCTURES !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}


		for (int i = 0; i < NUM_OF_ELEMENTS; i++) {
			for (int j = i; j < NUM_OF_ELEMENTS; j++) {
				for (int k = 0; k < REACTION_EQUATIONS[i][j].second.size(); k++) {
					if (!elements_in_gas[REACTION_EQUATIONS[i][j].second[k].first]) {
						// ADD IN COMPOSITION THIS ELEMENT!!!!!!!!!!!!!!!!!!!!
						//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					}
					elements_in_gas[REACTION_EQUATIONS[i][j].second[k].first] = true;
				}
			}
		}
		
		reset_amount_of_gas();
		reset_total_molecular_volume();
		reset_total_Cv();
		reset_ν2();
		reset_Concs();
		reset_TV();
		counter = 0;
		time = 0;
		reset_Pressure_by_TV();
		cout << "Fuel is loaded" << endl;

	}

	double Force() {
		return (area_of_piston*P);
	}

	// resetting gas parametrs

	void resetTemperatureAdi(double _V) {  // resetting in adiabatical process 
		T = TV_multiplication * exp(-R / average_Cv * log(_V - total_molecular_volume));
		V = _V;
		reset_Pressure_by_TV();
	}

	void reset_Pressure_by_TV() {
		double local_VDV_sum = 0;
		for (auto i = composition.begin(); i != composition.end(); ++i) {
			int j = i->first;
			double amount_molls = i->second.amount_of_substance;
			for (int z  = j; z < NUM_OF_ELEMENTS; ++z) {
				local_VDV_sum += VANDERVAL_COEFF_A[z][j] * amount_molls * amount_molls;
			}
		}
		P = total_amount_of_gas * R * T / (V - total_molecular_volume) -
			local_VDV_sum / (V * V);
		//(aVV[0] * ν2[0] + aVV[1] * ν2[1] + aVV[2] * ν2[2] + aVV[3] * ν2[3]) / (V * V);
	}

	void gas_burning(double dtime, double V_new) {
		double tmp = dQ_GasBurning(dtime);
		T += tmp / total_Cv;
		reset_TV();
		resetTemperatureAdi(V_new);
		reset_Concs();
	}

	//void Pressure_from_bernulli(double pistol_speed,double dtime)
	//{
	//	long double ρ_in, ρ_out;
	//	ρ_out = Patm * average_mol_mass;
	//	ρ_in = ρ_out * exp(log( P / Patm) / 4 * 3);
	//	P = Patm + pow(pistol_speed, 2) / 2 * ρ_in * (pow(area_of_piston / area_of_valve, 2) * ρ_in / ρ_out - 1);
	//}

	// Injecting:

	void dInject( double dtime) {
		for (auto i = composition.begin(); i != composition.end(); i++) {
			i->second.amount_of_substance += i->second.injection_amount * dtime / injection_time;
			//ν[i] += _ν[i] * dtime / injection_time;
		}
		reset_amount_of_gas();
		reset_ν2();
		reset_total_molecular_volume();
		T = injection_temperature;
		reset_Pressure_by_TV();
	}

	void dInject(double dtime, double func(int, int)) {
		int j = 0;
		for (auto i = composition.begin(); i != composition.end(); i++, ++j) {
			i->second.amount_of_substance += i->second.amount_of_substance * dtime / injection_time * func(time, j);
			/*j is costil ITERATOR IS NOT IN LINE
			ν[i] += _ν[i] * dtime / injection_time * func(time, j);*/
		}
		reset_amount_of_gas();
		reset_ν2();
		reset_total_molecular_volume();
		T = injection_temperature;
		reset_Pressure_by_TV();
	}

	// resetting temp values:

	void reset_total_molecular_volume() {
		//total_molecular_volume = bVV[0] * ν[0] + bVV[1] * ν[1] + bVV[2] * ν[2] + bVV[3] * ν[3];
		total_molecular_volume = 0;
		for (auto i = composition.begin(); i != composition.end(); ++i) {
			total_molecular_volume += i->second.Van_der_Vaals_coeff_b * i->second.amount_of_substance;
		}
	}

	void reset_total_Cv(){
		//total_Cv = Cv[0] * ν[0] + Cv[1] * ν[1] + Cv[2] * ν[2] + Cv[3] * ν[3];
		total_Cv = 0;
		for (auto i = composition.begin(); i != composition.end(); ++i) {
			total_Cv += i->second.Cv * i->second.amount_of_substance;
		}
	}

	void reset_amount_of_gas() {
		total_amount_of_gas = 0;
		for (auto i = composition.begin(); i != composition.end(); ++i) {
			total_amount_of_gas += i->second.amount_of_substance;
		}
	}

	void reset_average_Cv() {
		average_Cv = total_Cv / total_amount_of_gas;
	}

	void reset_TV() {
		TV_multiplication= T * exp(log(V - total_molecular_volume) * R /average_Cv); // VERIFY!!!
	}	
	
	void set_average_mol_mass() {
		double local_summ = 0;
		for (auto i = composition.begin(); i != composition.end(); ++i) {
			local_summ += i->second.molar_mass * i->second.amount_of_substance;
		}
		average_mol_mass = local_summ / (total_amount_of_gas * κ * T);
	}

	void reset_ν2() { // NOT REALISED!!!!!! PIZDOS!!!!! STTOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOPPPPPP!!!!!!!
		
		/*for (int i = 0; i < 4; i++) {
			ν2[i] = ν[i] * ν[i];
		}*/
	}

	void reset_Concs() {
		for (auto i = composition.begin(); i != composition.end(); ++i) {
			i->second.concentration = i->second.amount_of_substance / V;
			//C[i] = ν[i] / V;
		}
	}

	void set_NULL(double V_new) {
		for (auto i = composition.begin(); i != composition.end(); ++i) {
			i->second.amount_of_substance = 0;
		}
		// ATTENTION!!!!!!!!!   MAY BE COSTIL HEREEEEEE!!!!!!!!!!!!!!!!!!!!!!!!!!
		//ν[3] = P * V_new / R / injection_temperature; // YES, HERE!!!!!!!!
		T = injection_temperature;
		reset_amount_of_gas();
		reset_Concs();
	}

	void reset_ν_from_concs() {
		for (auto i = composition.begin(); i != composition.end(); ++i) {
			i->second.amount_of_substance = i->second.concentration * V;
			//ν[i] = C[i] * V;
		}
	}

	void total_reset_reaction() {
		
		reset_ν_from_concs();
		reset_amount_of_gas();
		reset_total_Cv();
		reset_average_Cv();
		reset_total_molecular_volume();
		//reset_ν2();

	}
	
	void total_reset_injection() {

		reset_Concs;
		reset_amount_of_gas();
		reset_total_Cv();
		reset_average_Cv();
		reset_total_molecular_volume();
		//reset_ν2();

	}
	// phase resettings:

	void close_out_valve() {
		phase = 0;
	}

	void open_in_valve() {
		phase = 0;
	}

	void close_in_valve() {
		phase = 1;
	}

	void start_adi_compression() 
{
		phase = 2;
	}

	void start_burning(){
		phase = 3;
	}

	void open_out_valve() {
		phase = 4;
	}

	// Gas burning functions

	double dQ_GasBurning(double dtime) {
		set_V_chem();
		double total_Q = 0;

		for (int i = 0; i < NUM_OF_ELEMENTS; i++) {

			double total_reaction_speed_i = 0;
			for (int j = i; j < NUM_OF_ELEMENTS; j++) {
				total_reaction_speed_i += chemical_reaction_speed[i][j] * REACTION_EQUATIONS[i][j].first.first;
			}
			if (composition[i].concentration < total_reaction_speed_i * dtime) {
				//ПРОВЕРКА НА СЛУЧАЙ, ЕСЛИ ВЕЩЕСТВО СГОРЕЛО БОЛЬШЕ, ЧЕМ ПОЛНОСТЬЮ!!!!
				// ПОКА ЗАБИЛИ НА ЭТО, ИБО СЛОЖНО. ДОБАВИЛИ ПРОВЕРКУ НА СЛУЧАЙБ ЕСЛИ РЕАЛЬНО СРАБОТАЕТ ЭТА ЕРЕСЬ:
				cerr << "ERROR (composition[" << i <<  "].concentration < total_reaction_speed_i * dtime) IN dQ_GasBurning \n Concentration less than zero :(\n\n PRESS F\n\n";
				system("pause");
				//sleep(30);
				exit(1);

				/*for (int j = 0; j < NUM_OF_ELEMENTS; j++) {
					total_Q += REACTION_ENERGY[i][j] * V * composition[i].concentration;
				}
				C[2] += C[0] * cstech[2] / cstech[0];
				C[i] = 0;

				C[1] -= chemical_reaction_speed * dtime * cstech[1];
				if (C[1] <= 0)
				{
					C[1] = 0;
				}
				C[3] -= chemical_reaction_speed * dtime * cstech[3];
				if (C[3] <= 0)
				{
					C[3] = 0;
				}

				reset_ν_from_concs();
				reset_total_Cv();
				reset_total_molecular_volume();
				reset_ν2();
				reset_amount_of_gas();
				//return heat_quantity;*/
			}

			/*if (C[0] < chemical_reaction_speed * dtime * cstech[0]) {

				heat_quantity = burnE * V * C[0];
				C[2] += C[0] * cstech[2] / cstech[0];
				C[0] = 0;

				C[1] -= chemical_reaction_speed * dtime * cstech[1];
				if (C[1] <= 0)
				{
					C[1] = 0;
				}
				C[3] -= chemical_reaction_speed * dtime * cstech[3];
				if (C[3] <= 0)
				{
					C[3] = 0;
				}

				reset_ν_from_concs();
				reset_total_Cv();
				reset_total_molecular_volume();
				reset_ν2();
				reset_amount_of_gas();
				return heat_quantity;
			}*/

			for (int j = i; j < NUM_OF_ELEMENTS; j++) {
				if (fabs(chemical_reaction_speed[i][j]) > MIN_SPEED_REACTION) {
					composition[i].concentration -= chemical_reaction_speed[i][j] * dtime *
						REACTION_EQUATIONS[i][j].first.first;
					composition[j].concentration -= chemical_reaction_speed[i][j] * dtime *
						REACTION_EQUATIONS[i][j].first.second;
					for (int k = 0; k < REACTION_EQUATIONS[i][j].second.size(); k++) {
						composition[REACTION_EQUATIONS[i][j].second[k].first].concentration += chemical_reaction_speed[i][j] * dtime *
							REACTION_EQUATIONS[i][j].second[k].second;
					}
					total_Q += chemical_reaction_speed[i][j] * dtime * 
						REACTION_EQUATIONS[i][j].first.first * REACTION_ENERGY[i][j] * V;
				}
			}
		}
		/*
		for (int i = 0; i < 2; i++) {
			C[i] -= chemical_reaction_speed * dtime * cstech[i];
		}
		for (int i = 2; i < 4; i++) {
			C[i] += chemical_reaction_speed * dtime * cstech[i];
		}
		chemical_reaction_speed * dtime * cstech[0] * burnE * V;
		*/

		total_reset_reaction();
		
		return total_Q;
	}

	void set_K_tmp() { // Unnecessary to use (const data)
		/*
		for (int i = 0; i < NUM_OF_ELEMENTS; i++) {
			for (int j = i; j < NUM_OF_ELEMENTS; j++) {
				// Pass
			}
		}
		local_reaction_multiplier_index = Nav * σ * σ *
			sqrt(8 * π * κ * (mol_mass[0] + mol_mass[1]) / (mol_mass[0] * mol_mass[1]));
			*/
	}

	void set_K_chem() {
		for (int i = 0; i < NUM_OF_ELEMENTS; i++) {
			for (int j = i; j < NUM_OF_ELEMENTS; j++) {
				reaction_speed_index[i][j] = LOCAL_REACTION_MULTIPLIER_INDEX[i][j] * sqrt(T) * 
					exp(-ACTIVATION_ENERGY[i][j] / (R * T));
			}
		}
		//reaction_speed_index = local_reaction_multiplier_index * sqrt(T) * exp(-Eact / (R * T));
	}

	void set_V_chem() {
		for (int i = 0; i < NUM_OF_ELEMENTS; i++) {
			for (int j = i; j < NUM_OF_ELEMENTS; j++) {
				if ((composition[i].concentration > 0) && (composition[j].concentration > 0)) {
					set_K_chem();
					chemical_reaction_speed[i][j] = reaction_speed_index[i][j] * 
						exp(log(composition[i].concentration) * REACTION_EQUATIONS[i][j].first.first * 
							log(composition[j].concentration) * REACTION_EQUATIONS[i][j].first.second);
				} else {
					chemical_reaction_speed[i][j] = 0;
				}
			}
		}
		
		/*if ((C[0] > 0) && (C[1] > 0)) {
			set_K_chem();
			chemical_reaction_speed = reaction_speed_index * exp(log(C[0]) * cstech[0] * log(C[1]) * cstech[1]);
		} else chemical_reaction_speed = 0;*/

	}

	// full update
	void GasFullUpdate(double dtime, double V_new, double piston_speed) {
		if (phase == 4) {
			time += dtime;
			if (counter == 0) {
				V = V_new;
				reset_Pressure_by_TV();
				set_average_mol_mass();
				reset_amount_of_gas();
				T = 0.95 * T;
				counter = 1;
			}

			if (abs(V) <= abs(V_new)) {
				P = Patm;
			}

			if ((counter == 3) && (abs(V) > abs(V_new))) {
				counter = 1;
			}

			if (((abs(V) < abs(V_new)) || (V_new < V_crit)) && (counter == 1)) {
				close_out_valve();
				open_in_valve();
				set_NULL(V_new);
				time = 0;
				if ((abs(V) < abs(V_new))) {
					counter = 0;
				} else {
					counter = 3;
				}
			}
			//if (V_new < V)
				/*Pressure_from_bernulli(piston_speed, dtime);*/
			V = V_new;
		}

		if (phase == 3) {
			time += dtime;
			if ((counter == 0) || (counter == 2)) {
				set_K_tmp();
				reset_TV();
				counter++;
			}

			if ((abs(V) > abs(V_new)) && (counter != 3)) {
				counter = 0;
				open_out_valve();
			}

			if ((counter == 3) && (V < V_new)) {
				counter = 1;
			}
			gas_burning(dtime, V_new);
		}

		if (phase == 2) {
			if (counter == 0) {
				reset_TV();
				counter = 1;
			}
			if ((T >= T_crit) || (V <= V_crit) ) {
				start_burning();
				reset_Concs();
				if (((T >= T_crit) || (V <= V_crit)) && (V > V_new)) {
					counter = 2;
				} else {
					counter = 0;
				}
			}
			time += dtime;
			resetTemperatureAdi(V_new);
		}

		if (phase == 1) {
			if (counter == 0) {
				reset_TV();
				counter = 1;
			}

			if ((counter == 3) && (abs(V) < abs(V_new))) {
				reset_TV();
				counter = 1;
			}

			if ((abs(V) > abs(V_new)) && (counter == 1)) {
				start_adi_compression();
				counter = 0;
			}

			time += dtime;
			resetTemperatureAdi(V_new);
		}

		if (phase == 0) {
			time += dtime;
			dInject(dtime);

			if ((counter == 3) && (abs(V) < abs(V_new))) {	
				counter = 1;
			}

			if (time >= injection_time){
				close_in_valve();
				counter = 3;
			}
			/*if ((abs(V) > abs(V_new)) && (counter == 1))
			{
				start_adi_compression();
				counter = 0;
			}*/

			V = V_new;
		}
		
		
	}
};
