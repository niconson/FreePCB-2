


#pragma once
#include <afxtempl.h>


class RectArray
{
private:
	int m_step;
	CArray<RECT> m_rects;

public:
	RectArray();
	~RectArray();
	void SetStep( int step );
	POINT CorrectAdd( RECT * R );
	void Clear();
};
