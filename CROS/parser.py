import sympy as sym
import re

TF_0 = 5
VII_0 = 10.0
TF__VII_0 = 0.0
VII_a_0 = 0.1
TF__VII_a_0 = 0.0
IX_0 = 90.0
IX_a_0 = 0.009
IX_m_0 = 0.0
IX_a_m_0 = 0.0
X_0 = 170
X_a_0 = 0.017
X_m_0 = 0.0
X_a_m_0 = 0.0
II_0 = 1400.0
II_a_0 = 0.14
II_m_0 = 0.0
II_a_m_0 = 0.0
PL_0 = 10.0
AP_0 = 0.001
VIII_0 = 0.7
VIII_a_0 = 0.00007
VIII_m_0 = 0.0
VIII_a_m_0 = 0.0
VIII_a_m__IX_a_m_0 = 0.0
V_0 = 20.0
V_a_0 = 0.002
V_m_0 = 0.0
V_a_m_0 = 0.0
X_a_m__V_a_m_0 = 0.0
I_0 = 7000.0
I_a_0 = 0.70
TFPI_0 = 2.5
X_a__TFPI_0 = 0.0
ATIII_0 = 3400

k_T7_pl = 0.0032
k_T7_min = 0.0031
k_T7a_pl = 0.023
k_T7a_min = 0.0031
k_TF7 = 0.00044
k_10_7 = 0.013
k_2_7 = 0.000023
h_7_TP = 0.05
h_7_AT = 0.00000045
k_9 = 0.26
K_9M = 243.0
k_9_pl = 0.01
k_9_min = 0.0257
h_9 = 0.0002223
N_9 = 250
N_9a = 550
k_TEN_pl = 0.01
k_TEN_min = 0.0050
k_7_10 = 1.15
K_7_10M = 450.0
k_10_pl = 0.029
k_10_min = 3.3
N_10 = 2700
h_10_TP_pl = 4.381
h_10_TP_min = 0.00000005293
h_10_AT = 0.00000305
k_10 = 8.33
K_10M = 63.0
k_PRO_pl = 0.4
k_PRO_min = 0.2
k_2t = 0.0000075
k_2_pl = 0.01
k_2_min = 5.9
N_2 = 2000
N_2a = 2000
h_2 = 0.000179
k_2 = 22.4
K_2M = 1060.0
k_pp = 0.3
k_p2 = 0.37
k_8 = 0.9
K_8M = 147.0
k_8_pl = 0.0043
k_8_min = 0.00246
N_8 = 750
h_8 = 0.0037
k_8_m = 0.9
K_8M_m = 200
k_8t_m = 0.023
K_8tM_m = 20.0
k_5 = 0.233
K_5M = 71.7
k_5_pl = 0.057
k_5_min = 0.17
N_5 = 2700
h_5 = 0.0028
k_5_m = 0.23
K_5M_m = 71.7
k_5t_m = 0.046
K_5tM_m = 10.4
k_f = 59.0
K_fM = 3160.0
K_M14 = 1

ynames = ["y" + str(i) for i in range(34)]
y0, y1, y2, y3, y4, y5, y6, y7, y8, y9, \
    y10, y11, y12, y13, y14, y15, y16, y17, y18, y19, \
    y20, y21, y22, y23, y24, y25, y26, y27, y28, y29, \
    y30, y31, y32, y33 = sym.symbols(ynames)

coords = y0, y1, y2, y3, y4, y5, y6, y7, y8, y9, \
    y10, y11, y12, y13, y14, y15, y16, y17, y18, y19, \
    y20, y21, y22, y23, y24, y25, y26, y27, y28, y29, \
    y30, y31, y32, y33

f0 = -k_T7_pl * y0 * y1 + k_T7_min * y2 - k_T7a_pl * y0 * y3 + k_T7a_min * y4
f1 = -k_T7_pl * y0 * y1 + k_T7_min * y2 - k_TF7 * y4 * y1 - k_10_7 * y10 * y1
- k_2_7 * y14 * y1
f2 = k_T7_pl * y0 * y1 - k_T7_min * y2
f3 = -k_T7a_pl * y0 * y3 + k_T7a_min * y4 + k_TF7 * y4 * y1
+ k_10_7 * y10 * y1 + k_2_7 * y14 * y1
f4 = k_T7a_pl * y0 * y3 - k_T7a_min * y4 - h_7_TP * y32 * y4
- h_7_AT * y33 * y4
f5 = -k_9 * y4 * y5 / (K_9M + y5) - k_9_pl * N_9 * y18 * y5 + k_9_min * y7
f6 = k_9 * y4 * y5 / (K_9M + y5) - k_9_pl * N_9a * y18 * y6 + k_9_min * y8
- h_9 * y6 * y33
f7 = k_9_pl * N_9 * y18 * y5 - k_9_min * y7
f8 = -k_TEN_pl * y22 * y8 + k_TEN_min * y23 + k_9_pl * N_9a * y18 * y6
- k_9_min * y8
f9 = -k_7_10 * y4 * y9 / (K_7_10M + y9) - k_10_pl * N_10 * y18 * y9
+ k_10_min * y11
f10 = k_7_10 * y4 * y9 / (K_7_10M + y9) - h_10_TP_pl * y31 * y10
+ h_10_TP_min * y32 - h_10_AT * y33 * y10 - k_10_pl * N_10 * y18 * y10
+ k_10_min * y12
f11 = -k_10 * y23 * y11 / (K_10M + y11) + k_10_pl * N_10 * y18 * y9
- k_10_min * y11
f12 = k_10 * y23 * y11 / (K_10M + y11) - k_PRO_pl * y27 * y12
+ k_PRO_min * y28 + k_10_pl * N_10 * y18 * y10 - k_10_min * y12
f13 = -k_2t * y10 * y13 - k_2_pl * N_2 * y18 * y13 + k_2_min * y15
f14 = k_2t * y10 * y13 - k_2_pl * N_2a * y18 * y14 + k_2_min * y16
- h_2 * y33 * y14
f15 = -k_2 * y28 * y15 / (K_2M + y15) + k_2_pl * N_2 * y18 * y13
- k_2_min * y15
f16 = k_2 * y28 * y15 / (K_2M + y15) + k_2_pl * N_2a * y18 * y14
- k_2_min * y16
f17 = -k_pp * y17 * y18 - k_p2 * y17 * y14 / (K_M14 + y14)
f18 = k_pp * y17 * y18 + k_p2 * y17 * y14 / (K_M14 + y14)
f19 = -k_8 * y14 * y19 / (K_8M + y19) - k_8_pl * N_8 * y18 * y19
+ k_8_min * y21
f20 = k_8 * y14 * y19 / (K_8M + y19) - k_8_pl * N_8 * y18 * y20
+ k_8_min * y22 - h_8 * y20
f21 = -k_8_m * y16 * y21 / (K_8M_m + y21)
-k_8t_m * y12 * y21 / (K_8tM_m + y21) + k_8_pl * N_8 * y18 * y19
- k_8_min * y21
f22 = k_8_m * y16 * y21 / (K_8M_m + y21) + k_8t_m * y12 * y21 / (K_8tM_m + y21)
+ k_8_pl * N_8 * y18 * y20 - k_8_min * y22 - k_TEN_pl * y22 * y8
+ k_TEN_min * y23
f23 = k_TEN_pl * y22 * y8 - k_TEN_min * y23
f24 = -k_5 * y14 * y24 / (K_5M + y24) - k_5_pl * N_5 * y18 * y24
+ k_5_min * y26
f25 = k_5 * y14 * y24 / (K_5M + y24) - k_5_pl * N_5 * y18 * y25
+ k_5_min * y27 - h_5 * y25
f26 = -k_5_m * y16 * y26 / (K_5M_m + y26)
- k_5t_m * y12 * y26 / (K_5tM_m + y26) + k_5_pl * N_5 * y18 * y24
- k_5_min * y26
f27 = k_5_m * y16 * y26 / (K_5M_m + y26)
+ k_5t_m * y12 * y26 / (K_5tM_m + y26) - k_PRO_pl * y12 * y27
+ k_PRO_min * y28 + k_5_pl * N_5 * y18 * y25 - k_5_min * y27
f28 = k_PRO_pl * y12 * y27 - k_PRO_min * y28
f29 = -k_f * y14 * y29 / (K_fM + y29)
f30 = k_f * y14 * y29 / (K_fM + y29)
f31 = -h_10_TP_pl * y10 * y31 + h_10_TP_min * y32
f32 = h_10_TP_pl * y10 * y31 - h_10_TP_min * y32 - h_7_TP * y4 * y32
f33 = y33 * (h_10_AT * y10 + h_9 * y6 + h_2 * y14 + h_7_AT * y4)

functions = f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, \
    f10, f11, f12, f13, f14, f15, f16, f17, f18, f19, \
    f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, \
    f30, f31, f32, f33
i, j = 0, 0
with open("Jmatrix.h", "w") as text_file:
    for f in functions:
        for y in coords:
            buff = str(sym.diff(f, y))
            if buff != '0':
                buff = re.sub(r'(y)(\d+)', r'y[\2]', buff)
                buff = (re.sub(r'(\(.*?\))\*\*(\d+)', r'pow(\1, \2)', buff))
                print(f"double J_{i}_{j} (double y[34]) {{\n    return {buff};\n}}\n", file=text_file)
            i += 1
        i = 0
        j += 1
