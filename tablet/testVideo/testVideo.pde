import apwidgets.*; 

APVideoView videoView; 
APWidgetContainer container; 
PImage test;
boolean isPlaying;
void setup()
{       
  size(1280, 800, P3D);

  container = new APWidgetContainer(this); //create a new widget container
  videoView = new APVideoView(160, 130, 960, 540, true); //create a new video view, without media controller
  videoView.setVideoPath("/sdcard/ioc/movie/test.mp4"); //specify the path to the video file
  container.addWidget(videoView); //place the video view in the container
  videoView.start(); //start playing the video
  //videoView.setLooping(true); //restart the video when the end of the file is reached
  test = loadImage("/sdcard/ioc/home.png");
  isPlaying = true;
}

void draw()
{
  background(255);
  image(test, 0, 0);
  if (isPlaying)
    delay(1000);
}

void mousePressed() {
  if (isPlaying)
  {
    videoView.stopPlayBack();
    container.removeWidget(videoView);
    container.release();
    isPlaying = false;
  }
  else
  {
    container = new APWidgetContainer(this); //create a new widget container
    videoView = new APVideoView(160, 130, 960, 540, true); //create a new video view, without media controller
    videoView.setVideoPath("/sdcard/ioc/movie/test.mp4"); //specify the path to the video file
    container.addWidget(videoView); //place the video view in the container
    videoView.start(); //start playing the video
    isPlaying=true;
  }
}

