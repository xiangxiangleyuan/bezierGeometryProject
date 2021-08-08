#ifdef GL_ES
precision mediump float;
#endif
uniform vec3 colorArray;

varying float nDot;
varying float nPowerFactor;
varying float vWizardGeomIndex;

varying vec3 v_blinePercent;
varying vec3 v_blindex1;
varying vec3 v_blindex2;
void main()
{
   //float colorR=0.8745;
   //float colorG=0.62353;
   //float colorB=0.07843;
   //if(int(v_blindex1[2])==5&&(int(v_blindex2[2])==10||int(v_blindex2[2])==15||int(v_blindex2[2])==20||int(v_blindex2[2])==25||int(v_blindex2[2])==30||int(v_blindex2[2])==35)){
   //  gl_FragColor=vec4(0.0,1.0,colorB,1.0)+vec4(0.0,1.0,colorB,1.0)*nDot;
   //}else{
       if(vWizardGeomIndex==0.0){
        gl_FragColor=vec4(colorArray[0],colorArray[1],colorArray[2],1.0)+vec4(colorArray[0],colorArray[1],colorArray[2],1.0)*nDot*0.3;
       }else{
        gl_FragColor=vec4(colorArray[0],colorArray[1],colorArray[2],1.0)+vec4(colorArray[0],colorArray[1],colorArray[2],1.0)*nDot*0.6;
       }

   //}

}
