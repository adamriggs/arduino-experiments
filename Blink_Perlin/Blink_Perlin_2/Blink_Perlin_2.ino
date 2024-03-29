/*
copyright 2007 Mike Edwards

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#include <math.h>

float x1,y1,x2,y2,persistence;
int octaves;

void setup()
{
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  analogWrite(5,0);
  analogWrite(6,0);
  //persistence affects the degree to which the "finer" noise is seen
  persistence = 0.25;
  //octaves are the number of "layers" of noise that get computed
  octaves = 3;
  Serial.begin(9600);
}

void loop()
{
  x1 = float(millis())/100.0f;
  y1 = 10.0f;
  x2 = float(millis())/100.0f;
  y2 = 11.0f;

  //PerlinNoise2 results in a float between -1 and 1
  //below we convert to a n int between 0 and 255
  int m = int(PerlinNoise2(x1,y1,persistence,octaves)*128+128);  
  int n = int(PerlinNoise2(x2,y2,persistence,octaves)*128+128);
  
  m = random(20);
  n = random(20);
  
//  Serial.print("x1: ");
//  Serial.print(x1);
//  Serial.print("\n");
//  
//  Serial.print("y1: ");
//  Serial.print(y1);
//  Serial.print("\n");
//  
//  Serial.print("persistence: ");
//  Serial.print(persistence);
//  Serial.print("\n");
//  
//  Serial.print("octaves: ");
//  Serial.print(octaves);
//  Serial.print("\n");
//  
//  Serial.print("PN: ");
//  Serial.print(PerlinNoise2(x1,y1,persistence,octaves));
//  Serial.print("\n");
//  
//  Serial.print("m: ");
//  Serial.print(m);
//  Serial.print("\n");
//  
//  Serial.print("*****\n");
  
  analogWrite(5,m);
  analogWrite(6,n);
  //delay(5);
}


//using the algorithm from http://freespace.virgin.net/hugo.elias/models/m_perlin.html
// thanks to hugo elias
float Noise2(float x, float y)
{
  long noise;
  noise = x + y * 57;
  noise = pow(noise << 13,noise);
  return ( 1.0 - ( long(noise * (noise * noise * 15731L + 789221L) + 1376312589L) & 0x7fffffff) / 1073741824.0);
}

float SmoothNoise2(float x, float y)
{
  float corners, sides, center;
  corners = ( Noise2(x-1, y-1)+Noise2(x+1, y-1)+Noise2(x-1, y+1)+Noise2(x+1, y+1) ) / 16;
  sides   = ( Noise2(x-1, y)  +Noise2(x+1, y)  +Noise2(x, y-1)  +Noise2(x, y+1) ) /  8;
  center  =  Noise2(x, y) / 4;
  return (corners + sides + center);
}

float InterpolatedNoise2(float x, float y)
{
  float v1,v2,v3,v4,i1,i2,fractionX,fractionY;
  long longX,longY;

  longX = long(x);
  fractionX = x - longX;

  longY = long(y);
  fractionY = y - longY;

  v1 = SmoothNoise2(longX, longY);
  v2 = SmoothNoise2(longX + 1, longY);
  v3 = SmoothNoise2(longX, longY + 1);
  v4 = SmoothNoise2(longX + 1, longY + 1);

  i1 = Interpolate(v1 , v2 , fractionX);
  i2 = Interpolate(v3 , v4 , fractionX);

  return(Interpolate(i1 , i2 , fractionY));
}

float Interpolate(float a, float b, float x)
{
  //cosine interpolations
  return(CosineInterpolate(a, b, x));
}

float LinearInterpolate(float a, float b, float x)
{
  return(a*(1-x) + b*x);
}

float CosineInterpolate(float a, float b, float x)
{
  float ft = x * 3.1415927;
  float f = (1 - cos(ft)) * .5;

  return(a*(1-f) + b*f);
}

float PerlinNoise2(float x, float y, float persistance, int octaves)
{
  float frequency, amplitude;
  float total = 0.0;

  for (int i = 0; i <= octaves - 1; i++)
  {
    frequency = pow(2,i);
    amplitude = pow(persistence,i);

    total = total + InterpolatedNoise2(x * frequency, y * frequency) * amplitude;
  }

  return(total);
}
