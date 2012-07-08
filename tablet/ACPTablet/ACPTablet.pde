

HomePage theHomePage;


void setup()
{
  size(1280, 800, P3D);
  frameRate(60);
  theCache = new ImageCache();
  theHomePage = new HomePage();
  theHomePage.postConstructor();
  theHomePage.currentSeq = theHomePage;
  theHomePage.addVideoAt("1/1", "/sdcard/Storages/acp_overview.mp4", 0, 600, 600, 700);
  theHomePage.addPDFAt("2/1", "/sdcard/Storages/education.pdf", 0, 600, 600, 700);
  theHomePage.addPDFAt("3/1", "/sdcard/Storages/lifeskills.pdf", 0, 600, 600, 700);
  theHomePage.addPDFAt("4/1", "/sdcard/Storages/employment.pdf", 0, 600, 300, 700);
  theHomePage.addVideoAt("4/1", "/sdcard/Storages/acp_keethsmart.mp4", 300, 600, 600, 700);
  theHomePage.addPDFAt("6/1", "/sdcard/Storages/entourage.pdf", 0, 600, 300, 700);
  theHomePage.addPDFAt("6/1", "/sdcard/Storages/entourage_parents.pdf", 300, 600, 600, 700);
}

long tick = 0;
void draw()
{ 
  background(255);    
  if (theHomePage.currentSeq != null)
    theHomePage.currentSeq = theHomePage.currentSeq.draw();
}

void mouseReleased()
{
  if (theHomePage.currentSeq != null)
    theHomePage.currentSeq = theHomePage.currentSeq.testIn(mouseX, mouseY);
}

