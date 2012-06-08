class Ribbon
{
  RibbonSection theSection[];
  int curPos = 0;
  int animIndex =1;
  int animPercent =0;

  Ribbon(int nb)
  {
    theSection = new RibbonSection[nb];
  }

  void addSection(int x1, int y1, int x2, int y2, int aC)
  {

    theSection[curPos] = new RibbonSection(x1, y1, x2, y2, aC);
    curPos++;
  }

  void addSection(int x1, int y1, int x2, int y2)
  {
    int tC=0;
    if (0 != curPos% 2)
    {
      tC= (curPos%6)%3+1;
    }

    addSection(x1, y1, x2, y2, tC);
  }

  void addSection(PVector aP1, PVector aP2)
  {
    int tC=0;
    if (0 != curPos% 2)
    {
      tC= (curPos%6)%3+1;
    }
    addSection(aP1, aP2, tC);
  }

  void addSection(PVector aP1, PVector aP2, int aC)
  {
    theSection[curPos] = new RibbonSection(aP1, aP2, aC);
    curPos++;
  }

  void drawSection(int index)
  {
    if (( 0 <index)&&(index < theSection.length))
    {
      theSection[index].drawFullFrom(theSection[index-1]);
    }
  }

  void drawFull(int index)
  {
    if ((index<0)||(theSection.length<index))
      index = theSection.length;
    for (int i=1;i<index;i++)
    {
      drawSection(i);
    }
  }


  void drawFullRecover(int index)
  {
    if ((index<0)||(theSection.length<index))
      index = theSection.length;
    for (int i=2;i<index;i+=2)
    {
      drawSection(i);
    }
    for (int i=1;i<index;i+=2)
    {
      drawSection(i);
    }
  }

  void drawPercentTo(int index, int percent)
  {
    drawFull(index);
    theSection[index].drawPercentFrom(theSection[index-1], percent);
  }


  void drawPercentRecoverTo(int index, int percent)
  {
    if (0 ==index%2)
    {
      theSection[index].drawPercentFrom(theSection[index-1], percent);
      drawFullRecover(index);
    }
    else 
    {
      drawFullRecover(index);
      theSection[index].drawPercentFrom(theSection[index-1], percent);
    }
  }

  void resetAnimation()
  {
    animIndex = 1;
    animPercent = 0;
  }

  boolean easing()
  {
    if (animPercent<100)
    {
      if (0==animIndex%2)
        animPercent+=-(animPercent-120)/6;
      else
        animPercent+=(120-animPercent)/10;
    }
    else
    {
      if (animIndex<(theSection.length-1))
      {
        animPercent=0;
        animIndex++;
      }
      else
      {
        return false;
      }
    }
    return true;
  }
  
  void shift(int x,int y)
  {
    PVector aShift = new PVector(x,y);
    for (int i=0;i<theSection.length;i++)
    {
      theSection[i].shift(aShift);
    }
  }

  boolean doAnimate()
  {
    drawPercentTo(animIndex, animPercent);
    return easing();
  }

  boolean doAnimateRecover()
  {
    drawPercentRecoverTo(animIndex, animPercent);
    return easing();
  }
  
  void drawBg(int x1,int y1,int x2,int y2)
  {
    fill(255);
    noStroke();
    beginShape();
    vertex(x1,y1);
    for (int i=0;i<theSection.length;i++)
    {
      PVector aM = PVector.div(PVector.add(theSection[i].p1,theSection[i].p2),2.);
      vertex(aM.x,aM.y);
    }
    vertex(x2,y2);
    endShape(CLOSE);
  }
}

