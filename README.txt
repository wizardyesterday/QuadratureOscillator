/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
1.0 Introduction
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
This application provides a means for a user to generate tones that might
be used to drive other signal processing blocks. A C++ class was written
to bury the implementation of this "coupled quadrature oscilator so that
applications can easily be created. A test program was written that uses
the  in-phase output of the oscillator, and output values are converted
to 16-nit signed little endian raw PCM samples.
An automatic gain control was incorporated so that a constant output level
of sqrt(2)/2 is maintained.

The equations for this
recursive oscillator follow:

  theta = 2*pi*f*fs (1), f = oscillator frequency (Hz), fs = sample rate (S/s)

  u(n) = [cos(theta) * yi(n-1)] - [sin(theta) * yq(n-1)] (2a)
  yi(n) = g(n) * u(n) (2b) 

  v(n) = [sin(theta) * yi(n-1)] + [cos(theta) * yq(n-1)] (3a)
  yq(n) = g(n) * v(n) (3b)
  
For the automatic gain control, the equations follow:

  g(n) = (3.0 / 2.0) - [(u(n)* u(n)) + (v(n)*v(n))] (4)

/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
2.0 File List
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

--------------------------------------
2.1 QuadratureOscillator/ Directory
--------------------------------------
LICENSE
README.txt
buildQuadratureOscillator.sh
clean.sh
include/
src/

--------------------------------------
2.2 include/ directory
--------------------------------------
include/QuadratureOscillator.h

--------------------------------------
2.3  src/ Directory
--------------------------------------
QuadratureOscillator.cc
quadratureOscillator.cc

/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
3.0 Building
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

--------------------------------------
3.1 quadratureOscillator Application
--------------------------------------
From the QuadratureOscillator directory type 'sh buildquadureOscillator.sh.
The program, called quadratureOscillator, will be created.

/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
4.0 Usage
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
To execute the quadratureOscillator program, type ./quadratureOscillator,
and the program will run with the default values of a 200Hz tone, a
sample rate of 8000 samples/second, and a  durtion of 1000 milliseconds.
For a printout of program usage, type ./quadratureOscillator -h.

/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
5.0 Summary
/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
This document has provided a quick overview of the quadrature oscillator demo
program.
Feel free to leave me any comments, suggestions, both, constructive and
destructive.

Many thanks go to Richard G. Lyons for presenting the material in his
Digital Processing Tips chapter in his book, "Understanding Digital Signal
Processing".

Facebook: Chris Gianakopoulos

IRC:
  Server: iec.libera.chat
  Nick: wizardyesterday
  Channels: ##trustnoone, ##rtlsdr

Feel free to contact me anytime!

