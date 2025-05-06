function estddotz = ALT_observer( in )
glob;

estz=in(1);
U1=in(2);

phi=in(3);
theta=in(4);
z=in(5);

% Observer Gain;
L=17;
ezest=z-estz;
estddotz=-g+((cos(phi)*cos(theta))/m)*U1+L*(z-estz);







