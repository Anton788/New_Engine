#pragma once
#include <iostream>
#include <iostream>
#include <cstdio>
#include <iostream>
#include <math.h>
#include <vecters.h>
using namespace std;
#define π 3.14159265358979323846
#define R 8.3144598
#define κ 1.38064852E-023
#define Nav 6.02214129E+023
#define Patm 100000
#define aem 1.660539040E-027

class Gas
{

	// temp variables in order to get bigger operation efficiency
	double time;		// temp time
	double
		TV,				// T * (V-bVVν_sum)^(R/Cv)
		ν_sum,			// summ of ν[i]
		bVVν_sum,		// summ of bVV[i] * ν[i]
		ν2[4],			// squares of ν[i]
		V2,				// squre of V
		F, tmp,			// tmp values
		Eact,			// energy of reaction activation
		vchem,			// speed of reaction
		γ[4],				// adiabatical coefficient
		kchem, k_tmp,	// constant of reaction speed (collision number)
		Cvν_sum;		// total thermal captivity
	long double 		mol_mass[4];	// mass of one molecule
public:
	double
		μ[4],			// molar mass
		aVV[4],			// a coefficient in Van-der-Vaals equation
		bVV[4],			// b coefficient in Van-der-Vaals equation
		cstech[4],		/* stoichiometrycal coefficients in reaction
						for example, 2 * H2 + O2 - 2 * H20 = 0 */
		Cv[4];			// molar thermal captivities const volume

	double
		P,				// Pressure
		V,				// Volume
		T,				// Temperature
		burnE,			// molar burning energy of the FIRST component
		C[4],			// concentrations
		ν[4],			// amount of mols
		S_pi,			// sectional area (square) of the piston
		S_valve,		// sectional area (square) of out valve
		T_crit,			// Autoignition temperature
		V_crit,
		L_pi,			// 
		InjQnu[4],		// amount of injecting moles
		Injtime,		// injecting time
		σ,				// effective cross section of a molecule
		av_mm,			// average molecule mass
		InjTemperature; // injecting gas temperature
	int counter, phase;

	//  loading fuel parametrs 
	Gas(double* _μ, double* _aVV, double* _bVV, double* _cstech, double* _Cv,
		double _V, double _T, double _burnE, double* _ν, double _Eact,
		double _S_pi, double* _InjQnu, double _Injtime,double _Injtemp, double _σ,
		double _S_valve, double _T_crit, double _V_crit, int zero_phase)
	{
		σ = _σ;
		burnE = _burnE;
		Eact = _Eact;
		V = _V;
		T = _T;
		Injtime = _Injtime;
		S_pi = _S_pi;
		S_valve = _S_valve;
		T_crit = _T_crit;
		V_crit = _V_crit;
		phase = zero_phase;
		InjTemperature = _Injtemp;
		for (int i = 0; i < 4; i++)
		{
			InjQnu[i] = _InjQnu[i];
			μ[i] = _μ[i];
			aVV[i] = _aVV[i];
			bVV[i] = _bVV[i];
			cstech[i] = _cstech[i];
			Cv[i] = _Cv[i];
			ν[i] = _ν[i];
			mol_mass[i] = aem * μ[i];
			//γ[i] = R / Cv[i];
		}
		reset_νsum();
		reset_bVVν_sum();
		reset_Cvν_sum();
		reset_ν2();
		reset_Concs();
		reset_TV();
		counter = 0;
		time = 0;
		reset_Pressure_by_TV();
		cout << "Fuel is loaded" << endl;
	}
	double Force()
	{
		return (S_pi*P);
	}

	// resetting gas parametrs

	void resetTemperatureAdi(double _V)  // resetting in adiabatical process 
	{
		
		T = TV * exp(-R / Cv[0] * log(_V - bVVν_sum));
		V = _V;
		reset_Pressure_by_TV();
	}
	void reset_Pressure_by_TV()
	{
		P = ν_sum * R * T / (V - bVVν_sum) -
			(aVV[0] * ν2[0] + aVV[1] * ν2[1] + aVV[2] * ν2[2] + aVV[3] * ν2[3]) / (V * V);
	}
	void gas_burning(double dtime, double V_new)
	{
		
		tmp = dQ_GasBurning(dtime);
	
		T += tmp / Cvν_sum;
		reset_TV();
		resetTemperatureAdi(V_new);
		reset_Concs();
	}
	void Pressure_from_bernulli(double pistol_speed,double dtime)
	{
		long double ρ_in, ρ_out;
		ρ_out = Patm * av_mm;

		ρ_in = ρ_out * exp(log( P / Patm) / 4 * 3);
		P = Patm + pow(pistol_speed, 2) / 2 * ρ_in * (pow(S_pi / S_valve, 2) * ρ_in / ρ_out - 1);
	}

	// Injecting:

	void dInject(double _ν[4], double dtime)
	{
		for (int i = 0; i < 4; i++)
		{
			ν[i] += _ν[i] * dtime / Injtime;
		}
		reset_νsum();
		reset_ν2();
		reset_bVVν_sum();
		T = InjTemperature;
		reset_Pressure_by_TV();

	}
	void dInject(double _ν[4], double dtime, int func(int, int))
	{

		for (int i = 0; i < 4; i++)
		{
			ν[i] += _ν[i] * dtime / Injtime * func(time, i);
		}
		reset_νsum();
		reset_ν2();
		reset_bVVν_sum();
		T = InjTemperature;
		reset_Pressure_by_TV();
	}

	// resetting temp values:

	void reset_bVVν_sum()
	{
		bVVν_sum = bVV[0] * ν[0] + bVV[1] * ν[1] + bVV[2] * ν[2] + bVV[3] * ν[3];
	}
	void reset_Cvν_sum()
	{
		Cvν_sum = Cv[0] * ν[0] + Cv[1] * ν[1] + Cv[2] * ν[2] + Cv[3] * ν[3];
	}
	void reset_TV()
	{
		TV = T * exp(log(V - bVVν_sum) * R / Cv[0]);
	}
	void set_av_mm()
	{
		av_mm = (mol_mass[3] * ν[3] + mol_mass[1] * ν[1] + mol_mass[2] * ν[2] + mol_mass[0] * ν[0]) / (ν_sum * κ * T);
	}
	void reset_νsum()
	{
		ν_sum = ν[0] + ν[1] + ν[2] + ν[3];
	}
	void reset_ν2()
	{
		for (int i = 0; i < 4; i++)
		{
			ν2[i] = ν[i] * ν[i];
		}
	}
	void reset_Concs()
	{
		for (int i = 0; i < 4; i++)
		{
			C[i] = ν[i] / V;
		}
	}
	void set_NULL(double V_new)
	{
		for (int i = 0; i < 4; i++)
		{
			ν[i] = 0;
		}
		ν[3] = P * V_new / R / InjTemperature  ;
		T = InjTemperature;
		reset_νsum();
		reset_Concs();
	}
	void reset_ν_from_concs()
	{
		for (int i = 0; i < 4; i++)
		{
			ν[i] = C[i] * V;
		}
	}
	
	// phase resettings:

	void close_out_valve()
	{
		phase = 0;
	}
	void open_in_valve()
	{
		phase = 0;
	}
	void close_in_valve()
	{
		phase = 1;
	}
	void start_adi_compression()
	{
		phase = 2;
	}
	void start_burning()
	{
		phase = 3;
	}
	void open_out_valve()
	{
		phase = 4;
	}

	// Gas burning functions

	double dQ_GasBurning(double dtime)
	{
		set_V_chem();
		
		if (C[0] < vchem * dtime * cstech[0])
		{
			
			F = burnE * V * C[0];
			C[2] += C[0] * cstech[2] / cstech[0];
			C[0] = 0;
			
				C[1] -= vchem * dtime * cstech[1];
				if (C[1] <= 0)
				{
					C[1] = 0;
				}
				C[3] -= vchem * dtime * cstech[3];
				if (C[3] <= 0)
				{
					C[3] = 0;
				}

			reset_ν_from_concs();
			reset_Cvν_sum();
			reset_bVVν_sum();
			reset_ν2();
			reset_νsum();
			return F;
		}
		for (int i = 0; i < 2; i++)
		{
			
			C[i] -= vchem * dtime * cstech[i];
			
		}
		for (int i = 2; i < 4; i++)
		{

			C[i] += vchem * dtime * cstech[i];

		}
		reset_ν_from_concs();
		reset_Cvν_sum();
		reset_bVVν_sum();
		reset_ν2();
		reset_νsum();
		return (vchem * dtime * cstech[0] * burnE * V);
	}
	void set_K_tmp()
	{
		k_tmp = Nav * σ * σ *
			sqrt(8 * π * κ * (mol_mass[0] + mol_mass[1]) / (mol_mass[0] * mol_mass[1]));
	}
	void set_K_chem()
	{
		kchem = k_tmp * sqrt(T) * exp(-Eact / (R * T));
	}
	void set_V_chem()
	{
		
		if ((C[0] > 0) && (C[1] > 0))
		{
			set_K_chem();
			vchem = kchem * exp(log(C[0]) * cstech[0] * log(C[1]) * cstech[1]);
		}
		
		else vchem = 0;
	}

	// full update
	void GasFullUpdate(double dtime, double V_new, double piston_speed)
	{
		if (phase == 4)
		{

			time += dtime;
			if (counter == 0)
			{
				V = V_new;
				reset_Pressure_by_TV();
				set_av_mm();
				reset_νsum();
				T = 0.95 * T;
				counter = 1;

			}

			if (abs(V) <= abs(V_new))
			{
				P = Patm;
			}
			if ((counter == 3) && (abs(V) > abs(V_new)))
				counter = 1;

			if (((abs(V) < abs(V_new)) || (V_new < V_crit)) && (counter == 1))
			{
				close_out_valve();
				open_in_valve();
				set_NULL(V_new);
				time = 0;
				if ((abs(V) < abs(V_new)))
					counter = 0;
				else counter = 3;
			}
			if (V_new < V)
				Pressure_from_bernulli(piston_speed, dtime);
			V = V_new;
		}
		if (phase == 3)
		{
			time += dtime;
			if ((counter == 0) || (counter == 2))
			{
				set_K_tmp();
				reset_TV();
				counter++;
			}

			if ((abs(V) > abs(V_new)) && (counter != 3))
			{
				counter = 0;
				open_out_valve();
			}
			if ((counter == 3) && (V < V_new))
			{
				counter = 1;
			}


			gas_burning(dtime, V_new);
		}
		if (phase == 2)
		{
			if (counter == 0)
			{
				reset_TV();
				counter = 1;
			}
			if ((T >= T_crit) || (V <= V_crit) )
			{
				start_burning();
				reset_Concs();
				if (((T >= T_crit) || (V <= V_crit)) && (V > V_new))
				{
					counter = 2;
				}
				else counter = 0;
			}
			time += dtime;
			resetTemperatureAdi(V_new);
		}
		if (phase == 1)
		{
			if (counter == 0)
			{

				reset_TV();
				counter = 1;
			}
			if ((counter == 3) && (abs(V) < abs(V_new)))
			{
				reset_TV();
				counter = 1;
			}
			if ((abs(V) > abs(V_new)) && (counter == 1))
			{
				start_adi_compression();
				counter = 0;
			}

			time += dtime;
			resetTemperatureAdi(V_new);
		}
		if (phase == 0)
		{
			

			time += dtime;
			dInject(InjQnu, dtime);

			if ((counter == 3) && (abs(V) < abs(V_new)))
			{	

				counter = 1;
			}

			if (time >= Injtime)
			{
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
