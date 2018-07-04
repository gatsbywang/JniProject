package com.demo.jni.arraylist;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Person[] persons = new Person[10];
        for(int i=0;i<persons.length;i++){
            persons[i] = new Person("Darren",24+i);
        }
        Person[] newPersons = new Person[10];
        arraycopy(persons,0,newPersons,0,10);
    }

    public static native void arraycopy(Object src,  int  srcPos,
                                        Object dest, int destPos,
                                        int length);
}
