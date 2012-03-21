ofxFaceTracker is openFrameworks addon is based on Jason Saragih's FaceTracker library.

[openFrameworks](http://openFrameworks.cc/) is an open source toolkit for creative coding.

FaceTracker is open source for non-commercial use, and is available [from Jason directly](http://web.mac.com/jsaragih/FaceTracker/FaceTracker.html). One you have Jason's source, you'll need to drop it in `libs/` (e.g., `libs/Tracker/Tracker.h`). You'll also need to drop the model data in `bin/data/model/`. If you see the error `Assertion failed: s.is_open()`, that means you forgot to drop the model files in the right folder.

If you would like to prototype an idea involving face tracking, I encourage you to download [FaceOSC](https://github.com/kylemcdonald/ofxFaceTracker/downloads).

## Examples

### Basic

Provides a minimal example of using an `ofxVideoGrabber` with an `ofxFaceTracker`, then extracts and draws the `ofPolyline` representing the  left and right eyes.

### Advanced

Demonstrates how to get the image-space position of the face, and the 3d orientation (collectively, the face "pose") then applies these to the OpenGL context in order to draw an oriented face mesh.

### Extraction

Demonstrates how to use the mean face mesh to draw pose and expression normalized representation of the face currently being tracked.

### Expression

Demonstrates the `ExpressionClassifier`, which can load, save, and classify expressions into pre-trained categories. Provides basic expressions (eyebrows raised, neutral, smiling) as examples.

### Calibrated

Fairly complicated example that demonstrates some advanced/experimental features of ofxCv and ofxFaceTracker for doing AR-style augmentation of the face.

### FaceOSC

Sends as much data as possible from `ofxFaceTracker` via OSC, including various "gestures", position, and orientation.