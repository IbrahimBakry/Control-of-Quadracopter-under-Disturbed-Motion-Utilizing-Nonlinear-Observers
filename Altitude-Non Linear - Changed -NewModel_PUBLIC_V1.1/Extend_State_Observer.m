function [ out ] = Extend_State_Observer( in )
glob;

estx1=in(2);
estx2=in(3);
estx3=in(4);
 
U1=in(1);
z=in(7);
phi=in(5);
psi=in(11);

estz=estx1;

% Observer Gain;
% wcl= ?          % frequency for z equation,
% w0z= (2~5)*wcl  % the desired frequency.
% L(1)=delta^(1-alpha(1))*3*woz;
% L(2)=delta^(1-alpha(2))*3*woz^2;
% L(3)=delta^(1-alpha(3))*woz^3;

L=[5 ; 50 ; 250];

% increasing L(1): will give the model long period, and reduce it too much
%                    will vibrate lift and control curves.
% Decreasing L(2): will give the model long period.
% increasing L(3)L is good.
% Done by Ibrahim Bakry;

% g function Parameters;
delta=0.05;
alpha=[1 ; 0.1 ; 1];   
e=z-estz;

% Notes about alpha: increasing alpha(1): will remove the overshoot,
%                    increasing alpha(2): will vibrate the curves,
%                    increasing alpha(3): will make the response good;
% finally: increas alpha(1) & alpha(2) and reduce alpha(3);
% Done By Ibrahim bakry;

% deffinning g function;
if abs(e) > abs(delta)
     g=[abs(e)^alpha(1)*sign(e);
         abs(e)^alpha(2)*sign(e);
         abs(e)^alpha(3)*sign(e)];
else
     g=[e/(delta^(1-alpha(1)));
         e/(delta^(1-alpha(2)));
         e/(delta^(1-alpha(3)))];
end

b=cos(psi)*cos(phi)/m;

% State space form of Altitude Equation by using "ESO";
estdotx1=estx2 + L(1)*g(1);
estdotx2=estx3 + b*U1 + L(2)*g(2);
estdotx3=L(3)*g(3);

out=[estdotx1;estdotx2;estdotx3];
end

