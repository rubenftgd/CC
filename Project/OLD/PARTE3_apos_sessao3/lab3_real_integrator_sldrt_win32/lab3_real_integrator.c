/*
 * lab3_real_integrator.c
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
#include "lab3_real_integrator_dt.h"

/* options for Simulink Desktop Real-Time board 0 */
static double RTWinBoardOptions0[] = {
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
  0.0,
};

/* list of Simulink Desktop Real-Time timers */
const int RTWinTimerCount = 1;
const double RTWinTimers[2] = {
  0.02, 0.0,
};

/* list of Simulink Desktop Real-Time boards */
const int RTWinBoardCount = 1;
RTWINBOARD RTWinBoards[1] = {
  { "National_Instruments/PCI-MIO-16E-4", 4294967295U, 6, RTWinBoardOptions0 },
};

/* Block signals (auto storage) */
B_lab3_real_integrator_T lab3_real_integrator_B;

/* Block states (auto storage) */
DW_lab3_real_integrator_T lab3_real_integrator_DW;

/* Real-time model */
RT_MODEL_lab3_real_integrator_T lab3_real_integrator_M_;
RT_MODEL_lab3_real_integrator_T *const lab3_real_integrator_M =
  &lab3_real_integrator_M_;

/* Model output function */
void lab3_real_integrator_output(void)
{
  /* local block i/o variables */
  real_T rtb_AnalogInput[2];
  real_T rtb_x_estimate[7];
  real_T rtb_y_error;
  int32_T i;
  real_T tmp;
  int32_T i_0;
  real_T rtb_x_estimate_o;

  /* SignalGenerator: '<Root>/Signal Generator' */
  rtb_y_error = lab3_real_integrator_P.SignalGenerator_Frequency *
    lab3_real_integrator_M->Timing.t[0];
  if (rtb_y_error - floor(rtb_y_error) >= 0.5) {
    lab3_real_integrator_B.SignalGenerator =
      lab3_real_integrator_P.SignalGenerator_Amplitude;
  } else {
    lab3_real_integrator_B.SignalGenerator =
      -lab3_real_integrator_P.SignalGenerator_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator' */

  /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  if (((lab3_real_integrator_B.SignalGenerator > 0.0) &&
       (lab3_real_integrator_DW.DiscreteTimeIntegrator_PrevResetState <= 0)) ||
      ((lab3_real_integrator_B.SignalGenerator <= 0.0) &&
       (lab3_real_integrator_DW.DiscreteTimeIntegrator_PrevResetState == 1))) {
    lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE =
      lab3_real_integrator_P.DiscreteTimeIntegrator_IC;
  }

  if (lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE >=
      lab3_real_integrator_P.DiscreteTimeIntegrator_UpperSat) {
    lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE =
      lab3_real_integrator_P.DiscreteTimeIntegrator_UpperSat;
  } else {
    if (lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE <=
        lab3_real_integrator_P.DiscreteTimeIntegrator_LowerSat) {
      lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE =
        lab3_real_integrator_P.DiscreteTimeIntegrator_LowerSat;
    }
  }

  lab3_real_integrator_B.DiscreteTimeIntegrator =
    lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE;

  /* End of DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  /* S-Function Block: <Root>/Analog Input */
  {
    ANALOGIOPARM parm;
    parm.mode = (RANGEMODE) lab3_real_integrator_P.AnalogInput_RangeMode;
    parm.rangeidx = lab3_real_integrator_P.AnalogInput_VoltRange;
    RTBIO_DriverIO(0, ANALOGINPUT, IOREAD, 2,
                   lab3_real_integrator_P.AnalogInput_Channels,
                   &rtb_AnalogInput[0], &parm);
  }

  /* Gain: '<Root>/Gain' */
  lab3_real_integrator_B.y_k = lab3_real_integrator_P.Gain_Gain[0] *
    rtb_AnalogInput[0] + lab3_real_integrator_P.Gain_Gain[1] * rtb_AnalogInput[1];

  /* Gain: '<Root>/Gain4' incorporates:
   *  Delay: '<Root>/Delay'
   */
  tmp = 0.0;
  for (i = 0; i < 7; i++) {
    tmp += lab3_real_integrator_P.C[i] * lab3_real_integrator_DW.Delay_DSTATE[i];
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/Gain4'
   */
  rtb_y_error = lab3_real_integrator_B.y_k - tmp;

  /* Gain: '<Root>/Gain5' incorporates:
   *  Sum: '<Root>/Sum5'
   */
  tmp = 0.0;
  for (i = 0; i < 7; i++) {
    /* Sum: '<Root>/Sum5' incorporates:
     *  Delay: '<Root>/Delay'
     *  Gain: '<Root>/Gain2'
     */
    rtb_x_estimate_o = lab3_real_integrator_P.M[i] * rtb_y_error +
      lab3_real_integrator_DW.Delay_DSTATE[i];
    tmp += lab3_real_integrator_P.K[i] * rtb_x_estimate_o;
    rtb_x_estimate[i] = rtb_x_estimate_o;
  }

  lab3_real_integrator_B.Gain5 = tmp;

  /* End of Gain: '<Root>/Gain5' */

  /* Sum: '<Root>/Sum6' incorporates:
   *  Gain: '<Root>/Gain6'
   */
  lab3_real_integrator_B.u_k = (lab3_real_integrator_P.Nbar *
    lab3_real_integrator_B.SignalGenerator +
    lab3_real_integrator_B.DiscreteTimeIntegrator) -
    lab3_real_integrator_B.Gain5;

  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) lab3_real_integrator_P.AnalogOutput_RangeMode;
      parm.rangeidx = lab3_real_integrator_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &lab3_real_integrator_P.AnalogOutput_Channels,
                     &lab3_real_integrator_B.u_k, &parm);
    }
  }

  /* Sum: '<Root>/Sum1' */
  lab3_real_integrator_B.Sum1 = lab3_real_integrator_B.SignalGenerator -
    lab3_real_integrator_B.y_k;
  for (i = 0; i < 7; i++) {
    /* Gain: '<Root>/Gain3' */
    lab3_real_integrator_B.Gain3[i] = 0.0;
    for (i_0 = 0; i_0 < 7; i_0++) {
      lab3_real_integrator_B.Gain3[i] += lab3_real_integrator_P.A[7 * i_0 + i] *
        rtb_x_estimate[i_0];
    }

    /* End of Gain: '<Root>/Gain3' */

    /* Sum: '<Root>/Sum3' incorporates:
     *  Gain: '<Root>/Gain1'
     */
    lab3_real_integrator_B.Sum3[i] = lab3_real_integrator_P.B[i] *
      lab3_real_integrator_B.u_k + lab3_real_integrator_B.Gain3[i];
  }
}

/* Model update function */
void lab3_real_integrator_update(void)
{
  int32_T i;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE +=
    lab3_real_integrator_P.DiscreteTimeIntegrator_gainval *
    lab3_real_integrator_B.Sum1;
  if (lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE >=
      lab3_real_integrator_P.DiscreteTimeIntegrator_UpperSat) {
    lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE =
      lab3_real_integrator_P.DiscreteTimeIntegrator_UpperSat;
  } else {
    if (lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE <=
        lab3_real_integrator_P.DiscreteTimeIntegrator_LowerSat) {
      lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE =
        lab3_real_integrator_P.DiscreteTimeIntegrator_LowerSat;
    }
  }

  if (lab3_real_integrator_B.SignalGenerator > 0.0) {
    lab3_real_integrator_DW.DiscreteTimeIntegrator_PrevResetState = 1;
  } else if (lab3_real_integrator_B.SignalGenerator < 0.0) {
    lab3_real_integrator_DW.DiscreteTimeIntegrator_PrevResetState = -1;
  } else if (lab3_real_integrator_B.SignalGenerator == 0.0) {
    lab3_real_integrator_DW.DiscreteTimeIntegrator_PrevResetState = 0;
  } else {
    lab3_real_integrator_DW.DiscreteTimeIntegrator_PrevResetState = 2;
  }

  /* End of Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */

  /* Update for Delay: '<Root>/Delay' */
  for (i = 0; i < 7; i++) {
    lab3_real_integrator_DW.Delay_DSTATE[i] = lab3_real_integrator_B.Sum3[i];
  }

  /* End of Update for Delay: '<Root>/Delay' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++lab3_real_integrator_M->Timing.clockTick0)) {
    ++lab3_real_integrator_M->Timing.clockTickH0;
  }

  lab3_real_integrator_M->Timing.t[0] =
    lab3_real_integrator_M->Timing.clockTick0 *
    lab3_real_integrator_M->Timing.stepSize0 +
    lab3_real_integrator_M->Timing.clockTickH0 *
    lab3_real_integrator_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.02s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++lab3_real_integrator_M->Timing.clockTick1)) {
      ++lab3_real_integrator_M->Timing.clockTickH1;
    }

    lab3_real_integrator_M->Timing.t[1] =
      lab3_real_integrator_M->Timing.clockTick1 *
      lab3_real_integrator_M->Timing.stepSize1 +
      lab3_real_integrator_M->Timing.clockTickH1 *
      lab3_real_integrator_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void lab3_real_integrator_initialize(void)
{
  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) lab3_real_integrator_P.AnalogOutput_RangeMode;
      parm.rangeidx = lab3_real_integrator_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &lab3_real_integrator_P.AnalogOutput_Channels,
                     &lab3_real_integrator_P.AnalogOutput_InitialValue, &parm);
    }
  }

  {
    int32_T i;

    /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
    lab3_real_integrator_DW.DiscreteTimeIntegrator_DSTATE =
      lab3_real_integrator_P.DiscreteTimeIntegrator_IC;
    lab3_real_integrator_DW.DiscreteTimeIntegrator_PrevResetState = 2;

    /* InitializeConditions for Delay: '<Root>/Delay' */
    for (i = 0; i < 7; i++) {
      lab3_real_integrator_DW.Delay_DSTATE[i] =
        lab3_real_integrator_P.Delay_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<Root>/Delay' */
  }
}

/* Model terminate function */
void lab3_real_integrator_terminate(void)
{
  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) lab3_real_integrator_P.AnalogOutput_RangeMode;
      parm.rangeidx = lab3_real_integrator_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &lab3_real_integrator_P.AnalogOutput_Channels,
                     &lab3_real_integrator_P.AnalogOutput_FinalValue, &parm);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  lab3_real_integrator_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  lab3_real_integrator_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  lab3_real_integrator_initialize();
}

void MdlTerminate(void)
{
  lab3_real_integrator_terminate();
}

/* Registration function */
RT_MODEL_lab3_real_integrator_T *lab3_real_integrator(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)lab3_real_integrator_M, 0,
                sizeof(RT_MODEL_lab3_real_integrator_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&lab3_real_integrator_M->solverInfo,
                          &lab3_real_integrator_M->Timing.simTimeStep);
    rtsiSetTPtr(&lab3_real_integrator_M->solverInfo, &rtmGetTPtr
                (lab3_real_integrator_M));
    rtsiSetStepSizePtr(&lab3_real_integrator_M->solverInfo,
                       &lab3_real_integrator_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&lab3_real_integrator_M->solverInfo,
                          (&rtmGetErrorStatus(lab3_real_integrator_M)));
    rtsiSetRTModelPtr(&lab3_real_integrator_M->solverInfo,
                      lab3_real_integrator_M);
  }

  rtsiSetSimTimeStep(&lab3_real_integrator_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&lab3_real_integrator_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = lab3_real_integrator_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    lab3_real_integrator_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    lab3_real_integrator_M->Timing.sampleTimes =
      (&lab3_real_integrator_M->Timing.sampleTimesArray[0]);
    lab3_real_integrator_M->Timing.offsetTimes =
      (&lab3_real_integrator_M->Timing.offsetTimesArray[0]);

    /* task periods */
    lab3_real_integrator_M->Timing.sampleTimes[0] = (0.0);
    lab3_real_integrator_M->Timing.sampleTimes[1] = (0.02);

    /* task offsets */
    lab3_real_integrator_M->Timing.offsetTimes[0] = (0.0);
    lab3_real_integrator_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(lab3_real_integrator_M, &lab3_real_integrator_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = lab3_real_integrator_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    lab3_real_integrator_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(lab3_real_integrator_M, 30.0);
  lab3_real_integrator_M->Timing.stepSize0 = 0.02;
  lab3_real_integrator_M->Timing.stepSize1 = 0.02;

  /* External mode info */
  lab3_real_integrator_M->Sizes.checksums[0] = (1265396265U);
  lab3_real_integrator_M->Sizes.checksums[1] = (557367151U);
  lab3_real_integrator_M->Sizes.checksums[2] = (1421486437U);
  lab3_real_integrator_M->Sizes.checksums[3] = (3051591737U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    lab3_real_integrator_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(lab3_real_integrator_M->extModeInfo,
      &lab3_real_integrator_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(lab3_real_integrator_M->extModeInfo,
                        lab3_real_integrator_M->Sizes.checksums);
    rteiSetTPtr(lab3_real_integrator_M->extModeInfo, rtmGetTPtr
                (lab3_real_integrator_M));
  }

  lab3_real_integrator_M->solverInfoPtr = (&lab3_real_integrator_M->solverInfo);
  lab3_real_integrator_M->Timing.stepSize = (0.02);
  rtsiSetFixedStepSize(&lab3_real_integrator_M->solverInfo, 0.02);
  rtsiSetSolverMode(&lab3_real_integrator_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  lab3_real_integrator_M->ModelData.blockIO = ((void *) &lab3_real_integrator_B);
  (void) memset(((void *) &lab3_real_integrator_B), 0,
                sizeof(B_lab3_real_integrator_T));

  /* parameters */
  lab3_real_integrator_M->ModelData.defaultParam = ((real_T *)
    &lab3_real_integrator_P);

  /* states (dwork) */
  lab3_real_integrator_M->ModelData.dwork = ((void *) &lab3_real_integrator_DW);
  (void) memset((void *)&lab3_real_integrator_DW, 0,
                sizeof(DW_lab3_real_integrator_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    lab3_real_integrator_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  lab3_real_integrator_M->Sizes.numContStates = (0);/* Number of continuous states */
  lab3_real_integrator_M->Sizes.numY = (0);/* Number of model outputs */
  lab3_real_integrator_M->Sizes.numU = (0);/* Number of model inputs */
  lab3_real_integrator_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  lab3_real_integrator_M->Sizes.numSampTimes = (2);/* Number of sample times */
  lab3_real_integrator_M->Sizes.numBlocks = (19);/* Number of blocks */
  lab3_real_integrator_M->Sizes.numBlockIO = (8);/* Number of block outputs */
  lab3_real_integrator_M->Sizes.numBlockPrms = (101);/* Sum of parameter "widths" */
  return lab3_real_integrator_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
