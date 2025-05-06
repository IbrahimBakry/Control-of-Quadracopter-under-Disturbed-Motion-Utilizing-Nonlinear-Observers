

function out = Hom(in)

x1      = in(1);
y1      = in(2);
z1      = in(3);
phi1    = in(4); % rotation around global z-axis
theta1  = in(5); % rotation around global y-axis
psi1    = in(6); % rotation around global x-axis

out = [ cos(phi1)*cos(theta1)   cos(phi1)*sin(theta1)*sin(psi1) - sin(phi1)*cos(psi1)   cos(phi1)*sin(theta1)*cos(psi1) + sin(phi1)*sin(psi1)   x1;...
        sin(phi1)*cos(theta1)   sin(phi1)*sin(theta1)*sin(psi1) + cos(phi1)*cos(psi1)   sin(phi1)*sin(theta1)*cos(psi1) - cos(phi1)*sin(psi1)   y1;...
        -sin(theta1)            cos(theta1)*sin(psi1)                                   cos(theta1)*cos(psi1)                                   z1;...
        0                       0                                                       0                                                       1];

    
