#ifndef ANIMATION_H
#define ANIMATION_H

struct Animation
{
	Animation() {}
	Animation(int startFrame, int endFrame, float animationSpeed = 1.0f, bool repeat = true, bool active = true)
	{
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->repeat = repeat;
		this->timePerFrame = animationSpeed / (endFrame - startFrame + 1);
		this->animActive = active;
	}
	void Set(int startFrame, int endFrame, float animationSpeed = 1.0f, bool repeat = true, bool active = true)
	{
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->repeat = repeat;
		this->timePerFrame = animationSpeed / (endFrame - startFrame + 1);
		this->animActive = active;
	}
	void SetSpeed(float animationSpeed)
	{
		this->timePerFrame = animationSpeed / (endFrame - startFrame);
	}
	int startFrame;
	int endFrame;
	bool repeat;
	float timePerFrame;
	bool ended;
	bool animActive;
};

class AnimationPlayer
{
public:
	AnimationPlayer(int row = 0, int col = 0);
	~AnimationPlayer();

	void Update(double dt);

	float m_currentTime;
	int m_currentFrame;
	bool m_pause;
	Animation *m_anim;
};

#endif