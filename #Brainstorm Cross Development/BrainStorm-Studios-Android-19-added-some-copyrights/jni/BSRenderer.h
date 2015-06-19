#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include <iostream>
#include <png.h>
#include <zip.h>
#include "BSValues.h"
#include "BSOpenGL.h"



//static void png_zip_read(png_structp png_ptr, png_bytep data, png_size_t length)
//{
    //zip_fread(file, data, length);
//}

/*static void loadTexture(std::string path, GLuint &thetextureToRender)
{
	std::string name = "assets/" + path;
	int width, height;
	const char* filename = name.c_str();
    file = zip_fopen(APKArchive, filename, 0);
    if (!file)
    {
        LOGE("Error opening %s from APK", filename);
        return;// TEXTURE_LOAD_ERROR;
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
        return;// TEXTURE_LOAD_ERROR;
    }

    //create png struct
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr)
    {
        zip_fclose(file);
        LOGE("Unable to create png struct : %s", filename);
        return;// (TEXTURE_LOAD_ERROR);
    }

    //create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
    {
        png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
        LOGE("Unable to create png info : %s", filename);
        zip_fclose(file);
        return;// (TEXTURE_LOAD_ERROR);
    }

    //create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info)
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        LOGE("Unable to create png end info : %s", filename);
        zip_fclose(file);
        return;// (TEXTURE_LOAD_ERROR);
    }

    //png error stuff, not sure libpng man suggests this.
    if (setjmp(png_jmpbuf(png_ptr)))
    {
        zip_fclose(file);
        LOGE("Error during setjmp : %s", filename);
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        return;// (TEXTURE_LOAD_ERROR);
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
    png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
                 NULL, NULL, NULL);

    //update width and height based on png info
    width = twidth;
    height = theight;

    // Update the png info struct.
    //png_read_update_info(png_ptr, info_ptr);

    // Row size in bytes.
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // Allocate the image_data as a big block, to be given to opengl
    png_byte *image_data = new png_byte[rowbytes * height];
    if (!image_data)
    {
        //clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        LOGE("Unable to allocate image_data while loading %s ", filename);
        zip_fclose(file);
        return;// TEXTURE_LOAD_ERROR;
    }

    //row_pointers is for pointing to image_data for reading the png with libpng
    png_bytep *row_pointers = new png_bytep[height];
    if (!row_pointers)
    {
        //clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        delete[] image_data;
        LOGE("Unable to allocate row_pointer while loading %s ", filename);
        zip_fclose(file);
        return;// TEXTURE_LOAD_ERROR;
    }
    // set the individual row_pointers to point at the correct offsets of image_data
    for (int i = 0; i < height; ++i)
    {
        row_pointers[height - 1 - i] = image_data + i * rowbytes;
    }

    //read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);

    //Now generate the OpenGL texture object

    glGenTextures(1, &thetextureToRender);
    glBindTexture(GL_TEXTURE_2D, thetextureToRender);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, (GLvoid*) image_data);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    delete[] image_data;
    delete[] row_pointers;
    zip_fclose(file);
}*/

static void renderBody(float coordX, float coordY, float coordZ, float xAngle, float yAngle, float zAngle,
							GLuint theTextureIdToRender, BSColorRGBA theColorOfObstacle,
							GLuint vboBuffer, float ScaleOnX, float ScaleOnY, float ScaleOnZ)
{
	//LOGI("%s", "hello51");
    checkGlError("glDraw1");
    glBindTexture(GL_TEXTURE_2D, theTextureIdToRender);

    checkGlError("glDraw2");
	//LOGI("%s", "hello52");
    BSModelViewMatrix = glm::translate( coordX * cross_platform_scale, coordY * cross_platform_scale, coordZ ) * LookAtMatrix;

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
    BSModelViewMatrix = BSModelViewMatrix * glm::scale( ScaleOnX * cross_platform_scale, ScaleOnY * cross_platform_scale, ScaleOnZ );

    checkGlError("glDraw4");
	//LOGI("%s", "hello54");
    glUniformMatrix4fv(	locationBSModelViewMatrix, 1, GL_FALSE, glm::value_ptr( BSModelViewMatrix ) );

    checkGlError("glDraw5");
	//LOGI("%s", "hello55");
    glUniform4f( locationBSTextureColor, theColorOfObstacle.r, theColorOfObstacle.g, theColorOfObstacle.b, theColorOfObstacle.a );

    checkGlError("glDraw6");
	//LOGI("%s", "hello56");

    glBindBuffer(GL_ARRAY_BUFFER, vboBuffer);
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
}

#endif
