#include "MedianFilter.h"
#include <Arduino.h>

MedianFilter::MedianFilter(int windowSize)
{
    N = windowSize;
    buffer = new float[N];
    temp   = new float[N];

    reset();
}

void MedianFilter::reset()
{
    count = 0;
    index = 0;
    ready = false;
}

void MedianFilter::push(float sample)
{
    buffer[index] = sample;
    index = (index + 1) % N;

    if(count < N) {
        count++;
        if(count < N) return;
    }

    computeMedian();
    ready = true;
}

bool MedianFilter::available()
{
    return ready;
}

float MedianFilter::getMedian()
{
    return medianValue;
}

void MedianFilter::computeMedian()
{
    for(int i=0;i<N;i++)
        temp[i] = buffer[i];

    for(int i=0;i<N-1;i++){
        for(int j=i+1;j<N;j++){
            if(temp[j] < temp[i]){
                float t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    medianValue = temp[N/2];
}