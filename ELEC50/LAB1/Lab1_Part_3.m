%% Header

% Name: Logan Calder
% Lab Number: 1
% Class: ECEN 50L
% Date: 4/9/24
% Section time: 14:00T

%% Creating Plot


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
