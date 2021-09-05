%% Parameters
% l/w/h = 30/0.25/0.1 mm nu = 0.89 mPa s 

l = 30e-3;
w = 0.25e-3;
h = 0.1e-3;
ratio = h/w;

% hydraulic resistance [Pa s m^-3]
% water viscosity nu = 0.89e-3 Pa s 
nu = 0.89e-3;
Rhyd = 12 * nu * l * h^(-3) * w^(-1);

% Qmin = 0.1µl/min
% Qmax = 1ml/min
% Qreg < 0.05 µl/min

Qmin = 1.6666666666667e-12;
Qmax = 1.6666666666667e-8;
Qreg = 0.5*Qmin; 

% less accurate equation

pmin = Rhyd * Qmin * 1e-2
pmax = Rhyd * Qmax * 1e-2
preg = Rhyd * Qreg * 1e-2

% accurate equation

acc_estimation_pmin = Rhyd * Qmin * 1e-2 / (1-0.63*ratio)
acc_estimation_pmax = Rhyd * Qmax * 1e-2 / (1-0.63*ratio)

% percentage difference between results

percentage_diff = (acc_estimation_pmax - pmax) / pmax *100