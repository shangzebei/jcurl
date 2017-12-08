package s.docker.com.jcurl;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

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
            "http://pic2.ooopic.com/12/42/25/02bOOOPIC95_1024.jpg",
            "http://imgsrc.baidu.com/image/c0%3Dshijue1%2C0%2C0%2C294%2C40/sign=178dcd40db09b3deffb2ec2ba4d606f4/9d82d158ccbf6c81c1c946c0b63eb13533fa401f.jpg",
            "http://img4.duitang.com/uploads/item/201402/18/20140218234821_8MMwE.jpeg",
            "http://pic29.photophoto.cn/20131204/0034034499213463_b.jpg",
            "http://imgsrc.baidu.com/imgad/pic/item/5ab5c9ea15ce36d32ae0f90a31f33a87e950b120.jpg",
            "http://imgsrc.baidu.com/imgad/pic/item/32fa828ba61ea8d3f7c2dc3d9c0a304e251f5822.jpg",
            "http://pic34.photophoto.cn/20150113/0006019095934688_b.jpg",
            "http://www.taopic.com/uploads/allimg/110910/2518-11091022301758.jpg",
            "http://pic.58pic.com/58pic/12/02/13/07p58PICgGD.jpg"
    };

    Handler handler = new Handler();

    public ImageViewAdapter(Context context) {
        this.context = context;
    }

    @Override
    public int getCount() {
        return aa.length;
    }

    @Override
    public Object getItem(int position) {
        return null;
    }

    @Override
    public long getItemId(int position) {
        return position;
    }


    @Override
    public View getView(final int position, View convertView, ViewGroup parent) {
        Log.i("szb", "getView: "+position);
        ViewHolder vh;
        View view;
        if (convertView != null) {
            view = convertView;
            vh = (ViewHolder) convertView.getTag();
        } else {
            vh = new ViewHolder();
            view = LayoutInflater.from(context).inflate(R.layout.activity_main, null);
            vh.imageView = view.findViewById(R.id.imagev);
            vh.imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
            vh.progressBar = view.findViewById(R.id.progressBar);
            view.setTag(vh);

        }
        Bitmap bitmap = hashMap.get(position);
        if (bitmap == null) {
            vh.imageView.setImageBitmap(null);
            getIamge(position, vh.imageView, vh.progressBar);
        } else {
            vh.imageView.setImageBitmap(bitmap);
        }
        return view;
    }

    HashMap<Integer,Bitmap> hashMap=new HashMap<>();

    private void getIamge(final int position, final ImageView imageView, final ProgressBar progressBar) {
        CurlUtil.getBytes(aa[position], new ByteResponse() {
            @Override
            public void callback(int result, ByteBuffer buf, long len) {
                Log.i("szb", "callback: " + Thread.currentThread().getName());
                final byte[] bytes = new byte[(int) len];
                buf.get(bytes, 0, (int) len);
//                    cache.put(position, bytes);
                Bitmap bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
                hashMap.put(position,bitmap);
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        imageView.setImageBitmap(hashMap.get(position));
                        imageView.setTag(position);
                    }
                });

            }
        }).setProgress(new Progress() {
            @Override
            public void progress(long unow, long utotal, final long dnow, final long dtotal) {
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        progressBar.setMax((int) dtotal);
                        progressBar.setProgress((int) dnow);

                    }
                });
            }
        }).execute();


    }

    public class ViewHolder {
        public ImageView imageView;
        public ProgressBar progressBar;
    }


}
