double J_0_0 (double y[34]) {
    return -0.0032*y1 - 0.023*y3;
}

double J_1_0 (double y[34]) {
    return -0.0032*y0;
}

double J_2_0 (double y[34]) {
    return 0.00310000000000000;
}

double J_3_0 (double y[34]) {
    return -0.023*y0;
}

double J_4_0 (double y[34]) {
    return 0.00310000000000000;
}

double J_0_1 (double y[34]) {
    return -0.0032*y1;
}

double J_1_1 (double y[34]) {
    return -0.0032*y0 - 0.013*y10 - 0.00044*y4;
}

double J_2_1 (double y[34]) {
    return 0.00310000000000000;
}

double J_4_1 (double y[34]) {
    return -0.00044*y1;
}

double J_10_1 (double y[34]) {
    return -0.013*y1;
}

double J_0_2 (double y[34]) {
    return 0.0032*y1;
}

double J_1_2 (double y[34]) {
    return 0.0032*y0;
}

double J_2_2 (double y[34]) {
    return -0.00310000000000000;
}

double J_0_3 (double y[34]) {
    return -0.023*y3;
}

double J_1_3 (double y[34]) {
    return 0.00044*y4;
}

double J_3_3 (double y[34]) {
    return -0.023*y0;
}

double J_4_3 (double y[34]) {
    return 0.00044*y1 + 0.0031;
}

double J_0_4 (double y[34]) {
    return 0.023*y3;
}

double J_3_4 (double y[34]) {
    return 0.023*y0;
}

double J_4_4 (double y[34]) {
    return -0.05*y32 - 0.0031;
}

double J_32_4 (double y[34]) {
    return -0.05*y4;
}

double J_4_5 (double y[34]) {
    return -0.26*y5/(y5 + 243.0);
}

double J_5_5 (double y[34]) {
    return -2.5*y18 + 4.40312283019187e-6*y4*y5/(0.00411522633744856*y5 + 1)**2 - 0.26*y4/(y5 + 243.0);
}

double J_7_5 (double y[34]) {
    return 0.0257000000000000;
}

double J_18_5 (double y[34]) {
    return -2.5*y5;
}

double J_4_6 (double y[34]) {
    return 0.26*y5/(y5 + 243.0);
}

double J_5_6 (double y[34]) {
    return -4.40312283019187e-6*y4*y5/(0.00411522633744856*y5 + 1)**2 + 0.26*y4/(y5 + 243.0);
}

double J_6_6 (double y[34]) {
    return -5.5*y18;
}

double J_8_6 (double y[34]) {
    return 0.0257000000000000;
}

double J_18_6 (double y[34]) {
    return -5.5*y6;
}

double J_5_7 (double y[34]) {
    return 2.5*y18;
}

double J_7_7 (double y[34]) {
    return -0.0257000000000000;
}

double J_18_7 (double y[34]) {
    return 2.5*y5;
}

double J_6_8 (double y[34]) {
    return 5.5*y18;
}

double J_8_8 (double y[34]) {
    return -0.01*y22;
}

double J_18_8 (double y[34]) {
    return 5.5*y6;
}

double J_22_8 (double y[34]) {
    return -0.01*y8;
}

double J_23_8 (double y[34]) {
    return 0.00500000000000000;
}

double J_4_9 (double y[34]) {
    return -1.15*y9/(y9 + 450.0);
}

double J_9_9 (double y[34]) {
    return -78.3*y18 + 5.67901234567901e-6*y4*y9/(0.00222222222222222*y9 + 1)**2 - 1.15*y4/(y9 + 450.0);
}

double J_18_9 (double y[34]) {
    return -78.3*y9;
}

double J_4_10 (double y[34]) {
    return 1.15*y9/(y9 + 450.0);
}

double J_9_10 (double y[34]) {
    return -5.67901234567901e-6*y4*y9/(0.00222222222222222*y9 + 1)**2 + 1.15*y4/(y9 + 450.0);
}

double J_10_10 (double y[34]) {
    return -4.381*y31;
}

double J_31_10 (double y[34]) {
    return -4.381*y10;
}

double J_9_11 (double y[34]) {
    return 78.3*y18;
}

double J_11_11 (double y[34]) {
    return 0.00209876543209877*y11*y23/(0.0158730158730159*y11 + 1)**2 - 8.33*y23/(y11 + 63.0);
}

double J_18_11 (double y[34]) {
    return 78.3*y9;
}

double J_23_11 (double y[34]) {
    return -8.33*y11/(y11 + 63.0);
}

double J_11_12 (double y[34]) {
    return -0.00209876543209877*y11*y23/(0.0158730158730159*y11 + 1)**2 + 8.33*y23/(y11 + 63.0);
}

double J_12_12 (double y[34]) {
    return -0.4*y27;
}

double J_23_12 (double y[34]) {
    return 8.33*y11/(y11 + 63.0);
}

double J_27_12 (double y[34]) {
    return -0.4*y12;
}

double J_10_13 (double y[34]) {
    return -7.5e-6*y13;
}

double J_13_13 (double y[34]) {
    return -7.5e-6*y10 - 20.0*y18;
}

double J_15_13 (double y[34]) {
    return 5.90000000000000;
}

double J_18_13 (double y[34]) {
    return -20.0*y13;
}

double J_10_14 (double y[34]) {
    return 7.5e-6*y13;
}

double J_13_14 (double y[34]) {
    return 7.5e-6*y10;
}

double J_14_14 (double y[34]) {
    return -20.0*y18;
}

double J_16_14 (double y[34]) {
    return 5.90000000000000;
}

double J_18_14 (double y[34]) {
    return -20.0*y14;
}

double J_13_15 (double y[34]) {
    return 20.0*y18;
}

double J_15_15 (double y[34]) {
    return 1.9935920256319e-5*y15*y28/(0.000943396226415094*y15 + 1)**2 - 22.4*y28/(y15 + 1060.0);
}

double J_18_15 (double y[34]) {
    return 20.0*y13;
}

double J_28_15 (double y[34]) {
    return -22.4*y15/(y15 + 1060.0);
}

double J_14_16 (double y[34]) {
    return 20.0*y18;
}

double J_15_16 (double y[34]) {
    return -1.9935920256319e-5*y15*y28/(0.000943396226415094*y15 + 1)**2 + 22.4*y28/(y15 + 1060.0);
}

double J_18_16 (double y[34]) {
    return 20.0*y14;
}

double J_28_16 (double y[34]) {
    return 22.4*y15/(y15 + 1060.0);
}

double J_14_17 (double y[34]) {
    return 0.37*y14*y17/(y14 + 1)**2 - 0.37*y17/(y14 + 1);
}

double J_17_17 (double y[34]) {
    return -0.37*y14/(y14 + 1) - 0.3*y18;
}

double J_18_17 (double y[34]) {
    return -0.3*y17;
}

double J_14_18 (double y[34]) {
    return -0.37*y14*y17/(y14 + 1)**2 + 0.37*y17/(y14 + 1);
}

double J_17_18 (double y[34]) {
    return 0.37*y14/(y14 + 1) + 0.3*y18;
}

double J_18_18 (double y[34]) {
    return 0.3*y17;
}

double J_14_19 (double y[34]) {
    return -0.9*y19/(y19 + 147.0);
}

double J_18_19 (double y[34]) {
    return -3.225*y19;
}

double J_19_19 (double y[34]) {
    return 4.1649312786339e-5*y14*y19/(0.00680272108843537*y19 + 1)**2 - 0.9*y14/(y19 + 147.0) - 3.225*y18;
}

double J_14_20 (double y[34]) {
    return 0.9*y19/(y19 + 147.0);
}

double J_18_20 (double y[34]) {
    return -3.225*y20;
}

double J_19_20 (double y[34]) {
    return -4.1649312786339e-5*y14*y19/(0.00680272108843537*y19 + 1)**2 + 0.9*y14/(y19 + 147.0);
}

double J_20_20 (double y[34]) {
    return -3.225*y18;
}

double J_16_21 (double y[34]) {
    return -0.9*y21/(y21 + 200);
}

double J_21_21 (double y[34]) {
    return 0.9*y16*y21/(y21 + 200)**2 - 0.9*y16/(y21 + 200);
}

double J_12_22 (double y[34]) {
    return 0.023*y21/(y21 + 20.0);
}

double J_16_22 (double y[34]) {
    return 0.9*y21/(y21 + 200);
}

double J_21_22 (double y[34]) {
    return -5.75e-5*y12*y21/(0.05*y21 + 1)**2 + 0.023*y12/(y21 + 20.0) - 0.9*y16*y21/(y21 + 200)**2 + 0.9*y16/(y21 + 200);
}

double J_8_23 (double y[34]) {
    return 0.01*y22;
}

double J_22_23 (double y[34]) {
    return 0.01*y8;
}

double J_23_23 (double y[34]) {
    return -0.00500000000000000;
}

double J_14_24 (double y[34]) {
    return -0.233*y24/(y24 + 71.7);
}

double J_18_24 (double y[34]) {
    return -153.9*y24;
}

double J_24_24 (double y[34]) {
    return 4.53228915615779e-5*y14*y24/(0.0139470013947001*y24 + 1)**2 - 0.233*y14/(y24 + 71.7) - 153.9*y18;
}

double J_14_25 (double y[34]) {
    return 0.233*y24/(y24 + 71.7);
}

double J_18_25 (double y[34]) {
    return -153.9*y25;
}

double J_24_25 (double y[34]) {
    return -4.53228915615779e-5*y14*y24/(0.0139470013947001*y24 + 1)**2 + 0.233*y14/(y24 + 71.7);
}

double J_25_25 (double y[34]) {
    return -153.9*y18;
}

double J_16_26 (double y[34]) {
    return -0.23*y26/(y26 + 71.7);
}

double J_26_26 (double y[34]) {
    return 4.47393350178666e-5*y16*y26/(0.0139470013947001*y26 + 1)**2 - 0.23*y16/(y26 + 71.7);
}

double J_16_27 (double y[34]) {
    return 0.23*y26/(y26 + 71.7);
}

double J_26_27 (double y[34]) {
    return -4.47393350178666e-5*y16*y26/(0.0139470013947001*y26 + 1)**2 + 0.23*y16/(y26 + 71.7);
}

double J_12_28 (double y[34]) {
    return 0.4*y27;
}

double J_27_28 (double y[34]) {
    return 0.4*y12;
}

double J_28_28 (double y[34]) {
    return -0.200000000000000;
}

double J_14_29 (double y[34]) {
    return -59.0*y29/(y29 + 3160.0);
}

double J_29_29 (double y[34]) {
    return 5.90850825188271e-6*y14*y29/(0.000316455696202532*y29 + 1)**2 - 59.0*y14/(y29 + 3160.0);
}

double J_14_30 (double y[34]) {
    return 59.0*y29/(y29 + 3160.0);
}

double J_29_30 (double y[34]) {
    return -5.90850825188271e-6*y14*y29/(0.000316455696202532*y29 + 1)**2 + 59.0*y14/(y29 + 3160.0);
}

double J_10_31 (double y[34]) {
    return -4.381*y31;
}

double J_31_31 (double y[34]) {
    return -4.381*y10;
}

double J_32_31 (double y[34]) {
    return 5.29300000000000e-8;
}

double J_4_32 (double y[34]) {
    return -0.05*y32;
}

double J_10_32 (double y[34]) {
    return 4.381*y31;
}

double J_31_32 (double y[34]) {
    return 4.381*y10;
}

double J_32_32 (double y[34]) {
    return -0.05*y4 - 5.293e-8;
}

double J_4_33 (double y[34]) {
    return 4.5e-7*y33;
}

double J_6_33 (double y[34]) {
    return 0.0002223*y33;
}

double J_10_33 (double y[34]) {
    return 3.05e-6*y33;
}

double J_14_33 (double y[34]) {
    return 0.000179*y33;
}

double J_33_33 (double y[34]) {
    return 3.05e-6*y10 + 0.000179*y14 + 4.5e-7*y4 + 0.0002223*y6;
}

