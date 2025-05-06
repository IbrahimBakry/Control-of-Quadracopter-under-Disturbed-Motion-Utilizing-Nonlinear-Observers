function [ out ] = V1( in )

% PD Constants;
Kp=15;
Kd=8;
Ki=7;

% estemated z' & z'';
estz=in(1);
estdotz=in(2);

% Desierd z & z';
zd=in(3); 
dotzd=0;

% Integral for PID;
 AfterIntegral=in(4);
 Integral=estz-zd;
 out(1)=Integral;

% control formula;
V1=-Kp*(estz-zd) - Kd*estdotz - Ki*AfterIntegral;
 out(2)=V1;
 
