class ActivitiesConnection extends Sequence
{
  Ribbon tagRibbon; 
  int yShift;
  Sequence nextSeq;

  ActivitiesConnection(String aLang)
  { 
    super("/sdcard/Storages/home.png");
    tagRibbon = new Ribbon(14);

    if ("en" == aLang) {
      tagRibbon.addSection(280, 0, 320, 0);
      tagRibbon.addSection(268, 80, 300, 100);
      tagRibbon.addSection(320, 60, 360, 100);
    }
    if ("fr" == aLang) {
      tagRibbon.addSection(400, 0, 440, 0);
      tagRibbon.addSection(368, 80, 400, 100);
      tagRibbon.addSection(330, 60, 380, 100);
    }
    if ("es" == aLang) {
      tagRibbon.addSection(520, 0, 560, 0);
      tagRibbon.addSection(468, 80, 500, 100);
      tagRibbon.addSection(420, 60, 460, 100);
    }
    if ("ru" == aLang) {
      tagRibbon.addSection(640, 0, 680, 0);
      tagRibbon.addSection(568, 80, 600, 100);
      tagRibbon.addSection(520, 60, 560, 100);
    }
    if ("ar" == aLang) {
      tagRibbon.addSection(760, 0, 800, 0);
      tagRibbon.addSection(668, 80, 700, 100);
      tagRibbon.addSection(620, 60, 660, 100);
    }
    if ("cn" == aLang) {
      tagRibbon.addSection(880, 0, 920, 0);
      tagRibbon.addSection(768, 80, 800, 100);
      tagRibbon.addSection(720, 60, 760, 100);
    }
    tagRibbon.addSection(240, 320, 300, 300);
    tagRibbon.addSection(160, 280, 200, 220);
    tagRibbon.addSection(220, 500, 260, 520);
    tagRibbon.addSection(300, 460, 340, 520);
    tagRibbon.addSection(200, 740, 220, 780);
    tagRibbon.addSection(300, 760, 300, 800);
    tagRibbon.addSection(168, 848, 160, 880);
    tagRibbon.addSection(200, 884, 192, 920);
    tagRibbon.addSection(72, 904, 56, 936);
    tagRibbon.addSection(96, 948, 88, 976);
    tagRibbon.addSection(0, 960, 0, 996);
    nextSeq = new ActivitiesPage(aLang);
    setup();
    theHomePage.activitiesPage.put(aLang, nextSeq);
  }
  void setup()
  {
    tagRibbon.resetAnimation();
    yShift=800;
  }
  Sequence draw()
  {
    if (-799<yShift)
    {
      if (0<yShift)
        yShift-=(900+yShift)/120;
      else
        yShift-=-(-900+yShift)/136;
    }
    translate(0, yShift);
    if (0<yShift)
      image(getImg(), 0, -800);
    if (!tagRibbon.doAnimateRecover())
    {
      nextSeq.setup();
      return nextSeq;
    }
    return this;
  }
}

