#pragma once
void alg_bubblesort(int invoer[], int lengte) 
 {
    int i, j, tijdelijk;
    for (j = 0; j < lengte; j++) 
    {
       for (i = 1; i < lengte - j; i++) 
       {
          if(invoer[i-1] > invoer[i]) 
          {
             tijdelijk = invoer[i];
             invoer[i] = invoer[i-1];
             invoer[i-1] = tijdelijk;
          }
       }
    }
 }