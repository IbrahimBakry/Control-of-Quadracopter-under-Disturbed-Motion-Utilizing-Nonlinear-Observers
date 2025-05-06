function [ U1 ] = U1_Controller( in )
glob;

phi=in(1);
theta=in(2);
psi=in(7);

zar=in(5);
zaf=in(6);
U0=in(9);

% %% For Control by nonlinear feadback;
% Controller Equation;
U1=((U0 + g*cos(phi)*cos(theta))* m - (zar-zaf))/(cos(psi)*cos(phi));

end
