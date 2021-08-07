#define _CRT_SECURE_NO_WARNINGS
#include "BoneAnimation.h"

float paiBoneAnim = 3.1415926 / 180.0;
BezierGeom bezierGeomBoneAnimation;
BezierBsplineGeom bezierBsplineGeomBoneAnimation;
//缓存贝塞尔伯恩斯坦因子的集合
float BoneAnimation::mouhBernsteinFactor[5000];
float BoneAnimation::mouhBernsteinFactor2[5000];
float BoneAnimation::bodyBernsteinFactor[5000];
float BoneAnimation::bodyBernsteinFactor2[5000];
float BoneAnimation::tailBernsteinFactor[5000];
float BoneAnimation::backSideFinsBernsteinFactor[5000];
float BoneAnimation::amboFinsFanBoneBernsteinFactor[5000];
float BoneAnimation::eye0BernsteinFactor[5000];
float BoneAnimation::eye1BernsteinFactor[5000];
float BoneAnimation::moustacheBernsteinFactor[5000];

int BoneAnimation::loopTime = 0;


BoneAnimation::BoneAnimation()
{
}

BoneAnimation::~BoneAnimation()
{
}

//鱼鳍摆动角度
float BoneAnimation::angleValue0_0 = 89.5;
float BoneAnimation::angleValue0_1 = 89.5;
float BoneAnimation::angleValue0_2 = 80.0;
float BoneAnimation::angleValue0_3 = 70.0;
float BoneAnimation::angleValue0_4 = 60.0;
float BoneAnimation::angleValue0_5 = 50.0;
float BoneAnimation::angleValue0_6 = 40.0;
float BoneAnimation::angleValue0_7 = 30.0;
float BoneAnimation::angleValue0_8 = 20.0;
float BoneAnimation::angleValue0_9 = 10.0;
float BoneAnimation::angleValue0_10 = 0.0;
float BoneAnimation::angleValue0_11 = -12.0;
float BoneAnimation::angleValue0_12 = -24.0;
float BoneAnimation::angleValue0_13 = -36.0;
float BoneAnimation::angleValue0_14 = -48.0;
float BoneAnimation::angleValue0_15 = -60.0;
float BoneAnimation::angleValue0_16 = -69.0;
float BoneAnimation::angleValue0_17 = -75.0;
float BoneAnimation::angleValue0_18 = -80.0;
float BoneAnimation::angleValue0_19 = -89.5;
float BoneAnimation::angleValue0_20 = -89.5;






float angleV = 0.0;
float BoneAnimation::angleValue1_0 = angleV;
float BoneAnimation::angleValue1_1 = angleV;
float BoneAnimation::angleValue1_2 = angleV;
float BoneAnimation::angleValue1_3 = angleV;
float BoneAnimation::angleValue1_4 = angleV;
float BoneAnimation::angleValue1_5 = angleV;
float BoneAnimation::angleValue1_6 = angleV;
float BoneAnimation::angleValue1_7 = angleV;
float BoneAnimation::angleValue1_8 = angleV;
float BoneAnimation::angleValue1_9 = angleV;
float BoneAnimation::angleValue1_10 = angleV;
float BoneAnimation::angleValue1_11 = angleV;
float BoneAnimation::angleValue1_12 = angleV;
float BoneAnimation::angleValue1_13 = angleV;
float BoneAnimation::angleValue1_14 = angleV;
float BoneAnimation::angleValue1_15 = angleV;
float BoneAnimation::angleValue1_16 = angleV;
float BoneAnimation::angleValue1_17 = angleV;
float BoneAnimation::angleValue1_18 = angleV;
float BoneAnimation::angleValue1_19 = angleV;
float BoneAnimation::angleValue1_20 = angleV;



bool angleAdd = true;
bool fanOpenCloseAngleAdd = true;
bool isMouthOpenCloseLengAdd = true;
float mouthOpenCloseLeng = 0.0;
float fanOpenCloseAngle = 0.0;
float angleFactorValue1 = 0.0;
float paiBoneAnimation = 3.1415926 / 180.0;

//鱼鳍骨骼动画
void BoneAnimation::fishFinsAnimation(){
	//if (loopTime > 2){
	//	//两侧鱼鳍转动
	//	amboFinsRotate();
	//	//鱼鳍像翅膀煽动
	//	fishFinsWingAnima();

	//}
	
	if (loopTime < 3){
		//鱼鳍和鱼鳍上面的扇面张开或闭合
		fishFinsFanOpenCloseAnima();
	}
	

	//嘴巴张开闭合说话的动画
	if (isMouthOpenCloseLengAdd){
		BezierGeom::mouthOpenCloseLeng += 0.0005;
		if (BezierGeom::mouthOpenCloseLeng>0.01){
			isMouthOpenCloseLengAdd = false;
		}
	}
	else{
		BezierGeom::mouthOpenCloseLeng -= 0.0005;
		if (BezierGeom::mouthOpenCloseLeng<0.001){
			isMouthOpenCloseLengAdd = true;
		}
	}


}

//鱼鳍上的扇面展开或闭合动画
void BoneAnimation::fishFinsFanOpenCloseAnima(){

	//鱼鳍上的扇面展开或闭合
	if (fanOpenCloseAngleAdd){
		fanOpenCloseAngle += 0.1;
		if (fanOpenCloseAngle>10.0){
			fanOpenCloseAngleAdd = false;
		}

	}
	else
	{
		//张开的角度
		fanOpenCloseAngle -= 0.3;
		if (fanOpenCloseAngle<0.0){
			fanOpenCloseAngleAdd = true;
			if (loopTime>2){
				fanOpenCloseAngleAdd = false;
				if (fanOpenCloseAngle<0.0){
					fanOpenCloseAngle = 0.0;
				}
			}
		}

	}

	//angleValue0_0 = 89.5 - fanOpenCloseAngle*8.0;//9
	//angleValue0_1 = 89.5 - fanOpenCloseAngle*8.0;//8
	//angleValue0_2 = 80.0 - fanOpenCloseAngle*7.3;//7
	//angleValue0_3 = 70.0 - fanOpenCloseAngle*6.4;//6
	//angleValue0_4 = 60.0 - fanOpenCloseAngle*5.5;//5
	//angleValue0_5 = 50.0 - fanOpenCloseAngle*4.6;//4
	//angleValue0_6 = 40.0 - fanOpenCloseAngle*3.7;//3
	//angleValue0_7 = 30.0 - fanOpenCloseAngle*2.8;//2
	//angleValue0_8 = 20.0 - fanOpenCloseAngle*1.9;//1
	//angleValue0_9 = 10.0 - fanOpenCloseAngle; //0
	//angleValue0_10 = -fanOpenCloseAngle*0.1;//-1
	//angleValue0_11 = -12.0 + fanOpenCloseAngle;//-2
	//angleValue0_12 = -24.0 + fanOpenCloseAngle*2.1;//-3
	//angleValue0_13 = -36.0 + fanOpenCloseAngle*3.2;//-4
	//angleValue0_14 = -48.0 + fanOpenCloseAngle*4.3;//-5
	//angleValue0_15 = -60.0 + fanOpenCloseAngle*5.4;//-6
	//angleValue0_16 = -69.0 + fanOpenCloseAngle*6.2;//-7
	//angleValue0_17 = -70.0 + fanOpenCloseAngle*6.2;//-8
	//angleValue0_18 = -80.0 + fanOpenCloseAngle*7.1;//-9
	//angleValue0_19 = -89.5 + fanOpenCloseAngle*7.95;//-10
	//angleValue0_20 = -89.5 + fanOpenCloseAngle*7.95;//-11


	//由前向后
	angleValue0_0 = 89.5 - fanOpenCloseAngle*15.4;//-53.0
	angleValue0_1 = 89.5 - fanOpenCloseAngle*15.4;//-54.0
	angleValue0_2 = 80.0 - fanOpenCloseAngle*13.5;//-55.0
	angleValue0_3 = 70.0 - fanOpenCloseAngle*12.6;//-56.0
	angleValue0_4 = 60.0 - fanOpenCloseAngle*11.7;//-57.0
	angleValue0_5 = 50.0 - fanOpenCloseAngle*10.8;//-58.0
	angleValue0_6 = 40.0 - fanOpenCloseAngle*9.9;//-59.0
	angleValue0_7 = 30.0 - fanOpenCloseAngle*9.0;//-60.0
	angleValue0_8 = 20.0 - fanOpenCloseAngle*8.1;//-61.0
	angleValue0_9 = 10.0 - fanOpenCloseAngle*7.2; //-62.0
	angleValue0_10 = -fanOpenCloseAngle*6.3;//-63.0
	angleValue0_11 = -12.0 - fanOpenCloseAngle*5.2;//-64.0
	angleValue0_12 = -24.0 - fanOpenCloseAngle*4.1;//-65.0
	angleValue0_13 = -36.0 - fanOpenCloseAngle*3.0;//-66.0
	angleValue0_14 = -48.0 - fanOpenCloseAngle*1.9;//-67.0
	angleValue0_15 = -60.0 - fanOpenCloseAngle*0.8;//-68.0
	angleValue0_16 = -69.0;
	angleValue0_17 = -75.0;//2
	angleValue0_18 = -80.0 + fanOpenCloseAngle*0.9;
	angleValue0_19 = -89.5 + fanOpenCloseAngle*1.75;
	angleValue0_20 = -89.5 + fanOpenCloseAngle*1.75;


	////由前向后
	//angleValue0_0 = 89.5 - fanOpenCloseAngle*11.35;//-24.0
	//angleValue0_1 = 89.5 - fanOpenCloseAngle*11.35;//-24.0
	//angleValue0_2 = 80.0 - fanOpenCloseAngle*10.5;//-25.0
	//angleValue0_3 = 70.0 - fanOpenCloseAngle*9.6;//-26.0
	//angleValue0_4 = 60.0 - fanOpenCloseAngle*8.7;//-27.0
	//angleValue0_5 = 50.0 - fanOpenCloseAngle*7.8;//-28.0
	//angleValue0_6 = 40.0 - fanOpenCloseAngle*6.9;//-29.0
	//angleValue0_7 = 30.0 - fanOpenCloseAngle*6.0;//-30.0
	//angleValue0_8 = 20.0 - fanOpenCloseAngle*5.1;//-31.0
	//angleValue0_9 = 10.0 - fanOpenCloseAngle*4.2; //-32.0
	//angleValue0_10 = -fanOpenCloseAngle*3.3;//-33.0
	//angleValue0_11 = -12.0 - fanOpenCloseAngle*2.2;//-34.0
	//angleValue0_12 = -24.0 - fanOpenCloseAngle*1.1;//-35.0
	//angleValue0_13 = -36.0;
	//angleValue0_14 = -48.0 + fanOpenCloseAngle*1.1;//-37.0
	//angleValue0_15 = -60.0 + fanOpenCloseAngle*2.2;//-38.0
	//angleValue0_16 = -69.0 + fanOpenCloseAngle*3.0;//-39.0
	//angleValue0_17 = -75.0 + fanOpenCloseAngle*3.5;//-40.0
	//angleValue0_18 = -80.0 + fanOpenCloseAngle*3.9;//-41.0
	//angleValue0_19 = -89.5 + fanOpenCloseAngle*4.75;//-42.0
	//angleValue0_20 = -89.5 + fanOpenCloseAngle*4.75;


	////由前向后
	//angleValue0_0 = 89.5 - fanOpenCloseAngle*3.55;//55.0
	//angleValue0_1 = 89.5 - fanOpenCloseAngle*3.55;//54.0
	//angleValue0_2 = 80.0 - fanOpenCloseAngle*2.7;//53.0
	//angleValue0_3 = 70.0 - fanOpenCloseAngle*1.8;//52.0
	//angleValue0_4 = 60.0 - fanOpenCloseAngle*0.9;//51.0
	//angleValue0_5 = 50.0;
	//angleValue0_6 = 40.0 + fanOpenCloseAngle*1.0;//49.0
	//angleValue0_7 = 30.0 + fanOpenCloseAngle*1.8;//48.0
	//angleValue0_8 = 20.0 + fanOpenCloseAngle*2.7;//47.0
	//angleValue0_9 = 10.0 + fanOpenCloseAngle*3.6; //46.0
	//angleValue0_10 = fanOpenCloseAngle*4.5;//45.0
	//angleValue0_11 = -12.0 + fanOpenCloseAngle*5.6;//44.0
	//angleValue0_12 = -24.0 + fanOpenCloseAngle*6.7;//43.0
	//angleValue0_13 = -36.0 + fanOpenCloseAngle*7.8;//42.0
	//angleValue0_14 = -48.0 + fanOpenCloseAngle*8.9;//41.0
	//angleValue0_15 = -60.0 + fanOpenCloseAngle*10.0;//40.0
	//angleValue0_16 = -69.0 + fanOpenCloseAngle*10.8;//39.0
	//angleValue0_17 = -75.0 + fanOpenCloseAngle*11.3;//38.0
	//angleValue0_18 = -80.0 + fanOpenCloseAngle*11.7;//37.0
	//angleValue0_19 = -89.5 + fanOpenCloseAngle*12.55;//36.0
	//angleValue0_20 = -89.5 + fanOpenCloseAngle*12.55;


}

//鱼鳍像翅膀一样煽动的动画
void BoneAnimation::fishFinsWingAnima(){
	
	if (angleAdd){
		angleFactorValue1 += 0.1;
		if (angleFactorValue1 > 70.0){
			angleAdd = false;
		}
	}
	else{
		angleFactorValue1 -= 0.1;
		if (angleFactorValue1 < 1.0){
			angleAdd = true;
		}
	}

	angleV = angleFactorValue1;
	angleValue1_0 = angleV;
	angleValue1_1 = angleV;
	angleValue1_2 = angleV;
	angleValue1_3 = angleV;
	angleValue1_4 = angleV;
	angleValue1_5 = angleV;
	angleValue1_6 = angleV;
	angleValue1_7 = angleV;
	angleValue1_8 = angleV;
	angleValue1_9 = angleV;
	angleValue1_10 = angleV;
	angleValue1_11 = angleV;
	angleValue1_12 = angleV;
	angleValue1_13 = angleV;
	angleValue1_14 = angleV;
	angleValue1_15 = angleV;
	angleValue1_16 = angleV;
	angleValue1_17 = angleV;
	angleValue1_18 = angleV;
}

//背鳍波浪状的动画
float backSideBendAngle = 0.0;
void BoneAnimation::backSideFinsBoneAnimation(float* backSideBezierControlPoints, int finsIndex){

	{
		backSideBezierControlPoints[9] = backSideBezierControlPoints[9] - 0.1*BezierGeom::innerVect[0];
		backSideBezierControlPoints[10] = backSideBezierControlPoints[10] - 0.1*BezierGeom::innerVect[1];
		backSideBezierControlPoints[11] = backSideBezierControlPoints[11] - 0.1*BezierGeom::innerVect[2];
	}

	backSideBendAngle += 0.08;
	if (backSideBendAngle>360.0){
		backSideBendAngle = 0.0;
	}


	float currAngle = backSideBendAngle - finsIndex*10.0;
	if (currAngle>360.0){
		currAngle = 360.0 - (currAngle - 360.0);
	}
	else if (currAngle<0.0){
		currAngle = -currAngle;
	}
	float moveLeng = cos(currAngle*paiBoneAnim)*0.25;
	if (moveLeng<0.0){
		moveLeng = -moveLeng;
		if (moveLeng<0.12){
			backSideBezierControlPoints[9] = backSideBezierControlPoints[9] + moveLeng*BezierGeom::leftVect[0];
			backSideBezierControlPoints[10] = backSideBezierControlPoints[10] + moveLeng*BezierGeom::leftVect[1];
			backSideBezierControlPoints[11] = backSideBezierControlPoints[11] + moveLeng*BezierGeom::leftVect[2];
		}
		else{
			float upLeng = moveLeng - 0.12;
			backSideBezierControlPoints[9] = backSideBezierControlPoints[9] + 0.12*BezierGeom::leftVect[0] - upLeng*BezierGeom::upVect[0];
			backSideBezierControlPoints[10] = backSideBezierControlPoints[10] + 0.12*BezierGeom::leftVect[1] - upLeng*BezierGeom::upVect[1];
			backSideBezierControlPoints[11] = backSideBezierControlPoints[11] + 0.12*BezierGeom::leftVect[2] - upLeng*BezierGeom::upVect[2];
		}
	}
	else{
		if (moveLeng<0.12){
			backSideBezierControlPoints[9] = backSideBezierControlPoints[9] - moveLeng*BezierGeom::leftVect[0];
			backSideBezierControlPoints[10] = backSideBezierControlPoints[10] - moveLeng*BezierGeom::leftVect[1];
			backSideBezierControlPoints[11] = backSideBezierControlPoints[11] - moveLeng*BezierGeom::leftVect[2];
		}
		else{
			float upLeng = moveLeng - 0.12;
			backSideBezierControlPoints[9] = backSideBezierControlPoints[9] - 0.12*BezierGeom::leftVect[0] - upLeng*BezierGeom::upVect[0];
			backSideBezierControlPoints[10] = backSideBezierControlPoints[10] - 0.12*BezierGeom::leftVect[1] - upLeng*BezierGeom::upVect[1];
			backSideBezierControlPoints[11] = backSideBezierControlPoints[11] - 0.12*BezierGeom::leftVect[2] - upLeng*BezierGeom::upVect[2];
		}
	}

}

//尾鳍波浪状的动画
float tailFinsBoneAngle = 0.0;
void BoneAnimation::tailFinsBoneAnimation(int tailFinsIndex, float* moveBeforePoint, float* moveAfterPoint, float space){
	//波浪的大小
	space *= 0.1;
	//波浪的快慢
	tailFinsBoneAngle += 0.8;
	if (tailFinsBoneAngle>360.0){
		tailFinsBoneAngle = 0.0;
	}
	//也是波浪的大小
	float currAngle = tailFinsBoneAngle - tailFinsIndex*40.0;
	if (currAngle>360.0){
		currAngle = 360.0 - (currAngle - 360.0);
	}
	else if (currAngle<0.0){
		currAngle = -currAngle;
	}

	float moveLeng = cos(currAngle*paiBoneAnim)*space;
	if (moveLeng<0.0){
		moveLeng = -moveLeng;
		if (moveLeng<space){
			moveAfterPoint[0] = moveBeforePoint[0] + moveLeng*BezierGeom::leftVect[0];
			moveAfterPoint[1] = moveBeforePoint[1] + moveLeng*BezierGeom::leftVect[1];
			moveAfterPoint[2] = moveBeforePoint[2] + moveLeng*BezierGeom::leftVect[2];
		}
		else{
			float upLeng = moveLeng - space;
			moveAfterPoint[0] = moveBeforePoint[0] + space*BezierGeom::leftVect[0] + upLeng*BezierGeom::innerVect[0];
			moveAfterPoint[1] = moveBeforePoint[1] + space*BezierGeom::leftVect[1] + upLeng*BezierGeom::innerVect[1];
			moveAfterPoint[2] = moveBeforePoint[2] + space*BezierGeom::leftVect[2] + upLeng*BezierGeom::innerVect[2];
		}
	}
	else{
		if (moveLeng<space){
			moveAfterPoint[0] = moveBeforePoint[0] - moveLeng*BezierGeom::leftVect[0];
			moveAfterPoint[1] = moveBeforePoint[1] - moveLeng*BezierGeom::leftVect[1];
			moveAfterPoint[2] = moveBeforePoint[2] - moveLeng*BezierGeom::leftVect[2];
		}
		else{
			float upLeng = moveLeng - space;
			moveAfterPoint[0] = moveBeforePoint[0] - space*BezierGeom::leftVect[0] + upLeng*BezierGeom::innerVect[0];
			moveAfterPoint[1] = moveBeforePoint[1] - space*BezierGeom::leftVect[1] + upLeng*BezierGeom::innerVect[1];
			moveAfterPoint[2] = moveBeforePoint[2] - space*BezierGeom::leftVect[2] + upLeng*BezierGeom::innerVect[2];
		}
	}

}



int initSecond = 0;
bool isInitSecond = false;
bool BoneAnimation::getIntervalTime(){
	time_t timer;
	time(&timer);
	tm* t_tm = localtime(&timer);
	//cout << "NOW IS : " << t_tm->tm_year + 1900 << "/" << t_tm->tm_mon + 1 << "/" << t_tm->tm_mday << " " << t_tm->tm_hour << ":" << t_tm->tm_min << ":" << t_tm->tm_sec << endl;
	if (!isInitSecond){
		initSecond = t_tm->tm_sec;
		isInitSecond = true;
	}

	int intervalSecond = t_tm->tm_sec - initSecond;
	if (intervalSecond>10){
		return true;
	}
	else{
		return false;
	}
}




void BoneAnimation::optimizeBezierBernsteinFactor(float* bernsteinCollection, int sectionNum, int bezierStep)
{

	int sectionNumber = sectionNum - 1;
	float factResArr[100];//介乘结果的集合
	for (int i = 0; i <= sectionNumber; i++){	//求0到n的阶乘
		factResArr[i] = factrial(i);
	}
	//循环每个点
	for (int i = 0; i <= bezierStep; i++)
	{
		//在bezier曲线上的节点的百分数
		float bezierPercentFractor = float(i) / float(bezierStep);
		if (bezierPercentFractor > 1)
		{
			bezierPercentFractor = 1;
		}

		float tka[100];
		float otka[100];
		for (int j = 0; j <= sectionNumber; j++)
		{
			tka[j] = (float)pow(bezierPercentFractor, j); //计算t的j次幂
			otka[j] = (float)pow(1.0 - bezierPercentFractor, j); //计算1-t的j次幂
		}

		float xf = 0.0;
		float yf = 0.0;
		float zf = 0.0;
		for (int k = 0; k <= sectionNumber; k++)
		{
			float xs = (factResArr[sectionNumber] / (factResArr[k] * factResArr[sectionNumber - k])) * tka[k] * otka[sectionNumber - k];
			bernsteinCollection[i*(sectionNumber + 1) + k] = xs;
		}

	}

}

//介乘
int BoneAnimation::factrial(int factrialCount)
{
	int factrialResult = 1;	//声明一个long型的变量
	if (factrialCount == 0)			//0的阶乘为1
	{
		return 1;
	}

	for (int i = 2; i <= factrialCount; i++){	//求大于等于2的数的阶乘
		factrialResult = factrialResult*i;
	}

	return factrialResult;	//返回结果

}


//收集贝塞尔伯恩斯坦因子的函数
void BoneAnimation::collectBernsteinFactor(){
	
	optimizeBezierBernsteinFactor(mouhBernsteinFactor, BezierGeom::mouthSectionNum, BezierGeom::mouthBezierStep);
	optimizeBezierBernsteinFactor(mouhBernsteinFactor2, BezierGeom::mouthSectionNum2, BezierGeom::mouthBezierStep2);
	optimizeBezierBernsteinFactor(bodyBernsteinFactor, BezierGeom::bodySectionNum, BezierGeom::bodyBezierStep);
	optimizeBezierBernsteinFactor(tailBernsteinFactor, BezierGeom::tailSectionNum, BezierGeom::tailBezierStep);
	optimizeBezierBernsteinFactor(backSideFinsBernsteinFactor, BezierGeom::backSideFinsSectionNum, BezierGeom::backSideFinsBezierStep);
	optimizeBezierBernsteinFactor(amboFinsFanBoneBernsteinFactor, BezierGeom::amboFinsFanBoneSectionNum, BezierGeom::amboFinsFanBoneBezierStep);
	optimizeBezierBernsteinFactor(eye0BernsteinFactor, BezierGeom::eye0SectionNum, BezierGeom::eye0BezierStep);
	optimizeBezierBernsteinFactor(eye1BernsteinFactor, BezierGeom::eye1SectionNum, BezierGeom::eye1BezierStep);
	optimizeBezierBernsteinFactor(moustacheBernsteinFactor, BezierGeom::moustacheSectionNum, BezierGeom::moustacheBezierStep);
	optimizeBezierBernsteinFactor(bodyBernsteinFactor2, BezierGeom::bodySectionNum2, BezierGeom::bodyBezierStep2);


}

float bezierControlPoints[] = { -0.5, 0.0, -1.0, 0.0, 0.0, 0.7, 0.5, 0.0, -1.0 };
float bezierPath[3000];
int currBezierValue = 0;
int bezierPathStep = 900;
bool isAdd = true;
void BoneAnimation::moveByBezierPathAndRoll(float* bezierStart3th, float*bezierStart4th, float*bezierStart5th, float* movedPoints){
	
	bezierBsplineGeomBoneAnimation.makeUpBezierLine(bezierPath, bezierControlPoints, 3, bezierPathStep);
	bezierBsplineGeomBoneAnimation.drawPointLineColorSize(bezierPath, 1.0, 0.0, 0.5, 3.0, bezierPathStep);

	{
		float currPathX = bezierPath[currBezierValue * 3];
		float currPathY = bezierPath[currBezierValue * 3 + 1];
		float currPathZ = bezierPath[currBezierValue * 3 + 2];
		float fishX = bezierStart4th[0];
		float fishY = bezierStart4th[1];
		float fishZ = bezierStart4th[2];
		float moveLeng = sqrt((currPathX - fishX)*(currPathX - fishX) + (currPathY - fishY)*(currPathY - fishY) + 
			(currPathZ - fishZ)*(currPathZ - fishZ));
		float moveVect[] = { currPathX - fishX, currPathY - fishY, currPathZ - fishZ};
		//bezierGeomBoneAnimation.normalize(moveVect);

		float headLeftVect[3];
		bezierGeomBoneAnimation.getVerticalVect(BezierGeom::upVect[0],BezierGeom::upVect[1],BezierGeom::upVect[2],
			moveVect[0], moveVect[1], moveVect[2], headLeftVect);
		bezierGeomBoneAnimation.normalize(headLeftVect);
		
		bezierStart3th[0] = bezierStart4th[0] + 0.025*headLeftVect[0]/* - 0.0001*BezierGeom::innerVect[0]*/;
		bezierStart3th[1] = bezierStart4th[1] + 0.025*headLeftVect[1] /*- 0.0001*BezierGeom::innerVect[1]*/;
		bezierStart3th[2] = bezierStart4th[2] + 0.025*headLeftVect[2]/* - 0.0001*BezierGeom::innerVect[2]*/;
		bezierStart5th[0] = bezierStart4th[0] - 0.025*headLeftVect[0]/* - 0.0001*BezierGeom::innerVect[0]*/;
		bezierStart5th[1] = bezierStart4th[1] - 0.025*headLeftVect[1]/* - 0.0001*BezierGeom::innerVect[1]*/;
		bezierStart5th[2] = bezierStart4th[2] - 0.025*headLeftVect[2]/* - 0.0001*BezierGeom::innerVect[2]*/;

		bezierGeomBoneAnimation.normalize(moveVect);
		movedPoints[0] = bezierStart3th[0] + moveLeng*moveVect[0];
		movedPoints[1] = bezierStart3th[1] + moveLeng*moveVect[1];
		movedPoints[2] = bezierStart3th[2] + moveLeng*moveVect[2];
		movedPoints[3] = bezierStart4th[0] + moveLeng*moveVect[0];
		movedPoints[4] = bezierStart4th[1] + moveLeng*moveVect[1];
		movedPoints[5] = bezierStart4th[2] + moveLeng*moveVect[2];
		movedPoints[6] = bezierStart5th[0] + moveLeng*moveVect[0];
		movedPoints[7] = bezierStart5th[1] + moveLeng*moveVect[1];
		movedPoints[8] = bezierStart5th[2] + moveLeng*moveVect[2];

	}
	if (isAdd){
		currBezierValue++;
	}
	else{
		currBezierValue--;
	}
	if (currBezierValue>895){
		isAdd = false;
	}


	/*float moveVect[3] = {0.0,0.0,0.5};
	bezierGeomBoneAnimation.normalize(moveVect);
	float speed = 0.001;
	movedPoints[0] = bezierStart3th[0] + speed*moveVect[0];
	movedPoints[1] = bezierStart3th[1] + speed*moveVect[1];
	movedPoints[2] = bezierStart3th[2] + speed*moveVect[2];
	movedPoints[3] = bezierStart4th[0] + speed*moveVect[0];
	movedPoints[4] = bezierStart4th[1] + speed*moveVect[1];
	movedPoints[5] = bezierStart4th[2] + speed*moveVect[2];
	movedPoints[6] = bezierStart5th[0] + speed*moveVect[0];
	movedPoints[7] = bezierStart5th[1] + speed*moveVect[1];
	movedPoints[8] = bezierStart5th[2] + speed*moveVect[2];*/

}


//摆尾动画
bool fishtailingAdd = true;
float  fishtailingLeng = 0.0;
void BoneAnimation::fishtailingAnima(float* bezierControlPoints_0, float* bezierControlPoints_1,
	float* bezierControlPoints_2, float* bezierControlPoints_3, float* bezierControlPoints_4){


	if (fishtailingAdd){
		fishtailingLeng += 0.007;
		if (fishtailingLeng>0.1){
			fishtailingAdd = false;
		}
	}
	else{
		fishtailingLeng -= 0.007;
		if (fishtailingLeng<-0.1){
			fishtailingAdd = true;
		}
	}

	bezierControlPoints_0[15] += fishtailingLeng*BezierGeom::leftVect[0];
	bezierControlPoints_0[16] += fishtailingLeng*BezierGeom::leftVect[1];
	bezierControlPoints_0[17] += fishtailingLeng*BezierGeom::leftVect[2];
	bezierControlPoints_1[15] += fishtailingLeng*BezierGeom::leftVect[0];
	bezierControlPoints_1[16] += fishtailingLeng*BezierGeom::leftVect[1];
	bezierControlPoints_1[17] += fishtailingLeng*BezierGeom::leftVect[2];
	bezierControlPoints_2[12] += fishtailingLeng*BezierGeom::leftVect[0];
	bezierControlPoints_2[13] += fishtailingLeng*BezierGeom::leftVect[1];
	bezierControlPoints_2[14] += fishtailingLeng*BezierGeom::leftVect[2];
	bezierControlPoints_3[12] += fishtailingLeng*BezierGeom::leftVect[0];
	bezierControlPoints_3[13] += fishtailingLeng*BezierGeom::leftVect[1];
	bezierControlPoints_3[14] += fishtailingLeng*BezierGeom::leftVect[2];
	bezierControlPoints_4[12] += fishtailingLeng*BezierGeom::leftVect[0];
	bezierControlPoints_4[13] += fishtailingLeng*BezierGeom::leftVect[1];
	bezierControlPoints_4[14] += fishtailingLeng*BezierGeom::leftVect[2];

}


//两侧鱼鳍翻转的动画
bool isAmmboFinsRoateAdd = true;
void BoneAnimation::amboFinsRotate(){

	if (isAmmboFinsRoateAdd){
		BezierGeom::amboFinsRoateAngle += 0.2;
		if (BezierGeom::amboFinsRoateAngle>89.0){
			isAmmboFinsRoateAdd = false;
		}
	}
	else{
		BezierGeom::amboFinsRoateAngle -= 0.2;
		if (BezierGeom::amboFinsRoateAngle<1.0){
			isAmmboFinsRoateAdd = true;
		}
	}



}


