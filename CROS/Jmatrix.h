double J_0_0 (double y[34]) {
    return -0.0032*y[1] - 0.023*y[3];
}

double J_1_0 (double y[34]) {
    return -0.0032*y[0];
}

double J_2_0 (double y[34]) {
    return 0.00310000000000000;
}

double J_3_0 (double y[34]) {
    return -0.023*y[0];
}

double J_4_0 (double y[34]) {
    return 0.00310000000000000;
}

double J_0_1 (double y[34]) {
    return -0.0032*y[1];
}

double J_1_1 (double y[34]) {
    return -0.0032*y[0] - 0.013*y[10] - 0.00044*y[4];
}

double J_2_1 (double y[34]) {
    return 0.00310000000000000;
}

double J_4_1 (double y[34]) {
    return -0.00044*y[1];
}

double J_10_1 (double y[34]) {
    return -0.013*y[1];
}

double J_0_2 (double y[34]) {
    return 0.0032*y[1];
}

double J_1_2 (double y[34]) {
    return 0.0032*y[0];
}

double J_2_2 (double y[34]) {
    return -0.00310000000000000;
}

double J_0_3 (double y[34]) {
    return -0.023*y[3];
}

double J_1_3 (double y[34]) {
    return 0.00044*y[4];
}

double J_3_3 (double y[34]) {
    return -0.023*y[0];
}

double J_4_3 (double y[34]) {
    return 0.00044*y[1] + 0.0031;
}

double J_0_4 (double y[34]) {
    return 0.023*y[3];
}

double J_3_4 (double y[34]) {
    return 0.023*y[0];
}

double J_4_4 (double y[34]) {
    return -0.05*y[32] - 0.0031;
}

double J_32_4 (double y[34]) {
    return -0.05*y[4];
}

double J_4_5 (double y[34]) {
    return -0.26*y[5]/(y[5] + 243.0);
}

double J_5_5 (double y[34]) {
    return -2.5*y[18] + 4.40312283019187e-6*y[4]*y[5]/pow((0.00411522633744856*y[5] + 1), 2) - 0.26*y[4]/(y[5] + 243.0);
}

double J_7_5 (double y[34]) {
    return 0.0257000000000000;
}

double J_18_5 (double y[34]) {
    return -2.5*y[5];
}

double J_4_6 (double y[34]) {
    return 0.26*y[5]/(y[5] + 243.0);
}

double J_5_6 (double y[34]) {
    return -4.40312283019187e-6*y[4]*y[5]/pow((0.00411522633744856*y[5] + 1), 2) + 0.26*y[4]/(y[5] + 243.0);
}

double J_6_6 (double y[34]) {
    return -5.5*y[18];
}

double J_8_6 (double y[34]) {
    return 0.0257000000000000;
}

double J_18_6 (double y[34]) {
    return -5.5*y[6];
}

double J_5_7 (double y[34]) {
    return 2.5*y[18];
}

double J_7_7 (double y[34]) {
    return -0.0257000000000000;
}

double J_18_7 (double y[34]) {
    return 2.5*y[5];
}

double J_6_8 (double y[34]) {
    return 5.5*y[18];
}

double J_8_8 (double y[34]) {
    return -0.01*y[22];
}

double J_18_8 (double y[34]) {
    return 5.5*y[6];
}

double J_22_8 (double y[34]) {
    return -0.01*y[8];
}

double J_23_8 (double y[34]) {
    return 0.00500000000000000;
}

double J_4_9 (double y[34]) {
    return -1.15*y[9]/(y[9] + 450.0);
}

double J_9_9 (double y[34]) {
    return -78.3*y[18] + 5.67901234567901e-6*y[4]*y[9]/pow((0.00222222222222222*y[9] + 1), 2) - 1.15*y[4]/(y[9] + 450.0);
}

double J_18_9 (double y[34]) {
    return -78.3*y[9];
}

double J_4_10 (double y[34]) {
    return 1.15*y[9]/(y[9] + 450.0);
}

double J_9_10 (double y[34]) {
    return -5.67901234567901e-6*y[4]*y[9]/pow((0.00222222222222222*y[9] + 1), 2) + 1.15*y[4]/(y[9] + 450.0);
}

double J_10_10 (double y[34]) {
    return -4.381*y[31];
}

double J_31_10 (double y[34]) {
    return -4.381*y[10];
}

double J_9_11 (double y[34]) {
    return 78.3*y[18];
}

double J_11_11 (double y[34]) {
    return 0.00209876543209877*y[11]*y[23]/pow((0.0158730158730159*y[11] + 1), 2) - 8.33*y[23]/(y[11] + 63.0);
}

double J_18_11 (double y[34]) {
    return 78.3*y[9];
}

double J_23_11 (double y[34]) {
    return -8.33*y[11]/(y[11] + 63.0);
}

double J_11_12 (double y[34]) {
    return -0.00209876543209877*y[11]*y[23]/pow((0.0158730158730159*y[11] + 1), 2) + 8.33*y[23]/(y[11] + 63.0);
}

double J_12_12 (double y[34]) {
    return -0.4*y[27];
}

double J_23_12 (double y[34]) {
    return 8.33*y[11]/(y[11] + 63.0);
}

double J_27_12 (double y[34]) {
    return -0.4*y[12];
}

double J_10_13 (double y[34]) {
    return -7.5e-6*y[13];
}

double J_13_13 (double y[34]) {
    return -7.5e-6*y[10] - 20.0*y[18];
}

double J_15_13 (double y[34]) {
    return 5.90000000000000;
}

double J_18_13 (double y[34]) {
    return -20.0*y[13];
}

double J_10_14 (double y[34]) {
    return 7.5e-6*y[13];
}

double J_13_14 (double y[34]) {
    return 7.5e-6*y[10];
}

double J_14_14 (double y[34]) {
    return -20.0*y[18];
}

double J_16_14 (double y[34]) {
    return 5.90000000000000;
}

double J_18_14 (double y[34]) {
    return -20.0*y[14];
}

double J_13_15 (double y[34]) {
    return 20.0*y[18];
}

double J_15_15 (double y[34]) {
    return 1.9935920256319e-5*y[15]*y[28]/pow((0.000943396226415094*y[15] + 1), 2) - 22.4*y[28]/(y[15] + 1060.0);
}

double J_18_15 (double y[34]) {
    return 20.0*y[13];
}

double J_28_15 (double y[34]) {
    return -22.4*y[15]/(y[15] + 1060.0);
}

double J_14_16 (double y[34]) {
    return 20.0*y[18];
}

double J_15_16 (double y[34]) {
    return -1.9935920256319e-5*y[15]*y[28]/pow((0.000943396226415094*y[15] + 1), 2) + 22.4*y[28]/(y[15] + 1060.0);
}

double J_18_16 (double y[34]) {
    return 20.0*y[14];
}

double J_28_16 (double y[34]) {
    return 22.4*y[15]/(y[15] + 1060.0);
}

double J_14_17 (double y[34]) {
    return 0.37*y[14]*y[17]/pow((y[14] + 1), 2) - 0.37*y[17]/(y[14] + 1);
}

double J_17_17 (double y[34]) {
    return -0.37*y[14]/(y[14] + 1) - 0.3*y[18];
}

double J_18_17 (double y[34]) {
    return -0.3*y[17];
}

double J_14_18 (double y[34]) {
    return -0.37*y[14]*y[17]/pow((y[14] + 1), 2) + 0.37*y[17]/(y[14] + 1);
}

double J_17_18 (double y[34]) {
    return 0.37*y[14]/(y[14] + 1) + 0.3*y[18];
}

double J_18_18 (double y[34]) {
    return 0.3*y[17];
}

double J_14_19 (double y[34]) {
    return -0.9*y[19]/(y[19] + 147.0);
}

double J_18_19 (double y[34]) {
    return -3.225*y[19];
}

double J_19_19 (double y[34]) {
    return 4.1649312786339e-5*y[14]*y[19]/pow((0.00680272108843537*y[19] + 1), 2) - 0.9*y[14]/(y[19] + 147.0) - 3.225*y[18];
}

double J_14_20 (double y[34]) {
    return 0.9*y[19]/(y[19] + 147.0);
}

double J_18_20 (double y[34]) {
    return -3.225*y[20];
}

double J_19_20 (double y[34]) {
    return -4.1649312786339e-5*y[14]*y[19]/pow((0.00680272108843537*y[19] + 1), 2) + 0.9*y[14]/(y[19] + 147.0);
}

double J_20_20 (double y[34]) {
    return -3.225*y[18];
}

double J_16_21 (double y[34]) {
    return -0.9*y[21]/(y[21] + 200);
}

double J_21_21 (double y[34]) {
    return 0.9*y[16]*y[21]/pow((y[21] + 200), 2) - 0.9*y[16]/(y[21] + 200);
}

double J_12_22 (double y[34]) {
    return 0.023*y[21]/(y[21] + 20.0);
}

double J_16_22 (double y[34]) {
    return 0.9*y[21]/(y[21] + 200);
}

double J_21_22 (double y[34]) {
    return -5.75e-5*y[12]*y[21]/pow((0.05*y[21] + 1), 2) + 0.023*y[12]/pow((y[21] + 20.0) - 0.9*y[16]*y[21]/(y[21] + 200), 2) + 0.9*y[16]/(y[21] + 200);
}

double J_8_23 (double y[34]) {
    return 0.01*y[22];
}

double J_22_23 (double y[34]) {
    return 0.01*y[8];
}

double J_23_23 (double y[34]) {
    return -0.00500000000000000;
}

double J_14_24 (double y[34]) {
    return -0.233*y[24]/(y[24] + 71.7);
}

double J_18_24 (double y[34]) {
    return -153.9*y[24];
}

double J_24_24 (double y[34]) {
    return 4.53228915615779e-5*y[14]*y[24]/pow((0.0139470013947001*y[24] + 1), 2) - 0.233*y[14]/(y[24] + 71.7) - 153.9*y[18];
}

double J_14_25 (double y[34]) {
    return 0.233*y[24]/(y[24] + 71.7);
}

double J_18_25 (double y[34]) {
    return -153.9*y[25];
}

double J_24_25 (double y[34]) {
    return -4.53228915615779e-5*y[14]*y[24]/pow((0.0139470013947001*y[24] + 1), 2) + 0.233*y[14]/(y[24] + 71.7);
}

double J_25_25 (double y[34]) {
    return -153.9*y[18];
}

double J_16_26 (double y[34]) {
    return -0.23*y[26]/(y[26] + 71.7);
}

double J_26_26 (double y[34]) {
    return 4.47393350178666e-5*y[16]*y[26]/pow((0.0139470013947001*y[26] + 1), 2) - 0.23*y[16]/(y[26] + 71.7);
}

double J_16_27 (double y[34]) {
    return 0.23*y[26]/(y[26] + 71.7);
}

double J_26_27 (double y[34]) {
    return -4.47393350178666e-5*y[16]*y[26]/pow((0.0139470013947001*y[26] + 1), 2) + 0.23*y[16]/(y[26] + 71.7);
}

double J_12_28 (double y[34]) {
    return 0.4*y[27];
}

double J_27_28 (double y[34]) {
    return 0.4*y[12];
}

double J_28_28 (double y[34]) {
    return -0.200000000000000;
}

double J_14_29 (double y[34]) {
    return -59.0*y[29]/(y[29] + 3160.0);
}

double J_29_29 (double y[34]) {
    return 5.90850825188271e-6*y[14]*y[29]/pow((0.000316455696202532*y[29] + 1), 2) - 59.0*y[14]/(y[29] + 3160.0);
}

double J_14_30 (double y[34]) {
    return 59.0*y[29]/(y[29] + 3160.0);
}

double J_29_30 (double y[34]) {
    return -5.90850825188271e-6*y[14]*y[29]/pow((0.000316455696202532*y[29] + 1), 2) + 59.0*y[14]/(y[29] + 3160.0);
}

double J_10_31 (double y[34]) {
    return -4.381*y[31];
}

double J_31_31 (double y[34]) {
    return -4.381*y[10];
}

double J_32_31 (double y[34]) {
    return 5.29300000000000e-8;
}

double J_4_32 (double y[34]) {
    return -0.05*y[32];
}

double J_10_32 (double y[34]) {
    return 4.381*y[31];
}

double J_31_32 (double y[34]) {
    return 4.381*y[10];
}

double J_32_32 (double y[34]) {
    return -0.05*y[4] - 5.293e-8;
}

double J_4_33 (double y[34]) {
    return 4.5e-7*y[33];
}

double J_6_33 (double y[34]) {
    return 0.0002223*y[33];
}

double J_10_33 (double y[34]) {
    return 3.05e-6*y[33];
}

double J_14_33 (double y[34]) {
    return 0.000179*y[33];
}

double J_33_33 (double y[34]) {
    return 3.05e-6*y[10] + 0.000179*y[14] + 4.5e-7*y[4] + 0.0002223*y[6];
}

