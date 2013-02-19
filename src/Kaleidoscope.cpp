#include "Kaleidoscope.h"


Kaleidoscope::Kaleidoscope(Vec2f videoSize)
{
    mVideoSize = videoSize;
    
    float triangleSize;
    if (videoSize.x > videoSize.y) 
        triangleSize = videoSize.y;
    else
        triangleSize = videoSize.x;    
    
    Vec2f center = Vec2f(videoSize.x/2, videoSize.y/2);
    
    mTriangleVec[0].x = center.x / videoSize.x;
    mTriangleVec[0].y = (center.y - (triangleSize/2.0f)) / videoSize.y;
    
    mTriangleVec[1].x = (center.x - (triangleSize/2.0f)) / videoSize.x;
    mTriangleVec[1].y = (center.y + (triangleSize/2.0f)) / videoSize.y;
    
    mTriangleVec[2].x = (center.x + (triangleSize/2.0f)) / videoSize.x;
    mTriangleVec[2].y = (center.y + (triangleSize/2.0f)) / videoSize.y;
}

void Kaleidoscope::updateTexture(gl::Texture texture)
{
    mTexture = texture;
}

void Kaleidoscope::resize(Vec2i windowSize )
{    
   if (windowSize.x > windowSize.y)
    {
        mScreenSize = windowSize.y;
        mOffset = Vec2f((windowSize.x - windowSize.y)/2, 0);
    }
    else
    {
        mScreenSize = windowSize.x;
        mOffset = Vec2f(0, (windowSize.y - windowSize.x)/2);
    }
}

void Kaleidoscope::rotate(float angle) {
    Vec2f center = Vec2f(mVideoSize.x/2, mVideoSize.y/2);
    center = center / mVideoSize;
    
    float radians = toRadians(angle);
    
    for(int i=0; i<3; i++) {
        float x = mTriangleVec[i].x - center.x;
        float y = mTriangleVec[i].y - center.y;
        
        Vec2f temp;
        temp.x = x * cos(radians) - y * sin(radians);
        temp.y = x * sin(radians) + y * cos(radians);
        
        mTriangleVec[i] = temp + center;
    }
}

void Kaleidoscope::draw()
{
    if( mTexture ) { 
        gl::pushModelView();
        mTexture.enableAndBind();
        
        glBegin(GL_TRIANGLES);
        {
            glTexCoord2f(mTriangleVec[0]);
            glVertex2f(mScreenSize*0.5 + mOffset.x, mScreenSize*0.5 + mOffset.y);   
            glTexCoord2f(mTriangleVec[1]);
            glVertex2f(0 + mOffset.x, mScreenSize*0.25 + mOffset.y);   
            glTexCoord2f(mTriangleVec[2]);
            glVertex2f(mScreenSize*0.5 + mOffset.x, 0 + mOffset.y);   
            
            glTexCoord2f(mTriangleVec[0]);
            glVertex2f(mScreenSize*0.5 + mOffset.x, mScreenSize*0.5 + mOffset.y);   
            glTexCoord2f(mTriangleVec[1]);
            glVertex2f(mScreenSize + mOffset.x, mScreenSize*0.25 + mOffset.y);   
            glTexCoord2f(mTriangleVec[2]);
            glVertex2f(mScreenSize*0.5 + mOffset.x, 0 + mOffset.y);  
            
            glTexCoord2f(mTriangleVec[0]);
            glVertex2f(mScreenSize*0.5f + mOffset.x, mScreenSize*0.5f + mOffset.y);   
            glTexCoord2f(mTriangleVec[1]);
            glVertex2f(mScreenSize + mOffset.x, mScreenSize*0.25f + mOffset.y);   
            glTexCoord2f(mTriangleVec[2]);
            glVertex2f(mScreenSize + mOffset.x, mScreenSize*0.75f + mOffset.y);
            
            glTexCoord2f(mTriangleVec[0]);
            glVertex2f(mScreenSize*0.5f + mOffset.x, mScreenSize*0.5f + mOffset.y);   
            glTexCoord2f(mTriangleVec[1]);
            glVertex2f(mScreenSize*0.5f + mOffset.x, mScreenSize + mOffset.y);   
            glTexCoord2f(mTriangleVec[2]);
            glVertex2f(mScreenSize + mOffset.x, mScreenSize*0.75f + mOffset.y);
            
            glTexCoord2f(mTriangleVec[0]);
            glVertex2f(mScreenSize*0.5f + mOffset.x, mScreenSize*0.5f + mOffset.y);   
            glTexCoord2f(mTriangleVec[1]);
            glVertex2f(mScreenSize*0.5f + mOffset.x, mScreenSize + mOffset.y);   
            glTexCoord2f(mTriangleVec[2]);
            glVertex2f(0 + mOffset.x, mScreenSize*0.75f + mOffset.y);
            
            glTexCoord2f(mTriangleVec[0]);
            glVertex2f(mScreenSize*0.5f + mOffset.x, mScreenSize*0.5f + mOffset.y);   
            glTexCoord2f(mTriangleVec[1]);
            glVertex2f(0 + mOffset.x, mScreenSize*0.25f + mOffset.y);   
            glTexCoord2f(mTriangleVec[2]);
            glVertex2f(0 + mOffset.x, mScreenSize*0.75f + mOffset.y); 
            
        } glEnd();
        mTexture.unbind();
        
		gl::popModelView();
	}
    
    

}