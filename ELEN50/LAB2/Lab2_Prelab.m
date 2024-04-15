%% Prelab 2

% Name: Logan Calder
% Lab Number: 2
% Class: ECEN 50L
% Date: 4/16/24
% Section time: 14:15T

%% Part 1 - Solving For Resistors in Series

Vs = 10;

R1 = 1000;
R2 = 2000;
R3 = 3000;
R4 = 4700;
R5 = 7500;
R6 = 9100;

% V = IR so I = V/R

Rt = R1+R2; % They are in series so add

I1 = Vs/(R1+R2)
V1 = I1*R1
V2 = I1*R2

%% Part 2 - Solving For Complex Circuit

syms I1 I2 V1 V2 V3 I3;

R23 = (R2+R3)/(R2*R3);

eq1 = I1 == V1/R1;
eq2 = I1 - I2 - I3 == 0;
eq3 = Vs-V1-V2 == 0;
eq4 = V3 == V2;
eq5 = I2 == V2/R2;
eq6 = I3 == V3/R3;


eqns = [eq1, eq2, eq3, eq4, eq5, eq6];

vars = [I1,I2,I3,V1,V2,V3];

[C, S] = equationsToMatrix(eqns, vars);
V = inv(C) * S

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
V = inv(C) * S

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

