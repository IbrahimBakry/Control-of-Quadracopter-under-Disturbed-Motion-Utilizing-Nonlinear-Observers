
function SALVAIMG(F,contss)

% Global variables declaration 

 global SwitchProc1                                                  % used for the Selection of the Procedures
 global GRAF                                                         % Radio Button
 global EDIT                                                         % Edit Text on Robox Window
 global EIXOS EIXOS1 EIXOS2 EIXOS3 EIXOS4 EIXOS5 EIXOS6
 global FIGU  FIGU1  FIGU2  FIGU3  FIGU4                             % Figure parameters      
 global LINHA XLIMI YLIMI
 global x y z

% -------------------------------------------------------------------------
SEMNOME=1;

while SEMNOME
   [ARQUIVO,CAMINHO]=uiputfile('*.jpg','Save Image As...');
   if ARQUIVO==0
      return
   end
   
   NTMP=length(ARQUIVO);
   if NTMP>4
      FLAG=~strcmp(upper(ARQUIVO(NTMP-3:NTMP)),'.JPG');
   else
      FLAG=1;
   end
   
   if FLAG
      ARQUIVO=strcat(ARQUIVO,'.JPG');
      
      if exist(strcat(CAMINHO,ARQUIVO))
         RESP=questdlg('There is a file which name is the same! Do you want to overwrite it?',...
            'Save file','YES','NO','NO');
         if strcmp(RESP,'YES')
            SEMNOME=0;
         end
      else
         SEMNOME=0;
      end
   else
      SEMNOME=0;
   end 
   
end 

if contss == 1
    FRAME=getframe(F,[1 1 480 380]);
elseif contss == 2
    FRAME=getframe(F,[1 50 830 580]);
elseif contss == 3
    FRAME=getframe(F,[10 150 870 450]);
elseif contss == 4
    FRAME=getframe(F,[10 150 570 450]);
end

F1=frame2im(FRAME);
imwrite(F1,strcat(CAMINHO,ARQUIVO),'jpeg','Quality',100);
