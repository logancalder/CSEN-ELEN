%% Prelab 7

% Name: Logan Calder
% Lab Number: 7
% Class: ECEN 50L
% Date: 6/4/24
% Section time: 14:15T

% Clear output
clc;

%% Variable Initialization
Rs1 = 1e3;
Rf1 = 10e3;

Rs2 = Rs1;
Rf2 = 3.9e3;

Rs = 1e3;

%% Part a

G1 = -(Rf1/Rs1);
G2 = (Rf2/Rs2) + 1;
G3 = 1;

gains = {'G1';'G2';'G3'};
gain_values = [G1;G2;G3];
T = table(gains,gain_values,'VariableNames',{'Gain','Value'});
disp(T)
