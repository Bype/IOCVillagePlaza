import android.net.Uri;
import android.content.Intent;


PImage test;
void setup()
{
  size(1280, 800, P3D);
  test = loadImage("/sdcard/ioc/home.png");
}

void draw()
{
  background(255);    
  image(test, 0, 0);
}

void mousePressed() {
  File file = new File("/sdcard/Storages/education.pdf");
  Uri uri = Uri.fromFile(file);
  Intent intent = new Intent(Intent.ACTION_VIEW);
  intent.setDataAndType(uri,"application/pdf");
  startActivity(intent);
}

