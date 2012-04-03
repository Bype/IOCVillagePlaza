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

  void drawSection(int index)
  {
    if (( 0 <index)&&(index < theSection.length))
    {
      theSection[index].drawFullFrom(theSection[index-1]);
    }
  }

  void drawFull(int index)
  {
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
    if (0 ==index%2)
    {
      theSection[index].drawPercentFrom(theSection[index-1], percent);
      drawFull(index);
    }
    else
    {
      drawFull(index);
      theSection[index].drawPercentFrom(theSection[index-1], percent);
    }
  }

  void resetAnimation()
  {
    animIndex = 1;
    animPercent = 0;
  }

  boolean doAnimate()
  {
    drawPercentTo(animIndex, animPercent);
    if (animPercent<100)
    {
      if (0==animIndex%2)
        animPercent+=-(animPercent-120)/8;
      else
        animPercent+=(120-animPercent)/12;
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
}

