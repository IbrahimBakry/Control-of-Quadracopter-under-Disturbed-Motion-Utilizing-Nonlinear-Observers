
% Altitude control function
% INPUT: state, desired altitude
% OUTPUT: desired speeds

function out=alt_control(in)

% global file for parameters
glob;

% ********* Operational Conditions *********
% roll=in(1);     % [rad]
% dotroll=in(2);  % [rad/s]
% pitch=in(3);
% dotpitch=in(4);
% yaw=in(5);
% dotyaw=in(6);
% z=in(7);        % [m]
% dotz=in(8);     % [m/s]
% x=in(9);
% dotx=in(10);
% y=in(11);
% doty=in(12);


roll=in(1);     % [rad]
pitch=in(2);
z=in(3);        % [m]

zd=in(4);  % desired altitude [m]
dotzd=0;

dotz=diff(z);
dotz(1)=0;

% ********** CONTROL 1 ************
a1=2;
a2=4;

r1=-a1*dotz-a2*(z-zd);

U1=(r1+m*g)/(cos(roll)*cos(pitch));


% % ********** CONTROL 2 ************
% alpha7= 4;
% alpha8= 4;
% z7=zd-z;
% z8=dotz - dotzd - alpha7*z7;
% U1=(m/(cos(roll)*cos(pitch)))*(z7 + g - alpha7*(z8 + alpha7*z7) - alpha8*z8);



% out(1)=5.1972;   % required thrust [N]
out(1)=U1;   % required thrust [N]
