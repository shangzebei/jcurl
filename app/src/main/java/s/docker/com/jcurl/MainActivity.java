package s.docker.com.jcurl;

import android.content.Context;
import android.os.Bundle;
import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.GridView;

public class MainActivity extends AppCompatActivity {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("jcurl");
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.grid_layout);
//        initView(this);
//        ParamMap map = new ParamMap();
//        map.set("username", "admin@localhost");
//        map.set("password", "123456");
//        CurlUtil.post("http://192.168.0.88:15000/v1/login", new Response() {
//            @Override
//            public void callback(int result, String s) {
//                Log.i("szb", "callback: " + s);
//            }
//        }).setParam(map).execute();




        getMethod();
//        getfile();

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
