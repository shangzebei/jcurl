package com.my.example;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;

import com.my.jcurl.CurlUtil;
import com.my.jcurl.ParamArray;
import com.my.jcurl.ParamFormData;
import com.my.jcurl.ParamFormMap;
import com.my.jcurl.ParamMap;
import com.my.jcurl.Progress;
import com.my.jcurl.Response;

public class MainActivity extends Activity {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("jcurl");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.grid_layout);
        GridView gridView = findViewById(R.id.grid);
        gridView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                postMulFiles();

            }
        });
        initView(this);


//        getMethod();
//        getMethodParam();
//        getfile();
//        postData();
//        postFile();

//        gethttps();

    }

    private void postMulFiles() {
        ParamFormMap paramFormMap = new ParamFormMap();
        ParamFormData pp = new ParamFormData();
        ParamArray arr = new ParamArray();
        arr.add("data/data/com.my.jcurl/lib/libjcurl.so");
        arr.add("/system/lib/libandroid.so");
        pp.setFiles(arr);
        paramFormMap.set("files", pp);
        CurlUtil.uploadMultiFile("http://192.168.1.88:8080/getFiles", paramFormMap, new Response() {
            @Override
            public void callback(int result, String s) {
                Log.i("szb", "callback: " + s);
            }
        }).execute();
    }

    private void postFile() {
        ParamMap paramMap = new ParamMap();
        paramMap.set("files", "data/data/com.my.jcurl/lib/libjcurl.so");
        CurlUtil.uploadMultiFile("http://192.168.0.164:8080/file",
                paramMap, new Response() {
                    @Override
                    public void callback(int result, String s) {
                        Log.i("szb", "callback: " + s);

                    }
                }).setProgress(new Progress() {
            @Override
            public void progress(long unow, long utotal, long dnow, long dtotal) {
                Log.i("szb", "progress: " + unow + ":::" + utotal);
            }
        }).execute();
    }

    private void gethttps() {
        ParamMap paramMap = new ParamMap();
        paramMap.set("local", "zh");
        CurlUtil.get("https://apigateway.21chinamall.com/v1/local", new Response() {
            @Override
            public void callback(int result, String s) {
                Log.i("szb", "callback: " + s);
            }
        }).setParam(paramMap).execute();
    }

    private void postData() {
        CurlUtil.post("http://192.168.0.164:8080/show", new Response() {
            @Override
            public void callback(int result, String s) {
                Log.i("szb", "callback: " + s);
            }
        }).setParamData("shang ze").execute();
    }

    private void getMethodParam() {
        ParamMap map = new ParamMap();
        map.set("username", "admin@localhost");
        map.set("password", "123456");
        CurlUtil.post("http://192.168.0.88:15000/v1/login", new Response() {
            @Override
            public void callback(int result, String s) {
                Log.i("szb", "callback: " + s);
            }
        }).setParam(map).execute();
    }

    private void getMethod() {
        CurlUtil.get("http://192.168.0.88:15000/v1/get_all_user", new Response() {
            @Override
            public void callback(int result, String s) {
                Log.i("szb", "callback: " + s);
            }
        }).setHeader("X-Auth-Token:admin@localhost:e58e67dba304027768c62c1160daeb3e")
                .setHeader("Accept: application/json")
                .execute();
    }

    private void getfile() {
        CurlUtil.getFile("https://wdl1.cache.wps.cn/wps/download/W.P.S.6930.19.552.exe",
                Environment.getExternalStorageDirectory() + "/wps.exe")
                .setProgress(new Progress() {
                    @Override
                    public void progress(long unow, long utotal, long dnow, long dtotal) {
                        Log.i("szb", "progress: " + dnow + "::" + dtotal);
                    }
                }).execute();
    }

    private void initView(Context mainActivity) {
        final ImageViewAdapter imageViewAdapter = new ImageViewAdapter(this);
        final GridView viewById = findViewById(R.id.grid);
        viewById.setAdapter(imageViewAdapter);
//        viewById.setOnItemClickListener(new AdapterView.OnItemClickListener() {
//            @Override
//            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
//                imageViewAdapter.notifyDataSetChanged();
//            }
//        });

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
}
