#include<stdio.h>												//Задача без анализа чувствительности
#include <stdlib.h>
#include<math.h>
using namespace std;

/*double TF_0=5, VII_0=0.7, TF__VII_0=0.0, VII_a_0=0.1, TF__VII_a_0=0.0, IX_0=90.0, IX_a_0=0.009, IX_m_0=0.0, IX_a_m_0=0.0;
double X_0=170.0, X_a_0=0.017, X_m_0=0.0, X_a_m_0=0.0, II_0=1400.0, II_a_0=0.140, II_m_0=0.0, II_a_m_0=0.0, PL_0=10.0, AP_0=0.001;
double VIII_0=0.7, VIII_a_0=0.00007, VIII_m_0=0.0, VIII_a_m_0=0.0, VIII_a_m__IX_a_m_0=0.0;
double V_0=20.0, V_a_0=0.002, V_m_0=0.0, V_a_m_0=0.0, X_a_m__V_a_m_0=0.0, I_0=7000.0, I_a_0=0.70, TFPI_0=2.5, X_a__TFPI_0=0.0, ATIII_0=3400;

double k_T7_pl=0.0032, k_T7_min=0.0031, k_T7a_pl=0.023, k_T7a_min=0.0031, k_TF7=0.00044, k_10_7=0.013, k_2_7=0.000023, h_7_TP=0.05, h_7_AT=0.0000009;
double k_9=0.26, K_9M=243.0, k_9_pl=0.01, k_9_min=0.0257, h_9=0.0002223, N_9=250, N_9a=550, k_TEN_pl=0.01, k_TEN_min=0.0050, k_7_10=1.15, K_7_10M=450.0;
double k_10_pl=0.029, k_10_min=3.3, N_10=2700, h_10_TP_pl=4.381, h_10_TP_min=0.00000005293, h_10_AT=0.00000305, k_10=8.33, K_10M=63.0;
double k_PRO_pl=0.4, k_PRO_min=0.2, k_2t=0.0000075, k_2_pl=0.01, k_2_min=5.9, N_2=30000, N_2a=1000, h_2=0.000179, k_2=22.4, K_2M=1060.0, k_pp=0.3;
double k_p2=0.37, k_8=0.9, K_8M=147.0, k_8_pl=0.0043, k_8_min=0.00246, N_8=750, h_8=0.0037, k_8_m=0.9, K_8M_m=200, k_8t_m=0.023, K_8tM_m=20.0;
double k_5=0.233, K_5M=71.7, k_5_pl=0.057, k_5_min=0.17, N_5=2700, h_5=0.0028, k_5_m=0.23, K_5M_m=71.7, k_5t_m=0.046, K_5tM_m=10.4, k_f=59.0, K_fM=3160.0;
double K_M14 = 0.14;*/

double TF_0=5, VII_0=10.0, TF__VII_0=0.0, VII_a_0=0.1, TF__VII_a_0=0.0, IX_0=90.0, IX_a_0=0.009, IX_m_0=0.0, IX_a_m_0=0.0;
double X_0=170, X_a_0=0.017, X_m_0=0.0, X_a_m_0=0.0, II_0=1400.0, II_a_0=0.14, II_m_0=0.0, II_a_m_0=0.0, PL_0=10.0, AP_0=0.001;
double VIII_0=0.7, VIII_a_0=0.00007, VIII_m_0=0.0, VIII_a_m_0=0.0, VIII_a_m__IX_a_m_0=0.0;
double V_0=20.0, V_a_0=0.002, V_m_0=0.0, V_a_m_0=0.0, X_a_m__V_a_m_0=0.0, I_0=7000.0, I_a_0=0.70, TFPI_0=2.5, X_a__TFPI_0=0.0, ATIII_0=3400;

double k_T7_pl=0.0032, k_T7_min=0.0031, k_T7a_pl=0.023, k_T7a_min=0.0031, k_TF7=0.00044, k_10_7=0.013, k_2_7=0.000023, h_7_TP=0.05, h_7_AT=0.00000045;
double k_9=0.26, K_9M=243.0, k_9_pl=0.01, k_9_min=0.0257, h_9=0.0002223, N_9=250, N_9a=550, k_TEN_pl=0.01, k_TEN_min=0.0050, k_7_10=1.15, K_7_10M=450.0;
double k_10_pl=0.029, k_10_min=3.3, N_10=2700, h_10_TP_pl=4.381, h_10_TP_min=0.00000005293, h_10_AT=0.00000305, k_10=8.33, K_10M=63.0;
double k_PRO_pl=0.4, k_PRO_min=0.2, k_2t=0.0000075, k_2_pl=0.01, k_2_min=5.9, N_2=2000, N_2a=2000, h_2=0.000179, k_2=22.4, K_2M=1060.0, k_pp=0.3;
double k_p2=0.37, k_8=0.9, K_8M=147.0, k_8_pl=0.0043, k_8_min=0.00246, N_8=750, h_8=0.0037, k_8_m=0.9, K_8M_m=200, k_8t_m=0.023, K_8tM_m=20.0;
double k_5=0.233, K_5M=71.7, k_5_pl=0.057, k_5_min=0.17, N_5=2700, h_5=0.0028, k_5_m=0.23, K_5M_m=71.7, k_5t_m=0.046, K_5tM_m=10.4, k_f=59.0, K_fM=3160.0;
double K_M14 = 1;

double h, T=800;
int N = 32000;

double J_0_0(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_T7_pl*y[1] - k_T7a_pl*y[3];
}

double J_0_1(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_T7_pl*y[0];
}

double J_0_2(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_T7_min;
}

double J_0_3(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_T7a_pl*y[0];
}

double J_0_4(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_T7a_min;
}

double J_1_0(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_T7_pl*y[1];
}

double J_1_1(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_T7_pl*y[0] - k_TF7*y[4] - k_10_7*y[10] - k_2_7*y[14];
}

double J_1_2(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_T7_min;
}

double J_1_4(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_TF7*y[1];
}

double J_1_10(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_10_7*y[1];
}

double J_1_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_2_7*y[1];
}

double J_2_0(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_T7_pl*y[1];
}

double J_2_1(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_T7_pl*y[0];
}

double J_2_2(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_T7_min;
}

double J_3_0(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_T7a_pl*y[3];
}

double J_3_1(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_TF7*y[4] + k_10_7*y[10] + k_2_7*y[14];
}

double J_3_3(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_T7a_pl*y[0];
}

double J_3_4(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_T7a_min + k_TF7*y[1];
}

double J_3_10(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_10_7*y[1];
}

double J_3_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_2_7*y[1];
}

double J_4_0(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_T7a_pl*y[3];
}

double J_4_3(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_T7a_pl*y[0];
}

double J_4_4(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_T7a_min - h_7_TP*y[32] - h_7_AT*y[33];
}

double J_4_32(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_7_TP*y[4];
}

double J_4_33(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_7_AT*y[4];
}

double J_5_4(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_9*y[5]/(K_9M + y[5]);
}

double J_5_5(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_9*K_9M*y[4]/(K_9M + y[5])/(K_9M + y[5]) - k_9_pl*N_9*y[18];
}

double J_5_7(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_9_min;
}

double J_5_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_9_pl*N_9*y[5];
}

double J_6_4(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_9*y[5]/(K_9M + y[5]);
}

double J_6_5(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_9*K_9M*y[4]/(K_9M + y[5])/(K_9M + y[5]);
}

double J_6_6(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_9_pl*N_9a*y[18] - h_9*y[33];
}

double J_6_8(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_9_min;
}

double J_6_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_9_pl*N_9a*y[6];
}

double J_6_33(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_9*y[6];
}

double J_7_5(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_9_pl*N_9*y[18];
}

double J_7_7(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_9_min;
}

double J_7_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_9_pl*N_9*y[5];
}

double J_8_6(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_9_pl*N_9a*y[18];
}

double J_8_8(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_TEN_pl*y[22] - k_9_min;
}

double J_8_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_9_pl*N_9a*y[6];
}

double J_8_22(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_TEN_pl*y[8];
}

double J_8_23(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_TEN_min;
}

double J_9_4(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_7_10*y[9]/(K_7_10M + y[9]);
}

double J_9_9(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_7_10*K_7_10M*y[4]/(K_7_10M + y[9])/(K_7_10M + y[9]) - k_10_pl*N_10*y[18];
}

double J_9_11(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_10_min;
}

double J_9_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_10_pl*N_10*y[9];
}

double J_10_4(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_7_10*y[9]/(K_7_10M + y[9]);
}

double J_10_9(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_7_10*K_7_10M*y[4]/(K_7_10M + y[9])/(K_7_10M + y[9]);
}

double J_10_10(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_10_TP_pl*y[31] - h_10_AT*y[33] - k_10_pl*N_10*y[18];
}

double J_10_12(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_10_min;
}

double J_10_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_10_pl*N_10*y[10];
}

double J_10_31(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_10_TP_pl*y[10];
}

double J_10_32(complex<double> y[34])            //Функция задачи элемента массива J
{
	return h_10_TP_min;
}

double J_10_33(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_10_AT*y[10];
}

double J_11_9(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_10_pl*N_10*y[18];
}

double J_11_11(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_10*K_10M*y[23]/(K_10M + y[11])/(K_10M + y[11]) - k_10_min;
}

double J_11_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_10_pl*N_10*y[9];
}

double J_11_23(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_10*y[11]/(K_10M + y[11]);
}

double J_12_10(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_10_pl*N_10*y[18];
}

double J_12_11(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_10*K_10M*y[23]/(K_10M + y[11])/(K_10M + y[11]);
}

double J_12_12(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_PRO_pl*y[27] - k_10_min;
}

double J_12_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_10_pl*N_10*y[10];
}

double J_12_23(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_10*y[11]/(K_10M + y[11]);
}

double J_12_27(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_PRO_pl*y[12];
}

double J_12_28(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_PRO_min;
}

double J_13_10(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_2t*y[13];
}

double J_13_13(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_2t*y[10] - k_2_pl*N_2*y[18];
}

double J_13_15(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_2_min;
}

double J_13_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_2_pl*N_2*y[13];
}

double J_14_10(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_2t*y[13];
}

double J_14_13(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_2t*y[10];
}

double J_14_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_2_pl*N_2a*y[18] - h_2*y[33];
}

double J_14_16(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_2_min;
}

double J_14_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_2_pl*N_2a*y[14];
}

double J_14_33(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_2*y[14];
}

double J_15_13(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_2_pl*N_2*y[18];
}

double J_15_15(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_2*K_2M*y[28]/(K_2M + y[15])/(K_2M + y[15]) - k_2_min;
}

double J_15_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_2_pl*N_2*y[13];
}

double J_15_28(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_2*y[15]/(K_2M + y[15]);
}

double J_16_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_2_pl*N_2a*y[18];
}

double J_16_15(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_2*K_2M*y[28]/(K_2M + y[15])/(K_2M + y[15]);
}

double J_16_16(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_2_min;
}

double J_16_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_2_pl*N_2a*y[14];
}

double J_16_28(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_2*y[15]/(K_2M + y[15]);
}

double J_17_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_p2*K_M14*y[17]/(K_M14 + y[14])/(K_M14 + y[14]);
}

double J_17_17(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_pp*y[18] - k_p2*y[14]/(K_M14 + y[14]);
}

double J_17_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_pp*y[17];
}

double J_18_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_p2*K_M14*y[17]/(K_M14 + y[14])/(K_M14 + y[14]);
}

double J_18_17(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_pp*y[18] + k_p2*y[14]/(K_M14 + y[14]);
}

double J_18_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_pp*y[17];
}

double J_19_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_8*y[19]/(K_8M + y[19]);
}

double J_19_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_8_pl*N_8*y[19];
}

double J_19_19(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_8*K_8M*y[14]/(K_8M + y[19])/(K_8M + y[19]) - k_8_pl*N_8*y[18];
}

double J_19_21(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_8_min;
}

double J_20_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_8*y[19]/(K_8M + y[19]);
}

double J_20_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_8*N_8*y[20];
}

double J_20_19(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_8*K_8M*y[14]/(K_8M + y[19])/(K_8M + y[19]);
}

double J_20_20(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_8_pl*N_8*y[18] - h_8;
}

double J_20_22(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_8_min;
}

double J_21_12(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_8t_m*y[21]/(K_8tM_m + y[21]);
}

double J_21_16(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_8_m*y[21]/(K_8M_m + y[21]);
}

double J_21_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_8_pl*N_8*y[19];
}

double J_21_19(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_8_pl*N_8*y[18];
}

double J_21_21(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_8_m*K_8M_m*y[16]/(K_8M_m + y[21])/(K_8M_m + y[21]) - k_8t_m*K_8tM_m*y[12]/(K_8tM_m + y[21])/(K_8tM_m + y[21]) - k_8_min;
}

double J_22_8(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_TEN_pl*y[22];
}

double J_22_12(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_8t_m*y[21]/(K_8tM_m + y[21]);
}

double J_22_16(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_8_m*y[21]/(K_8M_m + y[21]);
}

double J_22_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_8_pl*N_8*y[20];
}

double J_22_20(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_8_pl*N_8*y[18];
}

double J_22_21(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_8_m*K_8M_m*y[16]/(K_8M_m + y[21])/(K_8M_m + y[21]) + k_8t_m*K_8tM_m*y[12]/(K_8tM_m + y[21])/(K_8tM_m + y[21]);
}

double J_22_22(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_8_min - k_TEN_pl*y[8];
}

double J_22_23(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_TEN_min;
}

double J_23_8(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_TEN_pl*y[22];
}

double J_23_22(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_TEN_pl*y[8];
}

double J_23_23(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_TEN_min;
}

double J_24_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_5*y[24]/(K_5M + y[24]);
}

double J_24_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_5_pl*N_5*y[24];
}

double J_24_24(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_5*K_5M*y[14]/(K_5M + y[24])/(K_5M + y[24]) - k_5_pl*N_5*y[18];
}

double J_24_26(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_5_min;
}

double J_25_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_5*y[24]/(K_5M + y[24]);
}

double J_25_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_5_pl*N_5*y[25];
}

double J_25_24(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_5*K_5M*y[14]/(K_5M + y[24])/(K_5M + y[24]);
}

double J_25_25(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_5_pl*N_5*y[18] - h_5;
}

double J_25_27(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_5_min;
}

double J_26_12(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_5t_m*y[26]/(K_5tM_m + y[26]);
}

double J_26_16(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_5_m*y[26]/(K_5M_m + y[26]);
}

double J_26_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_5_pl*N_5*y[24];
}

double J_26_24(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_5_pl*N_5*y[18];
}

double J_26_26(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_5_m*K_5M_m*y[16]/(K_5M_m + y[26])/(K_5M_m + y[26]) - k_5t_m*K_5tM_m*y[12]/(K_5tM_m + y[26])/(K_5tM_m + y[26]) - k_5_min;
}

double J_27_12(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_5t_m*y[26]/(K_5tM_m + y[26]) - k_PRO_pl*y[27];
}

double J_27_16(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_5_m*y[26]/(K_5M_m + y[26]);
}

double J_27_18(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_5_pl*N_5*y[25];
}

double J_27_25(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_5_pl*N_5*y[18];
}

double J_27_26(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_5_m*K_5M_m*y[16]/(K_5M_m + y[26])/(K_5M_m + y[26]) + k_5t_m*K_5tM_m*y[12]/(K_5tM_m + y[26])/(K_5tM_m + y[26]);
}

double J_27_27(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_PRO_pl*y[12] - k_5_min;
}

double J_27_28(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_PRO_min;
}

double J_28_12(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_PRO_pl*y[27];
}

double J_28_27(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_PRO_pl*y[12];
}

double J_28_28(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_PRO_pl;
}

double J_29_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_f*y[29]/(K_fM + y[29]);
}

double J_29_29(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -k_f*K_fM*y[14]/(K_fM + y[29])/(K_fM + y[29]);
}

double J_30_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_f*y[29]/(K_fM + y[29]);
}

double J_30_29(complex<double> y[34])            //Функция задачи элемента массива J
{
	return k_f*K_fM*y[14]/(K_fM + y[29])/(K_fM + y[29]);
}

double J_31_10(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_10_TP_pl*y[31];
}

double J_31_31(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_10_TP_pl*y[10];
}

double J_31_32(complex<double> y[34])            //Функция задачи элемента массива J
{
	return h_10_TP_min;
}

double J_32_4(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_7_TP*y[32];
}

double J_32_10(complex<double> y[34])            //Функция задачи элемента массива J
{
	return h_10_TP_pl*y[31];
}

double J_32_31(complex<double> y[34])            //Функция задачи элемента массива J
{
	return h_10_TP_pl*y[10];
}

double J_32_32(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_10_TP_min - h_7_TP*y[4];
}

double J_33_4(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_7_AT*y[33];
}

double J_33_6(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_9*y[33];
}

double J_33_10(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_10_AT*y[33];
}

double J_33_14(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_2*y[33];
}

double J_33_33(complex<double> y[34])            //Функция задачи элемента массива J
{
	return -h_10_AT*y[10] - h_9*y[6] - h_2*y[14] - h_7_AT*y[4];
}

double f0(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_T7_pl*y[0]*y[1] + k_T7_min*y[2] - k_T7a_pl*y[0]*y[3] + k_T7a_min*y[4];
}

double f1(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_T7_pl*y[0]*y[1] + k_T7_min*y[2] - k_TF7*y[4]*y[1] - k_10_7*y[10]*y[1] - k_2_7*y[14]*y[1];
}

double f2(complex<double> y[34])               //Функция правой части уравнения
{
	return k_T7_pl*y[0]*y[1] - k_T7_min*y[2];
}

double f3(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_T7a_pl*y[0]*y[3] + k_T7a_min*y[4] + k_TF7*y[4]*y[1] + k_10_7*y[10]*y[1] + k_2_7*y[14]*y[1];
}

double f4(complex<double> y[34])               //Функция правой части уравнения
{
	return k_T7a_pl*y[0]*y[3] - k_T7a_min*y[4] - h_7_TP*y[32]*y[4] - h_7_AT*y[33]*y[4];
}

double f5(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_9*y[4]*y[5]/(K_9M + y[5]) - k_9_pl*N_9*y[18]*y[5] + k_9_min*y[7];
}

double f6(complex<double> y[34])               //Функция правой части уравнения
{
	return k_9*y[4]*y[5]/(K_9M + y[5]) - k_9_pl*N_9a*y[18]*y[6] + k_9_min*y[8] - h_9*y[6]*y[33];
}

double f7(complex<double> y[34])               //Функция правой части уравнения
{
	return k_9_pl*N_9*y[18]*y[5] - k_9_min*y[7];
}

double f8(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_TEN_pl*y[22]*y[8] + k_TEN_min*y[23] + k_9_pl*N_9a*y[18]*y[6] - k_9_min*y[8];
}

double f9(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_7_10*y[4]*y[9]/(K_7_10M + y[9]) - k_10_pl*N_10*y[18]*y[9] + k_10_min*y[11];
}

double f10(complex<double> y[34])               //Функция правой части уравнения
{
	return k_7_10*y[4]*y[9]/(K_7_10M + y[9]) - h_10_TP_pl*y[31]*y[10] + h_10_TP_min*y[32] - h_10_AT*y[33]*y[10] - k_10_pl*N_10*y[18]*y[10] + k_10_min*y[12];
}

double f11(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_10*y[23]*y[11]/(K_10M + y[11]) + k_10_pl*N_10*y[18]*y[9] - k_10_min*y[11];
}

double f12(complex<double> y[34])               //Функция правой части уравнения
{
	return k_10*y[23]*y[11]/(K_10M + y[11]) - k_PRO_pl*y[27]*y[12] + k_PRO_min*y[28] + k_10_pl*N_10*y[18]*y[10] - k_10_min*y[12];
}

double f13(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_2t*y[10]*y[13] - k_2_pl*N_2*y[18]*y[13] + k_2_min*y[15];
}

double f14(complex<double> y[34])               //Функция правой части уравнения
{
	return k_2t*y[10]*y[13] - k_2_pl*N_2a*y[18]*y[14] + k_2_min*y[16] - h_2*y[33]*y[14];
}

double f15(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_2*y[28]*y[15]/(K_2M + y[15]) + k_2_pl*N_2*y[18]*y[13] - k_2_min*y[15];
}

double f16(complex<double> y[34])               //Функция правой части уравнения
{
	return k_2*y[28]*y[15]/(K_2M + y[15]) + k_2_pl*N_2a*y[18]*y[14] - k_2_min*y[16];
}

double f17(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_pp*y[17]*y[18] - k_p2*y[17]*y[14]/(K_M14 + y[14]);
}

double f18(complex<double> y[34])               //Функция правой части уравнения
{
	return k_pp*y[17]*y[18] + k_p2*y[17]*y[14]/(K_M14 + y[14]);
}

double f19(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_8*y[14]*y[19]/(K_8M + y[19]) - k_8_pl*N_8*y[18]*y[19] + k_8_min*y[21];
}

double f20(complex<double> y[34])               //Функция правой части уравнения
{
	return k_8*y[14]*y[19]/(K_8M + y[19]) - k_8_pl*N_8*y[18]*y[20] + k_8_min*y[22] - h_8*y[20];
}

double f21(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_8_m*y[16]*y[21]/(K_8M_m + y[21]) - k_8t_m*y[12]*y[21]/(K_8tM_m + y[21]) + k_8_pl*N_8*y[18]*y[19] - k_8_min*y[21];
}

double f22(complex<double> y[34])               //Функция правой части уравнения
{
	return k_8_m*y[16]*y[21]/(K_8M_m + y[21]) + k_8t_m*y[12]*y[21]/(K_8tM_m + y[21]) + k_8_pl*N_8*y[18]*y[20] - k_8_min*y[22] - k_TEN_pl*y[22]*y[8] + k_TEN_min*y[23];
}

double f23(complex<double> y[34])               //Функция правой части уравнения
{
	return k_TEN_pl*y[22]*y[8] - k_TEN_min*y[23];
}

double f24(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_5*y[14]*y[24]/(K_5M + y[24]) - k_5_pl*N_5*y[18]*y[24] + k_5_min*y[26];
}

double f25(complex<double> y[34])               //Функция правой части уравнения
{
	return k_5*y[14]*y[24]/(K_5M + y[24]) - k_5_pl*N_5*y[18]*y[25] + k_5_min*y[27] - h_5*y[25];
}

double f26(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_5_m*y[16]*y[26]/(K_5M_m + y[26]) - k_5t_m*y[12]*y[26]/(K_5tM_m + y[26]) + k_5_pl*N_5*y[18]*y[24] - k_5_min*y[26];
}

double f27(complex<double> y[34])               //Функция правой части уравнения
{
	return k_5_m*y[16]*y[26]/(K_5M_m + y[26]) + k_5t_m*y[12]*y[26]/(K_5tM_m + y[26]) - k_PRO_pl*y[12]*y[27] + k_PRO_min*y[28] + k_5_pl*N_5*y[18]*y[25] - k_5_min*y[27];
}

double f28(complex<double> y[34])               //Функция правой части уравнения
{
	return k_PRO_pl*y[12]*y[27] - k_PRO_min*y[28];
}

double f29(complex<double> y[34])               //Функция правой части уравнения
{
	return -k_f*y[14]*y[29]/(K_fM + y[29]);
}

double f30(complex<double> y[34])               //Функция правой части уравнения
{
	return k_f*y[14]*y[29]/(K_fM + y[29]);
}

double f31(complex<double> y[34])               //Функция правой части уравнения
{
	return -h_10_TP_pl*y[10]*y[31] + h_10_TP_min*y[32];
}

double f32(complex<double> y[34])               //Функция правой части уравнения
{
	return h_10_TP_pl*y[10]*y[31] - h_10_TP_min*y[32] - h_7_TP*y[4]*y[32];
}

double f33(complex<double> y[34])               //Функция правой части уравнения
{
	return -y[33]*(h_10_AT*y[10] + h_9*y[6] + h_2*y[14] + h_7_AT*y[4]);
}

int main(int argc, char *argv[])
{	
	h = T/N;                      //Количество шагов по времени
	
	double M;
	
	double J[34][34];               //Якобиан системы размера 34*34
	double J1[34][34], J2[34][34];    //J1=E-1/2hJ - вещественная часть, J2=-1/2hJ - мнимая часть
	double J3[68][68];              //Вспомогательный массив для решения системы уравнений с комплексными числами
	
	double f[34], g[68];            //Массив правых частей и вспомогательный массив с нулями
	double u[34], z[68];            //Массив вещественной части и вспомогательный
	complex<double> y[34];                  //Искомый массив значения функций
	
	
	y[0] = TF_0;                   //Начальные условия
	y[1] = VII_0;
	y[2] = TF__VII_0;
	y[3] = VII_a_0;
	y[4] = TF__VII_a_0;
	y[5] = IX_0;
	y[6] = IX_a_0;
	y[7] = IX_m_0;
	y[8] = IX_a_m_0;
	y[9] = X_0;
	y[10] = X_a_0;
	y[11] = X_m_0;
	y[12] = X_a_m_0;
	y[13] = II_0;
	y[14] = II_a_0;
	y[15] = II_m_0;
	y[16] = II_a_m_0;
	y[17] = PL_0;
	y[18] = AP_0;
	y[19] = VIII_0;
	y[20] = VIII_a_0;
	y[21] = VIII_m_0;
	y[22] = VIII_a_m_0;
	y[23] = VIII_a_m__IX_a_m_0;
	y[24] = V_0;
	y[25] = V_a_0;
	y[26] = V_m_0;
	y[27] = V_a_m_0;
	y[28] = X_a_m__V_a_m_0;
	y[29] = I_0;
	y[30] = I_a_0;
	y[31] = TFPI_0;
	y[32] = X_a__TFPI_0;
	y[33] = ATIII_0;
	
	FILE *pf_anand;
//	FILE *pf;
	
//	pf_anand = fopen("new1_anand.txt", "w");
//	pf_anand = fopen("new2_anand.txt", "w");
	pf_anand = fopen("new3_anand.txt", "w");
//	pf = fopen("s.txt", "w");
	
	double t;
	
	t=0;
	
	for(int i=0; i<34; i++)
		for(int j=0; j<34; j++)
			J[i][j] = 0;			//Начальное значение J, нужно для того, чтобы каждый раз не описывать нули
	
	fprintf(pf_anand, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", t, y[0], y[1], y[2], y[3], y[4], y[5], y[6], y[7], y[8], y[9], y[10], y[11], y[12], y[13], y[14], y[15], y[16], y[17], y[18], y[19], y[20], y[21], y[22], y[23], y[24], y[25], y[26], y[27], y[28], y[29], y[30], y[31], y[32], y[33]);
	
	for(int i=1; i<=N; i++)
	{
		J[0][0] = J_0_0(y);       //Подсчёт текущего значения J
		J[0][1] = J_0_1(y);
		J[0][2] = J_0_2(y);
		J[0][3] = J_0_3(y);
		J[0][4] = J_0_4(y);
		J[1][0] = J_1_0(y);
		J[1][1] = J_1_1(y);
		J[1][2] = J_1_2(y);
		J[1][4] = J_1_4(y);
		J[1][10] = J_1_10(y);
		J[1][14] = J_1_14(y);
		J[2][0] = J_2_0(y);
		J[2][1] = J_2_1(y);
		J[2][2] = J_2_2(y);
		J[3][0] = J_3_0(y);
		J[3][1] = J_3_1(y);
		J[3][3] = J_3_3(y);
		J[3][4] = J_3_4(y);
		J[3][10] = J_3_10(y);
		J[3][14] = J_3_14(y);
		J[4][0] = J_4_0(y);
		J[4][3] = J_4_3(y);
		J[4][4] = J_4_4(y);
		J[4][32] = J_4_32(y);
		J[4][33] = J_4_33(y);
		J[5][4] = J_5_4(y);
		J[5][5] = J_5_5(y);
		J[5][7] = J_5_7(y);
		J[5][18] = J_5_18(y);
		J[6][4] = J_6_4(y);
		J[6][5] = J_6_5(y);
		J[6][6] = J_6_6(y);
		J[6][8] = J_6_8(y);
		J[6][18] = J_6_18(y);
		J[6][33] = J_6_33(y);
		J[7][5] = J_7_5(y);
		J[7][7] = J_7_7(y);
		J[7][18] = J_7_18(y);
		J[8][6] = J_8_6(y);
		J[8][8] = J_8_8(y);
		J[8][18] = J_8_18(y);
		J[8][22] = J_8_22(y);
		J[8][23] = J_8_23(y);
		J[9][4] = J_9_4(y);
		J[9][9] = J_9_9(y);
		J[9][11] = J_9_11(y);
		J[9][18] = J_9_18(y);
		J[10][4] = J_10_4(y);
		J[10][9] = J_10_9(y);
		J[10][10] = J_10_10(y);
		J[10][12] = J_10_12(y);
		J[10][18] = J_10_18(y);
		J[10][31] = J_10_31(y);
		J[10][32] = J_10_32(y);
		J[10][33] = J_10_33(y);
		J[11][9] = J_11_9(y);
		J[11][11] = J_11_11(y);
		J[11][18] = J_11_18(y);
		J[11][23] = J_11_23(y);
		J[12][10] = J_12_10(y);
		J[12][11] = J_12_11(y);
		J[12][12] = J_12_12(y);
		J[12][18] = J_12_18(y);
		J[12][23] = J_12_23(y);
		J[12][27] = J_12_27(y);
		J[12][28] = J_12_28(y);
		J[13][10] = J_13_10(y);
		J[13][13] = J_13_13(y);
		J[13][15] = J_13_15(y);
		J[13][18] = J_13_18(y);
		J[14][10] = J_14_10(y);
		J[14][13] = J_14_13(y);
		J[14][14] = J_14_14(y);
		J[14][16] = J_14_16(y);
		J[14][18] = J_14_18(y);
		J[14][33] = J_14_33(y);
		J[15][13] = J_15_13(y);
		J[15][15] = J_15_15(y);
		J[15][18] = J_15_18(y);
		J[15][28] = J_15_28(y);
		J[16][14] = J_16_14(y);
		J[16][15] = J_16_15(y);
		J[16][16] = J_16_16(y);
		J[16][18] = J_16_18(y);
		J[16][28] = J_16_28(y);
		J[17][14] = J_17_14(y);
		J[17][17] = J_17_17(y);
		J[17][18] = J_17_18(y);
		J[18][14] = J_18_14(y);
		J[18][17] = J_18_17(y);
		J[18][18] = J_18_18(y);
		J[19][14] = J_19_14(y);
		J[19][18] = J_19_18(y);
		J[19][19] = J_19_19(y);
		J[19][21] = J_19_21(y);
		J[20][14] = J_20_14(y);
		J[20][18] = J_20_18(y);
		J[20][19] = J_20_19(y);
		J[20][20] = J_20_20(y);
		J[20][22] = J_20_22(y);
		J[21][12] = J_21_12(y);
		J[21][16] = J_21_16(y);
		J[21][18] = J_21_18(y);
		J[21][19] = J_21_19(y);
		J[21][21] = J_21_21(y);
		J[22][8] = J_22_8(y);
		J[22][12] = J_22_12(y);
		J[22][16] = J_22_16(y);
		J[22][18] = J_22_18(y);
		J[22][20] = J_22_20(y);
		J[22][21] = J_22_21(y);
		J[22][22] = J_22_22(y);
		J[22][23] = J_22_23(y);
		J[23][8] = J_23_8(y);
		J[23][22] = J_23_22(y);
		J[23][23] = J_23_23(y);
		J[24][14] = J_24_14(y);
		J[24][18] = J_24_18(y);
		J[24][24] = J_24_24(y);
		J[24][26] = J_24_26(y);
		J[25][14] = J_25_14(y);
		J[25][18] = J_25_18(y);
		J[25][24] = J_25_24(y);
		J[25][25] = J_25_25(y);
		J[25][27] = J_25_27(y);
		J[26][12] = J_26_12(y);
		J[26][16] = J_26_16(y);
		J[26][18] = J_26_18(y);
		J[26][24] = J_26_24(y);
		J[26][26] = J_26_26(y);
		J[27][12] = J_27_12(y);
		J[27][16] = J_27_16(y);
		J[27][18] = J_27_18(y);
		J[27][25] = J_27_25(y);
		J[27][26] = J_27_26(y);
		J[27][27] = J_27_27(y);
		J[27][28] = J_27_28(y);
		J[28][12] = J_28_12(y);
		J[28][27] = J_28_27(y);
		J[28][28] = J_28_28(y);
		J[29][14] = J_29_14(y);
		J[29][29] = J_29_29(y);
		J[30][14] = J_30_14(y);
		J[30][29] = J_30_29(y);
		J[31][10] = J_31_10(y);
		J[31][31] = J_31_31(y);
		J[31][32] = J_31_32(y);
		J[32][4] = J_32_4(y);
		J[32][10] = J_32_10(y);
		J[32][31] = J_32_31(y);
		J[32][32] = J_32_32(y);
		J[33][4] = J_33_4(y);
		J[33][6] = J_33_6(y);
		J[33][10] = J_33_10(y);
		J[33][14] = J_33_14(y);
		J[33][33] = J_33_33(y);
		
/*		if(i == 40)
		{
			for(int j=0; j<34; j++)
			{
				for(int k=0; k<34; k++)
					fprintf(pf, "%f ", J[j][k]);
				fprintf(pf, "\n");
			}
		}*/
		
		for(int j=0; j<34; j++)					  //Подсчёт текущего значения J1
			for(int k=0; k<34; k++)
				J1[j][k] = -J[j][k]*h/2;
		
		for(int j=0; j<34; j++)
			J1[j][j] = 1.0 + J1[j][j];
		
		for(int j=0; j<34; j++)					  //Подсчёт текущего значения J2
			for(int k=0; k<34; k++)
				J2[j][k] = -J[j][k]*h/2;
		
		for(int j=0; j<34; j++)					  //Подсчёт текущего значения J3
			for(int k=0; k<34; k++)
			{
				J3[j][k] = J1[j][k];
				J3[j][k+34] = -J2[j][k];
				J3[j+34][k] = J2[j][k];
				J3[j+34][k+34] = J1[j][k];
			}

		g[0] = f0(y);           //Столбец вспомогательных функций правой части
		g[1] = f1(y);
		g[2] = f2(y);
		g[3] = f3(y);
		g[4] = f4(y);
		g[5] = f5(y);
		g[6] = f6(y);
		g[7] = f7(y);
		g[8] = f8(y);
		g[9] = f9(y);
		g[10] = f10(y);
		g[11] = f11(y);
		g[12] = f12(y);
		g[13] = f13(y);
		g[14] = f14(y);
		g[15] = f15(y);
		g[16] = f16(y);
		g[17] = f17(y);
		g[18] = f18(y);
		g[19] = f19(y);
		g[20] = f20(y);
		g[21] = f21(y);
		g[22] = f22(y);
		g[23] = f23(y);
		g[24] = f24(y);
		g[25] = f25(y);
		g[26] = f26(y);
		g[27] = f27(y);
		g[28] = f28(y);
		g[29] = f29(y);
		g[30] = f30(y);
		g[31] = f31(y);
		g[32] = f32(y);
		g[33] = f33(y);
		for (int i = 34; i < 68; ++i)
		{
			g[i] = 0;
		}
		
		double R, c[68], cc;                 //Вспомогательное число для метода Гаусса
		
		for(int k=0; k<68; k++)    //Метод Гаусса
		{		
				double max;
				int ind_max;
				
				max = abs(J3[k][k]);
				ind_max = k;
				
				for(int j=k+1; j<68; j++)
				{
					if(abs(J3[j][k]) > max)
					{
						ind_max = j;
					}
				}
				
				for(int j=0; j<68; j++)
				{
					c[j] = J3[k][j];
					J3[k][j] = J3[ind_max][j];
					J3[ind_max][j] = c[j];
				}
				
				cc = g[k];
				g[k] = g[ind_max];
				g[ind_max] = cc;
			
			for(int j=0; j<68; j++)
			{
				if(j != k)
				{ 
					if(J3[j][k] != 0)
					{
					R = J3[k][k]/J3[j][k];
					
						for(int l=0; l<68; l++)
						{
							J3[j][l] = J3[j][l] - J3[k][l]/R;
						}
						
						g[j] = g[j] - g[k]/R;
					}
				}
			}
			
			for(int j=0; j<68; j++)
				if(j != k)
					J3[k][j] = J3[k][j]/J3[k][k];
					
			g[k] = g[k]/J3[k][k];
			
			J3[k][k] = 1;
		}
		
		for(int m=0; m<68; m++)
		{
			z[m] = g[m];
		}

		for (int i = 0; i < 34; i++) {
			u[i] = z[i];
			y[i] += h * u[i];
		}

		t = T/N*i;
		
		fprintf(pf_anand, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f\n", t, y[0], y[1], y[2], y[3], y[4], y[5], y[6], y[7], y[8], y[9], y[10], y[11], y[12], y[13], y[14], y[15], y[16], y[17], y[18], y[19], y[20], y[21], y[22], y[23], y[24], y[25], y[26], y[27], y[28], y[29], y[30], y[31], y[32], y[33], y[14]+y[16]);
	}
	return 0;
}