// Fill out your copyright notice in the Description page of Project Settings.

#include "PathfinderLib.h"
#include <string>
#include <stdio.h>
#include <iostream>
DEFINE_LOG_CATEGORY(PathfinderLog)
//Happy Message
FTrajectoryStruct UPathfinderLib::GetPoints(TArray<FTransform> input)
{
	int POINT_LENGTH = input.Num();
	Waypoint *points = (Waypoint*)malloc(sizeof(Waypoint) * POINT_LENGTH);
	for (int i = 0; i < POINT_LENGTH; i++) {

		double conX = input[i].GetLocation().X / 100;
		double conY = input[i].GetLocation().Y / 100;
		double conRot = (double)input[i].GetRotation().Rotator().Yaw;

		if (conRot < 0) {
			conRot += 360; 
		}

		UE_LOG(PathfinderLog, Log, TEXT("Rot %d %f"), i, conRot);
		Waypoint point = { conX, conY , d2r(conRot) };      // Waypoint @ x=-4, y=-1, exit angle=45 degrees
		points[i] = point;
	}


	TrajectoryCandidate candidate;
	pathfinder_prepare(points, POINT_LENGTH, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_HIGH, 0.01, 15.0, 10.0, 60.0, &candidate);

	int length = candidate.length;
	Segment *trajectory = (Segment*)malloc(length * sizeof(Segment));

	pathfinder_generate(&candidate, trajectory);

	Segment *leftTrajectory = (Segment*)malloc(sizeof(Segment) * length);
	Segment *rightTrajectory = (Segment*)malloc(sizeof(Segment) * length);

	double wheelbase_width = 1.5;

	pathfinder_modify_tank(trajectory, length, leftTrajectory, rightTrajectory, wheelbase_width);

	// Do something with the trajectories...


	TArray<FVector2D> _botpoints;

	for (int i = 0; i < length; i++) {
		_botpoints.Add(FVector2D(trajectory[i].x * 100, trajectory[i].y * 100));
	}

	TArray<FVector2D> _leftpoints;

	for (int i = 0; i < length; i++) {
		_leftpoints.Add(FVector2D(leftTrajectory[i].x * 100, leftTrajectory[i].y * 100));
	}

	TArray<FVector2D> _rightpoints;

	for (int i = 0; i < length; i++) {
		_rightpoints.Add(FVector2D(rightTrajectory[i].x * 100, rightTrajectory[i].y * 100));
	}

	free(leftTrajectory);
	free(rightTrajectory);
	free(trajectory);

	FTrajectoryStruct returnData;
	returnData.BotTrajectory = _botpoints;
	returnData.LeftTrajectory = _leftpoints;
	returnData.RightTrajectory = _rightpoints;

	return returnData;
}
