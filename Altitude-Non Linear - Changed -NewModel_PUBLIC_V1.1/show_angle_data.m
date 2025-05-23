% ----------------------------------------------------------------
%                   ---  show_data  ----
%
%  This function displaies the OS4 simulation data. 
%    
%  
% Developed by Marcelo Becker & Samir Bouabdallah
%               - EPFL ASL October, 2005 -
%


% -----------------------------------------------------------------

function show_angle_data(L)

% Global variables declaration 

 global SwitchProc1                                                  % used for the Selection of the Procedures
 global GRAF                                                         % Radio Button
 global EDIT                                                         % Edit Text on Robox Window
 global EIXOS EIXOS1 EIXOS2 EIXOS3 EIXOS4 EIXOS5 EIXOS6
 global FIGU  FIGU1  FIGU2  FIGU3  FIGU4                             % Figure parameters      
 global LINHA XLIMI YLIMI
 global x y z
 global roll pitch yaw tout
 global OS4movie BOT_SAVE_F

% -------------------------------------------------------------------------

%========================
% Building the Interface
%========================

% Screen Resolution 

TMP=get(0,'ScreenSize');
RSTELA=TMP(3:4);

FOLGA=20;
COR_JANELA=[1 1 1];

TAM_FIG=[900 600];
FIGU2 = figure('Name',sprintf('  OS4 - Angle Data'),...
   'NumberTitle','off',...
   'MenuBar','figure',...
   'Resize','on',...
   'NextPlot','replacechildren',...
   'Color',COR_JANELA,...
   'Position',[(RSTELA-TAM_FIG)/2 TAM_FIG]);

% Figures
% -------

% Angles figure

POS_EIXOS4=[80 200];
TAM_EIXOS4=[350 350];
EIXOS4=axes('Box','on','Units','pixels','Position',[POS_EIXOS4 TAM_EIXOS4]);
TEXTOX4=xlabel('Time   [sec]','Parent',EIXOS4);
TEXTOY4=ylabel('Angle   [^{o}]','Parent',EIXOS4);
TITULO4=title('OS4 Angles','Parent',EIXOS4,...
'FontSize',12,'FontWeight','bold');

% Angle Ratio figure

POS_EIXOS5=[500 200];
TAM_EIXOS5=[350 350];
EIXOS5=axes('Box','on','Units','pixels','Position',[POS_EIXOS5 TAM_EIXOS5]);
TEXTOX5=xlabel('Time   [sec]','Parent',EIXOS5);
TEXTOY5=ylabel('Angle Ratio   [^{o}/sec]','Parent',EIXOS5);
TITULO5=title('OS4 Angle Ratios','Parent',EIXOS5,...
'FontSize',12,'FontWeight','bold');


% Checkboxes to enable or not the grid lines
% -------------------------------------------

GRADE1=uicontrol('Style','checkbox','Value',0,'Position',[100 120 110 20],...
   'BackgroundColor',COR_JANELA,'String','Enable Grid Lines','Callback',['TMP=get(gcbo,''Value'');',...
      'if TMP, set(EIXOS4,''XGrid'',''on'',''YGrid'',''on'');',...
      'else, set(EIXOS4,''XGrid'',''off'',''YGrid'',''off''); end;']);

GRADE2=uicontrol('Style','checkbox','Value',0,'Position',[520 120 110 20],...
   'BackgroundColor',COR_JANELA,'String','Enable Grid Lines','Callback',['TMP=get(gcbo,''Value'');',...
      'if TMP, set(EIXOS5,''XGrid'',''on'',''YGrid'',''on'');',...
      'else, set(EIXOS5,''XGrid'',''off'',''YGrid'',''off''); end;']);

  
% Checkboxes to enable or not the angle data
% ------------------------------------------

ANG(1)=uicontrol('Style','checkbox','Value',1,'Position',[100 80 100 20],...
   'BackgroundColor',COR_JANELA,'String','Roll angle','ForegroundColor','red','UserData',1);

ANG(2)=uicontrol('Style','checkbox','Value',1,'Position',[220 80 100 20],...
   'BackgroundColor',COR_JANELA,'String','Yaw angle','ForegroundColor',[0.75 0 0.75],'UserData',2);

ANG(3)=uicontrol('Style','checkbox','Value',1,'Position',[340 80 110 20],...
   'BackgroundColor',COR_JANELA,'String','Pitch angle','ForegroundColor','blue','UserData',3);


% Checkboxes to enable or not the angle ratio data
% ------------------------------------------------

ANG(4)=uicontrol('Style','checkbox','Value',1,'Position',[520 80 100 20],...
   'BackgroundColor',COR_JANELA,'String','Roll ratio','ForegroundColor','red','UserData',4);

ANG(5)=uicontrol('Style','checkbox','Value',1,'Position',[640 80 100 20],...
   'BackgroundColor',COR_JANELA,'String','Yaw ratio','ForegroundColor',[0.75 0 0.75],'UserData',5);

ANG(6)=uicontrol('Style','checkbox','Value',1,'Position',[760 80 110 20],...
   'BackgroundColor',COR_JANELA,'String','Pitch ratio','ForegroundColor','blue','UserData',6);


% Buttons
% -------

% SAVE Figure Button

BOT_SAVE=uicontrol('Position',[400 20 100 20],'String','Save Figure',...
   'BackgroundColor',COR_JANELA,'Callback','salvaimg(FIGU2,3);');

% EXIT Button

BOT_EXIT=uicontrol('Position',[250 20 100 20],'String','Exit',...
   'BackgroundColor',COR_JANELA,'Callback','close all;');

% RETURN Button

BOT_SAIDA=uicontrol('Position',[550 20 100 20],'String','Return',...
   'BackgroundColor',COR_JANELA,'Callback','close;');

% Initial Plots
% -------------

roll2 = roll*180/pi;
pitch2 = pitch*180/pi;
yaw2 = yaw*180/pi;

LINHA(1)=line(tout,roll2, 'Parent',EIXOS4,'Color',[1 0 0],'LineStyle','-', 'LineWidth',0.4);
LINHA(2)=line(tout,yaw2, 'Parent',EIXOS4,'Color',[0.75 0 0.75],'LineStyle','-', 'LineWidth',0.4);
LINHA(3)=line(tout,pitch2, 'Parent',EIXOS4,'Color',[0 0 1],'LineStyle','-', 'LineWidth',0.4);

ddroll=diff(roll2);
ddpitch=diff(pitch2);
ddyaw=diff(yaw2);

[cont1 cont2]=size(roll);

LINHA(4)=line(tout(1:cont1-1),ddroll, 'Parent',EIXOS5,'Color',[1 0 0],'LineStyle','-', 'LineWidth',0.4);
LINHA(5)=line(tout(1:cont1-1),ddyaw, 'Parent',EIXOS5,'Color',[0.75 0 0.75],'LineStyle','-', 'LineWidth',0.4);
LINHA(6)=line(tout(1:cont1-1),ddpitch, 'Parent',EIXOS5,'Color',[0 0 1],'LineStyle','-', 'LineWidth',0.4);

for I2=1:6
   
   set(ANG(I2),'Enable','on','Callback',...
      ['TMP=get(gcbo,''Value''); I2=get(gcbo,''UserData'');',...
         'if TMP, set(LINHA(I2),''Visible'',''on'');',...
         'else, set(LINHA(I2),''Visible'',''off''); end;']);
end
