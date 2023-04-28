package com.example.testlib

class NativeLib {

    /**
     * A native method that is implemented by the 'testlib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'testlib' library on application startup.
        init {
            System.loadLibrary("testlib")
        }
    }
}