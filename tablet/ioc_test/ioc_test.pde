
int x=0;
int initX=0;
int n=0;

int nbImg = 7;
int nbSec =  nbImg*8;
int rX[] = new int[nbSec+1];
int rY[] = new int[nbSec+1];
int rT[] = new int[nbSec+1];
int rA[] = new int[nbSec+1];
color rC[] = new color[nbSec+1];
PImage rI[] = new PImage[nbImg+1];

float aRad=0;

void randomize()
{
  rX[0]=-20;
  rY[0] = height/2;
  rT[0] = height/32;
  rC[0] = color(0, 153, 255);
  rA[0] = 0;
  for (int i=1;i<nbSec;i++)
  {
    if (i%2 == 0)
      // long
    {  
      rX[i] = rX[i-1] + 3*int(random(width/16, width/6));
      rT[i] = int(random(height/32, height/24));

      switch (i%6)
      {
      case 0:     
        rC[i] = color(0, 153, 255); 
        rA[i] = 50;
        rY[i] = height/2 -height/32;
        break;
      case 2: 
        rC[i] = color(223, 0, 148);
        rA[i] = 30;
        rY[i] = height/2 - height/24;
        break;
      case 4:
        rC[i] = color(255, 85, 0);
        rA[i] = +100;
        rY[i] = height/2 -height/16;
        break;
      }
    }
    else
      //small
    {
      if (i%3 == 0)
      {
        rX[i] = rX[i-1] +  int(random(width/24, width/16));
        rY[i] = height/2;
        rC[i] = color(68, 25, 59);      
        rT[i] = int(random(height/48, height/32));
        rA[i] = +120;
      }
      else
      {
        rX[i] = rX[i-1] +  int(random(-width/20, 0));
        rY[i] = height/2;
        rC[i] = color(68, 25, 59);      
        rT[i] = int(random(height/48, height/32));
        rA[i] = 120;
      }
    }
    rY[i]=rY[i]-20;
  }
  rX[nbSec]=400*8;
  rY[nbSec] = height/2;
  rA[nbSec] = 0;
  rT[nbSec] = height/32;
}

PImage tab;

void setup()
{
  size(800, 1280, P2D);
  frameRate(60);
  for (int i=0;i<nbImg;i++)
  {
    rI[i]=loadImage(int(i+1)+".png");
  }
  rI[nbImg] = loadImage("home.jpg");
  tab=loadImage("tab.png");
  randomize();
  noStroke();
  smooth();
}
int aShift=0;
void draw()
{
  background(248);
  int virPosX = n*width-x;
  image(rI[int(virPosX/width)], x, 0);
  image(rI[int(virPosX/width)+1], width+x, 0);
  image(tab, 0, 0);
  if ( -(width/2) < x)
  {
    if ( (mousePressed) && (0 < initX-mouseX))
      x-=initX-mouseX;
    else
    {

      if (x < 0)
      {
        x += (-x)/2;
      }
    }
    initX=mouseX;
  }
  else
  {
    if (-(width-1) < x)
    {  
      x -= (width+x)/2;
    }
    else
    {
      x=0;
      initX=0;
      n++;
      if ((nbImg-1)<n)
        n = 0;
    }
  }

  fill(color(248));
  aShift++;
  int rubPosX=virPosX+aShift;
  beginShape();
  vertex(0, height/2+40);
  for (int i=0;i<nbSec;i++)
  {

    if (rubPosX < rX[i+1])
    {
      if (rX[i-1] < rubPosX + 4*width/3)
      {
        vertex(rX[i]-rubPosX, rY[i]);
      }
      else
        break;
    }
  }
  vertex(width, height/2+40);
  endShape(CLOSE);

  for (int i=1;i<nbSec;i++)
  {

    if (rubPosX < rX[i+1])
    {
      if (rX[i-1] < rubPosX + 4*width/3)
      {


        fill(rC[i]);
        beginShape();
        vertex(rX[i-1]-rubPosX, rY[i-1]);
        vertex(rX[i]-rubPosX, rY[i]);
        vertex(rX[i]-rubPosX+rA[i]*rT[i]/100, rY[i] + rT[i]);
        vertex(rX[i-1]-rubPosX+rA[i-1]*rT[i-1]/100, rY[i-1] + rT[i-1]);
        endShape(CLOSE);
      }
      else
        break;
    }
  }
}

