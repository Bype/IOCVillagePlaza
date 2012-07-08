
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
    addATouchZone(272,300,384,800,new ContentConnection(aLang, "1",1, 272, 336, this));
    addATouchZone(384,300,496,800,new ContentConnection(aLang, "2",1, 384, 448, this));
    addATouchZone(496,300,607,800,new ContentConnection(aLang, "3",1, 496, 560, this));
    addATouchZone(607,300,721,800,new ContentConnection(aLang, "4",1, 607, 671, this));
    addATouchZone(735,300,847,800,new ContentConnection(aLang, "5",1, 735, 799, this));
    addATouchZone(865,300,976,800,new ContentConnection(aLang, "6",1, 865, 929, this));
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
    return this;
  }
}






