package s.docker.com.jcurl;

import android.content.Context;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;

import java.nio.ByteBuffer;
import java.util.HashMap;
import java.util.Map;

/**
 * Created by chinamall on 2017/12/6.
 */

public class ImageViewAdapter extends BaseAdapter {

    private Context context;
    String[] aa = {
            "http://attachments.gfan.com/forum/attachments2/201302/03/11281446n2st1its4152n5.jpg",
            "http://img2.niutuku.com/desk/1207/1057/ntk133889.jpg",
            "http://imgsrc.baidu.com/image/c0%3Dshijue1%2C0%2C0%2C294%2C40/sign=178dcd40db09b3deffb2ec2ba4d606f4/9d82d158ccbf6c81c1c946c0b63eb13533fa401f.jpg",
            "http://img4.duitang.com/uploads/item/201402/18/20140218234821_8MMwE.jpeg"
    };

    Handler handler=new Handler(){
        @Override
        public void handleMessage(Message msg) {
            super.handleMessage(msg);
//            ImageViewAdapter.this.notifyDataSetChanged();

        }
    };

    public ImageViewAdapter(Context context) {
        this.context = context;
    }

    @Override
    public int getCount() {
        return aa.length;
    }

    @Override
    public Object getItem(int position) {
        return "aaa";
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    Map<ImageView, byte[]> maps = new HashMap<>();

    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        final ImageView imageView = new ImageView(context);
        imageView.setBackgroundColor(android.R.color.darker_gray);
        imageView.setScaleType(ImageView.ScaleType.FIT_CENTER);
        getIamge(position,imageView);
        return imageView;
    }

//    Map<Integer, byte[]> cache = new HashMap<Integer, byte[]>();


    private void getIamge(final int position, final ImageView imageView) {
        if (true) {
//        if (cache.get(position) == null) {

            CurlUtil.getBytes(aa[position], new ByteResponse() {
                @Override
                public void callback(int result, ByteBuffer buf, long len) {
                    Log.i("szb", "callback: "+Thread.currentThread().getName());
                    final byte[] bytes = new byte[(int) len];
                    buf.get(bytes, 0, (int) len);
//                    cache.put(position, bytes);
                    handler.sendEmptyMessage(0);
                    handler.post(new Runnable() {
                        @Override
                        public void run() {
//                            byte[] bytess = cache.get(position);
                            Log.i("szb", "handler: "+Thread.currentThread().getName());
                            imageView.setImageDrawable(new BitmapDrawable(BitmapFactory.decodeByteArray(bytes,0,bytes.length)));
                        }
                    });

                }
            }).execute();
        } else {
//            byte[] bytes = cache.get(position);
//           imageView.setImageDrawable(new BitmapDrawable(BitmapFactory.decodeByteArray(bytes,0,bytes.length)));

        }


    }


}
