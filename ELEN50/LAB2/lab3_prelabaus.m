%% Prelab 3

% Name: Logan Calder
% Lab Number: 2
% Class: ECEN 50L
% Date: 4/23/24
% Section time: 14:15T

%% Part 1
Vs = 5;
Rs = 10e4;
Rvm = 15e5;
R1 = [15e3;20e3;30e3;68e3;100e3];

% Expected Value of v1
I = Vs./(Rs+R1);
V1 = Is .* R1;

% Expected value of v1L
R1vm = (R1.*Rvm)./(Rvm+R1);
Rt = (R1vm + Rs);
I = Vs./Rt;
V1L = I .* R1;

% Expected value of E1
E1 = (V1L - V1)./V1*100; % This is a provided formula

% Expected value of Rvm for known v1L
RmvL = V1L.*R1.*Rs./(Vs*R1-v1L.*(R1+Rs));
table_A = table (R1,V1,V1L, E1, RmvL)

%% Part 2

Vs = 2;
Rs = 98.5;
Ram = 1.902;
R2 = [51.1,61.6,98.4,267.8,326.5];

% Expected value of i2
I2 = Vs./(Rs + R2) * 1000;

% Expected value of i2L
I2L = Vs./(Rs + R2 + Ram) * 1000;

% Expected % error
E2 = (I2L - I2)./I2 * 100; % This is really big but seems right

% Expected RamL value
RamL = ((Vs ./I2L) * 10e2 - Rs - R2 );
R2 = R2';
I2 = I2';
I2L = I2L';
E2 = E2';
RamL = RamL';
table_B = table (R2,I2,I2L,E2,RamL)
