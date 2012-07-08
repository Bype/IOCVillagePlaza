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

  ArrayList theZones;
  int yShift=-900;

  ImagePage(String aFilename)
  {
    super(aFilename);
    theZones = new ArrayList();
  }

  void addATouchZone(int xmin, int ymin, int xmax, int ymax, Sequence aSeq)
  {
    theZones.add(new TouchZone(xmin, ymin, xmax, ymax, aSeq));
  }
  Sequence testIn(int x, int y)
  {
      for (int i=0;i<theZones.size();i++)
      {
        TouchZone aTZ = (TouchZone)theZones.get(i);
        if (aTZ.isIn(x, y))
        {
          yShift=0;
          Sequence aSeq = aTZ.tSequence;
          aSeq.setup(); 
          if (aSeq instanceof ActivitiesAction)
          {
            return this;
          }
          else
          {            
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

