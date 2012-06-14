

HomePage theHomePage;


void setup()
{
  size(1280, 800, P3D);
  frameRate(60);
  theCache = new ImageCache();
  theHomePage = new HomePage();
  theHomePage.postConstructor();
  theHomePage.currentSeq = theHomePage;
  theHomePage.addVideo("community_dev/0", "http://192.168.1.79/media/video/test.m3u8");
  theHomePage.addVideo("community_dev/1", "http://192.168.1.79/media/video/test.m3u8");
 
}

long tick = 0;
void draw()
{ 
  background(255);    
  if (theHomePage.currentSeq != null)
    theHomePage.currentSeq = theHomePage.currentSeq.draw();
}

