% ------------------------------------------------------------------
%                   ---  Visual  ----
%
%  This function shows the simulation window for the obstacle avoidance 
%      procedure developed for the OS4 helicopter. 
%      
%      Developed by Marcelo Becker & Samir Bouabdallah 
%               
%                   - EPFL ASL October, 2005 -


% ------------------------------------------------------------------

function visual(L)

% Global variables declaration 

 global SwitchProc1  SwitchCompl                                     % used for the Selection of the Procedures
 global GRAF chbox                                                   % Radio Button
 global EDIT                                                         % Edit Text on Robox Window
 global EIXOS EIXOS1 EIXOS2 EIXOS3 EIXOS4 EIXOS5 EIXOS6
 global FIGU  FIGU1  FIGU2  FIGU3  FIGU4                             % Figure parameters      
 global LINHA XLIMI YLIMI
 global x y z
 global roll pitch yaw tout
 global OS4movie BOT_SAVE_F

% -------------------------------------------------------------------------

%============================================
% Design of the Main Window  05/10/2005 (MB)
%============================================

% Simulation Parameters: file samir.mat


L=1;

% Window parameters

TMP=get(0,'ScreenSize');
RSTELA=TMP(3:4);
COR_JANELA=[1 1 1];
TAM_FIG=[880 680];

FIGU1=figure('Name',sprintf('  OS4 - EPFL - Autonomous System Lab'),...
   'NumberTitle','off',...
   'Resize','on',...
   'Color',COR_JANELA,...
   'Position',[(RSTELA-TAM_FIG)/2 TAM_FIG]);
    
% Figure view
% -----------

% % ASL LOGO
% 
% POS_EIXOS3=[600 630];
% TAM_EIXOS3=[120 40];
% EIXOS3=axes('Box','on','Units','pixels','Position',[POS_EIXOS3 TAM_EIXOS3]);
% RGB = imread('logoASL.jpg');
% imshow(RGB)
% 
% % EPFL LOGO
% 
% POS_EIXOS4=[210 640];
% TAM_EIXOS4=[90 30];
% EIXOS4=axes('Box','on','Units','pixels','Position',[POS_EIXOS4 TAM_EIXOS4]);
% RGB = imread('epfl_logo.jpg');
% imshow(RGB)
% 
uicontrol('Style','text','Position',[335 650 250 20],'BackgroundColor',COR_JANELA,...
   'String','École Polytechnique Fédérale de Lausanne','FontSize',8,'FontWeight','bold');
uicontrol('Style','text','Position',[335 630 250 20],'BackgroundColor',COR_JANELA,...
   'String','Autonomous System Lab','FontSize',10,'FontWeight','bold');
    

% Buttons
% -------

% SAVE Button

BOT_SALVA=uicontrol('Position',[60 20 100 20],'String','Save Figure',...
   'BackgroundColor',COR_JANELA,'Enable','off','Callback','salvaimg(FIGU1,2);');

% Angle Results Button

BOT_ANG=uicontrol('Position',[190 20 100 20],'String','Angle Results',...
   'BackgroundColor',COR_JANELA,'Enable','off','Callback','show_angle_data(L);'); 

% Position Results Button

BOT_POS=uicontrol('Position',[320 20 100 20],'String','Position Results',...
   'BackgroundColor',COR_JANELA,'Enable','off','Callback','show_position_data(L);');

% 3-D Path Button

L=1;
BOT_MAPA=uicontrol('Position',[450 20 100 20],'String','3-D Path',...
   'BackgroundColor',COR_JANELA,'Enable','off','Callback','drawOS43D(L);');

% Exit Button

BOT_SAIDA=uicontrol('Position',[710 20 100 20],'String','Exit',...
   'BackgroundColor',COR_JANELA,'Enable','off','Callback','close;');

% Repeat Button

BOT_REP=uicontrol('Position',[580 20 100 20],'String','Repeat',...
   'BackgroundColor',COR_JANELA,'Enable','off','Callback',['set(FIGU1,''Pointer'',''watch''); pause(0.01);',...
   '[cont1 cont2] = size(x);',...
   'for cont3 = 1:1:cont1,',... 
        'phi = roll(cont3);',...
        'theta = pitch(cont3);',...  
        'psi = yaw(cont3);',...  
        'axes(EIXOS);',...
        'cla;',...
        'draw_results_yaw(psi);',...
        'axes(EIXOS1);',...
        'cla;',...
        'draw_results_roll(phi);',...
        'axes(EIXOS2);',...
        'cla;',...
        'draw_results_pitch(theta);',...
        'axes(EIXOS3);',...
        'cla;',...
        'draw_results_3D(phi,theta,psi);',...
    'end; set(FIGU1,''Pointer'',''arrow'');']);

% =========================================================

    % XY Plane

    POS_EIXOS=[70 280];
    TAM_EIXOS=[300 300];
    EIXOS=axes('Box','on','Units','pixels','Position',[POS_EIXOS TAM_EIXOS],'XDir','reverse','NextPlot','New');
    TITULO=title('OS4 - Yaw Angle','Parent',EIXOS,...
        'FontSize',12,'FontWeight','bold');
    TEXTOX=xlabel('Y axis   [m]','Parent',EIXOS);
    TEXTOY=ylabel('X axis   [m]','Parent',EIXOS);
    set(EIXOS,'XLimMode','manual'); 
    set(EIXOS,'YLimMode','manual');
    XLIMI=[-0.8 0.8]; 
    YLIMI=[-0.8 0.8];
    set(EIXOS,'XLim',XLIMI); 
    set(EIXOS,'YLim',YLIMI);

    % YZ Plane

    POS_EIXOS1=[70 100];
    TAM_EIXOS1=[300 100];
    EIXOS1=axes('Box','on','Units','pixels','Position',[POS_EIXOS1 TAM_EIXOS1],'XDir','reverse','NextPlot','New');
    TITULO=title('OS4 - Roll Angle','Parent',EIXOS1,...
        'FontSize',12,'FontWeight','bold');
    TEXTOX=xlabel('Y axis   [m]','Parent',EIXOS1);
    TEXTOY=ylabel('Z axis   [m]','Parent',EIXOS1);
    set(EIXOS1,'XLimMode','manual'); 
    set(EIXOS1,'YLimMode','manual');
    XLIMI=[-0.8 0.8]; 
    YLIMI=[-0.8/3 0.8/3];
    set(EIXOS1,'XLim',XLIMI); 
    set(EIXOS1,'YLim',YLIMI);

    % XZ Plane

    POS_EIXOS2=[470 100];
    TAM_EIXOS2=[300 100];
    EIXOS2=axes('Box','on','Units','pixels','Position',[POS_EIXOS2 TAM_EIXOS2],'XDir','reverse','NextPlot','New');
    TITULO=title('OS4 - Pitch Angle','Parent',EIXOS2,...
        'FontSize',12,'FontWeight','bold');
    TEXTOX=xlabel('X axis   [m]','Parent',EIXOS2);
    TEXTOY=ylabel('Z axis   [m]','Parent',EIXOS2);
    set(EIXOS2,'XLimMode','manual'); 
    set(EIXOS2,'YLimMode','manual');
    XLIMI=[-0.8 0.8]; 
    YLIMI=[-0.8/3 0.8/3];
    set(EIXOS2,'XLim',XLIMI); 
    set(EIXOS2,'YLim',YLIMI);

    % 3-D View

    POS_EIXOS3=[470 280];
    TAM_EIXOS3=[300 300];
    EIXOS3=axes('Box','on','Units','pixels','Position',[POS_EIXOS3 TAM_EIXOS3],'XDir','reverse','NextPlot','New');
    TITULO=title('OS4 - 3-D View','Parent',EIXOS3,...
        'FontSize',12,'FontWeight','bold');

    TEXTOX=xlabel('Y axis   [m]','Parent',EIXOS3);
    TEXTOY=ylabel('X axis   [m]','Parent',EIXOS3);
    TEXTOZ=zlabel('Z axis   [m]','Parent',EIXOS3);
    set(EIXOS3,'XLimMode','manual'); 
    set(EIXOS3,'YLimMode','manual');
    set(EIXOS3,'ZLimMode','manual');
    set(EIXOS3,'Box','off');

    XLIMI=[-0.6 0.6]; 
    YLIMI=[-0.6 0.6];
    ZLIMI=[-0.6 0.6];
    set(EIXOS3,'XLim',XLIMI); 
    set(EIXOS3,'YLim',YLIMI);
    set(EIXOS3,'ZLim',ZLIMI);

% =========================================================


% Beginning of the visualization
% ------------------------------

[cont1 cont2] = size(x);
set(FIGU1,'Pointer','watch');
pause(0.01);
for cont3 = 1:1:cont1,

    phi = roll(cont3);            % Roll Angle   [rad]
    theta = pitch(cont3);         % Pitch Angle  [rad]
    psi = yaw(cont3);             % Yaw Angle    [rad]

    % Cleaning the axes
    
     axes(EIXOS);
     cla;
     draw_results_yaw(psi);
     axes(EIXOS1);
     cla;
     draw_results_roll(phi);
     axes(EIXOS2);
     cla;
     draw_results_pitch(theta);
     axes(EIXOS3);
     cla;
     draw_results_3D(phi,theta,psi);

end

set(FIGU1,'Pointer','arrow');
set(BOT_SALVA,'Enable','on');
set(BOT_SAIDA,'Enable','on');
set(BOT_MAPA,'Enable','on');
set(BOT_POS,'Enable','on');
set(BOT_ANG,'Enable','on');
set(BOT_REP,'Enable','on');

