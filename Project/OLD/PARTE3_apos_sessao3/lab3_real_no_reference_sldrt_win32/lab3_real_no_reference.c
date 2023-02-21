/*
 * lab3_real_no_reference.c
 *
 * Code generation for model "lab3_real_no_reference".
 *
 * Model version              : 1.78
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C source code generated on : Wed Dec 20 12:17:09 2017
 *
 * Target selection: rtwin.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Specified
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "lab3_real_no_reference.h"
#include "lab3_real_no_reference_private.h"
#include "lab3_real_no_reference_dt.h"

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
B_lab3_real_no_reference_T lab3_real_no_reference_B;

/* Block states (auto storage) */
DW_lab3_real_no_reference_T lab3_real_no_reference_DW;

/* Real-time model */
RT_MODEL_lab3_real_no_reference_T lab3_real_no_reference_M_;
RT_MODEL_lab3_real_no_reference_T *const lab3_real_no_reference_M =
  &lab3_real_no_reference_M_;

/* Model output function */
void lab3_real_no_reference_output(void)
{
  /* local block i/o variables */
  real_T rtb_AnalogInput[2];
  real_T rtb_x_estimate[7];
  real_T rtb_Gain5;
  int32_T i;
  real_T tmp;
  int32_T i_0;
  real_T rtb_x_estimate_o;

  /* Constant: '<Root>/Constant' */
  lab3_real_no_reference_B.Constant = lab3_real_no_reference_P.Constant_Value;

  /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  if (((lab3_real_no_reference_B.Constant > 0.0) &&
       (lab3_real_no_reference_DW.DiscreteTimeIntegrator_PrevResetState <= 0)) ||
      ((lab3_real_no_reference_B.Constant <= 0.0) &&
       (lab3_real_no_reference_DW.DiscreteTimeIntegrator_PrevResetState == 1)))
  {
    lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE =
      lab3_real_no_reference_P.DiscreteTimeIntegrator_IC;
  }

  if (lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE >=
      lab3_real_no_reference_P.DiscreteTimeIntegrator_UpperSat) {
    lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE =
      lab3_real_no_reference_P.DiscreteTimeIntegrator_UpperSat;
  } else {
    if (lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE <=
        lab3_real_no_reference_P.DiscreteTimeIntegrator_LowerSat) {
      lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE =
        lab3_real_no_reference_P.DiscreteTimeIntegrator_LowerSat;
    }
  }

  lab3_real_no_reference_B.DiscreteTimeIntegrator =
    lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE;

  /* End of DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  /* S-Function Block: <Root>/Analog Input */
  {
    ANALOGIOPARM parm;
    parm.mode = (RANGEMODE) lab3_real_no_reference_P.AnalogInput_RangeMode;
    parm.rangeidx = lab3_real_no_reference_P.AnalogInput_VoltRange;
    RTBIO_DriverIO(0, ANALOGINPUT, IOREAD, 2,
                   lab3_real_no_reference_P.AnalogInput_Channels,
                   &rtb_AnalogInput[0], &parm);
  }

  /* Gain: '<Root>/Gain' */
  lab3_real_no_reference_B.y_k = lab3_real_no_reference_P.Gain_Gain[0] *
    rtb_AnalogInput[0] + lab3_real_no_reference_P.Gain_Gain[1] *
    rtb_AnalogInput[1];

  /* Gain: '<Root>/Gain4' incorporates:
   *  Delay: '<Root>/Delay'
   */
  tmp = 0.0;
  for (i = 0; i < 7; i++) {
    tmp += lab3_real_no_reference_P.C[i] *
      lab3_real_no_reference_DW.Delay_DSTATE[i];
  }

  /* Sum: '<Root>/Sum4' incorporates:
   *  Gain: '<Root>/Gain4'
   */
  rtb_Gain5 = lab3_real_no_reference_B.y_k - tmp;

  /* Gain: '<Root>/Gain5' incorporates:
   *  Sum: '<Root>/Sum5'
   */
  tmp = 0.0;
  for (i = 0; i < 7; i++) {
    /* Sum: '<Root>/Sum5' incorporates:
     *  Delay: '<Root>/Delay'
     *  Gain: '<Root>/Gain2'
     */
    rtb_x_estimate_o = lab3_real_no_reference_P.M[i] * rtb_Gain5 +
      lab3_real_no_reference_DW.Delay_DSTATE[i];
    tmp += lab3_real_no_reference_P.K[i] * rtb_x_estimate_o;
    rtb_x_estimate[i] = rtb_x_estimate_o;
  }

  /* Sum: '<Root>/Sum6' incorporates:
   *  Gain: '<Root>/Gain5'
   *  Gain: '<Root>/Gain6'
   */
  lab3_real_no_reference_B.u_k = (lab3_real_no_reference_P.Nbar *
    lab3_real_no_reference_B.Constant +
    lab3_real_no_reference_B.DiscreteTimeIntegrator) - tmp;

  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) lab3_real_no_reference_P.AnalogOutput_RangeMode;
      parm.rangeidx = lab3_real_no_reference_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &lab3_real_no_reference_P.AnalogOutput_Channels,
                     &lab3_real_no_reference_B.u_k, &parm);
    }
  }

  /* Sum: '<Root>/Sum1' */
  lab3_real_no_reference_B.Sum1 = lab3_real_no_reference_B.Constant -
    lab3_real_no_reference_B.y_k;

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Gain: '<Root>/Gain3'
   */
  for (i = 0; i < 7; i++) {
    tmp = 0.0;
    for (i_0 = 0; i_0 < 7; i_0++) {
      tmp += lab3_real_no_reference_P.A[7 * i_0 + i] * rtb_x_estimate[i_0];
    }

    lab3_real_no_reference_B.Sum3[i] = lab3_real_no_reference_P.B[i] *
      lab3_real_no_reference_B.u_k + tmp;
  }

  /* End of Sum: '<Root>/Sum3' */
}

/* Model update function */
void lab3_real_no_reference_update(void)
{
  int32_T i;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE +=
    lab3_real_no_reference_P.DiscreteTimeIntegrator_gainval *
    lab3_real_no_reference_B.Sum1;
  if (lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE >=
      lab3_real_no_reference_P.DiscreteTimeIntegrator_UpperSat) {
    lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE =
      lab3_real_no_reference_P.DiscreteTimeIntegrator_UpperSat;
  } else {
    if (lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE <=
        lab3_real_no_reference_P.DiscreteTimeIntegrator_LowerSat) {
      lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE =
        lab3_real_no_reference_P.DiscreteTimeIntegrator_LowerSat;
    }
  }

  if (lab3_real_no_reference_B.Constant > 0.0) {
    lab3_real_no_reference_DW.DiscreteTimeIntegrator_PrevResetState = 1;
  } else if (lab3_real_no_reference_B.Constant < 0.0) {
    lab3_real_no_reference_DW.DiscreteTimeIntegrator_PrevResetState = -1;
  } else if (lab3_real_no_reference_B.Constant == 0.0) {
    lab3_real_no_reference_DW.DiscreteTimeIntegrator_PrevResetState = 0;
  } else {
    lab3_real_no_reference_DW.DiscreteTimeIntegrator_PrevResetState = 2;
  }

  /* End of Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */

  /* Update for Delay: '<Root>/Delay' */
  for (i = 0; i < 7; i++) {
    lab3_real_no_reference_DW.Delay_DSTATE[i] = lab3_real_no_reference_B.Sum3[i];
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
  if (!(++lab3_real_no_reference_M->Timing.clockTick0)) {
    ++lab3_real_no_reference_M->Timing.clockTickH0;
  }

  lab3_real_no_reference_M->Timing.t[0] =
    lab3_real_no_reference_M->Timing.clockTick0 *
    lab3_real_no_reference_M->Timing.stepSize0 +
    lab3_real_no_reference_M->Timing.clockTickH0 *
    lab3_real_no_reference_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void lab3_real_no_reference_initialize(void)
{
  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) lab3_real_no_reference_P.AnalogOutput_RangeMode;
      parm.rangeidx = lab3_real_no_reference_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &lab3_real_no_reference_P.AnalogOutput_Channels,
                     &lab3_real_no_reference_P.AnalogOutput_InitialValue, &parm);
    }
  }

  {
    int32_T i;

    /* InitializeConditions for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
    lab3_real_no_reference_DW.DiscreteTimeIntegrator_DSTATE =
      lab3_real_no_reference_P.DiscreteTimeIntegrator_IC;
    lab3_real_no_reference_DW.DiscreteTimeIntegrator_PrevResetState = 2;

    /* InitializeConditions for Delay: '<Root>/Delay' */
    for (i = 0; i < 7; i++) {
      lab3_real_no_reference_DW.Delay_DSTATE[i] =
        lab3_real_no_reference_P.Delay_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<Root>/Delay' */
  }
}

/* Model terminate function */
void lab3_real_no_reference_terminate(void)
{
  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) lab3_real_no_reference_P.AnalogOutput_RangeMode;
      parm.rangeidx = lab3_real_no_reference_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &lab3_real_no_reference_P.AnalogOutput_Channels,
                     &lab3_real_no_reference_P.AnalogOutput_FinalValue, &parm);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  lab3_real_no_reference_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  lab3_real_no_reference_update();
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
  lab3_real_no_reference_initialize();
}

void MdlTerminate(void)
{
  lab3_real_no_reference_terminate();
}

/* Registration function */
RT_MODEL_lab3_real_no_reference_T *lab3_real_no_reference(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)lab3_real_no_reference_M, 0,
                sizeof(RT_MODEL_lab3_real_no_reference_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = lab3_real_no_reference_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    lab3_real_no_reference_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    lab3_real_no_reference_M->Timing.sampleTimes =
      (&lab3_real_no_reference_M->Timing.sampleTimesArray[0]);
    lab3_real_no_reference_M->Timing.offsetTimes =
      (&lab3_real_no_reference_M->Timing.offsetTimesArray[0]);

    /* task periods */
    lab3_real_no_reference_M->Timing.sampleTimes[0] = (0.02);

    /* task offsets */
    lab3_real_no_reference_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(lab3_real_no_reference_M, &lab3_real_no_reference_M->Timing.tArray
             [0]);

  {
    int_T *mdlSampleHits = lab3_real_no_reference_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    lab3_real_no_reference_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(lab3_real_no_reference_M, 60.0);
  lab3_real_no_reference_M->Timing.stepSize0 = 0.02;

  /* External mode info */
  lab3_real_no_reference_M->Sizes.checksums[0] = (2154498023U);
  lab3_real_no_reference_M->Sizes.checksums[1] = (1229522011U);
  lab3_real_no_reference_M->Sizes.checksums[2] = (1589996258U);
  lab3_real_no_reference_M->Sizes.checksums[3] = (2676150873U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    lab3_real_no_reference_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(lab3_real_no_reference_M->extModeInfo,
      &lab3_real_no_reference_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(lab3_real_no_reference_M->extModeInfo,
                        lab3_real_no_reference_M->Sizes.checksums);
    rteiSetTPtr(lab3_real_no_reference_M->extModeInfo, rtmGetTPtr
                (lab3_real_no_reference_M));
  }

  lab3_real_no_reference_M->solverInfoPtr =
    (&lab3_real_no_reference_M->solverInfo);
  lab3_real_no_reference_M->Timing.stepSize = (0.02);
  rtsiSetFixedStepSize(&lab3_real_no_reference_M->solverInfo, 0.02);
  rtsiSetSolverMode(&lab3_real_no_reference_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  lab3_real_no_reference_M->ModelData.blockIO = ((void *)
    &lab3_real_no_reference_B);
  (void) memset(((void *) &lab3_real_no_reference_B), 0,
                sizeof(B_lab3_real_no_reference_T));

  /* parameters */
  lab3_real_no_reference_M->ModelData.defaultParam = ((real_T *)
    &lab3_real_no_reference_P);

  /* states (dwork) */
  lab3_real_no_reference_M->ModelData.dwork = ((void *)
    &lab3_real_no_reference_DW);
  (void) memset((void *)&lab3_real_no_reference_DW, 0,
                sizeof(DW_lab3_real_no_reference_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    lab3_real_no_reference_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  lab3_real_no_reference_M->Sizes.numContStates = (0);/* Number of continuous states */
  lab3_real_no_reference_M->Sizes.numY = (0);/* Number of model outputs */
  lab3_real_no_reference_M->Sizes.numU = (0);/* Number of model inputs */
  lab3_real_no_reference_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  lab3_real_no_reference_M->Sizes.numSampTimes = (1);/* Number of sample times */
  lab3_real_no_reference_M->Sizes.numBlocks = (19);/* Number of blocks */
  lab3_real_no_reference_M->Sizes.numBlockIO = (6);/* Number of block outputs */
  lab3_real_no_reference_M->Sizes.numBlockPrms = (100);/* Sum of parameter "widths" */
  return lab3_real_no_reference_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
