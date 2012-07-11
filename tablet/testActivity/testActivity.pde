
void saveData(String fileName, String newData, boolean appendData) {
  BufferedWriter bw = null;
  try {  
    FileWriter fw = new FileWriter(fileName, appendData);
    bw = new BufferedWriter(fw);
    bw.write(newData + System.getProperty("line.separator"));
  } 
  catch (IOException e) {
    println("error : "+ e);
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

int n = 0;

void setup()
{
  size(1280, 800, P3D);
}

void draw()
{
  background(255);
}

void mouseReleased() {
  n++;
  println("data : "+n);
  saveData("/sdcard/stat.log", "data : "+n, true);
}

