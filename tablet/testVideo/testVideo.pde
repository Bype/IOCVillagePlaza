import apwidgets.*; 

APVideoView videoView; 
APWidgetContainer container; 

void setup()
{
        container = new APWidgetContainer(this); //create a new widget container
        videoView = new APVideoView(0, 0,1280, 720, true); //create a new video view, without media controller
        //videoView = new APVideoView(false); //create a new video view that fills the screen, without a media controller
        //videoView = new APVideoView(); //create a new video view that fills the screen, with a media controller
        videoView.setVideoPath("/sdcard/test.mp4"); //specify the path to the video file
        container.addWidget(videoView); //place the video view in the container
        videoView.start(); //start playing the video
        videoView.setLooping(true); //restart the video when the end of the file is reached

}

void draw()
{
  background(0); //black background

}

void keyPressed() {
}
