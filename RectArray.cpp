


#include "stdafx.h"
#include "RectArray.h"

RectArray::RectArray()
{
	m_step = NM_PER_MM;
	Clear();
}

RectArray::~RectArray()
{
	Clear();
}

void RectArray::SetStep( int step )
{
	m_step = step;
}

void RectArray::Clear()
{
	m_rects.RemoveAll();
}

POINT RectArray::CorrectAdd( RECT * R )
{
	RECT mR;
	int shift = 0;
	int iterator = 0;
	BOOL bInterSection = 0;
	do
	{
		mR = *R;
		if( bInterSection )
		{
			switch( iterator%4 )
			{
			case 0:
				mR.top += shift;
				mR.bottom += shift;
				break;
			case 1:
				mR.left += shift;
				mR.right += shift;
				break;
			case 2:
				mR.top -= shift;
				mR.bottom -= shift;
				break;
			case 3:
				mR.left -= shift;
				mR.right -= shift;
				break;
			}
		}
		bInterSection = 0;
		for( int i=0; i<m_rects.GetSize(); i++ )
		{
			if( RectsIntersection( mR, m_rects.GetAt(i) ) >= 0 )
			{
				bInterSection = 1;
				break;
			}
		}
		iterator++;
		shift += m_step;
	} while( bInterSection );
	POINT RET;
	RET.x = mR.left - R->left;
	RET.y = mR.top - R->top;
	m_rects.Add( mR );
	return RET;
}