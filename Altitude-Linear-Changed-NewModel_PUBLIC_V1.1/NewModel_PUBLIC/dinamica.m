
% Dynamics fnction
% INPUT: state, aerodynamic forces & torques, prop rot speed
% OUTPUT: system accelerations

function out=dinamica(in)

glob;

global Om_old;

% ********* Operational Conditions *********
roll=in(1);     % [rad]
dotroll=in(2);  % [rad/s]
pitch=in(3);
dotpitch=in(4);
yaw=in(5);
dotyaw=in(6);
z=in(7);        % [m]
dotz=in(8);     % [m/s]
x=in(9);
dotx=in(10);
y=in(11);
doty=in(12);

% from aero file   
T=in(13:16);    % The thrusts [N]
Q=in(17:20);    % The counter-torques [Nm]
HX=in(21:24);    % The hub forces in X [N]
HY=in(25:28);   % The hub forces in Y [N]
RRX=in(29:32);   % The rolling moments in X [N]
RRY=in(33:36);   % The rolling moments in Y [N]

% from motor dyna file
Omega=in(37:40);    % [rad/s]
Om=+Omega(1)-Omega(2)+Omega(3)-Omega(4); % Om residual propellers rot. speed [rad/s]

% *************** Rotations (in body fixed frame) *************** 
% Roll moments
RgB = dotpitch*dotyaw*(Iyy-Izz);                % Body gyro effect [Nm]
RgP = jr*dotpitch*Om;                           % Propeller gyro effect [Nm] 
RaA = L*(-T(2)+T(4));                           % Roll actuator action [Nm]
RhF = (HY(1)+HY(2)+HY(3)+HY(4))*h;              % Hub force in y axis causes positive roll [Nm]
RrM = +RRX(1)-RRX(2)+RRX(3)-RRX(4);             % Rolling moment due to forward flight in X [Nm]
RfM = 0.5*Cz*A*rho*dotroll*abs(dotroll)*L*(P/2)*L;   % Roll friction moment VOIR L'IMPORTANCE [Nm]

% Pitch moments
PgB = dotroll*dotyaw*(Izz-Ixx); % [Nm]
PgP = jr*dotroll*Om; % [Nm]
PaA = L*(-T(1)+T(3)); % [Nm]  
PhF = (HX(1)+HX(2)+HX(3)+HX(4))*h; % [Nm]
PrM = +RRY(1)-RRY(2)+RRY(3)-RRY(4);             % Pitching moment due to sideward flight % [Nm]
PfM = 0.5*Cz*A*rho*dotpitch*abs(dotpitch)*L*(P/2)*L; % Pitch friction moment VOIR L'IMPORTANCE % [Nm]

% Yaw moments
YgB = dotpitch*dotroll*(Ixx-Iyy); % [Nm]
YiA = jr*(Om-abs(Om_old))/sp;   %% ???? %%         % Inertial acceleration/deceleration produces oposit yawing moment % [Nm]
YawA = +Q(1)-Q(2)+Q(3)-Q(4);               % counter torques difference produces yawing % [Nm]
YhFx = (-HX(2)+HX(4))*L;     % modified past is "(-HX(2)+HX(4))*L"                  % Hub force unbalance produces a yawing moment % [Nm]
YhFy = (-HY(1)+HY(3))*L; % [Nm]

Om_old=Om; % [rad/s]

% *************** Translations (in earth fixed frame) *************** 

% Z forces
ZaA = (cos(yaw)*cos(roll))*(T(1)+T(2)+T(3)+T(4));          % actuators action [N], "actuators here are the motors, We call it electrical Actuators"
ZaR = PArchim;      % Archimede force ;-) [N]
ZaF = 0.5*Cz*A*rho*dotz*abs(dotz)*P + 0.5*Cz*Ac*rho*dotz*abs(dotz);  % friction force estimation (propellers friction+OS4 center friction) [N]
% Zg = m*g*cos(pitch)*cos(roll);

% X forces
XaA = (sin(yaw)*sin(roll)+cos(yaw)*sin(pitch)*cos(roll))*(T(1)+T(2)+T(3)+T(4)); % [N] 
XdF = 0.5*Cx*Ac*rho*dotx*abs(dotx); % [N]
XhF = -(HX(1)+HX(2)+HX(3)+HX(4)); % [N]    % modified past is "HX(1)+HX(2)+HX(3)+HX(4)"
% Xg = -m*g*sin(pitch);

% Y forces
YaA = (-cos(yaw)*sin(roll)+sin(yaw)*sin(pitch)*cos(roll))*(T(1)+T(2)+T(3)+T(4)); % [N]
YdF = 0.5*Cy*Ac*rho*doty*abs(doty); % [N]
YhF =-( HY(1)+HY(2)+HY(3)+HY(4)); % [N]    % modified past is "HX(1)+HX(2)+HX(3)+HX(4)"
% Yg = m*g*cos(pitch)*sin(roll);

% *************** OS4 equations of motion *************** 
% ROTATIONS
out(1)=dotroll; % roll rate [rad/s] 
out(2)=(RgB + RgP + RaA + RhF + RrM - RfM) /Ixx; % roll accel [rad/s^2]

out(3)=dotpitch; % pitch rate [rad/s]
out(4)=(PgB - PgP + PaA - PhF + PrM - PfM) /Iyy; % pitch accel [rad/s^2]

out(5)=dotyaw; % yaw rate [rad/s]
out(6)=(YgB + YiA + YawA + YhFx + YhFy) /Izz;  % yaw accel [rad/s^2]

% TRANSLATIONS Z,X,Y
out(7)=dotz; % z rate [m/s]
out(8)= -g*cos(roll)*cos(pitch) + ( ZaR + ZaA - ZaF )/m;  % z accel [m/s^2] % modified past is"-g + (ZaR + ZaA - ZaF)/m;"

out(9)=dotx;   % x rate [m/s]
out(10)=(XaA - XdF - XhF)/m;  % x accel [m/s^2]

out(11)=doty;  % y rate [m/s]
out(12)=(YaA - YdF - YhF )/m;  % y accel [m/s^2]

% ***** additional outputs for dynamics analysis ********
out(13)=ZaA;    % replace by any term you want to analyse
out(14)=ZaR;
out(15)=ZaF;
out(16)=YhFx;
out(17)=YhFy;
out(18)=YhFy;