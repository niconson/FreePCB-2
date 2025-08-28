#include "stdafx.h"
#include "RectArray.h"
int page;
//======================================================================================
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//======================================================================================
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
void SavePcbViewWriteSegment(CStdioFile* f, int x, int y, int x2, int y2, int w, int L)
{
	int cds_layer;
	BOOL flipFlag = 0;
	if (L == LAY_BOARD_OUTLINE)
		cds_layer = 19;
	else if (L == LAY_TOP_COPPER || L == LAY_BOTTOM_COPPER)
		cds_layer = 20;
	else if (L == LAY_MASK_TOP || L == LAY_MASK_BOTTOM)
		cds_layer = 21;
	else if (L == LAY_SILK_TOP || L == LAY_SILK_BOTTOM)
		cds_layer = 22;
	else if (L == LAY_REFINE_TOP || L == LAY_REFINE_BOT)
		cds_layer = 23;
	else if (L == LAY_PAD_THRU)
		cds_layer = 24;
	else
		cds_layer = 25;
	CString line;
	line.Format("polyline: %d %d %d %d %d %d %d %d\n", 2, 0, cds_layer, w, -1, -1, -1, 0);
	f->WriteString(line);
	line.Format("  corner: %d %d %d %d %d\n", 1, page?-x:x, y, 0, 0);
	f->WriteString(line);
	line.Format("  corner: %d %d %d %d %d\n", 2, page?-x2:x2, y2, 0, 0);
	f->WriteString(line);
}
void SavePcbViewWriteRndRect(CStdioFile* f, int x, int y, int w, int h, int r, int a, int L)
{
	int np = 20;
	CPoint rnd[20];
	float radius = min(h, w) / 2;
	int cds_layer;
	BOOL flipFlag = 0;
	if (L == LAY_BOARD_OUTLINE)
		cds_layer = 19;
	else if (L == LAY_TOP_COPPER || L == LAY_BOTTOM_COPPER)
		cds_layer = 20;
	else if (L == LAY_MASK_TOP || L == LAY_MASK_BOTTOM)
		cds_layer = 21;
	else if (L == LAY_SILK_TOP || L == LAY_SILK_BOTTOM)
		cds_layer = 22;
	else if (L == LAY_REFINE_TOP || L == LAY_REFINE_BOT)
		cds_layer = 23;
	else if (L == LAY_PAD_THRU)
		cds_layer = 24;
	else
		cds_layer = 25;
	CString line;
	int nv = Gen_RndRectPoly(x, y, w, h, radius, -a, &rnd[0], np);
	if (nv)
	{
		line.Format("outline: %d %d %d %d %d %d %d %d\n", np, 1, cds_layer, NM_PER_MIL, -1, -1, -1, 0);
		f->WriteString(line);
		for (int i = 0; i < nv; i++)
		{
			line.Format("  corner: %d %d %d %d %d\n", i+1, page?-rnd[i].x:rnd[i].x, rnd[i].y, 0, 0);
			f->WriteString(line);
		}
	}
}
void SavePcbViewWritePolyline(CStdioFile* f, CPolyLine* p, int L)
{
	int cds_layer;
	BOOL flipFlag = 0;
	int np = p->GetNumCorners();
	int ht = p->GetHatch();
	int pw = p->GetW();
	int cl = p->GetClosed();
	if (L == LAY_BOARD_OUTLINE)
	{
		cds_layer = 19;
		ht = 20;
	}
	else if (L == LAY_TOP_COPPER || L == LAY_BOTTOM_COPPER)
		cds_layer = 20;
	else if (L == LAY_MASK_TOP || L == LAY_MASK_BOTTOM)
		cds_layer = 21;
	else if (L == LAY_SILK_TOP || L == LAY_SILK_BOTTOM)
		cds_layer = 22;
	else if (L == LAY_REFINE_TOP || L == LAY_REFINE_BOT)
		cds_layer = 23;
	else if (L == LAY_PAD_THRU)
		cds_layer = 24;
	else
		cds_layer = 25;
	CString line;
	if(cl)
		line.Format("outline: %d %d %d %d %d %d %d %d\n", np, ht, cds_layer, pw, -1, -1, -1, 0);
	else
		line.Format("polyline: %d %d %d %d %d %d %d %d\n", np, ht, cds_layer, pw, -1, -1, -1, 0);
	f->WriteString(line);
	for (int i = 0; i < np; i++)
	{
		int st = p->GetSideStyle(i);
		if (st)
			if (page)
				st = 3 - st;
		line.Format("  corner: %d %d %d %d %d\n", i + 1, page ? -p->GetX(i) : p->GetX(i), p->GetY(i), st, p->GetContour(i));
		f->WriteString(line);
	}
}
//======================================================================================
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//======================================================================================
void SavePcbView(CFreePcbDoc* doc)
{
	CStdioFile f;
	CString f_name;
	f_name.Format("%s%s\\PCBVIEW.cds", doc->m_path_to_folder, freeasy_netlist);
	int ok = f.Open(f_name, CFile::modeCreate | CFile::modeWrite);
	if (!ok)
	{
		CString log_message;
		log_message.Format("ERROR: Unable to open file \"%s\"\r\n", f_name);
		doc->m_dlg_log->AddLine(log_message);
	}
	else
	{
		f.WriteString("[options]\n");
		f.WriteString("n_additional_layers: 10\n");
		f.WriteString("layer_info: \"нижний 3\" 13 255 0 255 1\n");
		f.WriteString("layer_info: \"нижний 4\" 14 160 160 160 1\n");
		f.WriteString("layer_info: \"нижний 5\" 15 255 255 255 1\n");
		f.WriteString("layer_info: \"нижний 6\" 16 0 255 0 1\n");
		f.WriteString("layer_info: \"нижний 7\" 17 0 0 0 1\n");
		f.WriteString("layer_info: \"нижний 8\" 18 128 128 255 1\n");
		f.WriteString("[graphics]\n");
		for (page = 0; page < 2; page++)
		{
			RectArray RectA;
			RectA.Clear();
			RectA.SetStep(max(doc->m_part_grid_spacing, NM_PER_MIL));
			if (page == 0)
				f.WriteString("rename_page: \"TOP\"\n");
			else
				f.WriteString("add_new_page: \"BOTTOM\"\n");
			for (cnet* n = doc->m_nlist->GetFirstNet(); n; n = doc->m_nlist->GetNextNet())
			{
				for (int i = 0; i < n->nconnects; i++)
				{
					for (int ii = 0; ii < n->connect[i].nsegs; ii++)
					{
						int L = n->connect[i].seg[ii].layer;
						int x = n->connect[i].vtx[ii].x;
						int y = n->connect[i].vtx[ii].y;
						int x2 = n->connect[i].vtx[ii + 1].x;
						int y2 = n->connect[i].vtx[ii + 1].y;
						if ((L == LAY_TOP_COPPER && page == 0) || (L == LAY_BOTTOM_COPPER && page == 1))
						{
							int w = n->connect[i].seg[ii].width;
							SavePcbViewWriteSegment(&f, x, y, x2, y2, w, L);
						}
						if (n->connect[i].vtx[ii + 1].via_w && n->connect[i].vtx[ii + 1].via_hole_w)
						{
							int vw = n->connect[i].vtx[ii + 1].via_w;
							int vh = n->connect[i].vtx[ii + 1].via_hole_w;
							dl_element* el = n->connect[i].vtx[ii + 1].dl_el;
							if (el)
								SavePcbViewWriteRndRect(&f, x2, y2, vw, vw, vw / 2, 0, L);
							el = n->connect[i].vtx[ii + 1].dl_hole;
							if (el)
								SavePcbViewWriteRndRect(&f, x2, y2, vh, vh, vh / 2, 0, LAY_PAD_THRU);
						}
					}
				}
				for (int i = 0; i < n->nareas; i++)
				{
					CPolyLine* p = n->area[i].poly;
					if(p->GetHatch())
						if ((p->GetLayer() == LAY_TOP_COPPER && page == 0) ||
							(p->GetLayer() == LAY_BOTTOM_COPPER && page == 1))
							SavePcbViewWritePolyline(&f, p, p->GetLayer());
				}
			}
			for (int i = 0; i < doc->m_outline_poly.GetSize(); i++)
			{
				CPolyLine* p = &doc->m_outline_poly.GetAt(i);
				if (p->GetLayer() == LAY_BOARD_OUTLINE)
					SavePcbViewWritePolyline(&f, p, LAY_BOARD_OUTLINE);
				if ((p->GetLayer() == LAY_SILK_TOP && page == 0) ||
					(p->GetLayer() == LAY_SILK_BOTTOM && page == 1))
					SavePcbViewWritePolyline(&f, p, p->GetLayer());
				if ((p->GetLayer() == LAY_REFINE_TOP && page == 0) ||
					(p->GetLayer() == LAY_REFINE_BOT && page == 1))
					SavePcbViewWritePolyline(&f, p, p->GetLayer());
			}
			for (cpart* p = doc->m_plist->GetFirstPart(); p; p = doc->m_plist->GetNextPart(p))
			{

			}
		}
		f.WriteString("[end]\n");
		f.Close();
	}
}


