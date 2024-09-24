%% Prelab 4

% Name: Logan Calder
% Lab Number: 4
% Class: ECEN 50L
% Date: 4/30/24
% Section time: 14:15T

% Clear output
clc;

%% Part 1

R1 = 1.199e3;
R2 = 2.963e3;
R3 = 5.475e3;
R4 = 8.218e3;
R5 = 14.832e3;
R6 = 19.686e3;

Req1 = (R3*R4)/(R3+R4);
Req2 = (Req1*(R2+R5)/(Req1+R2+R5));

Vs = 11.9985;
V4 = (Req2/(R1+Req2+R6))*Vs;
V5 = (R5/(R2+R5))*V4;

IR4 = V4/R4 * 1e3;
IR5 = V5/R5 * 1e3;

PR4 = IR4 * V4; % This is already mW since we 
PR5 = IR5 * V5; % multiplied by 1e3 above.

table_1 = table (V4,V5,IR4, IR5, PR4, PR5)


%% Part 2

R1 = 2.958e3;
R2 = 8.218e3;
Radj = 179.5e3;

Rx = (R2/R1)*Radj;
Rt = ((1/(Radj + Rx)) + (1/(R1+R2)))^-1;

Vs = 10;

is = Vs/Rt * 1e3;

table_2 = table (R1,R2,Radj, Rx, is)