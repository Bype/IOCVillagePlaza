import android.net.Uri;
import android.content.Intent;


PImage test;
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
  size(1280, 800, P3D);
  test = loadImage("/sdcard/ioc/home.png");
  
}

void draw()
{
  background(255);    
  image(test, 0, 0);
}

void mousePressed() {
  Uri uri = Uri.parse("/sdcard/ioc/movie/test.mp4");
  Intent intent = new Intent(Intent.ACTION_VIEW);
  intent.setDataAndType(uri,"video/*");
  String t="*/";
  startActivity(intent);
}

