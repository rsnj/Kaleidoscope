#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Capture.h"
#include "Kaleidoscope.h"

using namespace ci;
using namespace ci::app;
using namespace std;

static const Vec2f captureSize = Vec2f(1024.0f, 768.0f);

class KaleidoscopeApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
    void resize( ResizeEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
  private:
    Capture		mCapture;
    shared_ptr<Kaleidoscope> mKaleidoscope;
    float mRotateSpeed;
};

void KaleidoscopeApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 500, 500 );
}

void KaleidoscopeApp::setup()
{
    vector<Capture::DeviceRef> devices( Capture::getDevices() );
	try {
        //This initializes the camera, change the index of the array to select a different camera.
		mCapture = Capture( captureSize.x, captureSize.y, devices[0] );
		mCapture.start();
	}
	catch( ... ) {
		console() << "Failed to initialize capture" << std::endl;
	}
    
    mRotateSpeed = 0.5f; //Set the default rotational speed
    mKaleidoscope = shared_ptr<Kaleidoscope>(new Kaleidoscope(captureSize));
}

void KaleidoscopeApp::resize( ResizeEvent event )
{
    Vec2i windowSize = getWindowSize();
    mKaleidoscope->resize(windowSize);
}

void KaleidoscopeApp::keyDown( KeyEvent event )
{
    switch (event.getCode())
	{
        case KeyEvent::KEY_ESCAPE:
            quit();
            break;
        case KeyEvent::KEY_f:
            setFullScreen( ! isFullScreen() );
            break;
        case KeyEvent::KEY_UP:
            //Increase the rotational speed.
            mRotateSpeed += 0.25f;
            break;
        case KeyEvent::KEY_DOWN:
            //Decrease the rotational speed.
            mRotateSpeed -= 0.25f;
            break;
    }
}

void KaleidoscopeApp::update()
{
    if( mCapture && mCapture.checkNewFrame() ) {
        gl::Texture captureTexture = gl::Texture( mCapture.getSurface() );
        
        mKaleidoscope->updateTexture(captureTexture);
        mKaleidoscope->rotate(mRotateSpeed);
    }
}

void KaleidoscopeApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    
    mKaleidoscope->draw();
}


CINDER_APP_BASIC( KaleidoscopeApp, RendererGl )
