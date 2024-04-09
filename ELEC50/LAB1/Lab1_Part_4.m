%% Header

% Name: Logan Calder
% Lab Number: 1
% Class: ECEN 50L
% Date: 4/9/24
% Section time: 14:00T

clear all;
close all;

%% Equation Creation
syms x;
f = (exp(-3*x) + 10*sin(x+1)) / (cos(x+1));
g = (exp(-2*x) / (1+(exp(-2*x))));
h = -4*x^2;

%% Differentiation

Df1 = diff(f,x);
Df2 = diff(g,x);

pretty(Df1);
pretty(Df2);

%% Integration

If1 = int(h,x, [-2,2]);

pretty(If1);