
class Word {

  String name;
  float x, y;
  float n1, n2;
  float noiseScale=0.02;
  float w, h;
  float hw, hh;
  color c = color(0);
  float opacity = 0;

  // Constructor
  Word(String name, float x, float y) {
    this.name = name;
    this.x = x;
    this.y = y;
    n1 = random(50000);
    n2 = random(50000);
    w = textWidth(name);
    h = textAscent() + textDescent();
    hw = w/2;
    hh = w/2;
  }

  String getName() {
    return name;
  }

  void draw() {

    // float around
    x += (noise(n1)*2);
    y += (noise(n2)*2)-1;

    // wrap around horizontally
    if (x > width+hw) x = -hw;
    if (x < -hw) x = width+hw;

    // block vertical edges
    if (y > height-hh) y = height-hh;
    if (y < +hh) y = +hh;

    // how fast we wander
    n1 += noiseScale;
    n2 += noiseScale;

    // fade back in
    opacity = min(opacity+1, 255);

    fill(c, opacity);

    // draw text
    textAlign(CENTER, CENTER);
    text(name, (int)x, (int)y);
  }

  // did someone just click on this object?
  boolean mousePressed(float x, float y) {
    if (x < this.x-hw) return false;
    if (x > this.x+hw) return false;
    if (y < this.y-hh) return false;
    if (y > this.y+hh) return false;
    return true;
  }

  // set fade back to invisible
  void fadeIn() {
    opacity = 0;
  }
}

