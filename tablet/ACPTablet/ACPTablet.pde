

HomePage theHomePage;


void setup()
{
  size(1280, 800, P3D);
  frameRate(60);
  theCache = new ImageCache();
  theHomePage = new HomePage();
  theHomePage.postConstructor();
  theHomePage.currentSeq = theHomePage;
  theHomePage.addVideoAt("1/1", "/sdcard/Storages/acp_overview.mp4", 0, 200, 700, 600);
  theHomePage.addPDFAt("2/1", "/sdcard/Storages/education.pdf", 0, 200, 700, 600);
  theHomePage.addPDFAt("3/1", "/sdcard/Storages/lifeskills.pdf", 0, 200, 700, 600);
  theHomePage.addPDFAt("4/1", "/sdcard/Storages/employement.pdf", 0, 200, 700, 600);
  theHomePage.addPDFAt("6/1", "/sdcard/Storages/entourage.pdf", 0, 200, 700, 600);
  
}

long tick = 0;
void draw()
{ 
  background(255);    
  if (theHomePage.currentSeq != null)
    theHomePage.currentSeq = theHomePage.currentSeq.draw();
}

