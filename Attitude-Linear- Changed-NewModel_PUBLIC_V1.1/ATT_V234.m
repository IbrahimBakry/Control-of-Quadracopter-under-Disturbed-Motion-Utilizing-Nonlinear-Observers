function [out]=ATT_V234(in)

estphi=in(1);
esttheta=in(2);
estpsi=in(3);
edphi=in(4);
edtheta=in(5);
edpsi=in(6);

% Desired Values;
phid=in(7);
thetad=in(8);
psid=in(9);
dotphid=0;
dthetad=0;
dotpsid=0;

% Controllers Gain;
k=[10 20 30;
   4 4 4;
   7 7 7];

% Doing Integration of "Integral Part of PID";
Integ1=in(10);
Integ2=in(11);
Integ3=in(12);
underInteg1=phid-estphi;
underInteg2=thetad-esttheta;
underInteg3=psid-estpsi;
out(1)=underInteg1;
out(2)=underInteg2;
out(3)=underInteg3;

% Controller Equations form Inversion Dynamics;
V2=k(1,1)*(phid-estphi)+k(1,2)*(dotphid-edphi)+k(1,3)*Integ1;
V3=k(2,1)*(thetad-esttheta)+k(2,2)*(dthetad-edtheta)+k(2,3)*Integ2;
V4=k(3,1)*(psid-estpsi)+k(3,2)*(dotpsid-edpsi)+k(3,3)*Integ3;

out(4)=V2;
out(5)=V3;
out(6)=V4;

