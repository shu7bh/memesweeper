#include "RectI.h"

RectI::RectI( int left_in,int right_in,int top_in,int bottom_in )
	:
	left( left_in ),
	right( right_in ),
	top( top_in ),
	bottom( bottom_in )
{
}

RectI::RectI( const Vec2& topLeft,const Vec2 & bottomRight )
	:
	RectI( int(topLeft.x), int(bottomRight.x), int(topLeft.y), int(bottomRight.y ))
{
}

RectI::RectI( const Vec2& topLeft,int width,int height )
	:
	RectI( topLeft,topLeft + Vec2( width,height ) )
{
}

bool RectI::IsOverlappingWith( const RectI& other ) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool RectI::IsContainedBy( const RectI & other ) const
{
	return left >= other.left && right <= other.right &&
		top >= other.top && bottom <= other.bottom;
}

RectI RectI::FromCenter( const Vec2 & center,int halfWidth,int halfHeight )
{
	const Vec2 half( halfWidth,halfHeight );
	return RectI( center - half,center + half );
}

RectI RectI::GetExpanded( int offset ) const
{
	return RectI( left - offset,right + offset,top - offset,bottom + offset );
}

Vec2 RectI::GetCenter() const
{
	return Vec2( (left + right) / 2,(top + bottom) / 2 );
}
