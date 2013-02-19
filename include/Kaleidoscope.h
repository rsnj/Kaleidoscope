#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "cinder/CinderMath.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Kaleidoscope {
public:
    Kaleidoscope(Vec2f videoSize);
    void resize(Vec2i windowSize);
    void updateTexture(gl::Texture texture);
    void draw();
    void rotate(float angle);
private:
    Vec2f mTriangleVec[3];
    Vec2f mVideoSize;
    gl::Texture mTexture;
    float mScreenSize;
    Vec2f mOffset;
};