int shiftY;
int inc;
static ImageCache theCache;

void saveData(String fileName, String newData, boolean appendData) {
  BufferedWriter bw = null;
  try {  
    FileWriter fw = new FileWriter(fileName, appendData);
    bw = new BufferedWriter(fw);
    bw.write(newData + System.getProperty("line.separator"));
  } 
  catch (IOException e) {
  } 
  finally {
    if (bw != null) {
      try { 
        bw.close();
      } 
      catch (IOException e) {
      }
    }
  }
}



void setup() { 
  theCache = new ImageCache(8);
  size(1280, 800, P3D);
  frameRate(60);
  shiftY = 0;
  inc = -12;
  for (int i=1;i<8;i++)
    theCache.getImg("http://192.168.1.79/media/img/en/community_dev/"+i+".jpg");
  saveData("/sdcard/stat.log", "une data", true);
}



void draw () {
  background(255);    
  translate(0, shiftY);
  int index = -shiftY/800;
  image(theCache.getImg("http://192.168.1.79/media/img/en/community_dev/"+int(index+1)+".jpg"), 0, index*800);
  if (index < 6)
    image(theCache.getImg("http://192.168.1.79/media/img/en/community_dev/"+int(2+index)+".jpg"), 0, (index+1)*800);  
  if (0<index)
    image(theCache.getImg("http://192.168.1.79/media/img/en/community_dev/"+index+".jpg"), 0, (index-1)*800);
  line(0, 0, 1280, 5600);
  shiftY += inc;
  if ((0<shiftY)|| (shiftY<-4800)) 
    inc = -inc;
}

