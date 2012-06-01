Ribbon aRibbon[]; 
color iColor[] = new color[4];

void setup() {
  size(1024, 768, P2D);
  iColor[0] = color(68, 25, 59);// Burgundy
  iColor[1] = color(255, 85, 0);// Orange
  iColor[2] = color(0, 153, 255);// Blue
  iColor[3] = color(223, 0, 148);// Pink
  aRibbon = new Ribbon[2];
  aRibbon[0] = new AutoRibbon(1024, 350, 1024, 400, 5, 0, 400, 0, 420, 2);
  aRibbon[1] = new AutoRibbon(0, 200, 0, 240, 5, 1024, 160, 1024, 200, 2);
  
  smooth();
}

void draw() {
  background(color(255,255,255));
  if( !aRibbon[0].doAnimate())
    aRibbon[1].doAnimate();
}

