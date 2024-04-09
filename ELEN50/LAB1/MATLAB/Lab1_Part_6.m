%% Header

% Name: Logan Calder
% Lab Number: 1
% Class: ECEN 50L
% Date: 4/9/24
% Section time: 14:00T

%% Matrix Declarations
C = [ 1,0,1; 3,3,4; 2,2,3];
S = [10;12;5];

% Inverting C
CI = inv(C);

%% Calculating Answer
V = CI*S
disp(V);

%% Double Checking Work

disp(C*V); % This gives us S, verifying the work