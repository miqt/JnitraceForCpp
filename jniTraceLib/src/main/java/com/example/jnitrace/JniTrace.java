package com.example.jnitrace;



import java.util.ArrayList;


public class JniTrace  {

    public native static void startJnitrace(ArrayList<String> soname,String save_path);

    static {
        System.loadLibrary("jnitrace");
    }
}