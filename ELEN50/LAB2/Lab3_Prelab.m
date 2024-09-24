%% Prelab 3

% Name: Logan Calder
% Lab Number: 2
% Class: ECEN 50L
% Date: 4/23/24
% Section time: 14:15T

%% Part 1 - Solving For Resistors in Series

Vs = 5;
Rs = 10e4;
Rvm = 10e5;
R1 = [15e3;20e3;30e3;56e3;100e3];

% V = IR so I = V/R

Rt = R1+Rs; % They are in series so add

Irs = Vs/(R1+Rs)
Vrs = Irs*Rs
V1 = Irs*R1

%% Part 2 - Solving For Complex Circuit

syms Irs I1 Irvm Vrs V1 Vrvm;

eq1 = Irs == Vrs/Rs;
eq2 = Irs - I1 - Irvm == 0;
eq3 = Vs-Vrs-V1 == 0;
eq4 = V1 == Vrvm;
eq5 = I1 == V1/R1;
eq6 = Irvm == Vrvm/Rvm;


eqns = [eq1, eq2, eq3, eq4, eq5, eq6];

vars = [Irs, I1, Irvm, Vrs, V1, Vrvm];

[C, S] = equationsToMatrix(eqns, vars);
V = inv(C) * S;
Vdouble = double(V)

%% Part 3 - Kirchhoff Laws

syms I1 I2 I3 I4 I5 V1 V2 V3 V4 V5 V6;

R56 = R5 + R6;
R456 = (R4+R56)/(R4*R56);

eq1 = Vs - V1 - V2 == 0;
eq2 = I1 == V1/R1;
eq3 = I2 == V2/R2;
eq4 = I3 == V3/R3;
eq5 = I4 == V4/R4;
eq6 = I5 == V5/R5;
eq7 = I5 == V6/R6;
eq8 = V5+V6-V4 == 0;
eq9 = V3 + V4 - V2 == 0;
eq10 = I3 + I2 - I1 == 0;
eq11 = I5 + I4 - I3 == 0;

eqns = [eq1, eq2, eq3, eq4, eq5, eq6, eq7, eq8, eq9, eq10, eq11];


vars = [I1,I2,I3,I4,I5,V1,V2,V3,V4,V5,V6];

[C, S] = equationsToMatrix(eqns, vars);
V = inv(C) * S;
double(V)

% Assign values from V back to the variables
I1 = V(1);
I2 = V(2);
I3 = V(3);
I4 = V(4);
I5 = V(5);
V1 = V(6);
V2 = V(7);
V3 = V(8);
V4 = V(9);
V5 = V(10);
V6 = V(11);

% Verify KCL:

I2+I3-I1 % a
I5+I4-I3 % b

% Verify KVL:

Vs-V1-V2
V3+V4-V2
V5+V6-V4

%% Part 4 - Nominal Value of Resistors

% Brown Black Red >>> 1000 Ohm
% Red Purple Red >>> 2700 Ohm

