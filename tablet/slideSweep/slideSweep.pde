int shiftY;
int inc;
static ImageCache theCache;


void setup() { 
  theCache = new ImageCache(5);
  size(1280, 800, P3D);
  frameRate(60);
  shiftY = 0;
  inc = -8;
  
}

void draw () {
  background(255);    
  translate(0, shiftY);
  int index = -shiftY/800;
  image(theCache.getImg(1+index+".png"),0,index*800);
  if(0<index)
    image(theCache.getImg(index+".png"),0,(index-1)*800);
  if(index < 6)
    image(theCache.getImg(2+index+".png"),0,(index+1)*800);
  
  
  line(0, 0, 1280, 5600);
  shiftY += inc;
  if (shiftY<-4800)
    inc = -inc;
}

