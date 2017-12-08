###JCURL的使用
getBytes
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