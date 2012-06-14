class HomePage extends ImagePage
{
  color iColor[] = new color[4];
  int nbPage;
  Sequence currentSeq;
  HashMap videoPage;
  HashMap activitiesPage;
  
  HomePage()
  {
    super("media/img/home.png");
    iColor[0] = color(68, 25, 59);// Burgundy
    iColor[1] = color(255, 85, 0);// Orange
    iColor[2] = color(0, 153, 255);// Blue
    iColor[3] = color(223, 0, 148);// Pink
    nbPage = 0;
    videoPage = new HashMap();
    activitiesPage = new HashMap();
  }
  void postConstructor()
  {
    addATouchZone(280, 540, 400, 800, new ActivitiesConnection("en"));
    addATouchZone(400, 540, 520, 800, new ActivitiesConnection("fr"));
    addATouchZone(520, 540, 640, 800, new ActivitiesConnection("es"));
    addATouchZone(640, 540, 760, 800, new ActivitiesConnection("ru"));
    addATouchZone(760, 540, 880, 800, new ActivitiesConnection("ar"));
    addATouchZone(880, 540, 1000, 800, new ActivitiesConnection("cn"));
  }
  void addVideo(String aPage, String aUrl)
  {
    videoPage.put(aPage, aUrl);
  }
}

