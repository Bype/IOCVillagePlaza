Ribbon aRibbon = new Ribbon(80);

void setup()
{
  size(800, 1280, P2D);
  orientation(PORTRAIT);
  aRibbon.randomize();
  smooth();
  frameRate(60);
}
int x=0;
void draw()
{  
  background(255);
  aRibbon.draw(0,x);
  x+=-(x-800)/16;
}

