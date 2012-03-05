String txt =" test1";
 PFont fontA;
void setup()
{
  size(400, 400,P3D);
  orientation(PORTRAIT);
  PFont fontA;
  fontA = loadFont("helvetica.vlw");
  textFont(fontA,32);
  
/*
  TestHttpGet mytest = new TestHttpGet();
  try
  {
    txt = mytest.executeHttpGet();
    System.out.println(txt);
  }
  catch (Exception e) {
    e.printStackTrace();
  }
  */

}
void loop()
{
     background(102);
  // Use fill() to change the value or color of the text
  fill(0);
  text("ichi", 20, 60);
  fill(51);
  text("ni", 20, 95);
  fill(204);
  text("san", 20, 130);
  fill(255);
  text("shi", 20, 165);
  
}

