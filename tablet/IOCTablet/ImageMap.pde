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
  PImage theImg;
  TouchZone theZone[];
  int curPos = 0;
  int yShift=-900;
  ImagePage(String aFilename, int nbZone)
  {
    theImg = loadImage(aFilename);
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
          return theZone[i].tSequence;
        }
      }
    }
    return this;
  }

  Sequence draw()
  {
    image(theImg, 0, 0);
    return testIn(mouseX, mouseY);
  }
}

class ActivitiesPage extends ImagePage
{
  Ribbon tagRibbon;
  PImage theTag;
  int yShift;
  ActivitiesPage(String aLang)
  {
    super("en_activities.png", 0);
    yShift=800;
    tagRibbon = new Ribbon(6);
    tagRibbon.addSection(280, -40, 300, 0);
    tagRibbon.addSection(168, 48, 160, 80,1);
    tagRibbon.addSection(200, 84, 192, 120);
    tagRibbon.addSection(72, 104, 56, 136,3);
    tagRibbon.addSection(96, 148, 88, 176);
    tagRibbon.addSection(0, 160, 0, 196,2);
    tagRibbon.resetAnimation();
     theTag = loadImage("en_tag.png");
  }
  Sequence draw()
  {
    if (0<yShift)
      yShift-=(900+yShift)/100;
    tint(255,255);
    image(theImg, 0, yShift);
    tagRibbon.drawFull(6);
    tint(255,255-(255*yShift)/800);
    image(theTag, 12, 8);
    return this;//testIn(mouseX, mouseY);
  }
}

class HomePage extends ImagePage
{
  HomePage()
  {
    super("home.png", 6);
    addATouchZone(280, 540, 400, 800, new EnglishConnection());
    addATouchZone(400, 540, 520, 800, new ActivitiesPage("en"));
    addATouchZone(520, 540, 640, 800, new ActivitiesPage("en"));
    addATouchZone(640, 540, 760, 800, new ActivitiesPage("en"));
    addATouchZone(760, 540, 880, 800, new ActivitiesPage("en"));
    addATouchZone(880, 540, 400, 1000, new ActivitiesPage("en"));
  }
}

