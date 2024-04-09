%% Header

% Name: Logan Calder
% Lab Number: 1
% Class: ECEN 50L
% Date: 4/9/24
% Section time: 14:00T

%% Part 5

A = [ 2,1; 3,2];
B = [ 3,1; 2,2];

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

% Name: Logan Calder
% Lab Number: 1
% Class: ECEN 50L
% Date: 4/9/24
% Section time: 14:00T

%% Inverses

% We may see that the below matrices being multiplied are inverses as they
% produce the identity matrix.

disp(A1*A5); 
disp(A3*A6);
disp(A2*A7);
disp(A4*A8);

%% Matrix Multiplications
% The below matrix multiplications produce the same results.

disp(A1*(A*B));
disp((A*B)*A1);