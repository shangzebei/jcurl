package s.docker.com.jcurl;

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
import android.widget.TextView;

import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;

public class MainActivity extends AppCompatActivity {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("jcurl");
    }

    private Bitmap bitmap;

    public static String getString(ByteBuffer buffer)
    {
        Charset charset = null;
        CharsetDecoder decoder = null;
        CharBuffer charBuffer = null;
        try
        {
            charset = Charset.forName("UTF-8");
            decoder = charset.newDecoder();
            // charBuffer = decoder.decode(buffer);//用这个的话，只能输出来一次结果，第二次显示为空
            charBuffer = decoder.decode(buffer.asReadOnlyBuffer());
            return charBuffer.toString();
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
            return "";
        }
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);


        final View viewById = findViewById(R.id.bk);

        final Handler handler = new Handler() {
            @RequiresApi(api = Build.VERSION_CODES.JELLY_BEAN)
            @Override
            public void handleMessage(Message msg) {
                viewById.setBackground(new BitmapDrawable(bitmap));
            }
        };

        final ByteResponse res = new ByteResponse() {
            @Override
            public void callback(int result, ByteBuffer buf, long len) {

                byte[] bytes = new byte[buf.remaining()];
                buf.get(bytes, 0, bytes.length);
                bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
                handler.sendEmptyMessage(1);
            }
        };



        final Response response = new Response() {
            @Override
            public void callback(int result, String s) {
                Log.i("szb", "callback: "+s);
            }
        };
        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                CurlUtil.getInstance().getBytes("http://c.hiphotos.baidu.com/image/pic/item/4d086e061d950a7be822550e03d162d9f3d3c9e1.jpg", res);

            }
        });
        tv.setText("hello");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
}
