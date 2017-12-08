###JCURL的使用
-get获取json
```java
ParamMap map = new ParamMap();
map.set("local", "zh");
CurlUtil.get("http://192.168.0.88:15000/v1/local", new Response() {
    @Override
    public void callback(int result, String s) {
        Log.i("szb", "callback: " + s);
    }
}).setParam(map).execute();
```
post方法
```
ParamMap map = new ParamMap();
map.set("username", "admin@localhost");
map.set("password", "123456");
CurlUtil.post("http://192.168.0.88:15000/v1/login", new Response() {
    @Override
    public void callback(int result, String s) {
        Log.i("szb", "callback: " + s);
    }
}).setParam(map).execute();
```
- 获取二进制流如图片
- getBytes(String url, ByteResponse response)
```java
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
```