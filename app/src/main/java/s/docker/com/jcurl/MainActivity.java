package s.docker.com.jcurl;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.os.Build;
import android.os.Handler;
import android.os.Message;
import android.support.annotation.RequiresApi;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.GridView;
import android.widget.ProgressBar;
import android.widget.TextView;

import java.math.BigInteger;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;

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
