function [ out ] = V1( in )

% PD Constants;
Kp=20;
Kd=6;
Ki=6;

% estemated z' & z'';
z=in(5);
dotz=in(16);

% Desierd z & z';
zd=in(1); 
dotzd=0;

% Integral for PID;
 AfterIntegral=in(2);
 Integral=z-zd;
 out(1)=Integral;

% control formula;
V1=-Kp*(z-zd) - Kd*dotz - Ki*AfterIntegral;

out(2)=V1;
 
