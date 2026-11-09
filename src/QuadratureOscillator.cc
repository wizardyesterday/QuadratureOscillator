//************************************************************************
// file name: QuadratureOscillator.cc
//************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "QuadratureOscillator.h"

using namespace std;

/*****************************************************************************

  Name: QuadratureOscillator

  Purpose: The purpose of this function is to serve as the constructor for
  an instance of a QuadratureOscillator.

  Calling Sequence: QuadratureOscillator(sampleRate,frequency);

  Inputs:

    sampleRate - The sample rate in S/s.

    frequency - The frequency in Hz.

  Outputs:

    None.

*****************************************************************************/
QuadratureOscillator::QuadratureOscillator(
  float sampleRate,
  float frequency,
  float alpha,
  float referencLevel)
{

  // Save parameters for later use.
  this->sampleRate = sampleRate;
  this->frequency = frequency;
  this->alpha = alpha;
  this->referenceLevel = referenceLevel;

  // Set filter coefficients.
  sineCoefficient = sin(2 * M_PI * frequency / sampleRate);
  cosineCoefficient = cos(2 * M_PI * frequency / sampleRate);

  // Set system to an initial state.
  reset();

  return;

} // QuadratureOscillator

/*****************************************************************************

  Name: ~QuadratureOscillator

  Purpose: The purpose of this function is to serve as the destructor for
  an instance of a QuadratureOscillator.

  Calling Sequence: ~QuadratureOscillator()

  Inputs:

    None.

  Outputs:

    None.

*****************************************************************************/
QuadratureOscillator::~QuadratureOscillator(void)
{

} // ~QuadratureOscillator

/*****************************************************************************

  Name: setFrquency

  Purpose: The purpose of this function is to reset all runtime values to
  initial values.

  Calling Sequence: setFrequency(frequency)

  Inputs:

    frequency - The operating frequency in Hz.

  Outputs:

    None.

*****************************************************************************/
void QuadratureOscillator::setFrequency(float frequency)
{
  uint32_t i;

  // Save for later use.
  this->frequency = frequency;

  // Set filter coefficients.
  sineCoefficient = sin(2 * M_PI * frequency / sampleRate);
  cosineCoefficient = cos(2 * M_PI * frequency / sampleRate);

  return;

} // setFrequency

/*****************************************************************************

  Name: reset

  Purpose: The purpose of this function is to reset all runtime values to
  initial values.

  Calling Sequence: reset()

  Inputs:

    None.

  Outputs:

    None.

*****************************************************************************/
void QuadratureOscillator::reset(void)
{

  // Se initial conditions of state memory.
  inPhaseState = 0;
  quadratureState = 1;

  // Set initial gain to something reasonable.
  agcGain = 1;

  return;

} // reset

/*****************************************************************************

  Name: run

  Purpose: The purpose of this function is to generate one sample of a
  complex exponentional function.

  Calling Sequence: run(iValuePtr,qValuePtr)

  Inputs:

    iValuePtr - A pointer to storage for the in-phase component.

    qValuePtr - A pointer to storage for the quadrature component.

  Outputs:

    None.

*****************************************************************************/
void QuadratureOscillator::run(float *iValuePtr,float *qValuePtr)
{
  float u;
  float v;

  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
  u = (cosineCoefficient * inPhaseState) -
      (sineCoefficient * quadratureState);

  v = (sineCoefficient * inPhaseState) +
      (cosineCoefficient * quadratureState);
  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

  *iValuePtr = agcGain * u;
  *qValuePtr = agcGain * v;

  // Update fillter state.
  inPhaseState = *iValuePtr;
  quadratureState = *qValuePtr;

  // Update AGC.
  updateGain(u,v);

  return;

} // run

/*****************************************************************************

  Name: updateGain

  Purpose: The purpose of this function is to generate one sample of a
  complex exponentional function.

  Calling Sequence: updateFain(iValue,qValue)

  Inputs:

    iValue - The in-phase value of a sample.

    qValue - The quadrature value of a sample.

  Outputs:

    gain - The updated gain.

*****************************************************************************/
void QuadratureOscillator::updateGain(float iValue,float qValue)

{
  float power;
  float error;

  // Compute magnitude-squared.
  power = (iValue * iValue) + (qValue * qValue);

  // Compute error signal.
  error =  referenceLevel - power;

  // Compute updated gain value.
  agcGain = agcGain + (alpha * error);

  return;

} // updateGain



