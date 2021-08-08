attribute vec3 blinePoints1;
attribute vec3 blinePoints2;
attribute vec3 blinePoints3;
attribute vec3 blinePoints4;
attribute vec3 blindex1;
attribute vec3 blindex2;
attribute vec3 blinePercent;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 normalMatrix;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform int wizardGeomIndex;
varying vec3 v_Normal;
varying vec3 v_blinePercent;
varying vec3 v_blindex1;
varying vec3 v_blindex2;
varying float nDot;
varying float nPowerFactor;
varying float vWizardGeomIndex;


void main()
{
    v_blindex1=blindex1;
    v_blindex2=blindex2;
    v_blinePercent=blinePercent;
    float f1 = blindex1[0];
	float f2 = blindex1[1];
	float dex = blindex1[2];
	float f3 = blindex2[0];
	float f4 = blindex2[1];
    float x = f1 * float(blinePoints1[0]) + f2 * float(blinePoints2[0]) + f3 * float(blinePoints3[0]) + f4 * float(blinePoints4[0]);
    float y = f1 * float(blinePoints1[1]) + f2 * float(blinePoints2[1]) + f3 * float(blinePoints3[1]) + f4 * float(blinePoints4[1]);
    float z = f1 * float(blinePoints1[2]) + f2 * float(blinePoints2[2]) + f3 * float(blinePoints3[2]) + f4 * float(blinePoints4[2]);

    float normalX=blinePoints1[0]-2.0*blinePoints2[0]+blinePoints3[0]+blinePercent[0]*(3.0*blinePoints2[0]-blinePoints1[0]-3.0*blinePoints3[0]+blinePoints4[0]);
    float normalY=blinePoints1[1]-2.0*blinePoints2[1]+blinePoints3[1]+blinePercent[0]*(3.0*blinePoints2[1]-blinePoints1[1]-3.0*blinePoints3[1]+blinePoints4[1]);
    float normalZ=blinePoints1[2]-2.0*blinePoints2[2]+blinePoints3[2]+blinePercent[0]*(3.0*blinePoints2[2]-blinePoints1[2]-3.0*blinePoints3[2]+blinePoints4[2]);
    //v_Normal=normalize((normalMatrix*vec4(finalNormX,finalNormY,finalNormZ,1.0)).xyz);
    v_Normal=normalize(vec3(normalX,normalY,normalZ));
    //计算从表面点到光源位置的向量vp
    //vec3 vp= normalize(vec4(ModelMatrix*(vec4(lightPosition.x, lightPosition.y, lightPosition.z,1.0))).xyz-vec4(ModelMatrix*vec4(x,y,z,1.0)).xyz);
    vec3 vp= normalize(vec3(lightPosition.x, lightPosition.y, lightPosition.z)-vec3(x,y,z));
    nDot=max(0.0,dot(v_Normal,vp)); 	//求法向量与vp的点积与0的最大值
    ////////////////////////////////////////////////////////
    //计算从表面点到摄像机的向量
    //vec3 eye= normalize(cameraPosition-vec3(x,y,z));
    //vec3 halfVector=normalize(vp+eye);	//求视线与光线的半向量
    //float shininess=10.0;				//粗糙度，越小越光滑
    //float nDotViewHalfVector=dot(v_Normal,normalize(halfVector));	//法线与半向量的点积
    //float powerFactor=max(0.0,pow(nDotViewHalfVector,shininess)); 	//镜面反射光强度因子
    //nPowerFactor=powerFactor;
    ////////////////////////////////////////////////////////
    vWizardGeomIndex=float(wizardGeomIndex);
    vec4 position = vec4(x,y,z,1.0);
    gl_Position = ProjectionMatrix*ViewMatrix*ModelMatrix*position;
    gl_PointSize = 2.3;
}
