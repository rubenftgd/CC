/*
 * sanity_check.c
 *
 * Code generation for model "sanity_check".
 *
 * Model version              : 1.23
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C source code generated on : Wed Dec 20 10:01:40 2017
 *
 * Target selection: rtwin.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Specified
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "sanity_check.h"
#include "sanity_check_private.h"
#include "sanity_check_dt.h"

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
B_sanity_check_T sanity_check_B;

/* Block states (auto storage) */
DW_sanity_check_T sanity_check_DW;

/* Real-time model */
RT_MODEL_sanity_check_T sanity_check_M_;
RT_MODEL_sanity_check_T *const sanity_check_M = &sanity_check_M_;

/* Model output function */
void sanity_check_output(void)
{
  /* Constant: '<Root>/Constant' */
  sanity_check_B.Constant = sanity_check_P.Constant_Value;

  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) sanity_check_P.AnalogOutput_RangeMode;
      parm.rangeidx = sanity_check_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &sanity_check_P.AnalogOutput_Channels,
                     &sanity_check_B.Constant, &parm);
    }
  }

  /* S-Function Block: <Root>/Analog Input */
  {
    ANALOGIOPARM parm;
    parm.mode = (RANGEMODE) sanity_check_P.AnalogInput_RangeMode;
    parm.rangeidx = sanity_check_P.AnalogInput_VoltRange;
    RTBIO_DriverIO(0, ANALOGINPUT, IOREAD, 2,
                   sanity_check_P.AnalogInput_Channels,
                   &sanity_check_B.AnalogInput[0], &parm);
  }
}

/* Model update function */
void sanity_check_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++sanity_check_M->Timing.clockTick0)) {
    ++sanity_check_M->Timing.clockTickH0;
  }

  sanity_check_M->Timing.t[0] = sanity_check_M->Timing.clockTick0 *
    sanity_check_M->Timing.stepSize0 + sanity_check_M->Timing.clockTickH0 *
    sanity_check_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void sanity_check_initialize(void)
{
  /* Start for Constant: '<Root>/Constant' */
  sanity_check_B.Constant = sanity_check_P.Constant_Value;

  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) sanity_check_P.AnalogOutput_RangeMode;
      parm.rangeidx = sanity_check_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &sanity_check_P.AnalogOutput_Channels,
                     &sanity_check_P.AnalogOutput_InitialValue, &parm);
    }
  }
}

/* Model terminate function */
void sanity_check_terminate(void)
{
  /* S-Function Block: <Root>/Analog Output */
  {
    {
      ANALOGIOPARM parm;
      parm.mode = (RANGEMODE) sanity_check_P.AnalogOutput_RangeMode;
      parm.rangeidx = sanity_check_P.AnalogOutput_VoltRange;
      RTBIO_DriverIO(0, ANALOGOUTPUT, IOWRITE, 1,
                     &sanity_check_P.AnalogOutput_Channels,
                     &sanity_check_P.AnalogOutput_FinalValue, &parm);
    }
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  sanity_check_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  sanity_check_update();
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
  sanity_check_initialize();
}

void MdlTerminate(void)
{
  sanity_check_terminate();
}

/* Registration function */
RT_MODEL_sanity_check_T *sanity_check(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)sanity_check_M, 0,
                sizeof(RT_MODEL_sanity_check_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = sanity_check_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    sanity_check_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    sanity_check_M->Timing.sampleTimes =
      (&sanity_check_M->Timing.sampleTimesArray[0]);
    sanity_check_M->Timing.offsetTimes =
      (&sanity_check_M->Timing.offsetTimesArray[0]);

    /* task periods */
    sanity_check_M->Timing.sampleTimes[0] = (0.02);

    /* task offsets */
    sanity_check_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(sanity_check_M, &sanity_check_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = sanity_check_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    sanity_check_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(sanity_check_M, 170.0);
  sanity_check_M->Timing.stepSize0 = 0.02;

  /* External mode info */
  sanity_check_M->Sizes.checksums[0] = (604560389U);
  sanity_check_M->Sizes.checksums[1] = (3853112146U);
  sanity_check_M->Sizes.checksums[2] = (57826642U);
  sanity_check_M->Sizes.checksums[3] = (1188855849U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    sanity_check_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(sanity_check_M->extModeInfo,
      &sanity_check_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(sanity_check_M->extModeInfo,
                        sanity_check_M->Sizes.checksums);
    rteiSetTPtr(sanity_check_M->extModeInfo, rtmGetTPtr(sanity_check_M));
  }

  sanity_check_M->solverInfoPtr = (&sanity_check_M->solverInfo);
  sanity_check_M->Timing.stepSize = (0.02);
  rtsiSetFixedStepSize(&sanity_check_M->solverInfo, 0.02);
  rtsiSetSolverMode(&sanity_check_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  sanity_check_M->ModelData.blockIO = ((void *) &sanity_check_B);
  (void) memset(((void *) &sanity_check_B), 0,
                sizeof(B_sanity_check_T));

  /* parameters */
  sanity_check_M->ModelData.defaultParam = ((real_T *)&sanity_check_P);

  /* states (dwork) */
  sanity_check_M->ModelData.dwork = ((void *) &sanity_check_DW);
  (void) memset((void *)&sanity_check_DW, 0,
                sizeof(DW_sanity_check_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    sanity_check_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 14;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Initialize Sizes */
  sanity_check_M->Sizes.numContStates = (0);/* Number of continuous states */
  sanity_check_M->Sizes.numY = (0);    /* Number of model outputs */
  sanity_check_M->Sizes.numU = (0);    /* Number of model inputs */
  sanity_check_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  sanity_check_M->Sizes.numSampTimes = (1);/* Number of sample times */
  sanity_check_M->Sizes.numBlocks = (4);/* Number of blocks */
  sanity_check_M->Sizes.numBlockIO = (2);/* Number of block outputs */
  sanity_check_M->Sizes.numBlockPrms = (14);/* Sum of parameter "widths" */
  return sanity_check_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
