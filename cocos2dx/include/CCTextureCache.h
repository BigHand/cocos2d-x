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

#ifndef __CCTEXTURE_CACHE_H__
#define __CCTEXTURE_CACHE_H__

#include <string>
#include "CCObject.h"
#include "CCMutableDictionary.h"

namespace   cocos2d {
class CCTexture2D;
class CCAsyncObject;
class CCLock;
class CCImage;

typedef void (*fpAsyncCallback)(CCTexture2D*, void*);

/** @brief Singleton that handles the loading of textures
* Once the texture is loaded, the next time it will return
* a reference of the previously loaded texture reducing GPU & CPU memory
*/
class CC_DLL CCTextureCache : public CCObject
{
protected:
	CCMutableDictionary<std::string, CCTexture2D*> * m_pTextures;
	CCLock				*m_pDictLock;
	CCLock				*m_pContextLock;

private:
	// @todo void addImageWithAsyncObject(CCAsyncObject* async);

public:

	CCTextureCache();
	virtual ~CCTextureCache();

	char * description(void);

	/** Retruns ths shared instance of the cache */
	static CCTextureCache * sharedTextureCache();

	/** purges the cache. It releases the retained instance.
	@since v0.99.0
	*/
	static void purgeSharedTextureCache();

	/** Returns a Texture2D object given an file image
	* If the file image was not previously loaded, it will create a new CCTexture2D
	*  object and it will return it. It will use the filename as a key.
	* Otherwise it will return a reference of a previosly loaded image.
	* Supported image extensions: .png, .bmp, .tiff, .jpeg, .pvr, .gif
	*/
	CCTexture2D* addImage(const char* fileimage);

	/* Returns a Texture2D object given a file image
	* If the file image was not previously loaded, it will create a new CCTexture2D object and it will return it.
	* Otherwise it will load a texture in a new thread, and when the image is loaded, the callback will be called with the Texture2D as a parameter.
	* The callback will be called from the main thread, so it is safe to create any cocos2d object from the callback.
	* Supported image extensions: .png, .jpg
	* @since v0.8
	*/
	
	// @todo void addImageAsync(const char* filename, CCObject*target, fpAsyncCallback func);

	/* Returns a Texture2D object given an CGImageRef image
	* If the image was not previously loaded, it will create a new CCTexture2D object and it will return it.
	* Otherwise it will return a reference of a previously loaded image
	* The "key" parameter will be used as the "key" for the cache.
	* If "key" is nil, then a new texture will be created each time.
	* @since v0.8
	*/
	// @todo CGImageRef CCTexture2D* addCGImage(CGImageRef image, string &  key);
	/** Returns a Texture2D object given an CCImage image
	* If the image was not previously loaded, it will create a new CCTexture2D object and it will return it.
	* Otherwise it will return a reference of a previously loaded image
	* The "key" parameter will be used as the "key" for the cache.
	* If "key" is nil, then a new texture will be created each time.
	*/
	CCTexture2D* addCCImage(CCImage *image, const char *key);

	/** Returns an already created texture. Returns nil if the texture doesn't exist.
	@since v0.99.5
	*/
	CCTexture2D* textureForKey(const char* key);
	/** Purges the dictionary of loaded textures.
	* Call this method if you receive the "Memory Warning"
	* In the short term: it will free some resources preventing your app from being killed
	* In the medium term: it will allocate more resources
	* In the long term: it will be the same
	*/
	void removeAllTextures();

	/** Removes unused textures
	* Textures that have a retain count of 1 will be deleted
	* It is convinient to call this method after when starting a new Scene
	* @since v0.8
	*/
	void removeUnusedTextures();

	/** Deletes a texture from the cache given a texture
	*/
	void removeTexture(CCTexture2D* texture);

	/** Deletes a texture from the cache given a its key name
	@since v0.99.4
	*/
	void removeTextureForKey(const char *textureKeyName);

#if _POWERVR_SUPPORT_
	/** Returns a Texture2D object given an PVRTC RAW filename
	* If the file image was not previously loaded, it will create a new CCTexture2D
	*  object and it will return it. Otherwise it will return a reference of a previosly loaded image
	*
	* It can only load square images: width == height, and it must be a power of 2 (128,256,512...)
	* bpp can only be 2 or 4. 2 means more compression but lower quality.
	* hasAlpha: whether or not the image contains alpha channel
	*/
	CCTexture2D* addPVRTCImage(const char* fileimage, int bpp, bool hasAlpha, int width);

	/** Returns a Texture2D object given an PVRTC filename
	* If the file image was not previously loaded, it will create a new CCTexture2D
	*  object and it will return it. Otherwise it will return a reference of a previosly loaded image
	*/
	CCTexture2D* addPVRTCImage(const char* fileimage);
#endif
};
}//namespace   cocos2d 

#endif //__CCTEXTURE_CACHE_H__

