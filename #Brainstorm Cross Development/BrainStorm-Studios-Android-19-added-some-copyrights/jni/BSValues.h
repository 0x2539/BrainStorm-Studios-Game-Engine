#ifndef VALUES_H_INCLUDED
#define VALUES_H_INCLUDED

#include <vector>
#include <sstream>
#include "glm/glm.hpp"
#include <Box2D/Box2D.h>
#include "BSOpenGL.h"


#include "BSTexturedPolygonProgram2D.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <png.h>
#include <zip.h>


#define TEXTURE_LOAD_ERROR 0

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_FPS;
extern int SCREEN_BPP;
extern float scaleSize;
#define Hero_size 1 //it has to be even, cuz when i render, i do it by /2
#define scaleSizeInitial -11.3

#define  LOG_TAG    "BS-Activity"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

extern std::string apkLocation;
extern struct android_app* androidOpener;

extern int xTouch, yTouch;

extern long long startTime, endTime;

extern int movedX, movedY, tapX, tapY, tapRadius;
extern double swipeDistance;
extern bool tapped, moved;
extern bool jumpPressed;
extern bool isButtonDown;
extern int buttonSize;
extern int quadrantIndex;
struct BSPoint
{
	int x, y;
};
extern BSPoint lastMovementPosition;
extern BSPoint startPoint, endPoint;
extern bool justJumped, justJumped2;


static long long now_ms(void)
{
    struct timespec res;
    clock_gettime(CLOCK_REALTIME, &res);
    return 1000.0 * res.tv_sec + (double) res.tv_nsec / 1e6;
}

static long long SDL_GetTicks()
{
	//double end = now_ms();
	return now_ms() - startTime;
}


static void checkGlError(const char* op)
{
    for (GLint error = glGetError(); error; error = glGetError())
    {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

static void printGLString(const char *name, GLenum s)
{
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

extern GLuint iboBuffer;

extern zip *APKArchive;;
extern zip_file* file;

extern GLuint locationBSVertexPosition3D, locationBSTextureCoordinate, locationBSModelViewMatrix, locationBSProjectionMatrix;
extern GLuint locationBSTextureColor, locationBSTextureUnit;
extern GLuint BSProgramID;

extern glm::mat4 BSProjectionMatrix;
extern glm::mat4 BSModelViewMatrix;
extern glm::mat4 LookAtMatrix;
extern glm::vec3 m_position;
extern glm::vec3 m_direction;
extern glm::vec3 m_up;

extern float cross_platform_scale;


extern float worldAngle;
extern b2Vec2 worldGravity;
extern int gravityIsChanging, startAngle;

template <typename Cons>
std::string BStoString(const Cons& t)
{
    std::ostringstream os;
    os<<t;
    std::string s(os.str());
    return s;
}

/*
 * loadAPK, getFile and loadTextureFromPNG methods are from the documentation of libpng and libzip. All rights reserved to libpng and libzip.
 */

static void loadAPK (const char* apkPath)//std::string path)
{
	//const char* apkPath = path.c_str();
    LOGI("Loading APK %s", apkPath);
    APKArchive = zip_open(apkPath, 0, NULL);
    if (APKArchive == NULL)
    {
        LOGE("Error loading APK");
        return;
    }

    //Just for debug, print APK contents
    int numFiles = zip_get_num_files(APKArchive);
    for (int i=0; i<numFiles; i++)
    {
        const char* name = zip_get_name(APKArchive, i, 0);
        if (name == NULL)
        {
            //LOGE("Error reading zip file name at index %i : %s", zip_strerror(APKArchive));
            return;
        }
        //LOGI("File %i : %s\n", i, name);
    }
}


static std::string getFile(std::string path)
{
	//loadAPK(apkLocation.c_str());
	if(APKArchive != NULL)
	{
		LOGI("Opening file: %s", path.c_str());
	    // file you wish to read; **any** file from the APK, you're not limited to regular assets
	    std::string fullPath = "assets/" + path;
		const char *file_name = fullPath.c_str();//"assets/file.txt";

	    bool apk_open;

	    int file_index;
	    zip_file *file;
	    struct zip_stat file_stat;

	    file_index = zip_name_locate(APKArchive, file_name, 0);

	    if(file_index == -1)
	    {
	        //zip_close(APKArchive);
	        apk_open = false;

	        LOGE("%s %s", "eroare 1 la file open: ", path.c_str());

	        return "";
	    }

	    file = zip_fopen_index(APKArchive, file_index, 0);
	    if(file == NULL)
	    {
	        //zip_close(APKArchive);
	        apk_open = false;
	        LOGE("%s %s", "eroare 2 la file open: ", path.c_str());

	        return "";
	    }

	    // get the file stats
	    zip_stat_init(&file_stat);
	    zip_stat(APKArchive, file_name, 0, &file_stat);
	    char *buffer = new char[file_stat.size];

	    // read the file
	    int result = zip_fread(file, buffer, file_stat.size);
	    if(result == -1)
	    {
	        delete[] buffer;
	        zip_fclose(file);

	        //zip_close(APKArchive);
	        apk_open = false;

	        LOGE("%s %s", "eroare3 la file open: ", path.c_str());
	        return "";
	    }
	    ///char job2[] = "asdasd";
	    ///std::string job = BStoString(buffer);
	    ///LOGE("%s", job.c_str());

	    std::string myString = BStoString(buffer);

	    // delete the buffer, close the file and apk
	    delete[] buffer;
	    zip_fclose(file);

	    //zip_close(APKArchive);
	    apk_open = false;
	    return myString;
	}
    LOGE("%s %s", "eroare 4 la file open: ", path.c_str());
	return "";
}

static std::string writeFile(std::string path, std::string input)
{
	//loadAPK(apkLocation.c_str());
	if(APKArchive != NULL)
	{
		LOGI("Writing file: %s", path.c_str());
	    // file you wish to read; **any** file from the APK, you're not limited to regular assets
	    std::string fullPath = "assets/" + path;
		const char *file_name = fullPath.c_str();//"assets/file.txt";

	    bool apk_open;

	    int file_index;
	    zip_file *file;
	    struct zip_stat file_stat;

//	    file_index = zip_name_locate(APKArchive, file_name, 0);
//
//	    if(file_index == -1)
//	    {
//	        //zip_close(APKArchive);
//	        apk_open = false;
//
//	        LOGE("%s %s", "eroare 1 la file open: ", path.c_str());
//
//	        return "";
//	    }

	    //file = zip_add(APKArchive, input);
	    file = zip_fopen_index(APKArchive, file_index, 0);
	    if(file == NULL)
	    {
	        //zip_close(APKArchive);
	        apk_open = false;
	        LOGE("%s %s", "eroare 2 la file open: ", path.c_str());

	        return "";
	    }

	    // get the file stats
	    zip_stat_init(&file_stat);
	    zip_stat(APKArchive, file_name, 0, &file_stat);
	    char *buffer = new char[file_stat.size];

	    // read the file
	    int result = zip_fread(file, buffer, file_stat.size);
	    if(result == -1)
	    {
	        delete[] buffer;
	        zip_fclose(file);

	        //zip_close(APKArchive);
	        apk_open = false;

	        LOGE("%s %s", "eroare3 la file open: ", path.c_str());
	        return "";
	    }
	    ///char job2[] = "asdasd";
	    ///std::string job = BStoString(buffer);
	    ///LOGE("%s", job.c_str());

	    std::string myString = BStoString(buffer);

	    // delete the buffer, close the file and apk
	    delete[] buffer;
	    zip_fclose(file);

	    //zip_close(APKArchive);
	    apk_open = false;
	    return myString;
	}
    LOGE("%s %s", "eroare 4 la file open: ", path.c_str());
	return "";
}

/*static std::string getFile(std::string path)
{
	AAsset *fileAsset= AAssetManager_open(androidOpener->activity->assetManager, path.c_str(), AASSET_MODE_BUFFER);
	size_t length = AAsset_getLength(fileAsset);

	//LOGI("file size: %d\n", length);
	char* buffer = (char*) malloc(length + 1);

	AAsset_read(fileAsset, buffer, length);

	// fix the string to be zero-terminated
	buffer[length] = 0;

	//LOGI("file:\n%s", buffer);
	std::string file = BStoString(buffer);
	AAsset_close(fileAsset);
	free(buffer);
	LOGI("Loaded the file: %s", path.c_str());
	return file;
}*/

static void png_zip_read(png_structp png_ptr, png_bytep data, png_size_t length)
{
  zip_fread(file, data, length);
}

static GLuint loadTextureFromPNG(std::string path, int &width, int &height)
{
	const char* filename = path.c_str();
	file = zip_fopen(APKArchive, filename, 0);
	if (!file)
	{
		LOGE("Error opening %s from APK", filename);
		return TEXTURE_LOAD_ERROR;
	}

	//header for testing if it is a png
	png_byte header[8];

	//read the header
	zip_fread(file, header, 8);

	//test if png
	int is_png = !png_sig_cmp(header, 0, 8);
	if (!is_png)
	{
		zip_fclose(file);
		LOGE("Not a png file : %s", filename);
		return TEXTURE_LOAD_ERROR;
	}

	//create png struct
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
	{
		zip_fclose(file);
		LOGE("Unable to create png struct : %s", filename);
		return (TEXTURE_LOAD_ERROR);
	}

	//create png info struct
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
		LOGE("Unable to create png info : %s", filename);
		zip_fclose(file);
		return (TEXTURE_LOAD_ERROR);
	}

	//create png info struct
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
		LOGE("Unable to create png end info : %s", filename);
		zip_fclose(file);
		return (TEXTURE_LOAD_ERROR);
	}

	//png error stuff, not sure libpng man suggests this.
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		zip_fclose(file);
		LOGE("Error during setjmp : %s", filename);
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return (TEXTURE_LOAD_ERROR);
	}

	//init png reading
	//png_init_io(png_ptr, fp);
	png_set_read_fn(png_ptr, NULL, png_zip_read);

	//let libpng know you already read the first 8 bytes
	png_set_sig_bytes(png_ptr, 8);

	// read all the info up to the image data
	png_read_info(png_ptr, info_ptr);

	//variables to pass to get info
	int bit_depth, color_type;
	png_uint_32 twidth, theight;

	// get info about png
	png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type, NULL, NULL, NULL);

	//update width and height based on png info
	width = twidth;
	height = theight;

    GLuint format;
    switch(color_type)
    {
    case PNG_COLOR_TYPE_RGB:
        format = GL_RGB;
        break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
        format = GL_RGBA;
        break;
    default:
        LOGE("%s: Unknown libpng color type %d.\n", filename, color_type);
    	//fprintf(stderr, "%s: Unknown libpng color type %d.\n", filename, color_type);
        //return 0;
    }
    //bit_depth = 8;
    //format = GL_RGBA;

	// Update the png info struct.
	png_read_update_info(png_ptr, info_ptr);

	// Row size in bytes.
	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // glTexImage2d requires rows to be 4-byte aligned
    //rowbytes += 3 - ((rowbytes-1) % 4);

	// Allocate the image_data as a big block, to be given to opengl
	png_byte *image_data = new png_byte[rowbytes * height];// * sizeof(png_byte)+15];
	if (!image_data)
	{
		//clean up memory and close stuff
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		LOGE("Unable to allocate image_data while loading %s ", filename);
		zip_fclose(file);
		return TEXTURE_LOAD_ERROR;
	}

	//row_pointers is for pointing to image_data for reading the png with libpng
	png_bytep *row_pointers = new png_bytep[height];// * sizeof(png_byte *)];
	if (!row_pointers)
	{
		//clean up memory and close stuff
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		delete[] image_data;
		LOGE("Unable to allocate row_pointer while loading %s ", filename);
		zip_fclose(file);
		return TEXTURE_LOAD_ERROR;
	}

	// set the individual row_pointers to point at the correct offsets of image_data
	for (int i = 0; i < height; ++i)
	{
		row_pointers[height - 1 - i] = image_data + i * rowbytes;
	}

	//read the png into image_data through row_pointers
	png_read_image(png_ptr, row_pointers);

	//Now generate the OpenGL texture object
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D,0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid*) image_data);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//clean up memory and close stuff
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
	delete[] image_data;
	delete[] row_pointers;
	zip_fclose(file);
	LOGI("Loaded image: %s", filename);
	return texture;
}


static void loadTexture(std::string path, GLuint &texture)
{
	int wid, hei;
	//path = "texture.png";
	path = "assets/" + path;
	LOGI("Began loading the image: %s", path.c_str());
	texture = loadTextureFromPNG(path.c_str(), wid, hei);
}

/*
AAsset* pngAsset_ = 0;
AAssetManager* pngAassetManager_ = 0;

void png_asset_read(png_structp png, png_bytep data, png_size_t size) {
    //AAsset_seek(pngAsset_, 0, 0);
    AAsset_read(pngAsset_, data, size);
    int numBytesRemaining = AAsset_getRemainingLength(pngAsset_);
    LOGI("Read size: %d, remaining: %d", size, numBytesRemaining);
}

Image* loadPngFile(AAssetManager* assetManager) {
    pngAassetManager_ = assetManager;

    LOGI("Trying to load image...");
    int HEADER_SIZE = 8;
    string filename = "skybox.png";
    pngAsset_ = AAssetManager_open(pngAassetManager_, filename.c_str(),
            AASSET_MODE_UNKNOWN);
    if (pngAsset_ == 0) {
        LOGW("Asset \"%s\" not found.", filename.c_str());
        return 0;
    }

    off_t bufferSize = AAsset_getLength(pngAsset_);
    png_byte* buffer = new png_byte[HEADER_SIZE];

    int numBytesRead = AAsset_read(pngAsset_, buffer, HEADER_SIZE);
    int numBytesRemaining = AAsset_getRemainingLength(pngAsset_);

    int is_png = !png_sig_cmp(buffer, 0, 8);
    if (!is_png) {
        LOGE("File %s format is not PNG.", filename.c_str());
        return 0;
    }
    LOGI("Size of the file: %d, bytes read: %d, bytes remain: %d",
            bufferSize, numBytesRead, numBytesRemaining);

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
            NULL, NULL);
    if (!png_ptr) {
        LOGE("Unable to create PNG structure: %s", filename.c_str());
        return 0;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
        LOGE("Unable to create png info : %s", filename.c_str());
        return 0;
    }

    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        LOGE("Unable to create png end info : %s", filename.c_str());
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        LOGE("Error during setjmp : %s", filename.c_str());
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return 0;
    }
    png_set_read_fn(png_ptr, NULL, png_asset_read);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    int bit_depth, color_type;
    png_uint_32 twidth, theight;
    png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
            NULL, NULL, NULL);
    LOGI("Width: %d, height: %d.", twidth, theight);

    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes.
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    LOGI("Row size: %d bytes.", rowbytes);

    // Allocate the image_data as a big block, to be given to opengl
    png_byte *image_data = new png_byte[rowbytes * theight];
    if (!image_data) {
        //clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        LOGE(
                "Unable to allocate image_data while loading %s ", filename.c_str());
    }

    //row_pointers is for pointing to image_data for reading the png with libpng
    png_bytep *row_pointers = new png_bytep[theight];
    if (!row_pointers) {
        //clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        delete[] image_data;
        LOGE(
                "Unable to allocate row_pointer while loading %s ", filename.c_str());
    }
    // set the individual row_pointers to point at the correct offsets of image_data
    for (int i = 0; i < theight; ++i)
        row_pointers[theight - 1 - i] = image_data + i * rowbytes;

    //read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    for (int i = 0; i < 10; i ++) {
        LOGI("Pixel %d: %f %f %f %f",i, image_data[i * 4], image_data[i * 4 + 1],
                image_data[i * 4 + 2], image_data[i * 4 + 3]);
    }

    //Now generate the OpenGL texture object
    Image* image = new Image((unsigned char*) image_data, twidth, theight,
            twidth * theight * 4, 0);

    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] row_pointers;

    AAsset_close(pngAsset_);

    return image;
}
 */

/*static std::string getFile(std::string path)
{
	//loadAPK(apkLocation.c_str());
	if(APKArchive != NULL)
	{
		LOGI("Opening file: %s", path.c_str());
	    // file you wish to read; **any** file from the APK, you're not limited to regular assets
	    std::string fullPath = "assets/" + path;
		const char *file_name = fullPath.c_str();//"assets/file.txt";

	    bool apk_open;

	    int file_index;
	    zip_file *file;
	    struct zip_stat file_stat;

	    file_index = zip_name_locate(APKArchive, file_name, 0);

	    if(file_index == -1)
	    {
	        //zip_close(APKArchive);
	        apk_open = false;

	        LOGE("%s %s", "eroare 1 la file open: ", path.c_str());

	        return "";
	    }

	    file = zip_fopen_index(APKArchive, file_index, 0);
	    if(file == NULL)
	    {
	        //zip_close(APKArchive);
	        apk_open = false;
	        LOGE("%s %s", "eroare 2 la file open: ", path.c_str());

	        return "";
	    }

	    // get the file stats
	    zip_stat_init(&file_stat);
	    zip_stat(APKArchive, file_name, 0, &file_stat);
	    char *buffer = new char[file_stat.size];

	    // read the file
	    int result = zip_fread(file, buffer, file_stat.size);
	    if(result == -1)
	    {
	        delete[] buffer;
	        zip_fclose(file);

	        //zip_close(APKArchive);
	        apk_open = false;

	        LOGE("%s %s", "eroare3 la file open: ", path.c_str());
	        return "";
	    }
	    ///char job2[] = "asdasd";
	    ///std::string job = BStoString(buffer);
	    ///LOGE("%s", job.c_str());

	    std::string myString = BStoString(buffer);

	    // delete the buffer, close the file and apk
	    delete[] buffer;
	    zip_fclose(file);

	    //zip_close(APKArchive);
	    apk_open = false;
	    return myString;
	}
    LOGE("%s %s", "eroare 4 la file open: ", path.c_str());
	return "";
}*/





struct BSTexCoord
{
    GLfloat s;
    GLfloat t;
};

struct BSRectangle
{
    GLfloat x;
    GLfloat y;
    GLfloat w;
    GLfloat h;
};

struct BSColorRGBA
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;

    void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
    {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }

    void setColorsTo1()
    {
        r = 1;
        g = 1;
        b = 1;
        a = 1;
    }
};

struct BSVertexPos2D
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct BSTexturedVertex2D
{
    BSVertexPos2D position;
	BSTexCoord texCoord;
};

struct BSBody
{
	float xCord = 0, yCord = 0, zCord = scaleSizeInitial, width = 0, height = 0, depth = 0, value1 = 0, value2 = 0,
        xInit = 0, yInit = 0, xAngle = 0, yAngle = 0, zAngle = 0;
	BSColorRGBA color;
	int index;
    BSTexturedVertex2D data[4];
    GLuint texture = 0, vbo = 0, ibo = 0;//, vao = 0;

    void draw()
    {
    	//LOGI("%s", "hello51");
        checkGlError("glDraw1");
        glBindTexture(GL_TEXTURE_2D, texture);

        checkGlError("glDraw2");
    	//LOGI("%s", "hello52");
        BSModelViewMatrix = glm::translate( xCord * cross_platform_scale, yCord * cross_platform_scale, zCord ) * LookAtMatrix;

        //inversez ordinea matricelor daca vreau sa se invarta in jurul originii scenei
        if(xAngle || yAngle || zAngle)
        {
            if(xAngle)
            {
                BSModelViewMatrix = BSModelViewMatrix * glm::rotate( xAngle, 0.0f, 0.0f, 1.0f );
            }
            if(yAngle)
            {
                BSModelViewMatrix = BSModelViewMatrix * glm::rotate( yAngle, 0.0f, 1.0f, 0.0f );
            }
            if(zAngle)
            {
                BSModelViewMatrix = BSModelViewMatrix * glm::rotate( zAngle, 1.0f, 0.0f, 0.0f );
            }
        }

        checkGlError("glDraw3");
    	//LOGI("%s", "hello53");
        BSModelViewMatrix = BSModelViewMatrix * glm::scale( width * cross_platform_scale, height * cross_platform_scale, 0.0f );


        checkGlError("glDraw4");
    	//LOGI("%s", "hello54");
        glUniformMatrix4fv(	locationBSModelViewMatrix, 1, GL_FALSE, glm::value_ptr( BSModelViewMatrix ) );

        checkGlError("glDraw5");
    	//LOGI("%s", "hello55");
        glUniform4f( locationBSTextureColor, color.r, color.g, color.b, color.a );

        checkGlError("glDraw6");
    	//LOGI("%s", "hello56");

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBuffer);

        checkGlError("glDraw7");
    	//LOGI("%s", "hello57");

        glEnableVertexAttribArray(locationBSVertexPosition3D);
        glVertexAttribPointer( locationBSVertexPosition3D, 3, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*)offsetof( BSTexturedVertex2D, position ) );

        checkGlError("glDraw8");
    	//LOGI("%s", "hello58");
        glEnableVertexAttribArray(locationBSTextureCoordinate);
        glVertexAttribPointer( locationBSTextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*)offsetof( BSTexturedVertex2D, texCoord ) );

        checkGlError("glDraw9");
    	//LOGI("%s", "hello59");

        checkGlError("glDraw10");
        glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, NULL);
        checkGlError("glDraw11");
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        checkGlError("glDraw12");
    	//LOGI("%s", "hello60");
        /*
        glBindTexture(GL_TEXTURE_2D, texture);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);

        BSModelViewMatrix = glm::translate( xCord, yCord, zCord ) * LookAtMatrix;

//        if(worldAngle != -xAngle)
        {
            //BSModelViewMatrix = glm::rotate( worldAngle, 0.0f, 0.0f, 1.0f ) * BSModelViewMatrix;
        }
        //inversez ordinea matricelor daca vreau sa se invarta in jurul originii scenei
        if(xAngle || yAngle || zAngle)
        {
            if(xAngle)
            {
                //BSModelViewMatrix = BSModelViewMatrix * glm::rotate( xAngle, 0.0f, 0.0f, 1.0f );
            }
            if(yAngle)
            {
                //BSModelViewMatrix = BSModelViewMatrix * glm::rotate( yAngle, 0.0f, 1.0f, 0.0f );
            }
            if(zAngle)
            {
                //BSModelViewMatrix = BSModelViewMatrix * glm::rotate( zAngle, 1.0f, 0.0f, 0.0f );
            }
        }

        BSModelViewMatrix = BSModelViewMatrix * glm::scale( width, height, 0.0f );

        glUniformMatrix4fv(	locationBSModelViewMatrix, 1, GL_FALSE, glm::value_ptr( BSModelViewMatrix ) );
        glUniform4f( locationBSTextureColor, color.r, color.g, color.b, color.a );

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBuffer);

        glEnableVertexAttribArray(locationBSVertexPosition3D);
        glVertexAttribPointer( locationBSVertexPosition3D, 3, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*)offsetof( BSTexturedVertex2D, position ) );

        glEnableVertexAttribArray(locationBSTextureCoordinate);
        glVertexAttribPointer( locationBSTextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*)offsetof( BSTexturedVertex2D, texCoord ) );

        glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, NULL);
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        glBindTexture(GL_TEXTURE_2D, 0);*/
    }

    void draw(GLuint differentTexture)
    {
        glBindTexture(GL_TEXTURE_2D, differentTexture);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);

        BSModelViewMatrix = glm::translate( xCord * cross_platform_scale, yCord * cross_platform_scale, zCord ) * LookAtMatrix;
        BSModelViewMatrix = glm::rotate( worldAngle, 0.0f, 0.0f, 1.0f ) * BSModelViewMatrix;

        //inversez ordinea matricelor daca vreau sa se invarta in jurul originii scenei
        if(xAngle || yAngle || zAngle)
        {
            if(xAngle)
            {
                BSModelViewMatrix = BSModelViewMatrix * glm::rotate( xAngle, 0.0f, 0.0f, 1.0f );
            }
            if(yAngle)
            {
                BSModelViewMatrix = BSModelViewMatrix * glm::rotate( yAngle, 0.0f, 1.0f, 0.0f );
            }
            if(zAngle)
            {
                BSModelViewMatrix = BSModelViewMatrix * glm::rotate( zAngle, 1.0f, 0.0f, 0.0f );
            }
        }

        BSModelViewMatrix = BSModelViewMatrix * glm::scale( width * cross_platform_scale, height * cross_platform_scale, 0.0f );

        glUniformMatrix4fv(	locationBSModelViewMatrix, 1, GL_FALSE, glm::value_ptr( BSModelViewMatrix ) );
        glUniform4f( locationBSTextureColor, color.r, color.g, color.b, color.a );

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBuffer);

        glEnableVertexAttribArray(locationBSVertexPosition3D);
        glVertexAttribPointer( locationBSVertexPosition3D, 3, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*)offsetof( BSTexturedVertex2D, position ) );

        glEnableVertexAttribArray(locationBSTextureCoordinate);
        glVertexAttribPointer( locationBSTextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*)offsetof( BSTexturedVertex2D, texCoord ) );

        glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, NULL);
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void draw(GLuint differentTexture, GLuint differentVao)
    {
        glBindTexture(GL_TEXTURE_2D, differentTexture);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR_MIPMAP_LINEAR);

        BSModelViewMatrix = glm::translate( xCord * cross_platform_scale, yCord * cross_platform_scale, zCord ) * LookAtMatrix;
        BSModelViewMatrix = glm::rotate( worldAngle, 0.0f, 0.0f, 1.0f ) * BSModelViewMatrix;

        //inversez ordinea matricelor daca vreau sa se invarta in jurul originii scenei
        if(xAngle || yAngle || zAngle)
        {
            if(xAngle)
            {
                BSModelViewMatrix = BSModelViewMatrix * glm::rotate( xAngle, 0.0f, 0.0f, 1.0f );
            }
            if(yAngle)
            {
                BSModelViewMatrix = BSModelViewMatrix * glm::rotate( yAngle, 0.0f, 1.0f, 0.0f );
            }
            if(zAngle)
            {
                BSModelViewMatrix = BSModelViewMatrix * glm::rotate( zAngle, 1.0f, 0.0f, 0.0f );
            }
        }

        BSModelViewMatrix = BSModelViewMatrix * glm::scale( width * cross_platform_scale, height * cross_platform_scale, 0.0f );

        glUniformMatrix4fv(	locationBSModelViewMatrix, 1, GL_FALSE, glm::value_ptr( BSModelViewMatrix ) );
        glUniform4f( locationBSTextureColor, color.r, color.g, color.b, color.a );

        glBindBuffer(GL_ARRAY_BUFFER, differentVao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBuffer);

        glEnableVertexAttribArray(locationBSVertexPosition3D);
        glVertexAttribPointer( locationBSVertexPosition3D, 3, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*)offsetof( BSTexturedVertex2D, position ) );

        glEnableVertexAttribArray(locationBSTextureCoordinate);
        glVertexAttribPointer( locationBSTextureCoordinate, 2, GL_FLOAT, GL_FALSE, sizeof(BSTexturedVertex2D), (GLvoid*)offsetof( BSTexturedVertex2D, texCoord ) );

        glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_SHORT, NULL);
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

struct BSVertices3D
{
    float x, y, z;
};

///UserData-ul din obstacole
struct USERDATA
{
    std::string name, width, height;
    int timeUntilDestroy;
    long long BumTime;
    bool canKillHero, isToNextLevel;
    int isDustAble, isDust;
};

///Butoanele
struct BSButtonStructure : BSBody
{
	int indexOfButton;
    float NextMenuIndex;
    BSTexturedVertex2D dataOfButtons[2][4]; //[0]->butonul cand nu este selectat, [1]->butonul este selectat
    GLuint vbo[2] = {0, 0}, ibo[2] = {0, 0};//, vaoOfButtons[2] = {0, 0};
    GLuint textureOfButtons[2];

    bool isSelected;

    std::string name;
};

struct BackButton
{
	float x, y, w, h;
	GLuint textureUp, textureDown, vbo, ibo;///, vao;
	BSTexturedVertex2D data[4];
	bool isDown, canClick;
};
extern BackButton *backBtn, *btnDarkLevels, *btnTimeControl, *btnPowerUp1, *btnPowerUp2, *btnPowerUp3;


struct BSMenuStructure
{
	int indexOfMenu;
    //BSButtonStructure *Buttons[40];

    std::vector<BSButtonStructure*> listOfButtons;

    int MenuIndex, numberOfButtons;

    GLuint textureOfMenu;

    ///int MenuState, NumberOfButtons;
    ///BSButtonStructure* thebuttons[];
};

///Backgroundurile
struct BSTheBackgrounds : BSBody
{
    float xInit, yInit;
};extern BSTheBackgrounds *backgroundSky, *backgroundMountain, *backgroundBush, *backgroundField, *backgroundHighField;

///Patratul cel mic cu care vad unde pun obiectele
struct BSTheSquare : BSBody
{
};

///Cercul cel mic cu care vad unde pun obiectele
struct BSTheCircle : BSBody
{
};

///Particulele
struct BSTheParticles : BSBody
{
    b2Body *theBodyOfParticle;
    float speedX, speedY, startX, startY;
    long long BumTime;//retine momentul in care e distrusa
    int timeUntilBum;//retine cat de mult sta pana face BUM
    BSColorRGBA initialcolor;
    bool isDestroyed;
};

struct BSBodyScript : BSBody
{
    float xPower, yPower, xLength, yLength, xInitial, yInitial;
};

///Structura pentru obiectele din Box2D
struct BSTheSquareBodies : BSBody
{
    b2Body *theBody;
    std::string nameOfTexture;
    bool heroIsDead, heroWasDead, heroWasToNextLevel, heroIsBerserk1, heroIsBerserk2, heroIsBerserk3,
            ObstacleCanKillHero, ObstacleFinishesLevel, heroStopped, heroBegan, heroIsMoving;

    BSBodyScript *script;

    float animationIndexPlayerStand,
			animationIndexPlayerMoveRight, animationIndexPlayerMoveLeft,
			animationIndexPlayerMoveUpRight, animationIndexPlayerMoveUpLeft,
			animationIndexPlayerMoveDownRight, animationIndexPlayerMoveDownLeft,
			animationIndexPlayerDied, animationIndexPlayerWallLeft, animationIndexPlayerWallRight,
			animationIndexPlayerDieLeft, animationIndexPlayerDieRight,
			animationIndexCurrentAnimation, animationIndexCurrentAnimationBerserk, animationIndexIntermediary,
			animationIndexPlayerTeleportedIn, animationIndexPlayerTeleportedOut,
			animationIndexPlayerAura1, animationIndexPlayerAura2, animationIndexPlayerAura3, animationIndexPlayerAuraElectricity,
			animationIndexPlayerWormHole;

    bool IsAtStepOfAnimation1, IsAtStepOfAnimation2, IsAtStepOfAnimation3;
    bool IsAtStepOfAnimation21, IsAtStepOfAnimation22, IsAtStepOfAnimation23;
    bool IsAtStepOfAnimation31, IsAtStepOfAnimation32, IsAtStepOfAnimation33;
    bool IsAtStepOfAnimation41, IsAtStepOfAnimation42, IsAtStepOfAnimation43;
    //bool playedAnimationOnce1, playedAnimationOnce2, playedAnimationOnce3;
}; extern int heroFacesLeftOrRight, timeWhenTeleported;

///Structura pentru obiectele din Box2D
struct BSTheRoundBodies : BSBody
{
    b2Body *theBody;
    BSBodyScript *script;
    std::string nameOfTexture;
    bool heroIsDead, heroWasDead, heroIsBerserk, ObstacleCanKillHero, ObstacleFinishesLevel;
    bool isRotating;
};

///Structura pentru mesajele jucatorului
struct BSTheMessages : BSBody
{
    float widthOfSign, heightOfSign, widthOfMessage, heightOfMessage;
    BSColorRGBA colorOfSign, colorOfMessage;
    GLuint textureOfSign, textureOfMessage,///, vaoBufferOfSign, vaoBufferOfMessage,
			vboBufferOfSign, vboBufferOfMessage, iboBufferOfSign, iboBufferOfMessage;
    std::string nameOfTextureSign, nameOfTextureMessage;
    BSTexturedVertex2D dataOfSign[4], dataOfMessage[4];

    bool isShownTheMessage;
};
extern std::vector<BSTheMessages*>listOfMessages; //BSTheMessages *theMessages[100];
extern int nrOfMessageSign;

struct BSCoins : BSBody
{
	float sinValue, sinValue2, xInit, yInit;
	int value;
	bool available, deleteIt, alreadyHadIt;
}; 	extern std::vector<BSCoins*> listOfCoins;
    extern BSTexturedVertex2D coinData[4];
    extern GLuint coinTexture, coinVbo, coinIbo;//, coinVao;
    extern bool canAddCoins;
    extern float theCoinX, theCoinY;

struct BSFans : BSBody
{
	float powerX, powerY, lenthOfPower;
	int nrOfParticles;
	float xMax, xMin, yMax, yMin;
	std::vector<BSBody*> particles;
}; 	extern std::vector<BSFans*> listOfFans;
    extern BSTexturedVertex2D fanData[4];
    extern GLuint fanTexture, fanVbo, fanIbo;///, fanVao;
    extern bool canAddFans;

struct BSSnowFlakes : BSBody
{
	float xPower, yPower, xInit, yInit, sinValue;

};extern std::vector<BSSnowFlakes*> listOfSnowFlakes;
extern long long timeSinceMovedMouse, timeSinceMovedLittleCircle;


struct BSCloudyParticles : BSBody
{
	float xPower, yPower, xInit, yInit, sinValue;
};extern std::vector<BSCloudyParticles*> listOfCloudyParticles;
extern GLuint clouds[6];


struct BSWormHole : BSBody
{
    int indexOfWorm, connectionIndex;
}; extern std::vector<BSWormHole*> listOfWormHoles;
extern BSWormHole *lastWorm;


struct BSWorldOfGooMouse : BSBody
{
};extern std::vector<BSWorldOfGooMouse*> listOfMouseCircles;


///Structura pentru o scena, de ex: se innegreste ecranul cand moare
struct BSSceneStructure : BSBody
{
    float SinValueColorOfTheScene, CosValueColorOfTheScene;
    int colorGoesUpOrDown;
};

///Structura pentru animatie
struct BSAnimation : BSBody
{
    long timeUntilNext = 0;//timpul cat dureaza animatia
};

struct BSAnimList
{
    int nr1 = 0, nr2 = 0, nr3 = 0;
    bool loop1 = false, loop2 = false, loop3 = false;
    std::vector<BSAnimation*>animation;
};
extern std::vector<BSAnimList*>listOfLoadedAnimations;

struct BSNewList
{
	int firstNR, secondNR, thirdNR;
	std::vector<BSAnimation*> listForAnimations1, listForAnimations2, listForAnimations3;

    int animationIndex;
    bool isContinuing, isOnLoopAnimation1, isOnLoopAnimation2, isOnLoopAnimation3;

    BSAnimation* theCurrentAnimation;
};
extern std::vector<BSNewList*>listOfAnimations;
extern int nrOfListOfAnimations;

struct BsActiveAnimations
{
    float xCord = 0, yCord = 0, zCord = scaleSizeInitial, width = 0, height = 0, depth = 0;

    long timeToShow = 0;//timpul in care trece la urmatoarea
    bool canPlayIt = false, finish = false;
    int indexOfTexture = 0, indexOfAnimation = 0;

    void setPlayableStatus(bool status)
    {
        canPlayIt = status;
        indexOfTexture = 0;
        finish = false;

        ///set the first texture of the animation to start
        timeToShow = listOfLoadedAnimations[indexOfAnimation]->animation[0]->timeUntilNext + (endTime-startTime);///SDL_GetTicks();
    }
};
extern std::vector<BsActiveAnimations*>listOfActiveAnimations;


///Structura doar pentru texturi patrate
struct BSTextureSquare : BSBody
{
    std::string nameOfTexture;
}; extern BSTextureSquare *mouseTexture;

///Structura doar pentru texturi rotunde
struct BSTextureRound : BSBody
{
    std::string nameOfTexture;
};


///Structura Level Choose-rului
struct ChapterLevelsStructure : BSBody
{
    bool isFinished, isCurrent, indexOfLevel, canPlayIt;

    GLuint textureOfLevel, textureOfConnectionLeftRight, textureOfConnectionUpDown, textureOfFinishedLevel,
           ///vaoBufferOfLevel, vaoBufferOfConnectionLeftRight, vaoBufferOfConnectionUpDown, vaoBufferOfFinishedLevel,
           vboBufferOfLevel, vboBufferOfConnectionLeftRight, vboBufferOfConnectionUpDown, vboBufferOfFinishedLevel,
           iboBufferOfLevel, iboBufferOfConnectionLeftRight, iboBufferOfConnectionUpDown, iboBufferOfFinishedLevel;

    GLuint textureOfConnectionLeftRightChapter, textureOfConnectionUpDownChapter, textureOfFinishedLevelChapter,
           ///vaoBufferOfConnectionLeftRightChapter, vaoBufferOfConnectionUpDownChapter, vaoBufferOfFinishedLevelChapter,
           vboBufferOfConnectionLeftRightChapter, vboBufferOfConnectionUpDownChapter, vboBufferOfFinishedLevelChapter,
           iboBufferOfConnectionLeftRightChapter, iboBufferOfConnectionUpDownChapter, iboBufferOfFinishedLevelChapter;

    BSTexturedVertex2D dataOfLevel[4], dataOfConnectionLeftRight[4], dataOfConnectionUpDown[4], dataOfFinishedLevel[4];
    BSTexturedVertex2D dataOfConnectionLeftRightChapter[4], dataOfConnectionUpDownChapter[4], dataOfFinishedLevelChapter[4];

	float widthConnectionLeftRightLevel, widthConnectionUpDownLevel, widthConnectionLeftRightChapter, widthConnectionUpDownChapter,
		heightConnectionLeftRightLevel, heightConnectionUpDownLevel, heightConnectionLeftRightChapter, heightConnectionUpDownChapter,
		widthFinishedLevel, heightFinishedLevel, widthFinishedChapter, heightFinishedChapter;
	std::string textOnLevel;
};
///Structura Chapterelor
struct ChapterStructure : BSBody
{
	ChapterLevelsStructure *levelFromChapter[100];
	bool isFinishedChapter, isAvailableChapter;
	int nrOfLevels;
	std::string nameOfTheChapter;

	std::string textOnChapter;

};


struct ListaDeCaractere
{
	std::string theCharArray1D;
	std::vector<std::string> theCharArray2D;
	std::vector<std::string> theCharArray2DAttributes;
};



struct LevelChooserPlayerTexture : BSBody
{
    int indexOfLevelThatItIsOn, indexOfChapterThatItIsOn;
    int isMovingLeftRight, isMovingUpDown;
    bool canMove, justFinished;
};



struct BSAnimationOfObject : BSBody
{
    std::string nameOfTheTexture;
    float timeUntilNext;//timpul cat dureaza animatia
    float timeToShow;//timpul in care trece la urmatoarea
    int nrOfAnimations;
};

struct BSAnimatedObject : BSBody
{
    std::string nameOfTexture;
    bool isSquare;
};





///Structura pentru obiectele din Box2D
struct BSTheFontLetters : BSBody
{
    float xCordInImage, yCordInImage, xCordOnScreen, yCordOnScreen,
		widthOfLetterInImage, heightOfLetterInImage, widthOfLetterOnScreen, heightOfLetterOnScreen;

	double xRatio, yRatio;

    char nameOfLetterCapsLockOff, nameOfLetterCapsLockOn;
};
extern BSTheFontLetters *letters[256];
extern int NrOfTotalLetters;

extern std::vector<BSSnowFlakes*>listOfRainDrops;
extern bool useSnow, useRain, useAssassinsCreed;

extern bool existsGamePad, useKeyboardOrGamePad;

extern char initialSquareTexturePath[100], initialRoundTexturePath[100];

extern float playerAnimWidth, playerAnimHeight;

	extern BSTextureSquare *theLoadingImage;
	extern bool doneLoadingTheGame, canRenderGameNow;


extern float gameBoundLeft, gameBoundRight, gameBoundDown, gameBoundUp;

extern GLuint blankTexture, whiteTexture;


extern long long timer;

extern float newVolumeAudio, newVolumeSFX, currentVolumeAudio, currentVolumeSFX;
extern float theTimeHowFast;//FPS in update, the bigger it is, the slower it moves; the smaller it is, the faster it moves
extern float WorldBoundaryLeft, WorldBoundaryDown, WorldBoundaryUp, WorldBoundaryRight;

///extern ChapterLevelsStructure *nivele[301];
extern ChapterStructure *chaptere[100];
extern int nrOfChapters;
extern LevelChooserPlayerTexture *levelChoserPlayer;

extern BSBody *CameraPosition;

extern std::vector<BSTheSquareBodies*> ListOfSquareBodies;
extern std::vector<BSTheSquareBodies*> ListOfSquareDustBodies;
extern BSTheSquareBodies *hero, *Hero2nd;
extern std::vector<BSTheRoundBodies*> ListOfRoundBodies;
extern std::vector<BSTheParticles*> ListOfParticles;
//extern std::vector<BSAnimation*> ListOfAnimations;
///extern BSAnimation *playerAnimation, *currentPlayerAnimation,
extern BSAnimation *SoundButtonTexture;//, *primulPlayer, *ultimulPlayer
extern std::vector<BSTextureSquare*> ListOfSquareTextures;
extern BSTextureSquare *selectedTextureSquare;//*primaTexturaSquare, *ultimaTexturaSquare,
extern std::vector<BSTextureRound*> ListOfRoundTextures;
extern BSTextureRound *selectedTextureRound;//*primaTexturaRound, *ultimaTexturaRound,

extern int coinsTotalNo, coinsThisLevel, deathsTotalNo, deathsThisLevel;

//extern BSTheRoundBodies *primulRoundStatic, *ultimulRoundStatic;
extern BSTheBackgrounds *theRenderedBackgrounds;
extern BSTheSquare *theRenderedObstacleSquare, *theRenderedTextureSquare;
extern BSTheCircle *theRenderedObstacleCircle, *theRenderedTextureCircle;
//extern BSTheParticles *theRenderedParticles[500], *whenHitsGroundParticles[500];
extern BSSceneStructure *deadScene;

extern bool DarkLevels;
    extern BSTexturedVertex2D mainDarkData[4], darkLevelData[4];
    extern GLuint mainDarkTexture, darkLevelTexture,///, mainDarkVao, darkLevelVao,
			vboMainDark, vboDarkLevel, iboMainDark, iboDarkLevel;

extern bool settingsFromFirstOrGame, isSpaceDown;

extern float HeroInitialX, HeroInitialY;



extern int muscicIndex;

extern GLuint soundPlayerTexture;
extern std::vector<BSMenuStructure*> listOfMenus;
extern BSMenuStructure *currentMenu;
extern BSButtonStructure *currentButton;

extern bool canChangeVolumeMusic, canChangeVolumeAudioSfx, canChangeResolution;

///extern int currentMenuIndex, currentButtonIndex;	//menuState[0]->First menu, [1]->SelectLevel, [2]->TheGame,
//[3]->PauseMenu, [4]->OptionsMenu, [5]->SettingsMenu

extern short BinaryPlayer;  // 0000000000000001 in binary
extern short BinaryMonster; // 0000000000000010 in binary
extern short BinaryScenery; // 0000000000000100 in binary
extern short BinaryParticles; // 0000000000000100 in binary



extern GLushort iData[4];
extern unsigned char* images[1000]; //for textures


extern float CameraExtremeLeft, CameraExtremeRight, CameraExtremeUp, CameraExtremeDown, MenuCoordinateX, MenuCoordinateY;
extern GLuint ShaderCameraExtremeLeft, ShaderCameraExtremeRight,
       ShaderCameraExtremeUp, ShaderCameraExtremeDown,
       ShaderPlayerCoordinatesX, ShaderPlayerCoordinatesY,
       ShaderMouseX, ShaderMouseY, ShaderIsTheSquare, ShaderWidthOfSquare, ShaderHeightOfSquare,
       ShaderAflaRestulWidthOfSquare, ShaderAflaRestulHeightOfSquare, ShaderScaleSize,
       ShaderRotationAngle, ShaderRotated, ShaderIsText, ShaderTextCoord, ShaderTextTex, ShaderIsCircle, ShaderCircleRadius,
       ShaderCosRotation, ShaderSinRotation, ShaderScaleOnX, ShaderScaleOnY, ShaderDark, ShaderFlake;

extern BSBody *originalParticle, *originalTransparentMenu, *originalCoin, *originalFan, *originalFanParticleX, *originalFanParticleY, *originalBody, *originalDarkLevel, *originalDarkMenu,
			*originalRainDrop, *originalWormHole, *originalDustBody;

extern float razaInitialaInner, razaInitialaOuter, changeInPosition, lastPositionOfHeroX, lastPositionOfHeroY,
       startPositionCameraX, sinX, sinY, iteratieSin, widthOfObstacle, heightOfObstacle, createObstacleX, createObstacleY;
extern int nrBodies, nrParticles, nrBodiesDistroyed, nrParticlesDistroyed,
       nrX, indexOfSelectedBody, nrOfWhenItHits;
extern float MouseX, MouseY, MouseXLast, MouseYLast;
extern bool theLevelHasFinished, quit, clean, isPaused, canPressTheKey, canMoveCamera, canWriteInConsole,
       canClickLeft, canClickRight, aSalvatHarta, corpulEsteDistrus[1000],//, particleIsDistroyed[1000],
       canChangeScaleSize, canTeleportHero, pressedJumpSecond, jumpSecondSpinned, isTeleporting;
extern float jumpSecondSpinAngle;
//LittleBigMoveTheObstacle va retine true daca mut obiectul doar cat este jucatorul,
//si false daca mut jucatorul cat width si height of the box
extern std::string consoleString;

extern float buttonMenuWidth, buttonMenuHeight;

extern bool moveLeftGround, moveRightGround, moveLeftAir, moveRightAir, isJumping, ButtonUp, ButtonDown,
       ButtonRight, ButtonLeft, ButtonRun, ButtonJump, MouseLeft, MouseRight, MouseMoved;

extern bool canClick, aDatClick;

extern float speedWalk, speedWalkFast, speedRun, speedJumpUp, speedJumpToSide, speedGoDown, speedJumpUpOnWall,
       speedWalkInAir, speedWalkInAirFast, speedJumpToTheSameSide, timeToStayInAirWhenJumpsOnTheSameWall, timeToStayOnWall;

extern b2World* world;

extern const char* SCREEN_TITLE;
extern GLuint texture, textureMill, playerTexture, playerTextureDead, playerTextureRound,
       starsTexture1, starsTexture2, starsTexture3, starsTexture4, backgroundTexture;

extern bool canPressKeyAgain[256];
extern std::string theString;
extern float SursaDeLuminaX, SursaDeLuminaY;

extern int numberOfSquaresForPath, levelHasScript;
extern float lastTime, lastMovedX;
extern bool itMovedX, itMovedY, itMovedXLeft, itMovedXRight, itTurnedX;


extern bool canJumpVertically, canJumpHorizontally, isOnGround, isOnLeftWall, isOnRightWall, isInAir, jumpsUpTheWall,
       isInCorner;
extern std::string anotherString;

extern float moveStringX, moveStringY;

extern int variableWall;

extern BSVertexPos2D gQuadVertices[1000][4], menuButtons[1000][4], texQuadVertices[1000][4];
extern GLuint gVertexBuffer, texVertexBuffer;
extern float panta, termenLiber;

extern bool wasPressed[256];



#endif
