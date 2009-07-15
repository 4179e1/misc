#include <stdio.h>
#include <math.h>


      main()
      {
        float x,y;

        x=74.12;
        y=6.4;
        printf("74.12/6.4: %f\n",fmod(x,y));        
        x=74.12;
        y=-6.4;
        printf("74.12/(-6.4): %f\n",fmod(x,y));        
        
        getchar();
        return 0;
      }
