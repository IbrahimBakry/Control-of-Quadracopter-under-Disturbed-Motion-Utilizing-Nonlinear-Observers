function [ U1 ] = U1( in )
glob; 

phi=in(1);
theta=in(2);
psi=in(8);
V1=in(9);         

% From reversed Dynamic Theory aplied on altitude Equation; 
U1=(m*(V1+g*cos(phi)*cos(theta))-in(6)+in(7))/(cos(psi)*cos(phi));
