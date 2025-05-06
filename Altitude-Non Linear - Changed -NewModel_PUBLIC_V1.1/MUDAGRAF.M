% --------------------------------------------------------------
%                   ---  MUDAGRAF  ----
%
%  This function permits the user to select each approach he/she
%    wants to use to simulate the OS4 helicopter.
%  
%    Developed by Marcelo Becker & Samir Bouabdallah
%                   - EPFL ASL September, 2005 -
%
% 
% ---------------------------------------------------------------

function MUDAGRAF(TIPO)

% Global variables declaration 

 global SwitchProc1  SwitchCompl                                     % used for the Selection of the Procedures
 global GRAF chbox                                                   % Radio Button
 global EDIT                                                         % Edit Text on Robox Window
 global EIXOS  EIXOS1  EIXOS2  EIXOS3
 global FIGU  FIGU1  FIGU2  FIGU3                                    % Figure parameters      
 global LINHA XLIMI YLIMI
 global x y z

% -------------------------------------------------------------------------

switch TIPO
   
case 1          %  Control Simulation
   
    set(GRAF(2),'Value',0);
    SwitchProc1 = 1;
   
case 2          % Obstacle Avoidance Simulation
   
    set(GRAF(1),'Value',0);
    SwitchProc1 = 2;

case 3
    
   SwitchCompl=1;
   set(chbox(2),'Value',0);
   set(chbox(3),'Value',0);
    
case 4
       
   SwitchCompl=2;
   set(chbox(1),'Value',0);
   set(chbox(3),'Value',0);
    
case 5
        
   SwitchCompl=3;
   set(chbox(1),'Value',0);
   set(chbox(2),'Value',0);

end


