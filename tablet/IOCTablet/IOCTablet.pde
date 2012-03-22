Ribbon aRibbon = new Ribbon(80);

void setup()
{
  size(1280, 800, P2D);
  aRibbon.randomize();
  smooth();
  frameRate(60);
}
int x=0;
void draw()
{  
  background(255);
  aRibbon.draw(0,x);
  x++;
}


