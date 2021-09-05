%% Parameters
% l/w/h = 30/0.25/0.1 mm
% nu = 1 mPa s 
%

l = 30e-3;
w = 0.25e-3;
h = 0.1e-3;

% hydraulic resistance [Pa s m^-3]
% water viscosity nu = 1e-3 Pa s 
nu = 1e-3;
Rhyd = 12 * nu * l * h^(-3) * w^(-1);

% Qmin = 0.1µl/min
% Qmax = 1ml/min
% Qreg < 0.05 µl/min

Qmin = 1.67e-10;
Qmax = 1.67e-8;
Qreg = 0.5*Qmin; 

pmin = Rhyd * Qmin * 1e-2
pmax = Rhyd * Qmax * 1e-2
preg = Rhyd * Qreg * 1e-2

% conversion to mbar 
