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

  // Save for frequency updates.
  this->sampleRate = sampleRate;

  // Save for display purposes.
  this->frequency = frequency;

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

  return;

} // run



