class ContentPages extends ImagePage
{
  Ribbon tRibbon, nextRibbon;
  Sequence prevImg;
  String nextFileName;
  int tNb;
  String tLang;
  String tContent;
  boolean isLast;
  int shiftY;


  ContentPages(String aLang, String aContent, Ribbon aRibbon, Sequence aImg, int nb)
  {
    super(aLang+"/"+aContent+"/"+(nb+1)+".jpg");
    nextRibbon = new AutoRibbon(580, 800, 630, 800, 5, 580, 1600, 630, 1600, 8);
    tNb = nb;
    tLang = aLang;
    tContent = aContent;
    addATouchZone(0, 0, 230, 120, theHomePage);
    prevImg = aImg;
    tRibbon = aRibbon;
    shiftY =0;
    if (theHomePage.videoPage.containsKey(aContent+"/"+nb))
    {
      addATouchZone(160, 200, 480, 600, new ActivitiesAction((String)theHomePage.videoPage.get(aContent+"/"+nb)));
    }
  }
  Sequence draw()
  {
    translate(0, shiftY);
    image(getImg(), 0, 800);
    nextRibbon.drawBg(700, 800, 700, 1600);
    nextRibbon.drawFullRecover(-1);
    image(prevImg.getImg(), 0, 0);
    tRibbon.drawBg(700, 0, 700, 800);
    tRibbon.drawFullRecover(-1);
    image(tagImg, 0, -shiftY);
    if (mousePressed)
    {

      if ((mouseY-pmouseY)<0)
        shiftY += (mouseY-pmouseY);

      if (shiftY<-800)
        shiftY=-800;
    }
    else
    {
      if (shiftY < -300)
      {
        if (-780 < shiftY)
        {
          shiftY -= (800+shiftY)/4;
        }
        else
        {
          if (-800<shiftY)
          {
            shiftY--;
          }
          else 
          {
            if (tNb < (theHomePage.nbPage-1))
            {
              nextRibbon.shift(0, -800);
              return new ContentPages(tLang, tContent, nextRibbon, this, tNb+1);
            }
          }
        }
      }
      else
      {
        shiftY += -shiftY/4;
      }
    }
    return testIn(mouseX, mouseY);
  }
}
