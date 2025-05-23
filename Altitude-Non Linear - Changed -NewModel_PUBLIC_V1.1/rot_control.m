

% Rotations control function
% INPUT: state, (phi,theta,psi)(ref)
% OUTPUT: desired prop speeds

function out=rot_control(in)

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

rolld=in(13);   % desired ROLL angle [rad]
pitchd=in(14);   % desired PITCH angle [rad]

Td=in(15);   % desired thrust [N]

yawd=in(16);    % desired yaw angle [rad]

% ******************************************************** CONTROL ******************************************************** 

% Coconut controller
U(1)=Td; % [N]
U(2)=0;
U(3)=0;
U(4)=0;


% Outputs
out(1)=U(1);
out(2)=U(2);
out(3)=U(3);
out(4)=U(4);