/*
 * lab3_real_integrator_data.c
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

#include "lab3_real_integrator.h"
#include "lab3_real_integrator_private.h"

/* Block parameters (auto storage) */
P_lab3_real_integrator_T lab3_real_integrator_P = {
  /*  Variable: A
   * Referenced by: '<Root>/Gain3'
   */
  { 2.3210617687746353, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.6772564287529842, 0.0,
    1.0, 0.0, 0.0, 0.0, 0.0, -2.0369150867657231, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0,
    1.0285911059474964, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.505821084862593, 0.0,
    0.0, 0.0, 0.0, 1.0, 0.0, -1.5460793857782038, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.40477694171218637, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /*  Variable: B
   * Referenced by: '<Root>/Gain1'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /*  Variable: C
   * Referenced by: '<Root>/Gain4'
   */
  { -0.094766414675641675, 0.17449421289483061, 0.0, 0.0, 0.0, 0.0, 0.0 },

  /*  Variable: K
   * Referenced by: '<Root>/Gain5'
   */
  { 0.058817980893065391, -0.076689951134982975, -0.038629356388476491,
    0.080809898984739351, 0.022216154580734494, -0.066295080533267367,
    0.023232055801830818 },

  /*  Variable: M
   * Referenced by: '<Root>/Gain2'
   */
  { 28.22294203960757, 20.982106494895962, 11.367611777485171,
    6.6068838256263387, 2.8913779715575654, 1.250366882820062,
    2.4007050809470281 },
  0.043419011699360854,                /* Variable: Nbar
                                        * Referenced by: '<Root>/Gain6'
                                        */
  0.0,                                 /* Mask Parameter: AnalogOutput_FinalValue
                                        * Referenced by: '<Root>/Analog Output'
                                        */
  0.0,                                 /* Mask Parameter: AnalogOutput_InitialValue
                                        * Referenced by: '<Root>/Analog Output'
                                        */
  10.0,                                /* Mask Parameter: AnalogInput_MaxMissedTicks
                                        * Referenced by: '<Root>/Analog Input'
                                        */
  10.0,                                /* Mask Parameter: AnalogOutput_MaxMissedTicks
                                        * Referenced by: '<Root>/Analog Output'
                                        */
  0.0,                                 /* Mask Parameter: AnalogInput_YieldWhenWaiting
                                        * Referenced by: '<Root>/Analog Input'
                                        */
  0.0,                                 /* Mask Parameter: AnalogOutput_YieldWhenWaiting
                                        * Referenced by: '<Root>/Analog Output'
                                        */

  /*  Mask Parameter: AnalogInput_Channels
   * Referenced by: '<Root>/Analog Input'
   */
  { 0, 1 },
  0,                                   /* Mask Parameter: AnalogOutput_Channels
                                        * Referenced by: '<Root>/Analog Output'
                                        */
  0,                                   /* Mask Parameter: AnalogInput_RangeMode
                                        * Referenced by: '<Root>/Analog Input'
                                        */
  0,                                   /* Mask Parameter: AnalogOutput_RangeMode
                                        * Referenced by: '<Root>/Analog Output'
                                        */
  0,                                   /* Mask Parameter: AnalogInput_VoltRange
                                        * Referenced by: '<Root>/Analog Input'
                                        */
  0,                                   /* Mask Parameter: AnalogOutput_VoltRange
                                        * Referenced by: '<Root>/Analog Output'
                                        */
  30.0,                                /* Expression: 30
                                        * Referenced by: '<Root>/Signal Generator'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Signal Generator'
                                        */
  0.003,                               /* Computed Parameter: DiscreteTimeIntegrator_gainval
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  0.42,                                /* Expression: 0.42
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  -0.46,                               /* Expression: -0.46
                                        * Referenced by: '<Root>/Discrete-Time Integrator'
                                        */
  0.0,                                 /* Expression: 0.0
                                        * Referenced by: '<Root>/Delay'
                                        */

  /*  Expression: [Kp Ke]
   * Referenced by: '<Root>/Gain'
   */
  { 34.0683, -4.2046 },
  1U                                   /* Computed Parameter: Delay_DelayLength
                                        * Referenced by: '<Root>/Delay'
                                        */
};
