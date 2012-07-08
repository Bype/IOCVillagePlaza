
class ActivitiesPage extends ImagePage
{
  int yShift;
  String theLang;
  Ribbon tagRibbon;
  ActivitiesPage(String aLang)
  {
    super("media/img/"+aLang+"_activities.png");
    tagRibbon = new Ribbon(15);
    tagRibbon.addSection(280, -40, 300, 0);
    tagRibbon.addSection(168, 48, 160, 80, 1);
    tagRibbon.addSection(200, 84, 192, 120);
    tagRibbon.addSection(72, 104, 56, 136, 3);
    tagRibbon.addSection(96, 148, 88, 176);
    tagRibbon.addSection(0, 160, 0, 196, 2);
    theLang = aLang;
    addATouchZone(0, 0, 230, 120, theHomePage);
    addATouchZone(160, 300, 240, 800, new ContentConnection(aLang, "sexual_harassment", 1, 160, 160+48, this));
    addATouchZone(240, 300, 320, 800, new ContentConnection(aLang, "healthy_body", 1, 240, 240+48, this));
    addATouchZone(320, 300, 400, 800, new ContentConnection(aLang, "aids_prevention", 7, 320, 320+48, this));

    addATouchZone(416, 400, 496, 800, new ContentConnection(aLang, "museum", 8, 416, 416+48, this));
    addATouchZone(496, 400, 576, 800, new ContentConnection(aLang, "words_olympians", 2, 496, 496+48, this));

    addATouchZone(592, 500, 672, 800, new ContentConnection(aLang, "community_dev", 7, 592, 592+48, this));
    addATouchZone(672, 500, 752, 800, new ContentConnection(aLang, "giving_winning", 4, 672, 672+48, this));

    addATouchZone(768, 500, 848, 800, new ContentConnection(aLang, "truce", 5, 768, 768+48, this));

    addATouchZone(864, 500, 944, 800, new ContentConnection(aLang, "women_sport", 5, 864, 864+48, this));

    addATouchZone(960, 600, 1040, 800, new ContentConnection(aLang, "sport_sustain", 5, 960, 960+48, this));

    addATouchZone(1056, 600, 1136, 800, new ContentConnection(aLang, "olympic_value", 4, 1056, 1104, this));
    addATouchZone(1136, 600, 1216, 800, new ContentConnection(aLang, "irregular_betting", 2, 1136, 1136+48, this));
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
    image(theCache.getImg("http://192.168.1.79/media/img/"+theLang+"_tag.png"), 0, 0);
    return this;
  }
}




