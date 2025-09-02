#include "stdafx.h"
#include "RectArray.h"
int page;
enum CDS_LAYER
{
	LBOARD=19,
	LCOPPER,
	LMASK,
	LHOLES,
	LSILK,
	LNOTES,
	LDEF
};
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
		cds_layer = LBOARD;
	else if (L == LAY_TOP_COPPER || L == LAY_BOTTOM_COPPER)
		cds_layer = LCOPPER;
	else if (L == LAY_SM_TOP || L == LAY_SM_BOTTOM)
		cds_layer = LMASK;
	else if (L == LAY_SILK_TOP || L == LAY_SILK_BOTTOM)
		cds_layer = LSILK;
	else if (L == LAY_REFINE_TOP || L == LAY_REFINE_BOT)
		cds_layer = LNOTES;
	else if (L == LAY_PAD_THRU)
		cds_layer = LHOLES;
	else
		cds_layer = LDEF;
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
	int radius = min(h, w) / 2;
	radius = min(r, radius);
	int cds_layer;
	BOOL flipFlag = 0;
	if (L == LAY_BOARD_OUTLINE)
		cds_layer = LBOARD;
	else if (L == LAY_TOP_COPPER || L == LAY_BOTTOM_COPPER)
		cds_layer = LCOPPER;
	else if (L == LAY_SM_TOP || L == LAY_SM_BOTTOM)
		cds_layer = LMASK;
	else if (L == LAY_SILK_TOP || L == LAY_SILK_BOTTOM)
		cds_layer = LSILK;
	else if (L == LAY_REFINE_TOP || L == LAY_REFINE_BOT)
		cds_layer = LNOTES;
	else if (L == LAY_PAD_THRU)
		cds_layer = LHOLES;
	else
		cds_layer = LDEF;
	CString line;
	int nv = Gen_RndRectPoly(x, y, w, h, radius, -a, &rnd[0], np);
	if (nv)
	{
		line.Format("outline: %d %d %d %d %d %d %d %d\n", nv, 1, cds_layer, NM_PER_MIL*4, -1, -1, -1, 0);
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
		cds_layer = LBOARD;
		ht = 20;
	}
	else if (L == LAY_TOP_COPPER || L == LAY_BOTTOM_COPPER)
		cds_layer = LCOPPER;
	else if (L == LAY_SM_TOP || L == LAY_SM_BOTTOM)
		cds_layer = LMASK;
	else if (L == LAY_SILK_TOP || L == LAY_SILK_BOTTOM)
		cds_layer = LSILK;
	else if (L == LAY_REFINE_TOP || L == LAY_REFINE_BOT)
		cds_layer = LNOTES;
	else if (L == LAY_PAD_THRU)
		cds_layer = LHOLES;
	else
		cds_layer = LDEF;
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
	f_name.Format("%s%s\\%s.fpc.PCBVIEW", doc->m_path_to_folder, freeasy_netlist, doc->m_name);
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
		f.WriteString("layer_info: \"контурный\" 13 0 115 60 1\n");
		f.WriteString("layer_info: \"медный\" 14 40 165 90 1\n");
		f.WriteString("layer_info: \"защитный\" 15 155 155 191 1\n");
		f.WriteString("layer_info: \"фрезерный\" 16 235 235 235 1\n");
		f.WriteString("layer_info: \"шёлковый\" 17 254 254 254 1\n");
		f.WriteString("layer_info: \"чертёжный\" 18 128 64 0 1\n");
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
								SavePcbViewWriteRndRect(&f, x2, y2, vw, vw, vw / 2, 0, LAY_TOP_COPPER);
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
			//f.WriteString("=====================================================================\n");
			int cds_layer = 0;
			for (cpart* p = doc->m_plist->GetFirstPart(); p; p = doc->m_plist->GetNextPart(p))
			{
				cds_layer = 0;
				for (int ip = 0; ip < p->pin.GetSize(); ip++)
				{
					for (int iel = 0; iel < p->pin[ip].dl_els.GetSize(); iel++)
					{
						dl_element* el = p->pin[ip].dl_els.GetAt(iel);
						if (el)
						{
							for (int step = 0; step < 2; step++)
							{
								cds_layer = 0; 
								switch (step)
								{
								case 0:
									if ((getbit(el->layers_bitmap, LAY_TOP_COPPER) && page == 0) ||
										(getbit(el->layers_bitmap, LAY_BOTTOM_COPPER) && page == 1))
										cds_layer = LCOPPER;
									break;
								case 1:
									if ((getbit(el->layers_bitmap, LAY_SM_TOP) && page == 0) ||
										(getbit(el->layers_bitmap, LAY_SM_BOTTOM) && page == 1))
										cds_layer = LMASK;
									break;
								default:
									break;
								}
								if (cds_layer)
								{
									if (el->gtype == DL_RECT || el->gtype == DL_RRECT || el->gtype == DL_CIRC)
									{
										RECT Get;
										el->dlist->Get_Rect(el, &Get);
										int xc = (Get.left + Get.right) / 2;
										int yc = (Get.bottom + Get.top) / 2;
										int w = abs(Get.right - Get.left);
										int h = abs(Get.top - Get.bottom);
										if (el->gtype == DL_RECT)
											SavePcbViewWriteRndRect(&f, xc, yc, w, h, 0, 0, step ? LAY_SM_TOP : LAY_TOP_COPPER);
										else if (el->gtype == DL_CIRC)
											SavePcbViewWriteRndRect(&f, xc, yc, w, h, w / 2, 0, step ? LAY_SM_TOP : LAY_TOP_COPPER);
										else
											SavePcbViewWriteRndRect(&f, xc, yc, w, h, el->el_w * m_pcbu_per_wu, 0, step ? LAY_SM_TOP : LAY_TOP_COPPER);
									}
									else if (el->gtype == DL_POLYGON)
									{
										CPoint Get[20];
										int np = 20;
										el->dlist->Get_Points(el, Get, &np);
										if (np > 2)
										{
											CString line;
											line.Format("outline: %d %d %d %d %d %d %d %d\n", np, 1, cds_layer, el->el_w * m_pcbu_per_wu, -1, -1, -1, 0);
											f.WriteString(line);
											for (int i = 0; i < np; i++)
											{
												line.Format("  corner: %d %d %d %d %d\n", i + 1, page ? -Get[i].x : Get[i].x, Get[i].y, 0, 0);
												f.WriteString(line);
											}
										}
									}
								}
							}
						}
					}
					dl_element* el = p->pin[ip].dl_hole;
					if (el)
					{
						RECT Get;
						el->dlist->Get_Rect(el, &Get);
						int xc = (Get.left + Get.right) / 2;
						int yc = (Get.bottom + Get.top) / 2;
						int w = abs(Get.right - Get.left);
						SavePcbViewWriteRndRect(&f, xc, yc, w, w, w / 2, 0, LAY_PAD_THRU);
					}
				}
				for (int i = 0; i < p->m_outline_stroke.GetSize(); i++)
				{
					cds_layer = 0;
					dl_element* el = p->m_outline_stroke.GetAt(i);
					if ((getbit(el->layers_bitmap, LAY_TOP_COPPER) && page == 0) ||
						(getbit(el->layers_bitmap, LAY_BOTTOM_COPPER) && page == 1))
						cds_layer = LCOPPER;
					else if ((getbit(el->layers_bitmap, LAY_SILK_TOP) && page == 0) ||
						(getbit(el->layers_bitmap, LAY_SILK_BOTTOM) && page == 1))
						cds_layer = LSILK;
					else if ((getbit(el->layers_bitmap, LAY_REFINE_TOP) && page == 0) ||
						(getbit(el->layers_bitmap, LAY_REFINE_BOT) && page == 1))
						cds_layer = LNOTES;
					if (cds_layer == 0)
						continue;
					if (el->gtype == DL_POLYGON)
					{
						CArray<CPoint> * arr = el->dlist->Get_Points(el, NULL, NULL);
						int np = arr->GetSize();
						CPoint* Get = new CPoint[np];
						el->dlist->Get_Points(el, Get, &np);
						if (np > 2)
						{
							CString line;
							line.Format("outline: %d %d %d %d %d %d %d %d\n", np, 1, cds_layer, el->el_w * m_pcbu_per_wu, -1, -1, -1, 0);
							f.WriteString(line);
							for (int i = 0; i < np; i++)
							{
								line.Format("  corner: %d %d %d %d %d\n", i + 1, page ? -Get[i].x : Get[i].x, Get[i].y, 0, 0);
								f.WriteString(line);
							}
						}
						delete Get;
					}
					else if (el->gtype == DL_POLYLINE)
					{
						CArray<CPoint>* arr = el->dlist->Get_Points(el, NULL, NULL);
						int np = arr->GetSize();
						CPoint* Get = new CPoint[np];
						el->dlist->Get_Points(el, Get, &np);
						if (np >= 2)
						{
							CString line;
							line.Format("polyline: %d %d %d %d %d %d %d %d\n", np, 1, cds_layer, el->el_w * m_pcbu_per_wu, -1, -1, -1, 0);
							f.WriteString(line);
							for (int i = 0; i < np; i++)
							{
								line.Format("  corner: %d %d %d %d %d\n", i + 1, page ? -Get[i].x : Get[i].x, Get[i].y, 0, 0);
								f.WriteString(line);
							}
						}
						delete Get;
					}
					else if (el->gtype == DL_LINES_ARRAY)
					{
						CArray<CPoint>* arr = el->dlist->Get_Points(el, NULL, NULL);
						int np = arr->GetSize();
						CPoint* Get = new CPoint[np];
						el->dlist->Get_Points(el, Get, &np);
						for (int i = 0; i < np - 1; i += 2)
						{
							CString line;
							line.Format("outline: %d %d %d %d %d %d %d %d\n", 2, 1, cds_layer, el->el_w * m_pcbu_per_wu, -1, -1, -1, 0);
							f.WriteString(line);
							line.Format("  corner: %d %d %d %d %d\n", 1, page ? -Get[i].x : Get[i].x, Get[i].y, 0, 0);
							f.WriteString(line);
							line.Format("  corner: %d %d %d %d %d\n", 2, page ? -Get[i + 1].x : Get[i + 1].x, Get[i + 1].y, 0, 0);
							f.WriteString(line);
						}
						delete Get;
					}
				}
				if ((p->side == 0 && page == 0) || (p->side && page))
				{
					CString RefText = p->ref_des;
					if (p->value.GetLength())
					{
						RefText += "|" + p->value;
						if (p->shape)
							if (p->shape->m_package.GetLength())
								RefText += "'" + p->shape->m_package;
					}
					RefText += "|C"; // alignment by center
					RECT partR;
					doc->m_plist->GetPartBoundingRect(p, &partR);
					int partW = partR.right - partR.left;
					int partH = partR.top - partR.bottom;
					int tx = (partR.left + partR.right) / 2;
					int ty = (partR.top + partR.bottom) / 2;
					CString line;
					line.Format("polyline: %d %d %d %d %d %d %d %d\n", 2, 0, 17, NM_PER_MIL, -1, -1, -1, 0);
					f.WriteString(line);
					line.Format("  corner: %d %d %d %d %d\n", 1, page ? -tx + NM_PER_MIL : tx + NM_PER_MIL, ty, 0, 0);
					f.WriteString(line);
					line.Format("  corner: %d %d %d %d %d\n", 2, page ? -tx + NM_PER_MIL : tx + NM_PER_MIL, ty, 0, 0);
					f.WriteString(line);
					line.Format("description: \"%s\" %d %d %d %d %d %d %d %d %d %d\n", RefText,
						page ? -tx : tx,
						ty,
						14, // layer
						partH > partW ? -90 : 0, // angle
						p->m_ref_size,
						p->m_ref_w,
						-1,
						-1,
						doc->m_smfontutil->m_font_number,
						0);
					f.WriteString(line);
				}
			}
			for (dl_element* el = doc->m_dlist->Get_Start(); el->next; el = el->next)
			{
				if (el->visible == 0)
					continue;
				CText* t = (CText*)el->ptr;
				if(t == NULL)
					continue;
				if (el->id.st == ID_VALUE_TXT)
					continue;
				//-----------------------------------
				cds_layer = 0;
				if ((getbit(el->layers_bitmap, LAY_TOP_COPPER) && page == 0) ||
					(getbit(el->layers_bitmap, LAY_BOTTOM_COPPER) && page == 1))
					cds_layer = LCOPPER;
				else if ((getbit(el->layers_bitmap, LAY_SILK_TOP) && page == 0) ||
					(getbit(el->layers_bitmap, LAY_SILK_BOTTOM) && page == 1))
					cds_layer = LSILK;
				else if ((getbit(el->layers_bitmap, LAY_REFINE_TOP) && page == 0) ||
					(getbit(el->layers_bitmap, LAY_REFINE_BOT) && page == 1))
					cds_layer = LNOTES;
				if (cds_layer == 0)
					continue;
				if (el->id.st == ID_REF_TXT)
					cds_layer = LNOTES + 1;
				if (el->gtype == DL_LINES_ARRAY)
				{
					CArray<CPoint>* arr = el->dlist->Get_Points(el, NULL, NULL);
					int np = arr->GetSize();
					CPoint* Get = new CPoint[np];
					el->dlist->Get_Points(el, Get, &np);
					for (int i = 0; i < np - 1; i += 2)
					{
						CString line;
						line.Format("outline: %d %d %d %d %d %d %d %d\n", 2, 1, cds_layer, el->el_w * m_pcbu_per_wu, -1, -1, -1, 0);
						f.WriteString(line);
						line.Format("  corner: %d %d %d %d %d\n", 1, page ? -Get[i].x : Get[i].x, Get[i].y, 0, 0);
						f.WriteString(line);
						line.Format("  corner: %d %d %d %d %d\n", 2, page ? -Get[i + 1].x : Get[i + 1].x, Get[i + 1].y, 0, 0);
						f.WriteString(line);
					}
					delete Get;
				}
			}
		}
		f.WriteString("[end]\n");
		f.Close();
	}
}


