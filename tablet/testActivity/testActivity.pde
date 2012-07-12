
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
  size(320, 320, P2D);
}

void draw()
{
  background(255);
  line(0,0,320,320);
}

void mouseReleased() {
  n++;
  println("data : "+n);
  println(loadStrings("http://ioc.bype.org/stat/museum/en/1.txt"));
}

