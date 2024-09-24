
	%% Prelab 3
Vs1 = 5; % voltmeter part source voltage
Vs2 = 2; % ammeter part source voltage
Rs_voltage = 100e3;
Rs_current = 100;
R1 = [15e3; 20e3; 30e3; 56e3; 100e3]; % Nominal

R2 = [51; 62; 100; 270; 330]; % Nominal

Rvm = 100e3;
Ram = 100;
% Part 1 Problem 1
% initialize null matrix before loop starts
v1 = []; v1L = []; E1=[];
% loop to calculate voltages (column vector) with or without meters
for n=1:length(R1)
% formulas to calculate the voltages (column vector)
v(n,1) = Vs1*(R1(n) / (R1(n) + Rs_voltage));
vL(n,1) = Vs1*Rvm*R1(n) / (Rvm*R1(n) + Rs_voltage*(R1(n) + Rvm));
E_voltage(n,1) = 100*(vL(n,1) - v(n,1)) / v(n,1);
end
% append the column to the null matrix
v1 = [v1 v]; v1L = [v1L vL]; E1 = [E1 E_voltage];
% append all 3 columns to create an output matrix
X1 = [v1 v1L E1];
% display heading and the output matrix
disp(' v1 v1L E1')
disp(X1)
% Part 1 Problem 2
% calculate and extract the meter resistance from meter voltages
for n = 1:length(v1L)
% calculate Rvm in kOhm
Rvm_calc(n,1) = 1e-3*(v1L(n)*Rs_voltage*R1(n))/ ((Vs1*R1(n)) - (v1L(n)*R1(n)) - (v1L(n)*Rs_voltage));
end
Y1 = [v1L Rvm_calc];
disp(' v1L Rvm_calculated in kOhm')
disp(Y1)
% Part 2 Problem 1
i2 = []; i2L = []; E2=[];
for n=1:length(R2)
% calculate currents (column matrix) in mA
i(n,1) = Vs2/(Rs_current + R2(n))*10^3;
iL(n,1) = Vs2/(Rs_current + R2(n) + Ram)*10^3;
E_current(n,1) = 100*(iL(n,1) - i(n,1)) / i(n,1);
end
i2 = [i2 i]; i2L = [i2L iL]; E2 = [E2 E_current];
X2 = [i2 i2L E2];
disp(' i2(mA) i2L(mA) E2')
disp(X2)
% Part 2 Problem 2
for n = 1:length(i2L)
Ram_calc(n,1) = (Vs2/(i2L(n)*10^-3)) - Rs_current - R2(n);
end
Y2 = [i2L Ram_calc];
disp(' i2L(mA) Ram_calculated')
disp(Y2)
