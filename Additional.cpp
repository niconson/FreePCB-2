#include "stdafx.h"

void AlignGroupByRatline( CFreePcbDoc * doc )
{
	if( doc->m_vis[LAY_RAT_LINE] == 0 )
		return;

	enum{ VALIDATE=1 };
	CPoint P45(1,1);
	int STEP = 0;
	do {
		int min_dist = INT_MAX;
		CPoint BestPoint(0, 0);
		for (cpart* p = doc->m_plist->GetFirstPart(); p; p = doc->m_plist->GetNextPart(p))
		{
			if (p->shape && p->selected)
			{
				int dist = Distance(doc->m_view->m_last_cursor_point.x, doc->m_view->m_last_cursor_point.y, p->x, p->y);
				if (dist <= min_dist)
				{
					for (int ip = 0; ip < p->shape->GetNumPins(); ip++)
					{
						CPoint pinP = doc->m_plist->GetPinPoint(p, ip, p->side, p->angle);
						dist = Distance(doc->m_view->m_last_cursor_point.x, doc->m_view->m_last_cursor_point.y, pinP.x, pinP.y);
						{
							CPoint P = doc->m_plist->AlignByRatline(p, ip, VALIDATE, P45);
							if (P.x || P.y)
							{
								if (P.x)
									if (BestPoint.x == 0 || dist < min_dist)
										BestPoint.x = P.x;
								if (P.y)
									if (BestPoint.y == 0 || dist < min_dist)
										BestPoint.y = P.y;
								min_dist = dist + 1;
							}
						}
					}
				}
			}
		}
		if (BestPoint.x || BestPoint.y)
			doc->m_view->MoveGroup(BestPoint.x, BestPoint.y, 0);
		if (BestPoint.x == 0 || BestPoint.y == 0)
			P45 = BestPoint;
		else
			break;
		STEP++;
	}while (STEP < 2);
}