PImage img[];

void load()
{
  for (int i=0;i<8;i++) {
    println("loading image : " + i);
    img[i] = loadImage("http://192.168.1.79:8000/image/en/museum/"+i+".jpg");
  }
 
}

void setup()
{
  img = new PImage[8];
  size(1280, 800, A3D);
  load();
}
int yShift =0;
long tick = 0;
void draw()
{
  translate(0, yShift--);
  background(0);


  for (int i=0;i<8;i++)
  {
    if (yShift > -800*(i+1))
    {
      image(img[i], 0, i*800);
    }

    if (yShift == -800*(i+1))
    { 
      println("removing : "+ i);
      img[i].delete();
      img[i] = null;
    }
  }
  if (yShift==-800*8)
  {
    load();
    yShift =0;
  }
  if ((tick++)%120==0) println(Runtime.getRuntime().maxMemory()/(1024*1024) +" / "+ Runtime.getRuntime().totalMemory()/(1024*1024) + " / " +Runtime.getRuntime().freeMemory()/(1024*1024));
}

