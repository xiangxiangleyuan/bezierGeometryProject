#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "BezierGeom.h"
#include "BezierBsplineGeom.h"
#include<iostream>
#include<windows.h>

class BoneAnimation
{
public:
	BoneAnimation();
	~BoneAnimation();

	static float angleValue0_0;
	static float angleValue0_1;
	static float angleValue0_2;
	static float angleValue0_3;
	static float angleValue0_4;
	static float angleValue0_5;
	static float angleValue0_6;
	static float angleValue0_7;
	static float angleValue0_8;
	static float angleValue0_9;
	static float angleValue0_10;
	static float angleValue0_11;
	static float angleValue0_12;
	static float angleValue0_13;
	static float angleValue0_14;
	static float angleValue0_15;
	static float angleValue0_16;
	static float angleValue0_17;
	static float angleValue0_18;
	static float angleValue0_19;
	static float angleValue0_20;



	static float angleValue1_0;
	static float angleValue1_1;
	static float angleValue1_2;
	static float angleValue1_3;
	static float angleValue1_4;
	static float angleValue1_5;
	static float angleValue1_6;
	static float angleValue1_7;
	static float angleValue1_8;
	static float angleValue1_9;
	static float angleValue1_10;
	static float angleValue1_11;
	static float angleValue1_12;
	static float angleValue1_13;
	static float angleValue1_14;
	static float angleValue1_15;
	static float angleValue1_16;
	static float angleValue1_17;
	static float angleValue1_18;
	static float angleValue1_19;
	static float angleValue1_20;


	static int loopTime;


	//������������
	void fishFinsAnimation();
	//������������
	void backSideFinsBoneAnimation(float* backSideBezierControlPoints, int finsIndex);
	//β����������
	void tailFinsBoneAnimation(int tailFinsIndex, float* moveBeforePoint, float* moveAfterPoint, float space2);

	bool getIntervalTime();
	//����������˹̹�Ż�
	void optimizeBezierBernsteinFactor(float* bezierPoints, int sectionNum, int bezierStep);
	int factrial(int factrialCount);
	//�ռ�����˹̹����
	void collectBernsteinFactor();

	static float mouhBernsteinFactor[5000];
	static float mouhBernsteinFactor2[5000];
	static float bodyBernsteinFactor[5000];
	static float bodyBernsteinFactor2[5000];
	static float tailBernsteinFactor[5000];
	static float backSideFinsBernsteinFactor[5000];
	static float amboFinsFanBoneBernsteinFactor[5000];
	static float eye0BernsteinFactor[5000];
	static float eye1BernsteinFactor[5000];
	//�����ı���������
	static float moustacheBernsteinFactor[5000];

	//���ձ������߶�λ�ƺͷ���
	void moveByBezierPathAndRoll(float* bezierStart3th, float*bezierStart4th, float*bezierStart5th, float* movedPoints);
	//��β�Ĺ�������
	void fishtailingAnima(float* bezierControlPoints_0, float* bezierControlPoints_1,
		float* bezierControlPoints_2, float* bezierControlPoints_3, float* bezierControlPoints_4);
	//����������ת�Ķ���
	void amboFinsRotate();
	//��������һ������
	void fishFinsWingAnima();
	//�����ϵ�����չ����պ϶���
	void fishFinsFanOpenCloseAnima();

private:

};

