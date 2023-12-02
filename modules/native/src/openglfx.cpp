#include "openglfx.h"

#include <iostream>

void* a_GetProcAddress(const char* name) {
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    if(libGL == NULL){
        libGL = LoadLibraryW(L"opengl32.dll");
        a_wglGetProcAddress = (wglGetProcAddressPtr)GetProcAddress(libGL, "wglGetProcAddress");
    }
    void* procAddr = a_wglGetProcAddress(name);
    if(procAddr == NULL)
        procAddr = GetProcAddress(libGL, name);
    return procAddr;

#elif defined(__linux__)
    if(libGL == NULL){
        static const char *NAMES[] = {"libGL.so.1", "libGL.so"};
        for(int i = 0; i < 2; i++)
            if((libGL = dlopen(NAMES[i], RTLD_NOW | RTLD_GLOBAL)) != NULL)
                break;
        a_gladGetProcAddress = (glXGetProcAddressPtr)dlsym(libGL, "glXGetProcAddressARB");
    }
    void* procAddr = (void*)a_gladGetProcAddress(name);
    if(procAddr == NULL)
        procAddr = dlsym(libGL, name);
    return procAddr;

#elif defined(__APPLE__)
    if(libGL == NULL){
        static const char *NAMES[] = {
            "../Frameworks/OpenGL.framework/OpenGL",
            "/Library/Frameworks/OpenGL.framework/OpenGL",
            "/System/Library/Frameworks/OpenGL.framework/OpenGL",
            "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
        };
        for(int i = 0; i < 4; i++)
            if((libGL = dlopen(NAMES[i], RTLD_NOW | RTLD_GLOBAL)) != NULL)
                break;
    }
    return dlsym(libGL, name);
#endif
}


glfun(void, nInitGLFunctions)(JNIEnv* env, jobject) {
    a_glViewport = (glViewportPtr)a_GetProcAddress("glViewport");
    a_glTexParameteri = (glTexParameteriPtr)a_GetProcAddress("glTexParameteri");
    a_glTexImage2D = (glTexImage2DPtr)a_GetProcAddress("glTexImage2D");
    a_glReadPixels = (glReadPixelsPtr)a_GetProcAddress("glReadPixels");
    a_glFramebufferRenderbuffer = (glFramebufferRenderbufferPtr)a_GetProcAddress("glFramebufferRenderbuffer");
    a_glRenderbufferStorage = (glRenderbufferStoragePtr)a_GetProcAddress("glRenderbufferStorage");
    a_glFramebufferTexture2D = (glFramebufferTexture2DPtr)a_GetProcAddress("glFramebufferTexture2D");
    a_glBindTexture = (glBindTexturePtr)a_GetProcAddress("glBindTexture");
    a_glBindRenderbuffer = (glBindRenderbufferPtr)a_GetProcAddress("glBindRenderbuffer");
    a_glBindFramebuffer = (glBindFramebufferPtr)a_GetProcAddress("glBindFramebuffer");
    a_glGenTextures = (glGenTexturesPtr)a_GetProcAddress("glGenTextures");
    a_glGenRenderbuffers = (glGenRenderbuffersPtr)a_GetProcAddress("glGenRenderbuffers");
    a_glGenFramebuffers = (glGenFramebuffersPtr)a_GetProcAddress("glGenFramebuffers");
    a_glDeleteTextures = (glDeleteTexturesPtr)a_GetProcAddress("glDeleteTextures");
    a_glDeleteRenderbuffers = (glDeleteRenderbuffersPtr)a_GetProcAddress("glDeleteRenderbuffers");
    a_glDeleteFramebuffers = (glDeleteFramebuffersPtr)a_GetProcAddress("glDeleteFramebuffers");
    a_glFinish = (glFinishPtr)a_GetProcAddress("glFinish");
    a_glRenderbufferStorageMultisample = (glRenderbufferStorageMultisamplePtr)a_GetProcAddress("glRenderbufferStorageMultisample");
    a_glBlitFramebuffer = (glBlitFramebufferPtr)a_GetProcAddress("glBlitFramebuffer");
    a_glGetIntegerv = (glGetIntegervPtr)a_GetProcAddress("glGetIntegerv");

    a_glCreateShader = (glCreateShaderPtr)a_GetProcAddress("glCreateShader");
    a_glDeleteShader = (glDeleteShaderPtr)a_GetProcAddress("glDeleteShader");
    a_glShaderSource = (glShaderSourcePtr)a_GetProcAddress("glShaderSource");
    a_glCompileShader = (glCompileShaderPtr)a_GetProcAddress("glCompileShader");
    a_glCreateProgram = (glCreateProgramPtr)a_GetProcAddress("glCreateProgram");
    a_glAttachShader = (glAttachShaderPtr)a_GetProcAddress("glAttachShader");
    a_glLinkProgram = (glLinkProgramPtr)a_GetProcAddress("glLinkProgram");
    a_glUseProgram = (glUseProgramPtr)a_GetProcAddress("glUseProgram");
    a_glUseProgram = (glUseProgramPtr)a_GetProcAddress("glUseProgram");
    a_glGetUniformLocation = (glGetUniformLocationPtr)a_GetProcAddress("glGetUniformLocation");
    a_glUniform2f = (glUniform2fPtr)a_GetProcAddress("glUniform2f");
    a_glGetShaderiv = (glGetShaderivPtr)a_GetProcAddress("glGetShaderiv");
    a_glGetShaderInfoLog = (glGetShaderInfoLogPtr)a_GetProcAddress("glGetShaderInfoLog");

    a_glGenVertexArrays = (glGenVertexArraysPtr)a_GetProcAddress("glGenVertexArrays");
    a_glBindVertexArray = (glBindVertexArrayPtr)a_GetProcAddress("glBindVertexArray");
    a_glGenBuffers = (glGenBuffersPtr)a_GetProcAddress("glGenBuffers");
    a_glBindBuffer = (glBindBufferPtr)a_GetProcAddress("glBindBuffer");
    a_glBufferData = (glBufferDataPtr)a_GetProcAddress("glBufferData");
    a_glVertexAttribPointer = (glVertexAttribPointerPtr)a_GetProcAddress("glVertexAttribPointer");
    a_glEnableVertexAttribArray = (glEnableVertexAttribArrayPtr)a_GetProcAddress("glEnableVertexAttribArray");
    a_glDeleteBuffers = (glDeleteBuffersPtr)a_GetProcAddress("glDeleteBuffers");
    a_glDrawArrays = (glDrawArraysPtr)a_GetProcAddress("glDrawArrays");

    #if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    wglChoosePixelFormatARB = (wglChoosePixelFormatARBPtr)a_GetProcAddress("wglChoosePixelFormatARB");
    wglCreateContextAttribsARB = (wglCreateContextAttribsARBPtr)a_GetProcAddress("wglCreateContextAttribsARB");
    wglDXOpenDeviceNV = (wglDXOpenDeviceNVPtr)a_GetProcAddress("wglDXOpenDeviceNV");
    wglDXCloseDeviceNV = (wglDXCloseDeviceNVPtr)a_GetProcAddress("wglDXCloseDeviceNV");
    wglDXRegisterObjectNV = (wglDXRegisterObjectNVPtr)a_GetProcAddress("wglDXRegisterObjectNV");
    wglDXSetResourceShareHandleNV = (wglDXSetResourceShareHandleNVPtr)a_GetProcAddress("wglDXSetResourceShareHandleNV");
    wglDXUnregisterObjectNV = (wglDXUnregisterObjectNVPtr)a_GetProcAddress("wglDXUnregisterObjectNV");
    wglDXLockObjectsNV = (wglDXLockObjectsNVPtr)a_GetProcAddress("wglDXLockObjectsNV");
    wglDXUnlockObjectsNV = (wglDXUnlockObjectsNVPtr)a_GetProcAddress("wglDXUnlockObjectsNV");
    #endif
}

glfun(void, glDeleteFramebuffers)(JNIEnv* env, jobject, jint fbo) {
    a_glDeleteFramebuffers(1, (GLuint*)&fbo);
}

glfun(void, glDeleteRenderbuffers)(JNIEnv* env, jobject, jint rbo) {
    a_glDeleteRenderbuffers(1, (GLuint*)&rbo);
}

glfun(void, glDeleteTextures)(JNIEnv* env, jobject, jint texture) {
    a_glDeleteTextures(1, (GLuint*)&texture);
}

glfun(jint, glGenFramebuffers)(JNIEnv* env, jobject) {
    GLuint framebuffer = 0;
    a_glGenFramebuffers(1, &framebuffer);
    return framebuffer;
}

glfun(jint, glGenRenderbuffers)(JNIEnv* env, jobject) {
    GLuint renderbuffer;
    a_glGenRenderbuffers(1, &renderbuffer);
    return renderbuffer;
}

glfun(jint, glGenTextures)(JNIEnv* env, jobject) {
    GLuint texture;
    a_glGenTextures(1, &texture);
    return texture;
}

glfun(void, glBindFramebuffer)(JNIEnv* env, jobject, jint target, jint fbo) {
    a_glBindFramebuffer(target, fbo);
}

glfun(void, glBindRenderbuffer)(JNIEnv* env, jobject, jint target, jint rbo) {
    a_glBindRenderbuffer(target, rbo);
}

glfun(void, glBindTexture)(JNIEnv* env, jobject, jint target, jint texture) {
    a_glBindTexture(target, texture);
}

glfun(void, glFramebufferTexture2D)(JNIEnv* env, jobject, jint target, jint attachment, jint texture, jint texId, jint level) {
    a_glFramebufferTexture2D(target, attachment, texture, texId, level);
}

glfun(void, glRenderbufferStorage)(JNIEnv* env, jobject, jint target, jint internalFormat, jint width, jint height) {
    a_glRenderbufferStorage(target, internalFormat, width, height);
}

glfun(void, glFramebufferRenderbuffer)(JNIEnv* env, jobject, jint target, jint attachment, jint renderbufferTarget, jint renderbuffer) {
    a_glFramebufferRenderbuffer(target, attachment, renderbufferTarget, renderbuffer);
}

glfun(void, glReadPixels)(JNIEnv* env, jobject, jint x, jint y, jint width, jint height, jint format, jint type, jobject pixels) {
    char* bb = (char*)env->GetDirectBufferAddress(pixels);
    a_glReadPixels(x, y, width, height, format, type, bb);
}

glfun(void, glTexImage2D)(JNIEnv* env, jobject, jint target, jint level, jint internalFormat, jint width, jint height, jint border, jint format, jint type, jobject pixels) {
    char* bb = pixels ? (char*)env->GetDirectBufferAddress(pixels) : NULL;
    a_glTexImage2D(target, level, internalFormat, width, height, border, format, type, bb);
}

glfun(void, glTexParameteri)(JNIEnv* env, jobject, jint target, jint pname, jint param) {
    a_glTexParameteri(target, pname, param);
}

glfun(void, glViewport)(JNIEnv* env, jobject, jint x, jint y, jint w, jint h) {
    a_glViewport(x, y, w, h);
}

glfun(void, glFinish)(JNIEnv* env, jobject) {
    a_glFinish();
}

glfun(void, glRenderbufferStorageMultisample)(JNIEnv* env, jobject, jint target, jint samples, jint internalformat, jint width, jint height) {
    a_glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}

glfun(void, glBlitFramebuffer)(JNIEnv* env, jobject, jint srcX0, jint srcY0, jint srcX1, jint srcY1, jint dstX0, jint dstY0, jint dstX1, jint dstY1, jint mask, jint filter) {
    a_glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

glfun(jint, glGetInteger)(JNIEnv* env, jobject, jint pname) {
    GLint data = 0;
    a_glGetIntegerv(pname, &data);
    return (jint)data;
}

glfun(jint, glCreateShader)(JNIEnv* env, jobject, jint type) {
    return a_glCreateShader(type);
}

glfun(void, glDeleteShader)(JNIEnv* env, jobject, jint shader) {
    a_glDeleteShader(shader);
}

glfun(void, glShaderSource)(JNIEnv* env, jobject, jint shader, jstring source) {
    const char* sourceCh = env->GetStringUTFChars(source, 0);
    a_glShaderSource(shader, 1, &sourceCh, NULL);
    env->ReleaseStringUTFChars(source, sourceCh);
}

glfun(void, glCompileShader)(JNIEnv* env, jobject, jint shader) {
    a_glCompileShader(shader);
}

glfun(jint, glCreateProgram)(JNIEnv* env, jobject) {
    return a_glCreateProgram();
}

glfun(void, glAttachShader)(JNIEnv* env, jobject, jint program, jint shader) {
    a_glAttachShader(program, shader);
}

glfun(void, glLinkProgram)(JNIEnv* env, jobject, jint program) {
    a_glLinkProgram(program);
}

glfun(void, glUseProgram)(JNIEnv* env, jobject, jint program) {
    a_glUseProgram(program);
}

glfun(jint, glGetUniformLocation)(JNIEnv* env, jobject, jint program, jstring name) {
    const char* nameCh = env->GetStringUTFChars(name, 0);

    jint location = (jint)a_glGetUniformLocation(program, nameCh);
    env->ReleaseStringUTFChars(name, nameCh);
    return location;
}

glfun(void, glUniform2f)(JNIEnv* env, jobject, jint program, jfloat value1, jfloat value2) {
    a_glUniform2f(program, value1, value2);
}

glfun(jint, glGetShaderi)(JNIEnv* env, jobject, jint shader, jint pname) {
    GLint result = 0;
    a_glGetShaderiv(shader, pname, &result);
    return result;
}

#define GL_INFO_LOG_LENGTH 0x8B84
glfun(jstring, glGetShaderInfoLog)(JNIEnv* env, jobject, jint shader) {
    GLint maxLength = 0;
    a_glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    char* errorLog = new char[maxLength];
    a_glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

    jstring result = env->NewStringUTF(errorLog);
    delete[] errorLog;
    return result;
}

glfun(jint, glGenVertexArrays)(JNIEnv* env, jobject) {
    unsigned int vao;
    a_glGenVertexArrays(1, &vao);
    return vao;
}

glfun(void, glBindVertexArray)(JNIEnv* env, jobject, jint vao) {
    a_glBindVertexArray(vao);
}

glfun(jint, glGenBuffers)(JNIEnv* env, jobject) {
    unsigned int vbo;
    a_glGenBuffers(1, &vbo);
    return vbo;
}

glfun(void, glBindBuffer)(JNIEnv* env, jobject, jint target, jint buffer) {
    a_glBindBuffer(target, buffer);
}

glfun(void, glBufferData)(JNIEnv* env, jobject, jint target, jobject verticesBuffer, jint type) {
    GLfloat* vertices = (GLfloat*)env->GetDirectBufferAddress(verticesBuffer);
    jlong length = env->GetDirectBufferCapacity(verticesBuffer) * 4;
    a_glBufferData(target, length, vertices, type);
}

glfun(void, glVertexAttribPointer)(JNIEnv* env, jobject, jint index, jint size, jint type, jboolean normalized, jint stride, jlong offset) {
    a_glVertexAttribPointer(index, size, type, normalized, stride, (void*)offset);
}

glfun(void, glEnableVertexAttribArray)(JNIEnv* env, jobject, jint index) {
    a_glEnableVertexAttribArray(index);
}

glfun(void, glDeleteBuffers)(JNIEnv* env, jobject, jint buffer) {
    a_glDeleteBuffers(1, (GLuint*)&buffer);
}

glfun(void, glDrawArrays)(JNIEnv* env, jobject, jint mode, jint first, jint count) {
    a_glDrawArrays(mode, first, count);
}