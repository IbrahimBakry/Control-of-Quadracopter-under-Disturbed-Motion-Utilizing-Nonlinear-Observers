function [ U1 ] = U1( in )
glob; 

phi=in(1);
theta=in(2);
V1=in(5);

%U1=(V1+m*g)/(cos(phi)*cos(theta));
U1=m*(V1+g)/(cos(phi)*cos(theta));

%U1=(m/(cos(phi)*cos(theta)))*(V1-g);



