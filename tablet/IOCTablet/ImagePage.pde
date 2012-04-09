class ImagePage extends Sequence
{
  class TouchZone
  {
    PVector tTopLeft;
    PVector tBottomRight;
    Sequence tSequence;
    TouchZone(int xmin, int ymin, int xmax, int ymax, Sequence aSeq)
    {
      tTopLeft = new PVector(xmin, ymin);
      tBottomRight = new PVector(xmax, ymax);
      tSequence = aSeq;
    }
    boolean isIn(int x, int y)
    {
      return ((tTopLeft.x < x) && (x < tBottomRight.x)) && ((tTopLeft.y < y) && (y < tBottomRight.y));
    }
  }

  TouchZone theZone[];
  int curPos = 0;
  int yShift=-900;

  ImagePage(String aFilename, int nbZone)
  {
    super(aFilename);
    theZone = new TouchZone[nbZone];
  }

  void addATouchZone(int xmin, int ymin, int xmax, int ymax, Sequence aSeq)
  {
    theZone[curPos] = new TouchZone(xmin, ymin, xmax, ymax, aSeq);
    curPos++;
  }
  Sequence testIn(int x, int y)
  {
    if (mousePressed)
    {
     for (int i=0;i<theZone.length;i++)
      {
        if (theZone[i].isIn(x, y))
        {
          yShift=0;
          Sequence aSeq =theZone[i].tSequence; 
          aSeq.setup();
          return aSeq;
        }
      }
    }
    return this;
  }

  Sequence draw()
  {
    image(getImg(), 0, 0);
    return testIn(mouseX, mouseY);
  }
}

class ActivitiesPage extends ImagePage
{
  int yShift;
  String theLang;
  Ribbon tagRibbon;
  ActivitiesPage(String aLang)
  {
    super(aLang+"/activities.png", 3);
    tagRibbon = new Ribbon(6);
    tagRibbon.addSection(280, -40, 300, 0);
    tagRibbon.addSection(168, 48, 160, 80, 1);
    tagRibbon.addSection(200, 84, 192, 120);
    tagRibbon.addSection(72, 104, 56, 136, 3);
    tagRibbon.addSection(96, 148, 88, 176);
    tagRibbon.addSection(0, 160, 0, 196, 2);
    tagImg = loadImage(aLang+"/tag.png");
    theLang = aLang;
    addATouchZone(0, 0, 230, 120, theHomePage);
    addATouchZone(1056, 600, 1136, 800, new ContentConnection(aLang, "museum",7, 1056, 1104, getImg()));
    addATouchZone(768, 500, 864, 800, new ContentConnection(aLang, "community",2, 768,816, getImg()));
    setup();
  }
  void setup()
  {
     yShift=800;
     tagRibbon.resetAnimation();
  }

  Sequence draw()
  {
    if (0<yShift)
      yShift-=(900+yShift)/100;
    tint(255, 255);
    image(getImg(), 0, yShift);
    tagRibbon.drawFullRecover(6);
    tint(255, 255-(255*yShift)/800);
    image(tagImg, 0, 0);
    return testIn(mouseX, mouseY);
  }
}




class HomePage extends ImagePage
{
  HomePage()
  {
    super("home.png", 1);
  }
  void postConstructor()
  {
    addATouchZone(280, 540, 400, 800, new ActivitiesConnection("en"));
    /*
    addATouchZone(400, 540, 520, 800, new ActivitiesConnection("fr"));
    addATouchZone(520, 540, 640, 800, new ActivitiesConnection("es"));
    addATouchZone(640, 540, 760, 800, new ActivitiesConnection("ru"));
    addATouchZone(760, 540, 880, 800, new ActivitiesConnection("ar"));
    addATouchZone(880, 540, 400, 1000, new ActivitiesConnection("cn"));
    */
  }
}

