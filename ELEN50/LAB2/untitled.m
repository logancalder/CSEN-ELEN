
Vs = 10;

R1 = 987;
R2 = 1990;
R3 = 2971;
R4 = 4637;
R5 = 7372;
R6 = 9043;

syms I1 I2 I3 I4 V1 V2 V3 V4;

R234 = (R3*R2 + R2*R4 + R3*R4)/(R3*R2*R4);

eq1 = I1 == V1/R1;
eq2 = I2 == V2/R2;
eq3 = I3 == V3/R3;
eq4 = I4 == V4/R4;
eq5 = R1 == R234;
eq6 = Vs - V1 - V2 == 0;
eq7 = V4 - V3 == 0;
eq8 = V3 - V2 == 0;


eqns = [eq1, eq2, eq3, eq4, eq5, eq6, eq7, eq8];

vars = [I1,I2,I3,I4,V1,V2,V3,V4];

[C, S] = equationsToMatrix(eqns, vars);
V = inv(C) * S;
double(V)
