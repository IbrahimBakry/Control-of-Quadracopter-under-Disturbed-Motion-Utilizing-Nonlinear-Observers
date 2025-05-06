#include "__cf_systema.h"
#include <math.h>
#include "systema_acc.h"
#include "systema_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T systema_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T
* tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T *
* tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr , boolean_T isfixedbuf ,
boolean_T istransportdelay , int_T * maxNewBufSzPtr ) { int_T testIdx ; int_T
tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf = * tBufPtr ;
real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if ( istransportdelay ) {
numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail < ( bufSz - 1 ) ) ? (
tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] ) && ! isfixedbuf ) {
int_T j ; real_T * tempT ; real_T * tempU ; real_T * tempX = ( NULL ) ;
real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024 ; if ( newBufSz > *
maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * )
utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL
) ) { return ( false ) ; } tempT = tempU + newBufSz ; if ( istransportdelay )
tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j -
tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay
) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT
[ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ;
if ( istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( *
lastPtr > tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail )
; } * tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr =
newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if ( istransportdelay ) *
xBufPtr = tempX ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
systema_acc_rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart ,
real_T * tBuf , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T
oldestIdx , int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout , t1 , t2 , u1 , u2
; if ( ( newIdx == 0 ) && ( oldestIdx == 0 ) && ( tMinusDelay > tStart ) )
return initOutput ; if ( tMinusDelay <= tStart ) return initOutput ; if ( (
tMinusDelay <= tBuf [ oldestIdx ] ) ) { if ( discrete ) { return ( uBuf [
oldestIdx ] ) ; } else { int_T tempIdx = oldestIdx + 1 ; if ( oldestIdx ==
bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [ oldestIdx ] ; t2 = tBuf [ tempIdx ] ;
u1 = uBuf [ oldestIdx ] ; u2 = uBuf [ tempIdx ] ; if ( t2 == t1 ) { if (
tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else { real_T f1 =
( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout = f1 * u1 +
f2 * u2 ; } return yout ; } } if ( minorStepAndTAtLastMajorOutput ) { if (
newIdx != 0 ) { if ( * lastIdx == newIdx ) { ( * lastIdx ) -- ; } newIdx -- ;
} else { if ( * lastIdx == newIdx ) { * lastIdx = bufSz - 1 ; } newIdx =
bufSz - 1 ; } } i = * lastIdx ; if ( tBuf [ i ] < tMinusDelay ) { while (
tBuf [ i ] < tMinusDelay ) { if ( i == newIdx ) break ; i = ( i < ( bufSz - 1
) ) ? ( i + 1 ) : 0 ; } } else { while ( tBuf [ i ] >= tMinusDelay ) { i = (
i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0
; } * lastIdx = i ; if ( discrete ) { double tempEps = ( DBL_EPSILON ) *
128.0 ; double localEps = tempEps * muDoubleScalarAbs ( tBuf [ i ] ) ; if (
tempEps > localEps ) { localEps = tempEps ; } localEps = localEps / 2.0 ; if
( tMinusDelay >= ( tBuf [ i ] - localEps ) ) { yout = uBuf [ i ] ; } else {
if ( i == 0 ) { yout = uBuf [ bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ;
} } } else { if ( i == 0 ) { t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1
] ; } else { t1 = tBuf [ i - 1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ;
u2 = uBuf [ i ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; }
else { yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 )
; real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } } return ( yout ) ; }
void systema_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( SimStruct * const
S ) { ssCallAccelRunBlock ( S , 1 , 32 , SS_CALL_MDL_OUTPUTS ) ; } void
systema_Synthesized_Atomic_Subsystem_For_Alg_Loop_1_Term ( SimStruct * const
S ) { } static void mdlOutputs ( SimStruct * S , int_T tid ) { real_T u ;
real_T u_0 ; real_T u_1 ; B_systema_T * _rtB ; P_systema_T * _rtP ;
X_systema_T * _rtX ; DW_systema_T * _rtDW ; _rtDW = ( ( DW_systema_T * )
ssGetRootDWork ( S ) ) ; _rtX = ( ( X_systema_T * ) ssGetContStates ( S ) ) ;
_rtP = ( ( P_systema_T * ) ssGetDefaultParam ( S ) ) ; _rtB = ( ( B_systema_T
* ) _ssGetBlockIO ( S ) ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB ->
B_1_0_0 = _rtP -> P_0 ; _rtB -> B_1_1_0 = _rtP -> P_1 ; _rtB -> B_1_2_0 =
_rtP -> P_2 ; _rtB -> B_1_3_0 = _rtP -> P_3 ; _rtB -> B_1_4_0 = _rtP -> P_4 ;
_rtB -> B_1_5_0 = _rtP -> P_5 ; _rtB -> B_1_6_0 = _rtP -> P_6 ; _rtB ->
B_1_7_0 = _rtP -> P_7 ; _rtB -> B_1_8_0 = _rtP -> P_8 ; _rtB -> B_1_9_0 =
_rtP -> P_9 ; _rtB -> B_1_10_0 = _rtP -> P_10 ; _rtB -> B_1_11_0 = _rtP ->
P_11 ; } if ( _rtDW -> Integrator_IWORK . IcNeedsLoading ) { ( ( X_systema_T
* ) ssGetContStates ( S ) ) -> Integrator_CSTATE [ 0 ] = ( ( B_systema_T * )
_ssGetBlockIO ( S ) ) -> B_1_0_0 ; ( ( X_systema_T * ) ssGetContStates ( S )
) -> Integrator_CSTATE [ 1 ] = ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) ->
B_1_1_0 ; ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Integrator_CSTATE [
2 ] = ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_2_0 ; ( ( X_systema_T
* ) ssGetContStates ( S ) ) -> Integrator_CSTATE [ 3 ] = ( ( B_systema_T * )
_ssGetBlockIO ( S ) ) -> B_1_3_0 ; ( ( X_systema_T * ) ssGetContStates ( S )
) -> Integrator_CSTATE [ 4 ] = ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) ->
B_1_4_0 ; ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Integrator_CSTATE [
5 ] = ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_5_0 ; ( ( X_systema_T
* ) ssGetContStates ( S ) ) -> Integrator_CSTATE [ 6 ] = ( ( B_systema_T * )
_ssGetBlockIO ( S ) ) -> B_1_6_0 ; ( ( X_systema_T * ) ssGetContStates ( S )
) -> Integrator_CSTATE [ 7 ] = ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) ->
B_1_7_0 ; ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Integrator_CSTATE [
8 ] = ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_8_0 ; ( ( X_systema_T
* ) ssGetContStates ( S ) ) -> Integrator_CSTATE [ 9 ] = ( ( B_systema_T * )
_ssGetBlockIO ( S ) ) -> B_1_9_0 ; ( ( X_systema_T * ) ssGetContStates ( S )
) -> Integrator_CSTATE [ 10 ] = ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) ->
B_1_10_0 ; ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Integrator_CSTATE [
11 ] = ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_11_0 ; } { int_T i1 ;
real_T * y0 = ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_12_0 ; real_T
* xc = & ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Integrator_CSTATE [ 0
] ; for ( i1 = 0 ; i1 < 12 ; i1 ++ ) { y0 [ i1 ] = xc [ i1 ] ; } } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_12 ; ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) ->
B_1_13_0 = systema_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer ,
* uBuffer , _rtDW -> TransportDelay1_IWORK . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK . Last , _rtDW -> TransportDelay1_IWORK . Tail , _rtDW
-> TransportDelay1_IWORK . Head , _rtP -> P_13 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay2_PWORK
. TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay2_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_14 ; ( ( B_systema_T * )
_ssGetBlockIO ( S ) ) -> B_1_14_0 = systema_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay2_IWORK .
CircularBufSize , & _rtDW -> TransportDelay2_IWORK . Last , _rtDW ->
TransportDelay2_IWORK . Tail , _rtDW -> TransportDelay2_IWORK . Head , _rtP
-> P_15 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } { real_T * * uBuffer =
( real_T * * ) & _rtDW -> TransportDelay3_PWORK . TUbufferPtrs [ 0 ] ; real_T
* * tBuffer = ( real_T * * ) & _rtDW -> TransportDelay3_PWORK . TUbufferPtrs
[ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP
-> P_16 ; ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_15_0 =
systema_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer , * uBuffer
, _rtDW -> TransportDelay3_IWORK . CircularBufSize , & _rtDW ->
TransportDelay3_IWORK . Last , _rtDW -> TransportDelay3_IWORK . Tail , _rtDW
-> TransportDelay3_IWORK . Head , _rtP -> P_17 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay4_PWORK
. TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * * ) & _rtDW ->
TransportDelay4_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_18 ; ( ( B_systema_T * )
_ssGetBlockIO ( S ) ) -> B_1_16_0 = systema_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * tBuffer , * uBuffer , _rtDW -> TransportDelay4_IWORK .
CircularBufSize , & _rtDW -> TransportDelay4_IWORK . Last , _rtDW ->
TransportDelay4_IWORK . Tail , _rtDW -> TransportDelay4_IWORK . Head , _rtP
-> P_19 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } ssCallAccelRunBlock ( S
, 1 , 17 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 18 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 19 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_1_20_0
= _rtP -> P_20 ; _rtB -> B_1_21_0 = _rtP -> P_21 ; _rtB -> B_1_22_0 = _rtB ->
B_1_12_0 [ 0 ] ; _rtB -> B_1_23_0 = _rtB -> B_1_12_0 [ 2 ] ; _rtB -> B_1_24_0
= _rtB -> B_1_12_0 [ 6 ] ; _rtB -> B_1_25_0 = _rtP -> P_22 ; _rtB -> B_1_26_0
= _rtB -> B_1_19_0 [ 12 ] ; _rtB -> B_1_27_0 = _rtB -> B_1_19_0 [ 13 ] ; _rtB
-> B_1_28_0 = _rtB -> B_1_19_0 [ 14 ] ; _rtB -> B_1_29_0 = _rtB -> B_1_12_0 [
4 ] ; } _rtB -> B_1_30_0 [ 0 ] = _rtX -> Integrator_CSTATE_o [ 0 ] ; _rtB ->
B_1_30_0 [ 1 ] = _rtX -> Integrator_CSTATE_o [ 1 ] ; _rtB -> B_1_30_0 [ 2 ] =
_rtX -> Integrator_CSTATE_o [ 2 ] ; _rtB -> B_1_31_0 = _rtX ->
Integrator1_CSTATE ; systema_Synthesized_Atomic_Subsystem_For_Alg_Loop_1 ( S
) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_1_33_0 = _rtB -> B_0_1_0 ;
} ssCallAccelRunBlock ( S , 1 , 34 , SS_CALL_MDL_OUTPUTS ) ; if (
ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_1_35_0 = _rtP -> P_25 ; }
ssCallAccelRunBlock ( S , 1 , 36 , SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit
( S , 1 , 0 ) ) { ssCallAccelRunBlock ( S , 1 , 37 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 38 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 39 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 40 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 41 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 42 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 43 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 44 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 45 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 46 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 47 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 48 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 49 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 50 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 51 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 52 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 53 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 54 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 55 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 56 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 57 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 58 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 59 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 60 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 61 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 62 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 63 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 64 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 65 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 66 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 67 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 68 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 69 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 70 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 71 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_1_72_0 =
_rtB -> B_1_24_0 - _rtB -> B_1_25_0 ; ssCallAccelRunBlock ( S , 1 , 73 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 74 ,
SS_CALL_MDL_OUTPUTS ) ; } ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) ->
B_1_75_0 = ( _rtP -> P_28 [ 0 ] ) * ( ( X_systema_T * ) ssGetContStates ( S )
) -> Motor1_CSTATE [ 0 ] + ( _rtP -> P_28 [ 1 ] ) * ( ( X_systema_T * )
ssGetContStates ( S ) ) -> Motor1_CSTATE [ 1 ] + ( _rtP -> P_28 [ 2 ] ) * ( (
X_systema_T * ) ssGetContStates ( S ) ) -> Motor1_CSTATE [ 2 ] ; ( (
B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_76_0 = ( _rtP -> P_33 [ 0 ] ) *
( ( X_systema_T * ) ssGetContStates ( S ) ) -> Motor2_CSTATE [ 0 ] + ( _rtP
-> P_33 [ 1 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) ->
Motor2_CSTATE [ 1 ] + ( _rtP -> P_33 [ 2 ] ) * ( ( X_systema_T * )
ssGetContStates ( S ) ) -> Motor2_CSTATE [ 2 ] ; ( ( B_systema_T * )
_ssGetBlockIO ( S ) ) -> B_1_77_0 = ( _rtP -> P_38 [ 0 ] ) * ( ( X_systema_T
* ) ssGetContStates ( S ) ) -> Motor3_CSTATE [ 0 ] + ( _rtP -> P_38 [ 1 ] ) *
( ( X_systema_T * ) ssGetContStates ( S ) ) -> Motor3_CSTATE [ 1 ] + ( _rtP
-> P_38 [ 2 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) ->
Motor3_CSTATE [ 2 ] ; ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_78_0 =
( _rtP -> P_43 [ 0 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) ->
Motor4_CSTATE [ 0 ] + ( _rtP -> P_43 [ 1 ] ) * ( ( X_systema_T * )
ssGetContStates ( S ) ) -> Motor4_CSTATE [ 1 ] + ( _rtP -> P_43 [ 2 ] ) * ( (
X_systema_T * ) ssGetContStates ( S ) ) -> Motor4_CSTATE [ 2 ] ;
ssCallAccelRunBlock ( S , 1 , 79 , SS_CALL_MDL_OUTPUTS ) ; u = _rtB ->
B_1_79_0 [ 0 ] ; u_0 = _rtP -> P_47 ; u_1 = _rtP -> P_46 ; if ( u >= u_1 ) {
u = u_1 ; } else { if ( u <= u_0 ) { u = u_0 ; } } _rtB -> B_1_80_0 [ 0 ] = u
; u = _rtB -> B_1_79_0 [ 1 ] ; u_0 = _rtP -> P_47 ; u_1 = _rtP -> P_46 ; if (
u >= u_1 ) { u = u_1 ; } else { if ( u <= u_0 ) { u = u_0 ; } } _rtB ->
B_1_80_0 [ 1 ] = u ; u = _rtB -> B_1_79_0 [ 2 ] ; u_0 = _rtP -> P_47 ; u_1 =
_rtP -> P_46 ; if ( u >= u_1 ) { u = u_1 ; } else { if ( u <= u_0 ) { u = u_0
; } } _rtB -> B_1_80_0 [ 2 ] = u ; u = _rtB -> B_1_79_0 [ 3 ] ; u_0 = _rtP ->
P_47 ; u_1 = _rtP -> P_46 ; if ( u >= u_1 ) { u = u_1 ; } else { if ( u <=
u_0 ) { u = u_0 ; } } _rtB -> B_1_80_0 [ 3 ] = u ; ( ( B_systema_T * )
_ssGetBlockIO ( S ) ) -> B_1_81_0 = ssGetT ( S ) ; if ( ssIsSampleHit ( S , 1
, 0 ) ) { ssCallAccelRunBlock ( S , 1 , 82 , SS_CALL_MDL_OUTPUTS ) ; }
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { B_systema_T * _rtB ;
P_systema_T * _rtP ; DW_systema_T * _rtDW ; _rtDW = ( ( DW_systema_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_systema_T * ) ssGetDefaultParam ( S ) )
; _rtB = ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) ; _rtDW ->
Integrator_IWORK . IcNeedsLoading = 0 ; { real_T * * uBuffer = ( real_T * * )
& _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 1 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK . Head = ( ( _rtDW ->
TransportDelay1_IWORK . Head < ( _rtDW -> TransportDelay1_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay1_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay1_IWORK . Head == _rtDW ->
TransportDelay1_IWORK . Tail ) { if ( !
systema_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay1_IWORK .
CircularBufSize , & _rtDW -> TransportDelay1_IWORK . Tail , & _rtDW ->
TransportDelay1_IWORK . Head , & _rtDW -> TransportDelay1_IWORK . Last ,
simTime - _rtP -> P_12 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
FALSE , & _rtDW -> TransportDelay1_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay1_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay1_IWORK . Head ] = ( ( B_systema_T * ) _ssGetBlockIO
( S ) ) -> B_1_75_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay2_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay2_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay2_IWORK . Head = ( ( _rtDW ->
TransportDelay2_IWORK . Head < ( _rtDW -> TransportDelay2_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay2_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay2_IWORK . Head == _rtDW ->
TransportDelay2_IWORK . Tail ) { if ( !
systema_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay2_IWORK .
CircularBufSize , & _rtDW -> TransportDelay2_IWORK . Tail , & _rtDW ->
TransportDelay2_IWORK . Head , & _rtDW -> TransportDelay2_IWORK . Last ,
simTime - _rtP -> P_14 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
FALSE , & _rtDW -> TransportDelay2_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay2_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay2_IWORK . Head ] = ( ( B_systema_T * ) _ssGetBlockIO
( S ) ) -> B_1_76_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay3_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay3_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay3_IWORK . Head = ( ( _rtDW ->
TransportDelay3_IWORK . Head < ( _rtDW -> TransportDelay3_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay3_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay3_IWORK . Head == _rtDW ->
TransportDelay3_IWORK . Tail ) { if ( !
systema_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay3_IWORK .
CircularBufSize , & _rtDW -> TransportDelay3_IWORK . Tail , & _rtDW ->
TransportDelay3_IWORK . Head , & _rtDW -> TransportDelay3_IWORK . Last ,
simTime - _rtP -> P_16 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
FALSE , & _rtDW -> TransportDelay3_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay3_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay3_IWORK . Head ] = ( ( B_systema_T * ) _ssGetBlockIO
( S ) ) -> B_1_77_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay4_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T *
* ) & _rtDW -> TransportDelay4_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay4_IWORK . Head = ( ( _rtDW ->
TransportDelay4_IWORK . Head < ( _rtDW -> TransportDelay4_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay4_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay4_IWORK . Head == _rtDW ->
TransportDelay4_IWORK . Tail ) { if ( !
systema_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW -> TransportDelay4_IWORK .
CircularBufSize , & _rtDW -> TransportDelay4_IWORK . Tail , & _rtDW ->
TransportDelay4_IWORK . Head , & _rtDW -> TransportDelay4_IWORK . Last ,
simTime - _rtP -> P_18 , tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 ,
FALSE , & _rtDW -> TransportDelay4_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
tBuffer ) [ _rtDW -> TransportDelay4_IWORK . Head ] = simTime ; ( * uBuffer )
[ _rtDW -> TransportDelay4_IWORK . Head ] = ( ( B_systema_T * ) _ssGetBlockIO
( S ) ) -> B_1_78_0 ; } UNUSED_PARAMETER ( tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_systema_T * _rtB ;
P_systema_T * _rtP ; XDot_systema_T * _rtXdot ; _rtXdot = ( ( XDot_systema_T
* ) ssGetdX ( S ) ) ; _rtP = ( ( P_systema_T * ) ssGetDefaultParam ( S ) ) ;
_rtB = ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) ; { { int_T i1 ; const
real_T * u0 = & ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_19_0 [ 0 ] ;
real_T * xdot = & ( ( XDot_systema_T * ) ssGetdX ( S ) ) -> Integrator_CSTATE
[ 0 ] ; for ( i1 = 0 ; i1 < 12 ; i1 ++ ) { xdot [ i1 ] = u0 [ i1 ] ; } } }
_rtXdot -> Integrator_CSTATE_o [ 0 ] = _rtB -> B_0_2_0 [ 0 ] ; _rtXdot ->
Integrator_CSTATE_o [ 1 ] = _rtB -> B_0_2_0 [ 1 ] ; _rtXdot ->
Integrator_CSTATE_o [ 2 ] = _rtB -> B_0_2_0 [ 2 ] ; _rtXdot ->
Integrator1_CSTATE = _rtB -> B_0_0_0 [ 0 ] ; { ( ( XDot_systema_T * ) ssGetdX
( S ) ) -> Motor1_CSTATE [ 0 ] = ( _rtP -> P_26 [ 0 ] ) * ( ( X_systema_T * )
ssGetContStates ( S ) ) -> Motor1_CSTATE [ 0 ] + ( _rtP -> P_26 [ 1 ] ) * ( (
X_systema_T * ) ssGetContStates ( S ) ) -> Motor1_CSTATE [ 1 ] + ( _rtP ->
P_26 [ 2 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Motor1_CSTATE [
2 ] ; ( ( XDot_systema_T * ) ssGetdX ( S ) ) -> Motor1_CSTATE [ 0 ] += _rtP
-> P_27 * ( ( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_80_0 [ 0 ] ; ( (
XDot_systema_T * ) ssGetdX ( S ) ) -> Motor1_CSTATE [ 1 ] = ( _rtP -> P_26 [
3 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Motor1_CSTATE [ 0 ] ;
( ( XDot_systema_T * ) ssGetdX ( S ) ) -> Motor1_CSTATE [ 2 ] = ( _rtP ->
P_26 [ 4 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Motor1_CSTATE [
1 ] ; } { ( ( XDot_systema_T * ) ssGetdX ( S ) ) -> Motor2_CSTATE [ 0 ] = (
_rtP -> P_31 [ 0 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) ->
Motor2_CSTATE [ 0 ] + ( _rtP -> P_31 [ 1 ] ) * ( ( X_systema_T * )
ssGetContStates ( S ) ) -> Motor2_CSTATE [ 1 ] + ( _rtP -> P_31 [ 2 ] ) * ( (
X_systema_T * ) ssGetContStates ( S ) ) -> Motor2_CSTATE [ 2 ] ; ( (
XDot_systema_T * ) ssGetdX ( S ) ) -> Motor2_CSTATE [ 0 ] += _rtP -> P_32 * (
( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_80_0 [ 1 ] ; ( (
XDot_systema_T * ) ssGetdX ( S ) ) -> Motor2_CSTATE [ 1 ] = ( _rtP -> P_31 [
3 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Motor2_CSTATE [ 0 ] ;
( ( XDot_systema_T * ) ssGetdX ( S ) ) -> Motor2_CSTATE [ 2 ] = ( _rtP ->
P_31 [ 4 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Motor2_CSTATE [
1 ] ; } { ( ( XDot_systema_T * ) ssGetdX ( S ) ) -> Motor3_CSTATE [ 0 ] = (
_rtP -> P_36 [ 0 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) ->
Motor3_CSTATE [ 0 ] + ( _rtP -> P_36 [ 1 ] ) * ( ( X_systema_T * )
ssGetContStates ( S ) ) -> Motor3_CSTATE [ 1 ] + ( _rtP -> P_36 [ 2 ] ) * ( (
X_systema_T * ) ssGetContStates ( S ) ) -> Motor3_CSTATE [ 2 ] ; ( (
XDot_systema_T * ) ssGetdX ( S ) ) -> Motor3_CSTATE [ 0 ] += _rtP -> P_37 * (
( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_80_0 [ 2 ] ; ( (
XDot_systema_T * ) ssGetdX ( S ) ) -> Motor3_CSTATE [ 1 ] = ( _rtP -> P_36 [
3 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Motor3_CSTATE [ 0 ] ;
( ( XDot_systema_T * ) ssGetdX ( S ) ) -> Motor3_CSTATE [ 2 ] = ( _rtP ->
P_36 [ 4 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Motor3_CSTATE [
1 ] ; } { ( ( XDot_systema_T * ) ssGetdX ( S ) ) -> Motor4_CSTATE [ 0 ] = (
_rtP -> P_41 [ 0 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) ->
Motor4_CSTATE [ 0 ] + ( _rtP -> P_41 [ 1 ] ) * ( ( X_systema_T * )
ssGetContStates ( S ) ) -> Motor4_CSTATE [ 1 ] + ( _rtP -> P_41 [ 2 ] ) * ( (
X_systema_T * ) ssGetContStates ( S ) ) -> Motor4_CSTATE [ 2 ] ; ( (
XDot_systema_T * ) ssGetdX ( S ) ) -> Motor4_CSTATE [ 0 ] += _rtP -> P_42 * (
( B_systema_T * ) _ssGetBlockIO ( S ) ) -> B_1_80_0 [ 3 ] ; ( (
XDot_systema_T * ) ssGetdX ( S ) ) -> Motor4_CSTATE [ 1 ] = ( _rtP -> P_41 [
3 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Motor4_CSTATE [ 0 ] ;
( ( XDot_systema_T * ) ssGetdX ( S ) ) -> Motor4_CSTATE [ 2 ] = ( _rtP ->
P_41 [ 4 ] ) * ( ( X_systema_T * ) ssGetContStates ( S ) ) -> Motor4_CSTATE [
1 ] ; } } static void mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal
( S , 0 , 3760019298U ) ; ssSetChecksumVal ( S , 1 , 659714905U ) ;
ssSetChecksumVal ( S , 2 , 479559986U ) ; ssSetChecksumVal ( S , 3 ,
328807249U ) ; { mxArray * slVerStructMat = NULL ; mxArray * slStrMat =
mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status =
mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if ( status
== 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 , "Version" ) ;
if ( slVerMat == NULL ) { status = 1 ; } else { status = mxGetString (
slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "8.1" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
DW_systema_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_systema_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_systema_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & systema_rtDefaultP ) ; } static void mdlInitializeSampleTimes (
SimStruct * S ) { } static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
