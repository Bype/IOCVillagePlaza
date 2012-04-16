
class ActivitiesPage extends ImagePage
{
  int yShift;
  String theLang;
  Ribbon tagRibbon;
  ActivitiesPage(String aLang)
  {
    super(aLang+"/activities.png");
    tagRibbon = new Ribbon(6);
    tagRibbon.addSection(280, -40, 300, 0);
    tagRibbon.addSection(168, 48, 160, 80, 1);
    tagRibbon.addSection(200, 84, 192, 120);
    tagRibbon.addSection(72, 104, 56, 136, 3);
    tagRibbon.addSection(96, 148, 88, 176);
    tagRibbon.addSection(0, 160, 0, 196, 2);
    tagImg = loadImage(aLang+"/tag.png");
    theLang = aLang;
    addATouchZone(0, 0, 230, 120, theHomePage);
    addATouchZone(1056, 600, 1136, 800, new ContentConnection(aLang, "museum",7, 1056, 1104, this));
    addATouchZone(768, 500, 864, 800, new ContentConnection(aLang, "community",2, 768,816, this));
    setup();
  }
  void setup()
  {
     yShift=800;
     tagRibbon.resetAnimation();
  }

  Sequence draw()
  {
    if (0<yShift)
      yShift-=(900+yShift)/100;
    tint(255, 255);
    image(getImg(), 0, yShift);
    tagRibbon.drawFullRecover(6);
    tint(255, 255-(255*yShift)/800);
    image(tagImg, 0, 0);
    return testIn(mouseX, mouseY);
  }
}






