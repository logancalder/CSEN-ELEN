%% Prelab 5

% Name: Logan Calder
% Lab Number: 5
% Class: ECEN 50L
% Date: 5/7/24
% Section time: 14:15T

% Clear output
clc;

%% Variable Initialization

R1 = 0.985e3;
R2 = 1.995e3;
R3 = 3.015e3;
R4 = 3.894e3;
R5 = 4.628e3;
R6 = 5.468e3;
R7 = 8.147e3;
R8 = 14.98e3;
R9 = 19.9e3;

Vs1 =9.998;
Vs2 = 3.995;

%% Solving for Voc

V1 = Vs1;
V4 = Vs2;

syms V2 V3 V5
vars = [V2, V3, V5];

eq1 = (V3-V2)/R3 + (V3-V4)/R6 + (V3-V1)/R2 + (V3-V5)/R7 == 0;
eq2 = (V2-V1)/R1 + (V2-V3)/R3 + V2/R9 + (V2-V5)/R5 == 0;
eq3 = (V5-V3)/R7 + (V5-V2)/R5 + (V5-V4)/R8 == 0;
eqns = [eq1, eq2, eq3];

voltages = solve(eqns, vars);

V2  = double(voltages.V2);
V3  = double(voltages.V3);
V5  = double(voltages.V5);
Voc = V5;

%% Solving for Isc

V5 = 0;

syms V2 V3  % define symbols
vars = [V2, V3];

eq1 = (V3-V5)/R7 + (V3-V2)/R3 + (V3-V1)/R2 + (V3-V4)/R6 == 0;
eq2 = (V2-V3)/R3 + (V2-V5)/R5 + V2/R9 + (V2-V1)/R1 == 0;
eqns = [eq1, eq2];

voltages = solve(eqns, vars);

V2  = double(voltages.V2);
V3  = double(voltages.V3);

IR5 = V2/R5;
IR7 = V3/R7;
IR8 = V4/R8;
Isc = IR5 + IR7 + IR8;

%% Solving for Rth
% Using that V = IR & Thus Voc = Isc/Rth
Rth = Voc/Isc;

%% Solving for Power Max
% P = Voc^2/4Rth
PRmax = (Voc^2)/(4*Rth)

%% Solving for Ratio of Max Power to Total Power Delivered

RL = Rth;

syms V2 V3 V5
vars = [V2, V3, V5];

eq1 = (V3-V5)/R7 + (V3-V2)/R3 + (V3-V1)/R2 + (V3-V4)/R6 == 0;
eq2 = (V2-V3)/R3 + (V2-V5)/R5 + V2/R9 + (V2-V1)/R1 == 0;
eq3 = (V5-V2)/R5 + (V5-V3)/R7 + (V5-V4)/R8 + (V5/RL) == 0;
eqns = [eq1, eq2, eq3];

voltages = solve(eqns, vars);

V2  = double(voltages.V2);
V3  = double(voltages.V3);
V5  = double(voltages.V5);

Is1 = (V1-V2)/R1 + (V1-V3)/R2 + (V1-V4)/R4;
Is2 = (V4-V1)/R4 + (V4-V3)/R6 + (V4-V5)/R8;

Ps1 = Vs1 * Is1;
Ps2 = Vs2 * Is2;
Pst = Ps1 + Ps2;

PRL = (V5^2)/RL;

rat = PRL/Pst;

Isc = Isc*1000; % mA
Rth = Rth/1000; % kohms
Ps1 = Ps1*1000; % mW
Ps2 = Ps2*1000; % mW
PRL = PRL*1000; % mW
table(Voc, Isc, Rth, Ps1, Ps2, PRL, rat)