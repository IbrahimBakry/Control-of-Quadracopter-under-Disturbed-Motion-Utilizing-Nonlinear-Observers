
% SIMINIT Initialization of global variables

clear all;
clc;


global x1_1;    % old integrator value
global x2_1;    % old integrator value
global x3_1;    % old integrator value

global Om_old; % old residual speed

global fIdx; % index for filtering

global rolli_1; % contains old values of the variables to be filtered in sam5_filter.m
global rolli_2;
global frolli;
global frolli_1;
global frolli_2;

global dotrolli_1;
global dotrolli_2;
global fdotrolli;
global fdotrolli_1;
global fdotrolli_2;

global pitchi_1;
global pitchi_2;
global fpitchi;
global fpitchi_1;
global fpitchi_2;

global dotpitchi_1;
global dotpitchi_2;
global fdotpitchi;
global fdotpitchi_1;
global fdotpitchi_2;

global yawi_1;
global yawi_2;
global fyawi;
global fyawi_1;
global fyawi_2;

global dotyawi_1;
global dotyawi_2;
global fdotyawi;
global fdotyawi_1;
global fdotyawi_2;

global zi_1;
global zi_2;
global fzi;
global fzi_1;
global fzi_2;

% global dotzi_1;
% global dotzi_2;
% global fdotzi;
% global fdotzi_1;
% global fdotzi_2;

% INITIALIZATIONS

x1_1=0;
x2_1=0;
x3_1=0;

Om_old=0;

fIdx=0; % index for filtering

rolli_1=0;
rolli_2=0;
frolli=0;
frolli_1=0;
frolli_2=0;

dotrolli_1=0;
dotrolli_2=0;
fdotrolli=0;
fdotrolli_1=0;
fdotrolli_2=0;

pitchi_1=0;
pitchi_2=0;
fpitchi=0;
fpitchi_1=0;
fpitchi_2=0;

dotpitchi_1=0;
dotpitchi_2=0;
fdotpitchi=0;
fdotpitchi_1=0;
fdotpitchi_2=0;

yawi_1=0;
yawi_2=0;
fyawi=0;
fyawi_1=0;
fyawi_2=0;

dotyawi_1=0;
dotyawi_2=0;
fdotyawi=0;
fdotyawi_1=0;
fdotyawi_2=0;

zi_1=0;
zi_2=0;
fzi=0;
fzi_1=0;
fzi_2=0;

% dotzi_1=0;
% dotzi_2=0;
% fdotzi=0;
% fdotzi_1=0;
% fdotzi_2=0;


disp('Done initializing')