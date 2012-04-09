

HomePage theHomePage;

void setup()
{
  size(1280, 800, P3D);
  frameRate(60);
  theHomePage = new HomePage();
  theHomePage.postConstructor();
  theHomePage.currentSeq = theHomePage;
  theHomePage.addVideo("community/0","/sdcard/ioc/movie/ioc0.mp4");
  theHomePage.addVideo("community/1","/sdcard/ioc/movie/ioc1.mp4");
}

long tick = 0;
void draw()
{ 
  background(255);    
  if (theHomePage.currentSeq != null)
    theHomePage.currentSeq = theHomePage.currentSeq.draw();
// if ((tick++)%120==0) println("max mem: " + Runtime.getRuntime().totalMemory()/1024 + " / " +Runtime.getRuntime().freeMemory()/1024);
}

