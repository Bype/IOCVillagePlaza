class AutoRibbon extends Ribbon
{
  PVector tEndP1, tEndP2;
  PVector tOrtho1, tOrtho2;
  PVector aLine1, aLine2;
  float aMag;
  float tAmp; 

  AutoRibbon(int xs1, int ys1, int xs2, int ys2, int nb, int xe1, int ye1, int xe2, int ye2, float aAmp)
  {
    super(nb*2);
    tAmp = aAmp;
    addSection(xs1, ys1, xs2, ys2);
    PVector tStartP1 = new PVector(xs1, ys1);
    PVector tStartP2= new PVector(xs2, ys2);
    tEndP1 = new PVector(xe1, ye1);
    tEndP2 = new PVector(xe2, ye2);

    aLine1 = PVector.sub(tEndP1, tStartP1);
    aLine2 = PVector.sub(tEndP2, tStartP2);
    aMag = min(aLine1.mag(), aLine2.mag());

    aLine1.normalize();
    tOrtho1 = new PVector(aLine1.y, -aLine1.x);

    aLine2.normalize();
    tOrtho2 = new PVector(-aLine2.y, aLine2.x);

    splitLine();
    alterWidth();
    if (tAmp < 10)
      alterAlterPos();
    else 
      alterPos();
  }

  void alterPos()
  { 
    for (int i=1;i<theSection.length-3;i++)
    {

      float rF = int(random(8, 12))*tAmp;
      
      if (rF < 1)
        rF = 2;
        
      float rF1 = random(.03, .07)*tAmp*aMag/10;
      float rF2 = aMag*.04;
      if ( 2 == (i%8))
      {

        // Shift 
        theSection[i].p1.add(PVector.mult(tOrtho1, rF));
        theSection[i].p2.add(PVector.mult(tOrtho1, rF));

        theSection[i+1].p1.add(PVector.mult(tOrtho1, rF));
        theSection[i+1].p2.add(PVector.mult(tOrtho1, rF));

        // Shear
        theSection[i-1].p2.add(PVector.mult(aLine2, rF2));

        theSection[i].p1.add(PVector.mult(aLine2, -2*rF1));      
        theSection[i+1].p1.add(PVector.mult(aLine2, 3*rF1/2));

        theSection[i+2].p2.add(PVector.mult(aLine2, -2*rF2));
      }
      else
        if ( 6 == (i%8))
        {
          //Shift
          theSection[i].p1.add(PVector.mult(tOrtho2, rF));
          theSection[i].p2.add(PVector.mult(tOrtho2, rF));
          theSection[i+1].p1.add(PVector.mult(tOrtho2, rF));
          theSection[i+1].p2.add(PVector.mult(tOrtho2, rF));

          // Shear
          theSection[i-1].p1.add(PVector.mult(aLine2, rF2));

          theSection[i].p2.add(PVector.mult(aLine2, -2*rF1));      
          theSection[i+1].p2.add(PVector.mult(aLine2, 3*rF1/2));

          theSection[i+2].p1.add(PVector.mult(aLine2, -2*rF2));
        }
        else
        {
          float rG = int(random(-4, 4))*5;    
          theSection[i].p1.add(PVector.mult(tOrtho1, rG));
          theSection[i].p2.add(PVector.mult(tOrtho1, rG));
        }
    }
  }

  void alterAlterPos()
  { 
    for (int i=1;i<theSection.length-3;i++)
    {

      float rF = int(random(8, 12))*tAmp;
      /*
      if (tAmp < 10)
        rF = int(random(55, 70));
        */
      float rF1 = random(.03, .07)*tAmp*aMag/10;
      float rF2 = aMag*.04;
      if ( 2 == (i%4))
      {

        if (0< random(-1, 1))
        {
          // Shift 
          theSection[i].p1.add(PVector.mult(tOrtho1, rF));
          theSection[i].p2.add(PVector.mult(tOrtho1, rF));

          theSection[i+1].p1.add(PVector.mult(tOrtho1, rF));
          theSection[i+1].p2.add(PVector.mult(tOrtho1, rF));

          // Shear
          theSection[i-1].p2.add(PVector.mult(aLine2, rF2));

          theSection[i].p1.add(PVector.mult(aLine2, -2*rF1));      
          theSection[i+1].p1.add(PVector.mult(aLine2, 3*rF1/2));

          theSection[i+2].p2.add(PVector.mult(aLine2, -2*rF2));
        }
        else
        {
          //Shift
          theSection[i].p1.add(PVector.mult(tOrtho2, rF));
          theSection[i].p2.add(PVector.mult(tOrtho2, rF));
          theSection[i+1].p1.add(PVector.mult(tOrtho2, rF));
          theSection[i+1].p2.add(PVector.mult(tOrtho2, rF));

          // Shear
          theSection[i-1].p1.add(PVector.mult(aLine2, rF2));

          theSection[i].p2.add(PVector.mult(aLine2, -2*rF1));      
          theSection[i+1].p2.add(PVector.mult(aLine2, 3*rF1/2));

          theSection[i+2].p1.add(PVector.mult(aLine2, -2*rF2));
        }
      }
      else
      {
        float rG = int(random(-4, 4))*5;    
        theSection[i].p1.add(PVector.mult(tOrtho1, rG));
        theSection[i].p2.add(PVector.mult(tOrtho1, rG));
      }
    }
  }


  void alterWidth()
  {
    for (int i=1;i<theSection.length-1;i++)
    {
      float rF = random(.9, 0.15);
      PVector tDir = PVector.sub(theSection[i].p2, theSection[i].p1);
      tDir.mult(rF);
      theSection[i].p2 = PVector.add(theSection[i].p1, tDir);
      PVector tDir1 = PVector.sub(theSection[i].p1, theSection[i].p2);
      tDir1.mult(rF);
      theSection[i].p1 = PVector.add(theSection[i].p2, tDir1);
    }
  }
  void splitLine()
  {

    for (int i=1;i<theSection.length-1;i++)
    {
      if (0==i%2)
      {
        float rF = 2;
        addSection( PVector.add(theSection[i-1].p1, PVector.mult(aLine1, aMag / (rF*theSection.length-1))), 
        PVector.add(theSection[i-1].p2, PVector.mult(aLine2, aMag / (rF*theSection.length-1))));
      }
      else
      {
        float rF= 3;
        addSection( PVector.add(theSection[i-1].p1, PVector.mult(aLine1, (rF*aMag) / (2*theSection.length-1))), 
        PVector.add(theSection[i-1].p2, PVector.mult(aLine2, (rF*aMag) / (2*theSection.length-1))));
      }
    }
    addSection( tEndP1, tEndP2);
  }
}

