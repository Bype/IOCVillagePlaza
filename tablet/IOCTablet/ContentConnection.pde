class ContentConnection extends Sequence
{
  AutoRibbon tRibbon;
  AutoRibbon sRibbon;
  Ribbon tagRibbon;
  Sequence lastImg;
  int yShift;
  String tLang;
  String tContent;
  Sequence tSequence;
  int localNb;
  int alphaT;  

  ContentConnection(String aLang, String aContent, int aPages, int x1, int x2, Sequence anImage)
  {
    super("media/img/"+aLang+"/"+aContent+"/1.jpg");
    tLang = aLang;
    tContent = aContent;
    yShift=800;
    localNb=aPages;
    lastImg = anImage;
    tRibbon =new AutoRibbon(x1, 0, x2, 0, 5, 550, 800, 600, 800, 10);
    alphaT=1;
  }
  void setup()
  {
    yShift=800;
    alphaT=1;
    theHomePage.nbPage=localNb;
    sRibbon =new AutoRibbon(550, 800, 600, 800, 5, 580, 1608, 630, 1608, 8);
    tRibbon.resetAnimation();
    sRibbon.resetAnimation();
  }
  Sequence draw()
  {

    if (-800<yShift)
    {
      if (0<yShift)
        yShift-=(900+yShift)/160;
      else
        yShift-=-(-900+yShift)/144;
    }
    translate(0, yShift);
    if (0<yShift)
      image(lastImg.getImg(), 0, -800);  
    if ((!tRibbon.doAnimateRecover()) )
      if ((!sRibbon.doAnimateRecover()) )
      {
        if (alphaT < 256)
        {
          alphaT += (1+alphaT/4);
          tint(255, alphaT);
          image(getImg(), 0, -yShift);
          tint(255, 255);
          sRibbon.drawBg(700, 800, 700, 1600);
          sRibbon.drawFullRecover(-1);
        }
        else
        {
          tint(255, 255);
          image(getImg(), 0, -yShift);
          sRibbon.drawBg(700, 800, 700, 1600);
          sRibbon.drawFullRecover(-1);
          image(theCache.getImg("http://192.168.1.79/media/img/"+tLang+"_tag.png"), 0, -yShift);
          sRibbon.shift(0, -808);
          if (1<localNb)
            return  new ContentPages(tLang, tContent, sRibbon, this, 1);
          else
            return new ContentPages(tLang, tContent, sRibbon, this, 0);
        }
      }
    image(theCache.getImg("http://192.168.1.79/media/img/"+tLang+"_tag.png"), 0, -yShift);
    return this;
  }
}

