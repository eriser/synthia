/*

MIT License
 
Copyright (c) 2016 Andy Best

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "PulseOscillator.h"

namespace Synthia
{
    void PulseOscillator::init(SynthContext *ctx)
    {
        this->_ctx = ctx;
        setFrequency(440.0f);
        setPulseWidth(0.5f);
    }
    
    void PulseOscillator::setFrequency(float freq)
    {
        this->_frequency = freq;
        _tickStep = _frequency / _ctx->sampleRate();
    }
    
    void PulseOscillator::setPulseWidth(float pulseWidth)
    {
        if(pulseWidth < 0)
            pulseWidth = 0;
        if(pulseWidth > 1)
            pulseWidth = 1;
        this->_pulseWidth = pulseWidth;
    }
    
    float PulseOscillator::tick(int channel)
    {
        float samp;
        
        if(_phase >= _pulseWidth)
            samp = 1.0f;
        else
            samp = -1.0f;
        
        _phase += _tickStep;
        
        if(_phase > 1)
            _phase -= 1;
        
        return samp;
    }
}