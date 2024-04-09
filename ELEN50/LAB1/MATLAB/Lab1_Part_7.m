%% Header

% Name: Logan Calder
% Lab Number: 1
% Class: ECEN 50L
% Date: 4/9/24
% Section time: 14:00T

%% Clearing

clear all;
close all;

%% Entering Variables for Known Variables

Vs1 = 6;
Vs2 = 12;
Is1 = 2e-3;
...
R1 = 1e3;

%% Define Unknown Symbolic Variables

syms Va Vb Vc Vd;

%% Equations

eq1 = (Va-Vb)/R1 - Is1 + (Va-Vd)/R2 - Is3 == 0;
...

%% Enter Equations & Variables
eqns = [eq1, eq2, eq3, eq4];
vars = [Va, Vb, Vc, Vd];

%% Turning Equations to Matrix

[C, S] = equationsToMatrix(eqns, vars);

%% Solving For V

V = inv(C) * S;

