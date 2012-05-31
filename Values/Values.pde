
/**
 * IOC Plaza
 * Values
 * (c) 2012 Douglas Edric Stanley, David Olivari / BYPE Productions, Nicholas Haagensen / Trivial Mass
 */
 
import processing.opengl.*;
import oscP5.*;
import netP5.*;

PFont font;

OscP5 osc;
NetAddress stadium;

ArrayList<Word> words = new ArrayList();

void setup() {

  size(1024, 768, OPENGL);

  font = loadFont("HelveticaNeueLTStd-Md-48.vlw");
  textFont(font);

  // get port & ip from osc.xml
  // listen on port 8000 (for what? who knows)
  osc = new OscP5(this, 8000);
  // configure address to send to stadium app
  stadium = new NetAddress("127.0.0.1", 9000);

  words.add(new Word("stadium", random(width), random(100, height-100)));
  words.add(new Word("hiv", random(width), random(100, height-100)));
}


void draw() {

  background(255);

  for (Word word : words) {
    word.draw();
  }
}


void mousePressed() {

  for (Word word : words) {
    // if not us, move on to next
    if (!word.mousePressed(mouseX, mouseY)) continue;
    //ok, we clicked on a word
    play(word.getName());
    word.fadeIn();
    break;
  }
}


void play(String name) {
  // create an osc message
  OscMessage m = new OscMessage("/play");
  // add name of animation to play
  m.add(name);
  // send out message
  osc.send(m, stadium);
}


// Incoming OSC
void oscEvent(OscMessage theOscMessage) {
  /* print the address pattern and the typetag of the received OscMessage */
  print("### received an osc message.");
  print(" addrpattern: "+theOscMessage.addrPattern());
  println(" typetag: "+theOscMessage.typetag());
}

