
class RibbonSection
{
  PVector p1, p2;
  int theC;

  RibbonSection( int x1, int y1, int x2, int y2, int aC) {
    p1=new PVector(x1, y1);
    p2=new PVector(x2, y2);
    theC = aC;
  }
  RibbonSection(PVector aP1,PVector aP2,int aC)
  {
    p1 = aP1;
    p2 = aP2;
    theC = aC;
  }
  void vP1() {
    vertex(p1.x, p1.y);
  }
  void vP2() {
    vertex(p2.x, p2.y);
  }
  void drawFullFrom(RibbonSection aRS)
  {
    fill(iColor[theC]);
    noStroke();
    beginShape();
    aRS.vP1();
    vP1();
    vP2();
    aRS.vP2();
    endShape(CLOSE);
  }
  void shift(PVector aShift)
  {
    p1.add(aShift);
    p2.add(aShift);
  }
  void drawPercentFrom(RibbonSection aRS, int aPercent)
  {
    PVector tP1 = PVector.sub(p1, aRS.p1);
    tP1.mult(aPercent/100.);
    PVector tP2 = PVector.sub(p2, aRS.p2);
    tP2.mult(aPercent/100.);
    PVector tRP1 = PVector.add(aRS.p1, tP1);
    PVector tRP2 = PVector.add(aRS.p2, tP2);    
    fill(iColor[theC]);
    noStroke();
    beginShape();
    aRS.vP1();
    vertex(tRP1.x, tRP1.y);
    vertex(tRP2.x, tRP2.y);
    aRS.vP2();
    endShape(CLOSE);
    
  }
}

