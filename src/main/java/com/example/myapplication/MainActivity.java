package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.content.pm.ActivityInfo;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.content.Context;

import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.EGLConfig;


class XGLRenderer implements GLSurfaceView.Renderer{


    public void onSurfaceCreated(GL10 gl, EGLConfig config){

        MainActivity.InitOpenGL();
        //gl.glClearColor(0.1f,0.4f,0.6f,1.0f);
    }

    public void onSurfaceChanged(GL10 gl,int width,int height){
        MainActivity.OnViewportChanged(width*0.1f,height*0.1f);
       // MainActivity.OnViewportChanged(height*0.1f,width*0.1f);
        //gl.glViewport(0,0,width,height);
    }

    public void onDrawFrame(GL10 gl){
        //gl.glClear(gl.GL_COLOR_BUFFER_BIT);
        MainActivity.Render();
    }



}


class XGLSurface extends GLSurfaceView{
    XGLRenderer mRenderer;
    boolean isInitSecond=false;
    long initSecond=0;

    public XGLSurface(Context context){
        super(context);
        setEGLContextClientVersion(2);
        mRenderer = new XGLRenderer();
        setRenderer(mRenderer);

    }

    //记录绘制手势的点个数
    int movePointer=0;
    @Override
    public boolean onTouchEvent(MotionEvent event) {

        switch(event.getAction()){

            case MotionEvent.ACTION_DOWN:
                break;
            case MotionEvent.ACTION_UP:

                //抬起后就可以绘制了
                if(movePointer>5&&movePointer<200){
                    //将手势的点转变成空间坐标系的点
                    MainActivity.controlPanelDraw();
                    movePointer=0;
                }else{
                    //清空存储手势坐标点的集合
                    MainActivity.clearControlPanelCollect();
                    movePointer=0;
                }
                //手势已经抬起不再滑动了 开始绘制
                MainActivity.setIsMoveEvent(false);
                //把位移距离设置为初始值
                MainActivity.setFrontMoveCountZero();
                break;
            case MotionEvent.ACTION_MOVE:
                boolean isDrawEnd=MainActivity.getIsDrawEnd();
                if(isDrawEnd){
                    float moveX=event.getX();
                    float moveY=event.getY();
                    MainActivity.incomingMoveCoords(moveX,moveY,movePointer);
                    //还在滑动中不能绘制
                    MainActivity.setIsMoveEvent(true);
                    movePointer++;
                }

                break;
            default:

                break;

        }

        long second=System.currentTimeMillis()/1000;
        if(!isInitSecond){
            initSecond=second;
            isInitSecond=true;
        }

        return true;
    }

    public void surfaceDestroyed(SurfaceHolder holder) {

    }



}


public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    XGLSurface mGLSurface;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        MainActivity.InitAssetManager(getAssets());
        setContentView(R.layout.activity_main);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);//横屏
        mGLSurface = new XGLSurface(getApplication());
        setContentView(mGLSurface);
        playMusic();
        playMusic2();
        //initView();
    }

    public static native void InitAssetManager(AssetManager am);
    public static native void InitOpenGL();
    public static native void OnViewportChanged(float width,float height);
    public static native void Render();
    public static native void incomingMoveCoords(float moveX,float moveY,int movePointer);
    public static native void controlPanelDraw();
    //清空存储手势点的集合
    public static native void clearControlPanelCollect();
    public static native void setIsMoveEvent(boolean isMoveEvent);
    public static native boolean getIsDrawEnd();
    //将前进位位移指针移设置为0
    public static native void setFrontMoveCountZero();

    @Override
    protected void onStop() {
        super.onStop();
        getDelegate().onStop();
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        System.exit(0);
        getDelegate().onDestroy();
        if (mTimer != null) {
            mTimer.cancel();
            mTimer = null;
        }
    }





    private CountDownTimer mTimer;
    private void initView() {
        if (mTimer == null) {
            mTimer = new CountDownTimer((long) (10 * 1000), 1000) {
                //onTick(long millisUntilFinished) 当前任务每完成一次倒计时间隔时间时回调
                @Override
                public void onTick(long millisUntilFinished) {
                    if (!MainActivity.this.isFinishing()) {
                        int remainTime = (int) (millisUntilFinished / 1000L);
                        //Log.e("zpan","===*===remainTime=====" + remainTime);
                    }
                }
                //onFinish() 当前任务完成的时候调用
                @Override
                public void onFinish() {
                    //Log.e("zpan","===*===onFinish=====");
                }
            };
            mTimer.start();
        }
    };

    MediaPlayer mediaPlayer;
    private void playMusic(){

        try {
            mediaPlayer = new MediaPlayer();
            AssetManager assetMg = this.getApplicationContext().getAssets();
            AssetFileDescriptor fileDescriptor = assetMg.openFd("fishmusic0.mp3");
            mediaPlayer.setDataSource(fileDescriptor.getFileDescriptor(), fileDescriptor.getStartOffset(), fileDescriptor.getLength());
            // 设置音频流的类型
            mediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
            // 通过异步的方式装载媒体资源
            mediaPlayer.prepareAsync();
            mediaPlayer.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                @Override
                     public void onPrepared(MediaPlayer mp) {
                        // 装载完毕 开始播放流媒体
                        mediaPlayer.start();
                }});
            // 设置循环播放
//            mediaPlayer.setLooping(false);
            mediaPlayer.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
                      @Override
                    public void onCompletion(MediaPlayer mp) {
                          // 在播放完毕被回调
                          replay();

                   }
            });

            mediaPlayer.setOnErrorListener(new MediaPlayer.OnErrorListener() {
                    @Override
                  public boolean onError(MediaPlayer mp, int what, int extra) {
                        // 如果发生错误，重新播放
                        replay();
                        return false;
                    }
             });

        }catch (Exception e){
            System.out.println("播放MP3失败 。。。。");
            System.out.println(e.toString());
        }

    }

    private void replay(){
        if (mediaPlayer != null && mediaPlayer.isPlaying()) {
            mediaPlayer.seekTo(0);
           return;
        }
        playMusic();
    }
    //////////////////////////////////////////////////////////
    MediaPlayer mediaPlayer2;
    private void playMusic2(){

        try {
            mediaPlayer2 = new MediaPlayer();
            AssetManager assetMg = this.getApplicationContext().getAssets();
            AssetFileDescriptor fileDescriptor = assetMg.openFd("fishmusic1.mp3");
            mediaPlayer2.setDataSource(fileDescriptor.getFileDescriptor(), fileDescriptor.getStartOffset(), fileDescriptor.getLength());
            // 设置音频流的类型
            mediaPlayer2.setAudioStreamType(AudioManager.STREAM_MUSIC);
            // 通过异步的方式装载媒体资源
            mediaPlayer2.prepareAsync();
            mediaPlayer2.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
                @Override
                public void onPrepared(MediaPlayer mp) {
                    // 装载完毕 开始播放流媒体
                    mediaPlayer2.start();
                    mediaPlayer2.setVolume(0.6f,0.6f);
                }});
            // 设置循环播放
//            mediaPlayer.setLooping(false);
            mediaPlayer2.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
                @Override
                public void onCompletion(MediaPlayer mp) {
                    // 在播放完毕被回调
                    replay2();

                }
            });

            mediaPlayer2.setOnErrorListener(new MediaPlayer.OnErrorListener() {
                @Override
                public boolean onError(MediaPlayer mp, int what, int extra) {
                    // 如果发生错误，重新播放
                    replay2();
                    return false;
                }
            });

        }catch (Exception e){
            System.out.println("播放MP3失败 。。。。");
            System.out.println(e.toString());
        }

    }

    private void replay2(){
        if (mediaPlayer2 != null && mediaPlayer2.isPlaying()) {
            mediaPlayer2.seekTo(0);
            return;
        }
        playMusic2();
    }

}




