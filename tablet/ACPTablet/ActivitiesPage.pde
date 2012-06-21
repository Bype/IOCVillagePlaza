
class ActivitiesPage extends ImagePage
{
  int yShift;
  String theLang;
  Ribbon tagRibbon;
  ActivitiesPage(String aLang)
  {
    super("/sdcard/Storages/"+aLang+"_acp.png");
    tagRibbon = new Ribbon(6);
    tagRibbon.addSection(280, -40, 300, 0);
    tagRibbon.addSection(168, 48, 160, 80, 1);
    tagRibbon.addSection(200, 84, 192, 120);
    tagRibbon.addSection(72, 104, 56, 136, 3);
    tagRibbon.addSection(96, 148, 88, 176);
    tagRibbon.addSection(0, 160, 0, 196, 2);
    theLang = aLang;
    addATouchZone(0, 0, 230, 120, theHomePage);
    addATouchZone(270,300,380,800,new ContentConnection(aLang, "1",1, 270, 330, this));
    addATouchZone(380,300,490,800,new ContentConnection(aLang, "2",1, 380, 430, this));
    addATouchZone(490,300,600,800,new ContentConnection(aLang, "3",1, 490, 540, this));
    addATouchZone(600,300,710,800,new ContentConnection(aLang, "4",1, 600, 650, this));
    addATouchZone(760,300,880,800,new ContentConnection(aLang, "5",1, 760, 810, this));
    addATouchZone(910,300,1020,800,new ContentConnection(aLang, "6",1, 910, 960, this));
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
    image(theCache.getImg("/sdcard/Storages/"+theLang+"_tag.png"), 0, 0);
    return testIn(mouseX, mouseY);
  }
}






