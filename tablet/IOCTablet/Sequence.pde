static PImage tagImg;
public class Sequence
{ 
  private PImage theImg;
  String theImageFileName;

  Sequence draw() {
    return this;
  };
  Sequence() {
  }
  Sequence(String aFilename)
  {
    setImage(aFilename);
  }
  void setup()
  {
  }
  PImage getImg()
  {
    if ((theImageFileName !="") && (theImg == null))
    {       
      System.gc();
      theImg = loadImage(""+theImageFileName);
    }
    return theImg;
  }
  void setImage(String aFilename)
  {
    freeImage();
    theImageFileName = aFilename;
  }
  void freeImage()
  {
    theImg = null;
    
  }
}

