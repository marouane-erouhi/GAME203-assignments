#include "Body.h" 
#include <iostream>
#include <SDL_image.h>

using namespace MATH;

Body::Body(char* imageName_, MATH::Vec3 pos_, int tags_) {
	SetImage(imageName_);//Load .png
	SetPosition(pos_);//Set initial position
	tags = tags_;
	//Find out the size/dimension from the image file
	length = getImage()->w;
	width = getImage()->h;
	radius = length / 2;
	color.r = 255; color.g = 0; color.b = 55; color.a = 255;//default color
}

Body::Body(char* imageName_, float radius_, Vec3 pos_){//Circle
	SetImage(imageName_);
	SetPosition(pos_);
	radius = radius_;
}

Body::Body(char* imageName_, float length_, float width_, MATH::Vec3 pos_) {//Rectangle
	SetImage(imageName_);
	SetPosition(pos_);
	length = length_;
	width = width_;
}

Body::Body(char* imageName_, float mass_, Vec3 pos_, Vec3 vel_, Vec3 accel_) {
	SetImage(imageName_);
	SetPosition(pos_);
	
	mass = mass_;

	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;

	accel.x = accel_.x;
	accel.y = accel_.y;
	accel.z = accel_.z;
}

Body::~Body() {
	OnDestroy();
} /// There is really nothing to do here - yet!

void Body::OnDestroy() {
	if (bodyImage) delete bodyImage;
	bodyImage = nullptr;
}

void Body::SetImage(const char* imageName_) {
	bodyImage = IMG_Load(imageName_);
	if (bodyImage == nullptr) {
		/// What should we do?
		std::cout << "Error cannot load image" << std::endl;
	}
}

void Body::SetPosition(Vec3 pos_) {
	pos.x = pos_.x;
	pos.y = pos_.y;
	pos.z = pos_.z;
}

void Body::SetVelocity(Vec3 vel_) {
	vel.x = vel_.x;
	vel.y = vel_.y;
	vel.z = vel_.z;
}

void Body::SetColor(int r, int g, int b, int a) {
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
}

void Body::Update(const float deltaTime) {
	if (OutOfBounds())	alive = false;//kill when out of bounds

	pos.x += (vel.x * deltaTime) + (0.5f * accel.x * (deltaTime * deltaTime));
	pos.y += (vel.y * deltaTime) + (0.5f * accel.y * (deltaTime * deltaTime));
	pos.z += (vel.z * deltaTime) + (0.5f * accel.z * (deltaTime * deltaTime));

	vel.x += accel.x * deltaTime;
	vel.y += accel.y * deltaTime;
	vel.z += accel.z * deltaTime;

	/// Assuming all acceleration comes from an applied force - maybe not in the future - gravity!!
	accel.x = 0.0f;
	accel.y = 0.0f;
	accel.z = 0.0f;

}

void Body::Render(MATH::Matrix4 projectionMatrix, SDL_Surface* screenSurface_) {
	Vec3 screenCoords = projectionMatrix * pos;
	SDL_Rect imageRectangle_;
	imageRectangle_.h = getImage()->h;
	imageRectangle_.w = getImage()->w;
	imageRectangle_.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning (int = float)
	imageRectangle_.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning

	SDL_BlitSurface(getImage(), nullptr, screenSurface_, &imageRectangle_);
}

void Body::Render(MATH::Matrix4 projectionMatrix, SDL_Renderer * renderer_) {
	Vec3 screenCoords = projectionMatrix * pos;
	SDL_Rect imageRectangle_;
	imageRectangle_.h = getImage()->h;
	imageRectangle_.w = getImage()->w;
	imageRectangle_.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning (int = float)
	imageRectangle_.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning


	SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);//set shape color

	if (tags == 2) {//circle
		for (int w = 0; w < radius * 2; w++) {
			for (int h = 0; h < radius * 2; h++) {
				int dx = radius - w; // horizontal offset
				int dy = radius - h; // vertical offset
				if ((dx*dx + dy * dy) <= (radius * radius)) {
					SDL_RenderDrawPoint(renderer_, screenCoords.x + dx, screenCoords.y + dy);
				}
			}
		}
	}
	else{//rect
		SDL_RenderFillRect(renderer_, &imageRectangle_);//draw

	}

}

int Body::GetTags() {
	return tags;
}

void Body::ApplyForce(Vec3 force) {
	accel.x = force.x / mass;
	accel.y = force.y / mass;
	accel.z = force.z / mass;
}


SDL_Surface* Body::getImage() {
	return bodyImage;
}

bool Body::OutOfBounds() {
	if (pos.y < -350)	return true;
	return false;
}
