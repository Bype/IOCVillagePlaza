
class ImageCache {
  HashMap imageDict;
  int nbImage;
  int curIndex;
  String imageBuffer[];
  ImageCache(int aNb)
  {
    nbImage=aNb;
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
         println("miss : " + aFileName);
        }
      }
      if (null!=imageBuffer[curIndex])
      {
        println("delete : " + imageBuffer[curIndex]);
        imageDict.remove(imageBuffer[curIndex]);
      }
      println("load : " + aFileName);
      PImage newImg = loadImage(aFileName);
      imageDict.put(aFileName, newImg);
      imageBuffer[curIndex]=aFileName;
      curIndex = (curIndex+1)%nbImage;
      return newImg;
    }
    return null;
  }
}
