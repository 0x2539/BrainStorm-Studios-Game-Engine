# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)
LS_CPP=$(subst $(1)/,,$(wildcard $(1)/$(2)/*.cpp))
BOX2D_CPP:= $(call LS_CPP,$(LOCAL_PATH),Box2D/Collision) \
            $(call LS_CPP,$(LOCAL_PATH),Box2D/Collision/Shapes) \
            $(call LS_CPP,$(LOCAL_PATH),Box2D/Common) \
            $(call LS_CPP,$(LOCAL_PATH),Box2D/Dynamics) \
            $(call LS_CPP,$(LOCAL_PATH),Box2D/Dynamics/Contacts) \
            $(call LS_CPP,$(LOCAL_PATH),Box2D/Dynamics/Joints) \
            $(call LS_CPP,$(LOCAL_PATH),Box2D/Rope)

LIBPNG_CPP:= $(call LS_CPP,$(LOCAL_PATH),libpng/)

include $(CLEAR_VARS)

LOCAL_MODULE:= box2d_static
LOCAL_SRC_FILES:= $(BOX2D_CPP)
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/Box2D
LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)

include $(BUILD_STATIC_LIBRARY)



include $(CLEAR_VARS)

LOCAL_MODULE    := libzip
LOCAL_SRC_FILES :=\
	libzip/zip_add.c \
	libzip/zip_add_dir.c \
	libzip/zip_close.c \
	libzip/zip_delete.c \
	libzip/zip_dirent.c \
	libzip/zip_entry_free.c \
	libzip/zip_entry_new.c \
	libzip/zip_err_str.c \
	libzip/zip_error.c \
	libzip/zip_error_clear.c \
	libzip/zip_error_get.c \
	libzip/zip_error_get_sys_type.c \
	libzip/zip_error_strerror.c \
	libzip/zip_error_to_str.c \
	libzip/zip_fclose.c \
	libzip/zip_file_error_clear.c \
	libzip/zip_file_error_get.c \
	libzip/zip_file_get_offset.c \
	libzip/zip_file_strerror.c \
	libzip/zip_filerange_crc.c \
	libzip/zip_fopen.c \
	libzip/zip_fopen_index.c \
	libzip/zip_fread.c \
	libzip/zip_free.c \
	libzip/zip_get_archive_comment.c \
	libzip/zip_get_archive_flag.c \
	libzip/zip_get_file_comment.c \
	libzip/zip_get_num_files.c \
	libzip/zip_get_name.c \
	libzip/zip_memdup.c \
	libzip/zip_name_locate.c \
	libzip/zip_new.c \
	libzip/zip_open.c \
	libzip/zip_rename.c \
	libzip/zip_replace.c \
	libzip/zip_set_archive_comment.c \
	libzip/zip_set_archive_flag.c \
	libzip/zip_set_file_comment.c \
	libzip/zip_source_buffer.c \
	libzip/zip_source_file.c \
	libzip/zip_source_filep.c \
	libzip/zip_source_free.c \
	libzip/zip_source_function.c \
	libzip/zip_source_zip.c \
	libzip/zip_set_name.c \
	libzip/zip_stat.c \
	libzip/zip_stat_index.c \
	libzip/zip_stat_init.c \
	libzip/zip_strerror.c \
	libzip/zip_unchange.c \
	libzip/zip_unchange_all.c \
	libzip/zip_unchange_archive.c \
	libzip/zip_unchange_data.c

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/libzip
LOCAL_LDLIBS := -lz

include $(BUILD_STATIC_LIBRARY)




include $(CLEAR_VARS)

LOCAL_MODULE := libpng
LOCAL_SRC_FILES = libpng/png.c \
			        libpng/pngerror.c \
			        libpng/pngget.c \
			        libpng/pngmem.c \
			        libpng/pngpread.c \
			        libpng/pngread.c \
			        libpng/pngrio.c \
			        libpng/pngrtran.c \
			        libpng/pngrutil.c \
			        libpng/pngset.c \
			        libpng/pngtrans.c \
			        libpng/pngwio.c \
			        libpng/pngwrite.c \
			        libpng/pngwtran.c \
			        libpng/pngwutil.c 
LOCAL_LDLIBS    += -landroid
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/libpng
LOCAL_C_INCLUDES := $(LOCAL_EXPORT_C_INCLUDES)
LOCAL_EXPORT_LDLIBS := -lz

include $(BUILD_STATIC_LIBRARY)




include $(CLEAR_VARS)

LOCAL_STATIC_LIBRARIES := box2d_static libpng libzip
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes    

LOCAL_MODULE    := BSView
LOCAL_CFLAGS    := -Werror -std=c++11 #-Wno-psabi 
LOCAL_SRC_FILES := BSTexture.cpp main.cpp BSObstacles.cpp BSTexturedPolygonProgram2D.cpp BSUtilities.cpp BSInputClass.cpp BSXmlFiles.cpp BSShaderProgram.cpp BSActionStuff.cpp BSAnimationClass.cpp BSLevelMenu.cpp
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2

include $(BUILD_SHARED_LIBRARY)
