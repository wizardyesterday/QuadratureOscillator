//**************************************************************************
// file name: QuadratureOscillator.h
//**************************************************************************
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
// This class implements a signal processing block that performs a
// numerically controlled oscillator (NCO) function.
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#ifndef __QUADRATUREOSCILLQTOR__
#define __QUADRATUREOSCILLQTOR__

#include <stdint.h>

class QuadratureOscillator
{
  //***************************** operations **************************

  public:

  QuadratureOscillator(float sampleRate,float frequency, float alpha,
                       float referencLevel);

  ~QuadratureOscillator(void);

  void setFrequency(float frequency);
  void setAlpha(float alpha);
  void setReferenceLevel(float referenceLevel);
  void reset(void);
  void run(float *iValuePtr,float *qValuePtr);

  //***************************** attributes **************************
  private:

  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
  // Utility functions.
  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
  void updateGain(float iValue,float qValue);
  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
  // Attributes.
  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
  // The sample rate is needed when performing frequency changes.
  float sampleRate;

  // The operating frequency of the NCO.
  float frequency;

  // The convergence constant.
  float alpha;

  // The desired output level.
  float referenceLevel;

  // Filter coefficients.
  float sineCoefficient;
  float cosineCoefficient;

  // State memory.
  float inPhaseState;
  float quadratureState;

  // Automatic gain control gain.
  float agcGain;
  //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
};

#endif // __QUADRATUREOSCILLQTOR__
