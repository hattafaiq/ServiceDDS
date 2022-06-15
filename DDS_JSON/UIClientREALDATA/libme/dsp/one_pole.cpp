#include "one_pole.h"

//
//  OnePole.h
//  http://www.earlevel.com/main/2012/12/15/a-one-pole-filter/
//

/*
OnePole *dcBlockerLp = new OnePole(10.0 / sampleRate);
...
// for each sample:
sample -= dcBlockerLp->process(sample);
*/

//inline
void OnePole::setFc(double Fc) {
    b1 = exp(-2.0 * M_PI * Fc);
    a0 = 1.0 - b1;
}

//inline
float OnePole::process(float in) {
    return z1 = in * a0 + z1 * b1;
}


/*
OnePole::OnePole()
{
}*/
