function [out]=ATT_observer(in)
glob;

% eddphi=estddotphi;
% eddpsi=estddotpsi;
% eddtheta=estddottheta;
% edphi=estdotphi;
% edpsi=estdotpsi;
% edtheta=estdottheta;

% Inputs;
phi=in(7);
theta=in(9);
psi=in(11);

estphi=in(1);
esttheta=in(2);
estpsi=in(3);

edphi=in(30);
edtheta=in(31);
edpsi=in(32);

U2=in(4);
U3=in(5);
U4=in(6);

% Add ATT_Terms Inputs;
RhF=in(33);
RrM=in(34);
PhF=in(35);
PrM=in(36);
YhFx=in(37);
YhFy=in(38);
YiA=in(39);

% "Omegar" residual propellers rot. speed [rad/s]
omega=in(26:29);    % [rad/s]
omegar=+omega(1)-omega(2)+omega(3)-omega(4); 

% Observer Equations Parameters;
a1=(Iyy-Izz)/Ixx;
a2=jr/Ixx;
a3=(Izz-Ixx)/Iyy;
a4=jr/Iyy;
a5=(Ixx-Iyy)/Izz;

b1=L/Ixx;
b2=L/Iyy;
b3=1/Izz;

% observer Gain;
LO=[30 300 1000];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Additional Terms;
% % Roll Terms;
% RhF = (HY(1)+HY(2)+HY(3)+HY(4))*h;              % Hub force in y axis causes positive roll [Nm]
% RrM = +RRX(1)-RRX(2)+RRX(3)-RRX(4);             % Rolling moment due to forward flight in X [Nm]
% RfM = 0.5*Cz*A*rho*dotroll*abs(dotroll)*L*(P/2)*L;   % Roll friction moment VOIR L'IMPORTANCE [Nm]
% 
% % Pitch Terms;
% PhF = (HX(1)+HX(2)+HX(3)+HX(4))*h; % [Nm]
% PrM = +RRY(1)-RRY(2)+RRY(3)-RRY(4);             % Pitching moment due to sideward flight % [Nm]
% PfM = 0.5*Cz*A*rho*dotpitch*abs(dotpitch)*L*(P/2)*L; % Pitch friction moment VOIR L'IMPORTANCE % [Nm]
% 
% % Yaw Terms;
% YiA = jr*(Om-abs(Om_old))/sp;    % Inertial acceleration/deceleration produces oposit yawing moment % [Nm]
% YhFx = (-HX(2)+HX(4))*L;     % modified past is "(-HX(2)+HX(4))*L"                  % Hub force unbalance produces a yawing moment % [Nm]
% YhFy = (-HY(1)+HY(3))*L; % [Nm]
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

RfM = 0.5*Cz*A*rho*edphi*abs(edphi)*L*(P/2)*L;   % Roll friction moment VOIR L'IMPORTANCE [Nm]
PfM = 0.5*Cz*A*rho*edtheta*abs(edtheta)*L*(P/2)*L; % Pitch friction moment VOIR L'IMPORTANCE % [Nm]


% Observer Equations;
eddphi=edtheta*edpsi*a1+edtheta*a2*omegar + b1*U2+ RhF+RrM-RfM + LO(1)*(phi-estphi); % + RhF+RrM-RfM;
eddtheta=edphi*edpsi*a3-edphi*a4*omegar + b2*U3- PhF+PrM-PfM + LO(2)*(theta-esttheta); % - PhF+PrM-PfM;
eddpsi=edtheta*edphi*a5 + b3*U4+ YhFx+YhFy+YiA + LO(3)*(psi-estpsi);  % + YhFx+YhFy+YiA;

out=[eddphi eddtheta eddpsi];

