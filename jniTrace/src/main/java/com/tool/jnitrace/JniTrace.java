package com.tool.jnitrace;

import java.util.ArrayList;

public class JniTrace {


    public static native void startHookJni(boolean isListenerAll, ArrayList<String> jFilterList, ArrayList<String> jFunctionList, String filepath);

    static {
        System.loadLibrary("jnitrace");
    }
}