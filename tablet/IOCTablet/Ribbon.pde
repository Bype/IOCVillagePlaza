class Ribbon
{
  int rX[]; // top.left x pos
  int rY[]; // top.left y pos
  int rH[]; // height  
  int rA[]; // angle
  color rC[]; // color
  int rNb; //nb of segment
  color rBlue = color(0, 153, 255), 
  rOrange = color(255, 85, 0), 
  rPink =  color(223, 0, 148), 
  rBurgundy = color(68, 25, 59);

  Ribbon(int aNb) {
    rNb = aNb;
    rX = new int[aNb+1];
    rY = new int[aNb+1];
    rH = new int[aNb+1];
    rA = new int[aNb+1];
    rC = new color[aNb+1];
  }

  void randomize()
  {
    // Initial Segment  
    rX[0]=-100;
    rY[0] = height/2;
    rH[0] = height/32;
    rC[0] = rBlue;
    rA[0] = 0;

    for (int i=1;i<rNb;i++)
    {
      if (i%2 == 0)
        // even index : long
      {  
        rX[i] = rX[i-1] + 3*int(random(width/16, width/6));
        rH[i] = int(random(height/16, height/12));

        switch (i%6)
          // iterate throu the 3 kind of long segment
        {
        case 0:     
          rC[i] = rBlue; 
          rA[i] = 50;
          rY[i] = height/2 -height/32;
          break;
        case 2: 
          rC[i] = rPink;
          rA[i] = 30;
          rY[i] = height/2 - height/24;
          break;
        case 4:
          rC[i] = rOrange;
          rA[i] = 100;
          rY[i] = height/2 -height/16;
          break;
        }
      }
      else
        // odd index : small
      {
        rY[i] = height/2;
        rA[i] = 120;        
        rH[i] = int(random(height/24, height/16));
        rC[i] = rBurgundy;
        if (i%3 == 0)
        {
          rX[i] = rX[i-1] +  int(random(width/24, width/16));
        }
        else
        {
          rX[i] = rX[i-1] +  int(random(-width/20, 0));
        }
      }
      rY[i]=rY[i]-20;
    }
    rX[rNb]=400*8;
    rY[rNb] = height/2;
    rA[rNb] = 0;
    rH[rNb] = height/32;
  }

  void draw(int aXa, int aXb)
  {
    for (int i=1;i<rNb;i++)
    {
      if (aXa < rX[i+1])
      {
        
        if (rX[i-1] < aXb)
        {
          /*
          fill(rC[i]);
          noStroke();
          beginShape();
          vertex(rX[i-1]-aXa, rY[i-1]);
          vertex(rX[i]-aXa, rY[i]);
          vertex(rX[i]-aXa+rA[i]*rH[i]/100, rY[i] + rH[i]);
          vertex(rX[i-1]-aXa+rA[i-1]*rH[i-1]/100, rY[i-1] + rH[i-1]);
          endShape(CLOSE);
          */
        }
        else
          break;
       
        if (aXb<rX[i])
        {
          fill(rC[i]);
          noStroke();
          beginShape();
          vertex(rX[i-1]-aXa, rY[i-1]);
          vertex(aXb-aXa, rY[i]);
          vertex(aXb-aXa+rA[i]*rH[i]/100, rY[i] + rH[i]);
          vertex(rX[i-1]-aXa+rA[i-1]*rH[i-1]/100, rY[i-1] + rH[i-1]);
          endShape(CLOSE);
        }
        else
        {
          fill(rC[i]);
          noStroke();
          beginShape();
          vertex(rX[i-1]-aXa, rY[i-1]);
          vertex(rX[i]-aXa, rY[i]);
          vertex(rX[i]-aXa+rA[i]*rH[i]/100, rY[i] + rH[i]);
          vertex(rX[i-1]-aXa+rA[i-1]*rH[i-1]/100, rY[i-1] + rH[i-1]);
          endShape(CLOSE);
        }
      }
    }
  }
}

