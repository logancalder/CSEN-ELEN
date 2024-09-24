%% Prelab 6

% Name: Logan Calder
% Lab Number: 5
% Class: ECEN 50L
% Date: 5/21/24
% Section time: 14:15T

% Clear output
clc;

%% Variable Initialization
Vs = 2;

C1 = 1e-6;
C2 = 2.2e-6;
C3 = 4.7e-6;

%% Part 1

Ceq = 1/C1 + 1/C2 + 1/C3;
Ceq = 1/Ceq;

V1 = (Ceq/C1) * Vs;
V2 = (Ceq/C2) * Vs;
V3 = (Ceq/C3) * Vs;

capacitors = {'C1';'C2';'C3'};
voltages = [V1;V2;V3];
T = table(capacitors,voltages,'VariableNames',{'Capacitor','Voltage(V)'});
disp(T)

%% Part 2

R1 = 500;
R2 = 750;

T1 = R1 * C1;
T2 = R2 * C1;

time_const = {'T1';'T2'};
values = [T1;T2];
T = table(time_const,values,'VariableNames',{'Time Constant','Value (s)'});
disp(T)
