function [out] = ALT_observer( in )
glob;

estz=in(1);
U1=in(2);

phi=in(3);
theta=in(4);
psi=in(10);
z=in(5) - ES;
estdotz=in(11);

% friction force estimation (propellers friction+OS4 center friction) [N]
ZaF = 0.5*Cz*A*rho*estdotz*abs(estdotz)*P + 0.5*Cz*Ac*rho*estdotz*abs(estdotz);  

% Observer Gain;
L=12;   

% estddotz=+g-((cos(phi)*cos(theta))/m)*U1+L*(z-estz);
estddotz=-g*cos(phi)*cos(theta)+(cos(psi)*cos(phi)*U1-ZaF+in(9))/m + L*(z-estz);

out(1)=estddotz;
out(2)=(z-estz);

