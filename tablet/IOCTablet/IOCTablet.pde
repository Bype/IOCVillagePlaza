static color iColor[] = new color[4];

Sequence currentSeq;

void setup()
{

  try {
    Process  proc = Runtime.getRuntime().exec(new String[] {
      "su", "-c", "service call activity 79 s16 com.android.systemui"
    }
    );

    try
    {
      proc.waitFor();
    }
    catch (java.lang.InterruptedException e)
    {
    }
  }
  catch(java.io.IOException e)
  {
  }
  size(1280, 800, A3D);
  frameRate(60);
  iColor[0] = color(68, 25, 59);// Burgundy
  iColor[1] = color(255, 85, 0);// Orange
  iColor[2] = color(0, 153, 255);// Blue
  iColor[3] = color(223, 0, 148);// Pink
  currentSeq = new HomePage();
}

void draw()
{    
  background(255);
  currentSeq = currentSeq.draw();
}

