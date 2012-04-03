
Ribbon aRibbon = new Ribbon(6);
void setup()
{
  size(1280, 800,P2D);
  frameRate(60);
  iColor[0] = color(68, 25, 59);// Burgundy
  iColor[1] = color(0, 153, 255);// Blue
  iColor[2] = color(255, 85, 0);// Orange
  iColor[3] = color(223, 0, 148);// Pink
  aRibbon.addSection(240, 0, 304, 0);
  aRibbon.addSection(168, 48, 160, 80);
  aRibbon.addSection(200, 84, 192, 120);
  aRibbon.addSection(72, 104, 56, 136);
  aRibbon.addSection(96, 148, 88, 176);
  aRibbon.addSection(0, 160, 0, 196);
  aRibbon.resetAnimation();
}
void draw()
{    
  background(255);
  aRibbon.doAnimate();
}

