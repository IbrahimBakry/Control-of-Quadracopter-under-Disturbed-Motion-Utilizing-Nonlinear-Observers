function [ out ] = V1( in )
obser=in(1);
estdotz=in(2);
estz=in(3);
zd=in(4); 
dotzd=0;


% PD Constants;
Kp=6;
Kd=8;
ki=3;

%V1=-Kd*estdotz-Kp*(estz-zd);

%pid control
out(1)=estz-zd;
V1=-Kd*estdotz-Kp*(estz-zd)-ki*obser;
out(2)=V1;

%V1=Kp*(zd-estz)+Kd*(dotzd-estdotz);


 




