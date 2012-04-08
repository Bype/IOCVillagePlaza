class ActivitiesConnection extends Sequence
{
  Ribbon tagRibbon; 
  int yShift;
  Sequence nextSeq;

  ActivitiesConnection(String aLang)
  { 
    super("home.png");
    tagRibbon = new Ribbon(14);
    tagRibbon.addSection(280, 0, 320, 0);
    tagRibbon.addSection(268, 80, 300, 100);
    tagRibbon.addSection(320, 60, 360, 100);
    tagRibbon.addSection(240, 280, 280, 260);
    tagRibbon.addSection(160, 280, 200, 220);
    tagRibbon.addSection(220, 500, 260, 520);
    tagRibbon.addSection(300, 460, 340, 500);
    tagRibbon.addSection(220, 740, 240, 760);
    tagRibbon.addSection(280, 760, 300, 800);
    tagRibbon.addSection(168, 848, 160, 880);
    tagRibbon.addSection(200, 884, 192, 920);
    tagRibbon.addSection(72, 904, 56, 936);
    tagRibbon.addSection(96, 948, 88, 976);
    tagRibbon.addSection(0, 960, 0, 996);
    nextSeq = new ActivitiesPage(aLang);
    setup();
   
  }
  void setup()
  {
     tagRibbon.resetAnimation();
     yShift=800;
  }
  Sequence draw()
  {
    if (-799<yShift)
    {
      if (0<yShift)
        yShift-=(900+yShift)/200;
      else
        yShift-=-(-900+yShift)/180;
    }
    translate(0, yShift);
    if (0<yShift)
      image(getImg(), 0, -800);
    else
      freeImage();
    if (!tagRibbon.doAnimateRecover())
    {
      return nextSeq;
    }
    return this;
  }
}

class ContentConnection extends Sequence
{
  AutoRibbon tRibbon;
  AutoRibbon sRibbon;
  Ribbon tagRibbon;
  PImage lastImg;
  int yShift;
  String tLang;
  String tContent;
  Sequence tSequence;
  ContentConnection(String aLang, String aContent, int x1, int x2, PImage anImage)
  {
    super(aLang+"/"+aContent+"/0.jpg");
    tLang = aLang;
    tContent = aContent;
    yShift=800;
    lastImg = anImage;
    tRibbon =new AutoRibbon(x1, 0, x2, 0, 5, 550, 800, 600, 800,10);
    setup(); 
  }
  void setup()
  {
    yShift=800;
    tRibbon.resetAnimation();
    sRibbon =new AutoRibbon(550, 800, 600, 800, 5, 580, 1608, 630, 1608,8);
    sRibbon.resetAnimation();
  }
  Sequence draw()
  {
      
    if (-800<yShift)
    {
      if (0<yShift)
        yShift-=(900+yShift)/200;
      else
        yShift-=-(-900+yShift)/180;
    }
    translate(0, yShift);
    if (0<yShift)
      image(lastImg, 0, -800);
    if ((!tRibbon.doAnimateRecover()) )
      if ((!sRibbon.doAnimateRecover()) )
      {
        image(tagImg, 0, -yShift);
        sRibbon.shift(0, -808);
        return  new ContentPages(tLang, tContent, sRibbon,getImg(),0);
      }
    image(tagImg, 0, -yShift);
    return this;
  }
}

