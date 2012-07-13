String[] names = { "cheat", "development", "effort", "giving", "hiv", "museum", "peace", "secrets", "sustainability", "together", "words"};
String current = "english";
String[] languageOrder = { "english", "russian", "spanish", "french", "arab", "chinese" };
int currentIndex = -2;
PImage logo;
PImage badge;

int lastTouch = 0;

Langue langue;

ArrayList<Animation> animations = new ArrayList();

void setup() {

  size(1024, 768);

  logo = loadImage("logo.png");
  badge = loadImage("badge.png");

  smooth();

  PVector loc;

  for (int i=0; i<names.length; i++) {
    float h = int(height / 11.0);
    float y = int(h/2) + (h*i);
    loc = new PVector(width/2, y);
    animations.add(new Animation(names[i], loc));
  }

  langue = new Langue();

  setupScanner();
  setupRibbon();
  setupOsc();
}

void draw() {

  background(255);
  
  if (currentIndex > -2 && abs(lastTouch - millis()) > 30000) {
    currentIndex = -2;
  }

  if (currentIndex == -2) {
    drawBadge();
  } else if (currentIndex == -1) {
    drawLanguage();
  } 
  else {
    drawScenarios();
  }


  //drawRibbon();
}


void drawBadge() {
  
  image(badge, width/2-badge.width/2, height/2-badge.height/2);
  
  float x = width/2;
  float y = width/2 - 175;
  float s = sin(millis()*0.002);
  y += s * 25;
  
  stroke(255,0,0,127);
  line(x-150,y,x+150,y);
  
}


void drawLanguage() {
  
    drawRibbon();
    langue.draw();
}

void drawScenarios() {
  
    drawRibbon();
    image(logo, 20, 0, 100, 100);
    for (Animation animation : animations) {
      animation.draw();
    }
}


void mousePressed() {

  lastTouch = millis();
  
  if (currentIndex < 0) {
    int index = langue.mousePressed(mouseX,mouseY);
    if (index >= 0) {
      setupRibbon();
      currentIndex = index;
    }
    return;
  }

  if (mouseX < 120 && mouseY < 100) {
    currentIndex = -2;
      setupRibbon();
    return;
  }

  for (Animation animation: animations) {
    if (animation.mousePressed(mouseX, mouseY)) {
      play(animation.name);
      println("play: " + animation.name);
      break;
    }
  }
}

void keyPressed() {

  lastTouch = millis();

  addToScanner(key);
}

