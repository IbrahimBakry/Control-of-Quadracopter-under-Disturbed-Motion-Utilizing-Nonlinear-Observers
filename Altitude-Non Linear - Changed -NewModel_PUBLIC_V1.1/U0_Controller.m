function [ out ] = U0_Controller( in )
glob;

estx1=in(1);
estx2=in(2);
zd=in(4);

estz=estx1;
estdotz=estx2;

% controller constants;
a1=2;   % 2
a2=6;    % 6
a3=5;     % 5

% Integrator;
Afterintegrat=in(5);
integ=estz-zd;
out(1)=integ;

%% For Control by nonlinear feadback;
V1=-a1*estdotz-a2*(estz-zd)-a3*Afterintegrat;
out(2)=V1;


% %%  for active disturbance rejection control "ADRC"  Structure;
% % Controller Equation;
% U0=Kp*(r-estx1)-Kd*estx2 ;% Ki*Afterintegrat;
% out(2)=U0;

end

