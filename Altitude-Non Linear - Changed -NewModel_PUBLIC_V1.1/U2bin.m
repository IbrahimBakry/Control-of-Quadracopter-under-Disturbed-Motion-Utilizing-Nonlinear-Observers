


% Transformation from U commands to binary image of propellers speed
% INPUT: U vector (4 elements)
% OUTPUT: decimal value to be sent to motor module

function out=U2bin(in)

glob;

% U to Omega file
U(1)=in(1);
U(2)=in(2);
U(3)=in(3);
U(4)=in(4);

mapmat=[ b  b b  b; 
         0 -b 0  b;
        -b  0 b  0;
         d -d d -d];    % thrust and drag coefficients matrix (for hover)
     
Omd=sqrt(inv(mapmat)*U');   % desired prop speeds [rad/s]

bin=(Omd+shi)/slo;  % setpoint to be sent to motor modules

% Only for test
out(1)=bin(1); % [dec]
out(2)=bin(2);
out(3)=bin(3);
out(4)=bin(4);


% FOR INFORMATION MAPPING T&Q to U (Xsens MTx)
% U(1)=+T(1)+T(2)+T(3)+T(4); % [N]
% U(2)=-T(2)+T(4); % [N]
% U(3)=-T(1)+T(3); % [N]
% U(4)=+Q(1)-Q(2)+Q(3)-Q(4); % [Nm]