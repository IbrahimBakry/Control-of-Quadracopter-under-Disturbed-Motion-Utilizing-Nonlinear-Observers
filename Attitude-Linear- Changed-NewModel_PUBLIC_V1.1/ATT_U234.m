function [out]=ATT_U234(in)
glob;

dotphi=in(2);
dottheta=in(4);
dotpsi=in(6);

V2=in(24);
V3=in(25);
V4=in(26);

RhF=in(27);
RrM=in(28);
PhF=in(29);
PrM=in(30);
YhFx=in(31);
YhFy=in(32);
YiA=in(33);

edphi=in(34);
edtheta=in(35);
edpsi=in(36);

% "Omegar" residual propellers rot. speed [rad/s]
omega=in(19:23);    % [rad/s]
omegar=+omega(1)-omega(2)+omega(3)-omega(4); 

% Attitude moments Equations Parameters;
a1=(Iyy-Izz)/Ixx;
a2=jr/Ixx;
a3=(Izz-Ixx)/Iyy;
a4=jr/Iyy;
a5=(Ixx-Iyy)/Izz;

b1=L/Ixx;  
b2=L/Iyy;  
b3=1/Izz;  

RfM = 0.5*Cz*A*rho*edphi*abs(edphi)*L*(P/2)*L;   % Roll friction moment VOIR L'IMPORTANCE [Nm]
PfM = 0.5*Cz*A*rho*edtheta*abs(edtheta)*L*(P/2)*L; % Pitch friction moment VOIR L'IMPORTANCE % [Nm]


% ATTITUDE Momment Equations;
U2=(1/b1)*(V2-(dottheta*dotpsi*a1+dottheta*a2*omegar -RhF-RrM+RfM));
U3=(1/b2)*(V3-(dotphi*dotpsi*a3-dotphi*a4*omegar +PhF-PrM+PfM));
U4=(1/b3)*(V4-(dottheta*dotphi*a5 -YhFx-YhFy-YiA));

out=[U2 U3 U4];
