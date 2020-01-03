/*
 * Copyright (c) 2020, Valerio Bellizzomi
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the System Experiments Laboratory, Rome nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <unistd.h>
#include <cmath>

/* Declare and initialize variables */

float D=0, Y=0, H=0, TEF=0, TAU=0, Q=0, Z=0, P=0, EMP=0, REMS=0;

int main(int argc, char *argv[]) {

  printf("*** NUCLEAR BLAST CALCULATION ***\n");
  printf("The calculations performed here are based on information published by the American Institute of Physics.\n");
  printf("Specify your slant range (distance) from the blast in miles:\n");
  scanf("%f", &D);
  printf("Specify the yield of the blast in megatons. Typical values range from 0.8 to 20 megatons:\n");
  scanf("%f", &Y);
  printf("Specify the height of the blast in feet:\n");
  scanf("%f", &H);
  printf("Specify the thermal energy fraction. This is the fraction of heat:\n");
  scanf("%f", &TEF);
  printf("Specify the atmospheric transmission factor. It should be between 0 (very cloudy day) and 1 (perfectly clear day):\n");
  scanf("%f", &TAU);

// CALC BLAST EFFECTS

  // Thermal flux Q
  Q=3000.0 * TEF * TAU * Y / (D * D);
  // Blast overpressure P
  Z=(std::pow(Y,0.333))/D;
  P=22.4*(std::pow(Z,3.0)) + 15.8 * (std::pow(Z,1.5));
  // EMP range
  EMP=sqrt(2.0 * H * 3963.0 / 5280.0);
  // Radiation dosage REM
  REMS=250.0 * 1000.0 * Y / (16.0 * 3.1416 * D * D);

// Results

printf("\n\nThe NUCLEAR BLAST had the following effects:\n");
printf("\nTHERMAL FLUX (cal/sq cm) %f", Q);
printf("\nOVERPRESSURE (lb/sq in) %f", P);
printf("\nEMP RANGE (miles) %f", EMP);
printf("\nRADIATION DOSAGE (rems) %f", REMS);

// Overpressure Effects

if (P>20) { printf("\nOverpressure has caused winds in excess of 500 miles per hour. Even multi-story reinforced concrete buildings are leveled.\n");}
else if (P>10) { printf("\nOverpressure has caused winds in excess of 300 miles per hour. Most factories and commercial buildings are leveled, as are small wood and brick residences.\n");}
else if (P>5) { printf("\nOverpressure has caused winds in excess of 160 miles per hour. Unreinforced brick and wood houses are leveled.\n");}
else if (P>2) { printf("\nOverpressure has not had a significant effect on wind conditions or the structure of buildings.\n");};


// Thermal Effect
if (Q>10) { printf("\nThermal flux has burned you to a crisp.\n"); }
else if (Q>5) { printf("\nYou have suffered third degree burns because of Thermal Flux.\n");}
else if (Q>1) { printf("\nYou have suffered second degree burns because of Thermal Flux.\n");}
else if (Q<1) { printf("\nThermal flux has added to your tan.\n");};

};
