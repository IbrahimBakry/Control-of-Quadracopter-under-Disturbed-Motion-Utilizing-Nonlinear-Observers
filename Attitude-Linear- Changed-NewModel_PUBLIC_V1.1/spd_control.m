
% Speed control function
% INPUT: state, desired dotX & dotY
% OUTPUT: desired speeds

function out=spd_control(in)

% global file for parameters
glob;



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

dotxd=in(19);  % Modified Past 13;   % desired linear x speed [m/s]
dotyd=in(20);  % Modified past 14;   % desired linear x speed [m/s]

U1=in(21);     % Modified past 15;

% ********** CONTROL ************
ax=1;
ay=1;

ex=dotxd - dotx; % dot x error
ey=dotyd - doty; % dot y error

% Control and Roll and Pitch extraction

if (U1 > 0)
UX=(ax*ex)*m/U1;    % dot x ctrl
UY=(ay*ey)*m/U1;
rolld = asin(UX*sin(yaw) - UY*cos(yaw)); % desired roll
pitchd = asin ((UX - sin(roll)*sin(yaw))/(cos(roll)*cos(yaw))); % desired pitch  (the yaw must be -pi/2 < yaw < pi/2
else
U1=m*g;
rolld=0;
pitchd=0;
end

% phi and theta extraction

out(1)=rolld;   % required roll angle [rad]
out(2)=pitchd;   % required pitch angle [rad]

% out(1)=0;
% out(2)=0;