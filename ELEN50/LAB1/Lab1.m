%% Header

% Name: Logan Calder
% Lab Number: 1
% Class: ECEN 50L
% Date: 4/9/24
% Section time: 14:15T

%% PART 1

% Equation Creation

disp((3.7*4+3*5+2.3*3)/(4+5+3)); % Displaying the equation to console

%% PART 2

% Cosine of a value in even steps

a=pi*0.1*[0:19];
disp(cos(a)); % Displays the cos of a in even steps of 0.1pi * i, where i is 0:19.

%% PART 3

% Creating Plot


% Below is equation and varaible declaration

t=[0:0.01:100]; % This is the range for t var
a = pi * [0:0.05:12]; % Range for a var
plot (t, exp(-t), a, cos(a), linewidth=1.5); %% Plotting each var w/ respective equations

% The bellow is plot formatting

xlim([0,12*pi]);
title('f=exp(-t),g=cos(a)');
xticks(pi*[0:1:12]);
Labels = string([0:1:12]) + "\pi";
xticklabels(Labels);
legend("exp(-t)" , "cos(a)");
set(findall(gca, '-Property', 'FontName'), 'FontName', 'Times New Roman');
grid on;

%% PART 4

clear all;
close all;

% Equation Creation
syms x;
f = (exp(-3*x) + 10*sin(x+1)) / (cos(x+1));
g = (exp(-2*x) / (1+(exp(-2*x))));
h = -4*x^2;

% Differentiation

Df1 = diff(f,x);
Df2 = diff(g,x);

pretty(Df1);
pretty(Df2);

% Integration

If1 = int(h,x, [-2,2]);

pretty(If1);

%% PART 5

A = [ 2,1; 3,2];
B = [ 3,1; 2,2];

% Transposes

disp(A');
disp(B');

% Matmul

A1 = A * B;
A2 = B * A;
A3 = (A'* B')';
A4 = (B' * A')';

disp(A1); % Same as A4
disp(A2); % Same as A3
disp(A3);
disp(A4);

A5 = inv (A * B);
A6 = inv(A) * inv(B);
A7 = inv (B * A);
A8 = inv(B) * inv(A);

% Inverses

% We may see that the below matrices being multiplied are inverses as they
% produce the identity matrix.

disp(A1*A5); 
disp(A3*A6);
disp(A2*A7);
disp(A4*A8);

% Matrix Multiplications
% The below matrix multiplications produce the same results.

disp(A1*(A*B));
disp((A*B)*A1);

%% PART 6

% Matrix Declarations
C = [ 1,0,1; 3,3,4; 2,2,3];
S = [10;12;5];

% Inverting C
Ci = inv(C)

% Calculating Answer
V = Ci*S

% Double Checking Work

C*V % This gives us S, verifying the work

%% PART 7

% Clearing

clear all;
close all;

% Entering Variables for Known Variables

% Voltages
Vs = 12;

% Current
Is1 = 4e-3;
Is2 = 2e-3;

% Resistance
R1 = 1e3;
R2 = R1;
R3 = R1;
R4 = R1;
R5 = R1;
R6 = R1;

% Define Unknown Symbolic Variables

syms Va Vb Vc Vd;

% Equations

eq1 = -Is1 + (Va-Vb)/R1 + (Vd-Vc)/R2 + Vd/R5 + Vd/(R3+R6) == 0;
eq2 = (Vb-Va)/R1 + Is2 + Vc/R4 + (Vc-Vd)/R2 == 0;
eq3 = Vc - Vb == Vs;
eq4 = Vd - Va == 2*Vc;

% Enter Equations & Variables
eqns = [eq1, eq2, eq3, eq4];
vars = [Va, Vb, Vc, Vd];

% Turning Equations to Matrix

[C, S] = equationsToMatrix(eqns, vars);


% Solving For V

V = inv(C) * S;
pretty(C);
pretty(S);
pretty(V)
