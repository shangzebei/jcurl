## JCURL的使用支持http和https

项目编译需要swig的支持，需要配置环境变量。

### 简单请求,支持GET,POST,PUT,DELETE等方法
```java
CurlUtil.get("http://www.baidu.com", new Response() {
    @Override
    public void callback(int result, String s) {
        Log.i("szb", "callback: " + s);
    }
}).execute();
```
#### get方法加参数
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
#### post方法加参数
```java
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


#### post body体方式
```java
CurlUtil.post("http://192.168.0.164:8080/show",new Response(){
            @Override
            public void callback(int result, String s) {
                Log.i("szb", "callback: "+s);
            }
}).setParamData("{\"data\":\"jjjj\"}").execute();
```


#### 设置header参数
```java
CurlUtil.get("http://192.168.0.88:15000/v1/get_all_user", new Response() {
            @Override
            public void callback(int result, String s) {
                Log.i("szb", "callback: " + s);
            }
}).setHeader("X-Auth-Token:admin@localhost:e58e67dba304027768c62c1160daeb3e")
  .setHeader("Accept: application/json")
  .execute();
```
####添加进度条
```
public CurlUtil setProgress(Progress progress);//任何方法都可以添加就可以实现进度条
```
#### 下载大文件加进度条
```java
CurlUtil.getFile("https://wdl1.cache.wps.cn/wps/download/W.P.S.6930.19.552.exe",
        this.getFilesDir().getAbsolutePath()+"/wps.exe")
.setProgress(new Progress(){
    @Override
    public void progress(long unow, long utotal, long dnow, long dtotal) {
        Log.i("szb", "progress: "+dnow+"::"+dtotal);
    }
}).execute();
```


#### 获取二进制流如图片
- getBytes(String url, ByteResponse response)
```java
CurlUtil.getBytes(aa[position], new ByteResponse() {
      @Override
      public void callback(int result, ByteBuffer buf, long len) {
          Log.i("szb", "callback: " + Thread.currentThread().getName());
          final byte[] bytes = new byte[(int) len];
          buf.get(bytes, 0, (int) len);
                cache.put(position, bytes);//获取bytes
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
  }).setProgress(new Progress() { //进度条
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

### 带参多文件上传 （不同的key）
```java
ParamMap paramMap = new ParamMap();
paramMap.set("file","data/data/com.my.jcurl/lib/libjcurl.so");
paramMap.set("files","data/data/com.my.jcurl/lib/kkk.so");
CurlUtil.uploadMultiFile("http://192.168.0.164:8080/file",
        paramMap,new Response(){
            @Override
            public void callback(int result, String s) {
                Log.i("szb", "callback: "+s);

            }
        }).execute();
```
### 带参文件上传加进度条需要（不同的key）
```java
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
```
### 带参批量上传
```java
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
```