Ribbon aRibbon[]; 
color iColor[] = new color[4];

void setup() {
  size(1024, 768, P2D);
  iColor[0] = color(68, 25, 59);// Burgundy
  iColor[1] = color(255, 85, 0);// Orange
  iColor[2] = color(0, 153, 255);// Blue
  iColor[3] = color(223, 0, 148);// Pink
  aRibbon = new Ribbon[3];

  int x[] = new int[6];
  int factor = 64;
  x[0]=factor;
  x[1]=x[0]+factor;
  x[2]=x[1]+factor*2;
  x[3]=x[2]+factor*3;
  x[4]=x[3]+(factor*3)/2;
  x[5]=x[4]+factor*3;

  aRibbon[0] = new AutoRibbon(0, x[0], 0, x[1], 3, 1024, x[1], 1024, x[2], 4);
  aRibbon[1] = new AutoRibbon(1024, x[1], 1024, x[2], 3, 0, x[3], 0, x[4], 4);
  aRibbon[2] = new AutoRibbon(0, x[3], 0, x[4], 3, 1024, x[4], 1024, x[5], 4);
  smooth();
}

void draw() {
  background(color(255, 255, 255));
  if ( !aRibbon[0].doAnimateRecover())
    if ( !aRibbon[1].doAnimate())
      aRibbon[2].doAnimateRecover();
}

