PFont fontA;
String txt =" test1";

void setup() 
{
  size(screenWidth, screenHeight, P3D);
  orientation(PORTRAIT);
  background(102);

  fontA = loadFont("helvetica.vlw");

  // Set the font and its size (in units of pixels)
  textFont(fontA, 30);
  TestHttpGet mytest = new TestHttpGet();
  try
  {
    txt = mytest.executeHttpGet("http://192.168.1.79:8000/text/welcome/fr/1/");
  }
  catch (Exception e) {
    e.printStackTrace();
  }
}

void draw() {
    background(102);
  // Use fill() to change the value or color of the text
  fill(0);
  text(txt,10,10,width-20,height-20);
}
