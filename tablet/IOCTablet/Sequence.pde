static PImage tagImg;
static ImageCache theCache;

class ImageCache {
  HashMap imageDict;
  int nbImage;
  int curIndex;
  String imageBuffer[];
  ImageCache()
  {
    nbImage=12;
    curIndex=0;
    imageDict = new HashMap();
    imageBuffer = new String[nbImage];
    for (int i=0;i<nbImage;i++)
      imageBuffer[i]=null;
  }

  PImage getImg(String aFileName)
  {
    if ("" != aFileName)
    {
      if (imageDict.containsKey(aFileName)) {
        PImage anImg = (PImage)imageDict.get(aFileName);
        if (null != anImg)
        {
           return anImg;
        }
        else
        {
         // println("miss : " + aFileName);
        }
      }
      if (null!=imageBuffer[curIndex])
      {
        // println("delete : " + imageBuffer[curIndex]);
        PImage delImg = (PImage)imageDict.get(imageBuffer[curIndex]);
        delImg.delete();
        imageDict.put(imageBuffer[curIndex], null);
        delImg=null;
      }
      // println("load : " + aFileName);
      PImage newImg = loadImage(aFileName);
      imageDict.put(aFileName, newImg);
      imageBuffer[curIndex]=aFileName;
      curIndex = (curIndex+1)%nbImage;
      return newImg;
    }
    return null;
  }
}

public class Sequence
{ 
  private PImage theImg;
  String theImageFileName;
  Sequence mParent;

  Sequence draw() {
    return this;
  };
  Sequence() {
    theImg=null;
    theImageFileName="";
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
    return theCache.getImg(""+theImageFileName);
  }
  void setImage(String aFilename)
  {
    theImageFileName = aFilename;
  }
  void freeImage()
  {
  }
}

