#include "Animation.h"
#include "MyMath.h"

AnimationPlayer::AnimationPlayer(int row, int col):
m_currentTime(0),
m_currentFrame(0),
m_pause(false)
{
	m_anim = NULL;
}

AnimationPlayer::~AnimationPlayer()
{
	//if (m_anim)
	//	delete m_anim;
}

void AnimationPlayer::Update(double dt)
{
	if (m_anim == NULL)
		return;
	if (m_pause)
		return;

	if (m_anim->animActive == true) // If animation happens
	{
		// Get Animation current time, m_currentTime.
		//Animation current time increments with dt
		m_currentTime += (float)dt;

		// Get Animation current frame, m_currentFrame.
		m_currentFrame = Math::Min(m_anim->endFrame, m_anim->startFrame + (int)(m_currentTime / m_anim->timePerFrame));

		// Check if m_currentTime is greater than or equal animTime
		if (m_currentFrame >= m_anim->endFrame)
		{
			if (m_anim->repeat)
			{
				m_currentTime = 0.0f;
				m_currentFrame = m_anim->startFrame;
			}
			else
			{
				m_pause = true;
				m_currentTime = 0.0f;
				m_currentFrame = 0;
			}
		}
	}
}