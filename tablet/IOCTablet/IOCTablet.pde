static color iColor[] = new color[4];
static int nbPage;

static Sequence currentSeq,theHomePage;
AutoRibbon aRibbon;
int Xshift=1136;

void setup()
{
  size(1280, 800,P3D);
  frameRate(60);
  iColor[0] = color(68, 25, 59);// Burgundy
  iColor[1] = color(255, 85, 0);// Orange
  iColor[2] = color(0, 153, 255);// Blue
  iColor[3] = color(223, 0, 148);// Pink
  nbPage = 7;
  theHomePage = currentSeq = new HomePage();
  
}

long tick = 0;
void draw()
{ 
  background(255);    
  if(currentSeq != null)
    currentSeq = currentSeq.draw();
  else
    println("Null Sequence");
  if ((tick++)%120==0) println("max mem: " + Runtime.getRuntime().totalMemory()/1024 + " / " +Runtime.getRuntime().freeMemory()/1024);
}

