PImage bg;

PFont titleFont, txtFont;
String title, txt, img;

void setup() {
  size(800, 1280, P3D);
  titleFont = loadFont("title.vlw");
  txtFont = loadFont("text.vlw");
  TestHttpGet mytest = new TestHttpGet();
  try
  {
    title = mytest.executeHttpGet("http://192.168.1.79:8000/title/TestTopic/en/1/");
    txt = mytest.executeHttpGet("http://192.168.1.79:8000/text/TestTopic/en/1/");
    img  = mytest.executeHttpGet("http://192.168.1.79:8000/image/TestTopic/en/1/");
    bg = loadImage(img);
  }
  catch (Exception e) {
    e.printStackTrace();
  }
}
int x=0;
void draw()
{
  background(248);
  fill(16);
  image(bg, 0, 0);
  textFont(titleFont, 40);
  text(title,50,750,width-100,50);
  textFont(txtFont,24);
  text(txt,50,820,width-100,height/2);
}

