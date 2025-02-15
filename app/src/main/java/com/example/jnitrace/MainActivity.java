package com.example.jnitrace;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import com.example.Jnitrace.R;

import java.io.File;
import java.util.ArrayList;


public class MainActivity extends AppCompatActivity {



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        //需要监听的SO关键字,监听多个SO添加即可
        ArrayList<String> list = new ArrayList<>();
        list.add("tracetest");
        JniTrace.startJnitrace(list,new File(getFilesDir(),"trace.log").getAbsolutePath());
        System.loadLibrary("tracetest");

    }


}