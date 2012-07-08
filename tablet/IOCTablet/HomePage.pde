class HomePage extends ImagePage {
  color iColor[] = new color[4];
  int nbPage;
  Sequence currentSeq;
  Map<String, List<VideoStart> > videoPage;
  HashMap activitiesPage;
  PImage tPlay;

  class VideoStart {
    int _xmin; 
    int _ymin; 
    int _xmax; 
    int _ymax;
    String _url;
    VideoStart(String aUrl) {
      _url = aUrl;
    }
    VideoStart(int xmin, int ymin, int xmax, int ymax, String aUrl)
    {
      _xmin = xmin;
      _ymin = ymin;
      _xmax = xmax;
      _ymax = ymax;
      _url = aUrl;
    }
  }

  HomePage() {
    super("media/img/home.png");
  
    iColor[0] = color(68, 25, 59);// Burgundy
    iColor[1] = color(255, 85, 0);// Orange
    iColor[2] = color(0, 153, 255);// Blue
    iColor[3] = color(223, 0, 148);// Pink
    nbPage = 0;
    videoPage = new HashMap<String, List<VideoStart>>();
    activitiesPage = new HashMap();
    tPlay = loadImage("http://192.168.1.79/media/img/play.png");
  }
  void postConstructor() {
    addATouchZone(280, 540, 400, 800, new ActivitiesConnection("en"));
    addATouchZone(400, 540, 520, 800, new ActivitiesConnection("fr"));
    addATouchZone(520, 540, 640, 800, new ActivitiesConnection("es"));
    addATouchZone(640, 540, 760, 800, new ActivitiesConnection("ru"));
    addATouchZone(760, 540, 880, 800, new ActivitiesConnection("ar"));
    addATouchZone(880, 540, 1000, 800, new ActivitiesConnection("cn"));
  }
  void addVideo(String aPage, String aUrl) {
    addVideoAt(aPage, aUrl, 0, 600, 600, 800);
  }
  void addVideoAt(String aPage, String aUrl, int xmin, int ymin, int xmax, int ymax)
  {
    List<VideoStart> l = (List<VideoStart>)videoPage.get(aPage);
    if ( l == null)
      videoPage.put(aPage, l = new ArrayList<VideoStart>());
    l.add(new VideoStart(xmin, ymin, xmax, ymax, aUrl));
  }
  void populate(ImagePage aIm, String aContent, int aNb)
  {
    if (videoPage.containsKey(aContent+"/"+aNb))
    {
      {
        Iterator it=videoPage.get(aContent+"/"+aNb).iterator();
        while (it.hasNext ())
        {
          VideoStart aVs = (VideoStart)it.next();
          aIm.addATouchZone(aVs._xmin, aVs._ymin, aVs._xmax, aVs._ymax, new ActivitiesAction(aVs._url));
          println("map : " + aVs._url +"@"+ aVs._xmin+","+ aVs._ymin+","+ aVs._xmax+","+aVs._ymax);
        }
      }
    }
  }
  void overlay(String aContent, int aNb)
  {
    if (videoPage.containsKey(aContent+"/"+aNb))
    {
      {
        Iterator it=videoPage.get(aContent+"/"+aNb).iterator();
        while (it.hasNext ())
        {
          VideoStart aVs = (VideoStart)it.next();
          int x = ((aVs._xmax+aVs._xmin)/2) - 48;
          int y = ((aVs._ymax+aVs._ymin)/2) - 48;
          image(tPlay, x, y);
        }
      }
    }
  }
}

