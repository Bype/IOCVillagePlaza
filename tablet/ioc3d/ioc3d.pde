PImage img[] = new ;

void setup() {
  orientation(PORTRAIT);
  size(800,1280, P3D);
  img = loadImage("http://192.168.1.79:8000/image/TestTopic/fr/1.png");
  noStroke();
}

void draw() {
  background(0);
  translate(width / 2, height / 2,0);
  
  beginShape();
  texture(img);
  vertex(-400, -640, 0,0, 0);
  vertex(400, -640, 0, 800, 0);
  vertex(400, 640, 0, 800, 1280);
  vertex(-400, 640, 0, 0, 1280);
  endShape();
}
