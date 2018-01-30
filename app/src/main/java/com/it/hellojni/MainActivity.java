package com.it.hellojni;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("hello-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
//        tv.setText(Integer.toString(resultFromC(10, 20)));
//        tv.setText(encodeString("hello world"));
//        tv.setText(arryToString());
        writeFileInternal();
    }


    public String arryToString(){
        int[] arr = {2, 4, 5, 9, 1};
        sortArray(arr);
        StringBuilder sb = new StringBuilder(5);
        for (int i = 0; i < arr.length; i++) {
            sb.append(arr[i]);
        }
        return sb.toString();
    }

    public void writeFileInternal() {
        String fileName = "surprise.text";
        String content = "Surprise, there is nothing!";
        String filePath = getFilesDir() + File.separator + fileName;
        Log.i("jni", filePath);
        writeFile(filePath, content);
    }


    public native String sayHelloWorld();

    public native int resultFromC(int a, int b);

    /**
     * 对字符串加密
     * @param str
     * @return
     */
    public native String encodeString(String str);

    /**
     * 传入int数组,并进行排序
     * @param arr
     */
    public native void sortArray(int[] arr);


    /**
     * 在本地创建一个文件
     * @param filePath
     */
    public native void writeFile(String filePath, String content);



}
