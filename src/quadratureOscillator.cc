//*************************************************************************
// File name: cosine.cc
//*************************************************************************

//*************************************************************************
// This program generates DTMF tones that are suitable for dialers on
// the old PSTN. Two numerically oscillators are used for tone generation,
// and if only one oscillator needs to be used, the frequency and
// amplitude of that oscillator will be used. The program was written in
// order to wring out any bugs before it is integrated into the
// MajikWhistle touch tone generator program.
// The NCO data is written to an output file with the format described
// below.  Note that only the in-phase component of the NCO output is
// used, therefore the output file represents a cosine waveform.
//
// To run this program type,
// 
//     ./quadraOscillator -a alpha -R referenceLevel -f frequency 
//            -r sampleRate -d duration (ms) > pcmFileName
//
// where,
//
//    alpha - The convergence coefficient for the AGC.
//    referenceLevel - The desired output power of the oscillator.
//    frequency - The oscilator frequency in Hz..
//    sampleRate - The sample rate in samples/second.
//    duration - The duration in milliseconds.
//*************************************************************************

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "QuadratureOscillator.h"

// This structure is used to consolidate user parameters.
struct MyParameters
{
  float *alphaPtr;
  float *referenceLevelPtr;
  float *frequencyPtr;
  float *sampleRatePtr;
  float *durationPtr;
};

/*****************************************************************************

  Name: getUserArguments

  Purpose: The purpose of this function is to retrieve the user arguments
  that were passed to the program.  Any arguments that are specified are
  set to reasonable default values.

  Calling Sequence: exitProgram = getUserArguments(parameters)

  Inputs:

    parameters - A structure that contains pointers to the user parameters.

  Outputs:

    exitProgram - A flag that indicates whether or not the program should
    be exited.  A value of true indicates to exit the program, and a value
    of false indicates that the program should not be exited..

*****************************************************************************/
bool getUserArguments(int argc,char **argv,struct MyParameters parameters)
{
  bool exitProgram;
  bool done;
  int opt;

  // Default not to exit program.
  exitProgram = false;

  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
  // Default parameters.
  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
  // Default value for convergence constant.
  *parameters.alphaPtr = 0.01;

  // Default value for reference level.
  *parameters.referenceLevelPtr = 0.5;

  // Default to 200Hz.
  *parameters.frequencyPtr = 200;

  // Default to 8000 S/s.
  *parameters.sampleRatePtr = 8000;

  // Default for a 1000 millisecond signal.
  *parameters.durationPtr = 1000;
  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

  // Set up for loop entry.
  done = false;

  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
  // Retrieve the command line arguments.
  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
  while (!done)
  {
    // Retrieve the next option.
    opt = getopt(argc,argv,"a:R:f:r:d:h");

    switch (opt)
    {
      case 'a':
      {
        *parameters.alphaPtr = atof(optarg);
        break;
      } // case

      case 'f':
      {
        *parameters.frequencyPtr = atof(optarg);
        break;
      } // case

      case 'r':
      {
        *parameters.sampleRatePtr = atof(optarg);
        break;
      } // case

      case 'd':
      {
        *parameters.durationPtr = atof(optarg);
        break;
      } // case

      case 'h':
      {

        // Display usage.
        fprintf(stderr,"./quadratureOscillator -a alpha R referenceLevel"
                       " -f frequency -r sampleRate -d duration, ms\n");

        // Indicate that program must be exited.
        exitProgram = true;
        break;
      } // case

      case -1:
      {
        // All options consumed, so bail out.
        done = true;
      } // case
    } // switch

  } // while
  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

  return (exitProgram);

} // getUserArguments

//*************************************************************************
// Mainline code.
//*************************************************************************
int main(int argc,char **argv)
{
  int i;
  bool exitProgram;
  float iValue, qValue;
  int16_t cosineValue;
  float alpha;
  float referenceLevel;
  float frequency;
  float sampleRate;
  float duration;
  int numberOfSamples;
  QuadratureOscillator *myOscillatorPtr;
  struct MyParameters parameters;

  // Set up for parameter transmission.
  parameters.alphaPtr = &alpha;
  parameters.referenceLevelPtr = &referenceLevel;
  parameters.frequencyPtr = &frequency;
  parameters.sampleRatePtr = &sampleRate;
  parameters.durationPtr = &duration;

  // Retrieve the system parameters.
  exitProgram = getUserArguments(argc,argv,parameters);

  if (exitProgram)
  {
    // Bail out.
    return (0);
  } // if

  // We derive this converting milliseconds to seconds.
  numberOfSamples = (int)((sampleRate * duration / 1000));

  // Instantiate a quadrature oscillator.
  myOscillatorPtr = new QuadratureOscillator(sampleRate,
                                              frequency,
                                              alpha,
                                              referenceLevel);

  for (i = 0; i < numberOfSamples; i++)
  {
    // Get the next sample pair.
    myOscillatorPtr->run(&iValue,&qValue);

    // Convert to integer and scale.
    cosineValue = (int16_t)(iValue * 32767);

   // Write the samples to stdout
   fwrite(&cosineValue,sizeof(int16_t),1,stdout);
  } // for

  // Release resource.
  if (myOscillatorPtr != NULL)
  {
    delete myOscillatorPtr;
  } // if

  return (0);

} // main
