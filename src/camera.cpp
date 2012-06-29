/*
 * Camera.cpp
 *
 *  Created on: Jun 24, 2012
 *      Author: Nikhil
 */
#include "camera.h"

void Camera::setup(float cameraZoom)
{
	zoom = cameraZoom;
}

//--------------------------------------------------------------
void Camera::update(ofVec2f playerPosition, int windowWidth, int windowHeight)
{
	pos = playerPosition;

	offset.x = -(pos.x - windowWidth/2);
	offset.y = -(pos.y - windowHeight/2);

	//offset = ofVec2f(0,0);
}

//--------------------------------------------------------------
void Camera::draw()
{
}
