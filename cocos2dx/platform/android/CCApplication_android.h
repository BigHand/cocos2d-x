/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CC_APPLICATION_UPHONE_H__
#define __CC_APPLICATION_UPHONE_H__

#include "CCGeometry.h"
#include "CCDirector.h"

#include <jni.h>

namespace   cocos2d {

class CC_DLL CCApplication
{
public:
    CCApplication();
    virtual ~CCApplication();

    /**
    @brief	rotate main window by device orientation.
    @param  nOritation device orientation enum value.
    @see    ccDeviceOrientation
    */
	ccDeviceOrientation setDeviceOrientation(ccDeviceOrientation eOritation);
	
	/**
    @brief	Implement CCDirector and sense init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching() = 0;

    /**
    @brief	Get status bar rectangle in EGLView window.
    */
    CCRect statusBarFrame();
    
    void Run();

	void setAnimationInterval(double interval);
	
	/**
	@brief	Get current applicaiton instance.
	@return Current application instance pointer.
	*/
	static CCApplication * sharedApplication();
};

}       // end of namespace   cocos2d

#endif	// end of __CC_APPLICATION_UPHONE_H__
