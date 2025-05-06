#include "__cf_systema.h"
#ifndef RTW_HEADER_systema_acc_h_
#define RTW_HEADER_systema_acc_h_
#ifndef systema_acc_COMMON_INCLUDES_
#define systema_acc_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#include <float.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#endif
#include "systema_acc_types.h"
typedef struct { real_T B_1_0_0 ; real_T B_1_1_0 ; real_T B_1_2_0 ; real_T
B_1_3_0 ; real_T B_1_4_0 ; real_T B_1_5_0 ; real_T B_1_6_0 ; real_T B_1_7_0 ;
real_T B_1_8_0 ; real_T B_1_9_0 ; real_T B_1_10_0 ; real_T B_1_11_0 ; real_T
B_1_12_0 [ 12 ] ; real_T B_1_13_0 ; real_T B_1_14_0 ; real_T B_1_15_0 ;
real_T B_1_16_0 ; real_T B_1_17_0 [ 4 ] ; real_T B_1_18_0 [ 24 ] ; real_T
B_1_19_0 [ 18 ] ; real_T B_1_20_0 ; real_T B_1_21_0 ; real_T B_1_22_0 ;
real_T B_1_23_0 ; real_T B_1_24_0 ; real_T B_1_25_0 ; real_T B_1_26_0 ;
real_T B_1_27_0 ; real_T B_1_28_0 ; real_T B_1_29_0 ; real_T B_1_30_0 [ 3 ] ;
real_T B_1_31_0 ; real_T B_1_33_0 ; real_T B_1_34_0 [ 2 ] ; real_T B_1_35_0 ;
real_T B_1_36_0 [ 6 ] ; real_T B_1_72_0 ; real_T B_1_75_0 ; real_T B_1_76_0 ;
real_T B_1_77_0 ; real_T B_1_78_0 ; real_T B_1_79_0 [ 4 ] ; real_T B_1_80_0 [
4 ] ; real_T B_1_81_0 ; real_T B_0_0_0 [ 2 ] ; real_T B_0_1_0 ; real_T
B_0_2_0 [ 3 ] ; } B_systema_T ; typedef struct { struct { real_T modelTStart
; } TransportDelay1_RWORK ; struct { real_T modelTStart ; }
TransportDelay2_RWORK ; struct { real_T modelTStart ; } TransportDelay3_RWORK
; struct { real_T modelTStart ; } TransportDelay4_RWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay1_PWORK ; struct { void * TUbufferPtrs [
2 ] ; } TransportDelay2_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay3_PWORK ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay4_PWORK ; void *
Synthesized_Atomic_Subsystem_For_Alg_Loop_1_AlgLoopData ; struct { void *
LoggedData ; } U1_PWORK ; struct { void * LoggedData ; } U2_PWORK ; struct {
void * LoggedData ; } U3_PWORK ; struct { void * LoggedData ; } U4_PWORK ;
struct { void * LoggedData ; } e1_PWORK ; struct { void * LoggedData ; }
e2_PWORK ; struct { void * LoggedData ; } raa_PWORK ; struct { void *
LoggedData ; } rgb_PWORK ; struct { void * LoggedData ; } rgp_PWORK ; struct
{ void * LoggedData ; } rhf_PWORK ; struct { void * LoggedData ; } rrm_PWORK
; struct { void * LoggedData ; } rrm1_PWORK ; struct { void * LoggedData ; }
omega1_PWORK ; struct { void * LoggedData ; } omega2_PWORK ; struct { void *
LoggedData ; } omega3_PWORK ; struct { void * LoggedData ; } omega4_PWORK ;
void * ToWorkspace_PWORK ; void * altitude_PWORK ; struct { void * LoggedData
; } pitch_PWORK ; void * pitchout_PWORK ; struct { void * LoggedData ; }
pitchd_PWORK ; struct { void * LoggedData ; } roll_PWORK ; void *
rollout_PWORK ; struct { void * LoggedData ; } rolld_PWORK ; struct { void *
LoggedData ; } x_PWORK ; void * xposition_PWORK ; struct { void * LoggedData
; } xd_PWORK ; struct { void * LoggedData ; } y_PWORK ; void *
yposition_PWORK ; struct { void * LoggedData ; } yaw_PWORK ; void *
yawout_PWORK ; struct { void * LoggedData ; } yawd_PWORK ; struct { void *
LoggedData ; } yd_PWORK ; struct { void * LoggedData ; } z_PWORK ; struct {
void * LoggedData ; } zd_PWORK ; struct { void * LoggedData ; } SSError_PWORK
; struct { void * LoggedData ; } U0U1_PWORK ; void * ToWorkspace_PWORK_f ;
struct { int_T IcNeedsLoading ; } Integrator_IWORK ; struct { int_T Tail ;
int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay1_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay2_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay3_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay4_IWORK ; char pad_TransportDelay4_IWORK [ 4 ] ; } DW_systema_T
; typedef struct { real_T Integrator_CSTATE [ 12 ] ; real_T
Integrator_CSTATE_o [ 3 ] ; real_T Integrator1_CSTATE ; real_T Motor1_CSTATE
[ 3 ] ; real_T Motor2_CSTATE [ 3 ] ; real_T Motor3_CSTATE [ 3 ] ; real_T
Motor4_CSTATE [ 3 ] ; } X_systema_T ; typedef struct { real_T
Integrator_CSTATE [ 12 ] ; real_T Integrator_CSTATE_o [ 3 ] ; real_T
Integrator1_CSTATE ; real_T Motor1_CSTATE [ 3 ] ; real_T Motor2_CSTATE [ 3 ]
; real_T Motor3_CSTATE [ 3 ] ; real_T Motor4_CSTATE [ 3 ] ; } XDot_systema_T
; typedef struct { boolean_T Integrator_CSTATE [ 12 ] ; boolean_T
Integrator_CSTATE_o [ 3 ] ; boolean_T Integrator1_CSTATE ; boolean_T
Motor1_CSTATE [ 3 ] ; boolean_T Motor2_CSTATE [ 3 ] ; boolean_T Motor3_CSTATE
[ 3 ] ; boolean_T Motor4_CSTATE [ 3 ] ; } XDis_systema_T ; struct
P_systema_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4
; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ; real_T P_9 ; real_T
P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T P_14 ; real_T P_15 ;
real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ; real_T P_20 ; real_T
P_21 ; real_T P_22 ; real_T P_23 ; real_T P_24 ; real_T P_25 ; real_T P_26 [
5 ] ; real_T P_27 ; real_T P_28 [ 3 ] ; real_T P_31 [ 5 ] ; real_T P_32 ;
real_T P_33 [ 3 ] ; real_T P_36 [ 5 ] ; real_T P_37 ; real_T P_38 [ 3 ] ;
real_T P_41 [ 5 ] ; real_T P_42 ; real_T P_43 [ 3 ] ; real_T P_46 ; real_T
P_47 ; } ; extern P_systema_T systema_rtDefaultP ;
#endif
