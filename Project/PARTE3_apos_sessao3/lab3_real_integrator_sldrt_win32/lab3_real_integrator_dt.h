/*
 * lab3_real_integrator_dt.h
 *
 * Code generation for model "lab3_real_integrator".
 *
 * Model version              : 1.77
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C source code generated on : Wed Dec 20 12:13:50 2017
 *
 * Target selection: rtwin.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Specified
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&lab3_real_integrator_B.SignalGenerator), 0, 0, 20 }
  ,

  { (char_T *)(&lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE), 0, 0, 8
  },

  { (char_T *)(&lab3_real_integrator_DW.AnalogInput_PWORK), 11, 0, 4 },

  { (char_T *)(&lab3_real_integrator_DW.DiscreteTimeIntegrator_PrevResetState),
    2, 0, 1 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  4U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&lab3_real_integrator_P.A[0]), 0, 0, 84 },

  { (char_T *)(&lab3_real_integrator_P.AnalogInput_Channels[0]), 6, 0, 7 },

  { (char_T *)(&lab3_real_integrator_P.SignalGenerator_Amplitude), 0, 0, 9 },

  { (char_T *)(&lab3_real_integrator_P.Delay_DelayLength), 7, 0, 1 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  4U,
  rtPTransitions
};

/* [EOF] lab3_real_integrator_dt.h */
