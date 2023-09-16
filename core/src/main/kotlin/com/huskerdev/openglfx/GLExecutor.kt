package com.huskerdev.openglfx

import com.huskerdev.openglfx.implementation.InteropImpl
import com.huskerdev.openglfx.implementation.SharedImpl
import com.huskerdev.openglfx.implementation.UniversalImpl
import java.nio.ByteBuffer


const val GL_BGRA = 0x80E1
const val GL_RGBA = 0x1908
const val GL_RGBA8 = 0x8058
const val GL_UNSIGNED_BYTE = 0x1401
const val GL_UNSIGNED_INT_8_8_8_8_REV = 0x8367
const val GL_FRAMEBUFFER = 0x8D40
const val GL_TEXTURE_2D = 0xDE1
const val GL_RENDERBUFFER = 0x8D41
const val GL_COLOR_ATTACHMENT0 = 0x8CE0
const val GL_DEPTH_COMPONENT = 0x1902
const val GL_DEPTH_ATTACHMENT = 0x8D00
const val GL_TEXTURE_MIN_FILTER = 0x2801
const val GL_NEAREST = 0x2600
const val GL_READ_FRAMEBUFFER = 0x8CA8
const val GL_DRAW_FRAMEBUFFER = 0x8CA9
const val GL_COLOR_BUFFER_BIT = 0x4000
const val GL_DRAW_FRAMEBUFFER_BINDING = 0x8CA6
const val GL_READ_FRAMEBUFFER_BINDING = 0x8CAA
const val GL_MAX_SAMPLES = 0x8D57


abstract class GLExecutor {

    companion object {
        private var isInitialized = false
        @JvmStatic external fun nInitGLFunctions()

        @JvmStatic external fun glDeleteFramebuffers(fbo: Int)
        @JvmStatic external fun glDeleteRenderbuffers(rbo: Int)
        @JvmStatic external fun glDeleteTextures(texture: Int)
        @JvmStatic external fun glGenFramebuffers(): Int
        @JvmStatic external fun glGenRenderbuffers(): Int
        @JvmStatic external fun glGenTextures(): Int
        @JvmStatic external fun glBindFramebuffer(target: Int, fbo: Int)
        @JvmStatic external fun glBindRenderbuffer(target: Int, rbo: Int)
        @JvmStatic external fun glBindTexture(target: Int, texture: Int)
        @JvmStatic external fun glFramebufferTexture2D(target: Int, attachment: Int, texture: Int, texId: Int, level: Int)
        @JvmStatic external fun glRenderbufferStorage(target: Int, internalformat: Int, width: Int, height: Int)
        @JvmStatic external fun glFramebufferRenderbuffer(target: Int, attachment: Int, renderbufferTarget: Int, renderbuffer: Int)
        @JvmStatic external fun glReadPixels(x: Int, y: Int, width: Int, height: Int, format: Int, type: Int, pixels: ByteBuffer)
        @JvmStatic external fun glTexImage2D(target: Int, level: Int, internalformat: Int, width: Int, height: Int, border: Int, format: Int, type: Int, pixels: ByteBuffer?)
        @JvmStatic external fun glTexParameteri(target: Int, pname: Int, param: Int)
        @JvmStatic external fun glViewport(x: Int, y: Int, w: Int, h: Int)
        @JvmStatic external fun glFinish()

        @JvmStatic external fun glRenderbufferStorageMultisample(target: Int, samples: Int, internalformat: Int, width: Int, height: Int)
        @JvmStatic external fun glBlitFramebuffer(srcX0: Int, srcY0: Int, srcX1: Int, srcY1: Int, dstX0: Int, dstY0: Int, dstX1: Int, dstY1: Int, mask: Int, filter: Int)
        @JvmStatic external fun glGetInteger(pname: Int): Int

        fun initGLFunctions(){
            if(isInitialized) return
            isInitialized = true
            nInitGLFunctions()
        }
    }

    open fun universalCanvas(profile: GLProfile, flipY: Boolean, msaa: Int) = UniversalImpl(this, profile, flipY, msaa)
    open fun sharedCanvas(profile: GLProfile, flipY: Boolean, msaa: Int) = SharedImpl(this, profile, flipY, msaa)
    open fun interopCanvas(profile: GLProfile, flipY: Boolean, msaa: Int) = InteropImpl(this, profile, flipY, msaa)

    abstract fun initGLFunctionsImpl()

}