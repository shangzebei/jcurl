package s.docker.com.jcurl;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.nio.ByteBuffer;

public class MainActivity extends AppCompatActivity {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("jcurl");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);

        final ByteResponse res = new ByteResponse() {
            @Override
            public void callback(int result, ByteBuffer buf) {
                byte[] array = buf.array();
                Log.i("szb", "callback: "+ new String(array));
            }
        };
        findViewById(R.id.button).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                CurlUtil.getInstance().getBytes("http://www.hao123.com",res);

            }
        });
        tv.setText("hello");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
}
