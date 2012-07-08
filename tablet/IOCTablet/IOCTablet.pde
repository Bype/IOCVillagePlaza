

HomePage theHomePage;


void setup()
{
  size(1280, 800, P3D);
  frameRate(60);
  theCache = new ImageCache(6);
  theHomePage = new HomePage();
  theHomePage.postConstructor();
  theHomePage.currentSeq = theHomePage;
  theHomePage.addVideo("aids_prevention/1", "/sdcard/Movies/aids_prevention-01-marcos.mp4");
  theHomePage.addVideo("aids_prevention/2", "/sdcard/Movies/aids_prevention-02-johnson_ming.mp4");
  theHomePage.addVideo("aids_prevention/6", "/sdcard/Movies/aids_prevention-07.mp4");
  theHomePage.addVideo("community_dev/1", "/sdcard/Movies/community_dev-01-intro.mp4");
  theHomePage.addVideo("community_dev/2", "/sdcard/Movies/community_dev-02-osire.mp4");
  theHomePage.addVideo("community_dev/3", "/sdcard/Movies/community_dev-03-haiti.mp4");
  theHomePage.addVideo("community_dev/4", "/sdcard/Movies/community_dev-04-lusaka.mp4");
  theHomePage.addVideo("giving_wining/3","/sdcard/Movies/giving_wining-03.mp4");
  theHomePage.addVideoAt("healthy_body/1", "/sdcard/Movies/healthy_body-01a.mp4",200,0,400,200);
  theHomePage.addVideoAt("healthy_body/1", "/sdcard/Movies/healthy_body-01b.mp4",200,200,400,400);
  theHomePage.addVideoAt("healthy_body/1", "/sdcard/Movies/healthy_body-01c.mp4",200,400,400,600);
  theHomePage.addVideoAt("healthy_body/1", "/sdcard/Movies/healthy_body-01d.mp4",200,600,400,800);
  theHomePage.addVideo("irregular_betting/1", "/sdcard/Movies/irregular_betting-01.mp4");
  theHomePage.addVideo("museum/6", "/sdcard/Movies/museum-06.mp4");
  theHomePage.addVideoAt("olympic_value/2", "/sdcard/Movies/olympic_value-02a.mp4",200,0,400,267);
  theHomePage.addVideoAt("olympic_value/2", "/sdcard/Movies/olympic_value-02b.mp4",200,267,400,534);
  theHomePage.addVideoAt("olympic_value/2", "/sdcard/Movies/olympic_value-02c.mp4",200,534,400,800);
  theHomePage.addVideo("sport_sustain/1", "/sdcard/Movies/sport_sustain-01.mp4");
  theHomePage.addVideo("truce/1", "/sdcard/Movies/truce-01.mp4");
  theHomePage.addVideoAt("sexual_harassment/1", "/sdcard/Movies/sha_ASHLEY.mp4",20,142,207,356);
  theHomePage.addVideoAt("sexual_harassment/1", "/sdcard/Movies/sha_HELGA.mp4",207,142,388,356);
  theHomePage.addVideoAt("sexual_harassment/1", "/sdcard/Movies/sha_JACK.mp4",388,142,575,356);
  theHomePage.addVideoAt("sexual_harassment/1", "/sdcard/Movies/sha_JAVIER.mp4",20,356,207,567);
  theHomePage.addVideoAt("sexual_harassment/1", "/sdcard/Movies/sha_LING.mp4",207,356,388,567);
  theHomePage.addVideoAt("sexual_harassment/1", "/sdcard/Movies/sha_MARIA.mp4",388,356,575,567);
  theHomePage.addVideoAt("sexual_harassment/1", "/sdcard/Movies/sha_RYK.mp4",20,567,207,781);
  theHomePage.addVideoAt("sexual_harassment/1", "/sdcard/Movies/sha_SOPHIE.mp4",207,567,388,781);
  theHomePage.addVideoAt("sexual_harassment/1", "/sdcard/Movies/sha_STEPHEN.mp4",388,567,575,781);
}


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
