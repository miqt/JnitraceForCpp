package com.tool.jnitrace;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.example.testlib.NativeLib;
import com.tool.jnitrace.JniTrace;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ArrayList<String> arrayList = new ArrayList<>();
        arrayList.add("testlib");
        ArrayList<String> funlist  =new ArrayList<>();
        funlist.add("0");
//        funlist.add("1");
//        funlist.add("2");
//        funlist.add("3");
//        funlist.add("4");
        JniTrace.startHookJni(true,arrayList,funlist, getFilesDir().getAbsolutePath()+"/jni.log");

        new NativeLib().stringFromJNI();
        new NativeLib().stringFromJNI();
        new NativeLib().stringFromJNI();
        new NativeLib().stringFromJNI();
        new NativeLib().stringFromJNI();
    }
}