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
					if (n->connect[i].utility == 0)
						continue;
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
					if (n->area[i].utility == 0)
						continue;
					CPolyLine* p = n->area[i].poly;
					if(p->GetHatch() || p->GetW())
						if ((p->GetLayer() == LAY_TOP_COPPER && page == 0) ||
							(p->GetLayer() == LAY_BOTTOM_COPPER && page == 1))
							SavePcbViewWritePolyline(&f, p, p->GetLayer());
				}
			}
			for (int i = 0; i < doc->m_outline_poly.GetSize(); i++)
			{
				CPolyLine* p = &doc->m_outline_poly.GetAt(i);
				if (p->GetUtility() == 0)
					continue;
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
				if (p->utility == 0)
					continue;
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
					else if (getbit(el->layers_bitmap, LAY_PAD_THRU))
						cds_layer = LHOLES;
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
					if (p->dl_ref_el)
					{
						if (p->dl_ref_el->gtype == DL_LINES_ARRAY)
						{
							CArray<CPoint>* arr = p->dl_ref_el->dlist->Get_Points(p->dl_ref_el, NULL, NULL);
							int np = arr->GetSize();
							CPoint* Get = new CPoint[np];
							p->dl_ref_el->dlist->Get_Points(p->dl_ref_el, Get, &np);
							for (int i = 0; i < np - 1; i += 2)
							{
								CString line;
								line.Format("outline: %d %d %d %d %d %d %d %d\n", 2, 1, (LNOTES + 1), p->dl_ref_el->el_w * m_pcbu_per_wu, -1, -1, -1, 0);
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
			}
			int it = 0;
			for (CText* t=doc->m_tlist->GetFirstText(); t; t = doc->m_tlist->GetNextText(&it))
			{
				if (t->m_utility == 0)
					continue;
				dl_element* el = t->dl_el;
				if (el == NULL)
					continue;
				if (el->visible == 0)
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

int MarkLegalElementsForExport(CFreePcbDoc* doc)
{
	doc->m_view->MarkAllOutlinePoly(0,-1);
	doc->m_plist->MarkAllParts(0);
	doc->m_nlist->MarkAllNets(0);
	doc->m_tlist->MarkAllTexts(0);
	
	// find legal board outline
	int nonLegalBoard = 0, n_bo = 0, i_bo = -1;
	for (int i = 0; i < doc->m_outline_poly.GetSize(); i++)
	{
		if (i >= 32)
			break;
		CPolyLine* po = &doc->m_outline_poly.GetAt(i);
		if (po->GetLayer() != LAY_BOARD_OUTLINE)
			setbit(nonLegalBoard, i);
		else if( po->GetClosed() == 0)
			setbit(nonLegalBoard, i);
		else 
		{
			n_bo++;
			i_bo = i;
			for (cpart* p = doc->m_plist->GetFirstPart(); p;)
			{
				if (p->shape)
				{
					if (p->ref_des.Left(3) != "VIA")
						if (p->shape->m_name != "MILLING_BOARD_OUTLINE")
						{
							if (po->TestPointInside(p->x, p->y))
							{
								if (p->ref_des.Find("|") >= 0)
									setbit(nonLegalBoard, i);
								break;
							}
						}
				}
				p = doc->m_plist->GetNextPart(p);
				if (p == NULL)
					setbit(nonLegalBoard, i);
			}
		}
	}
	int iLegal = -1;
	for (int i = 0; i < doc->m_outline_poly.GetSize(); i++)
	{
		if (i >= 32)
			break;
		if (getbit(nonLegalBoard, i) == 0)
			iLegal = i;
	}
	if (iLegal == -1)
	{
		if (n_bo == 1)
			iLegal = i_bo;
		else
		{
			doc->m_view->MarkAllOutlinePoly(1, -1);
			doc->m_plist->MarkAllParts(1);
			doc->m_nlist->MarkAllNets(1);
			doc->m_tlist->MarkAllTexts(1);
			return iLegal;
		}
	}
		
	CPolyLine* LegalBoard = &doc->m_outline_poly.GetAt(iLegal);
	RECT LegalRect = LegalBoard->GetCornerBounds(0);
	for (cpart* p = doc->m_plist->GetFirstPart(); p; p = doc->m_plist->GetNextPart(p))
	{
		if (p->x > LegalRect.right)
			continue;
		if (p->x < LegalRect.left)
			continue;
		if (p->y > LegalRect.top)
			continue;
		if (p->y < LegalRect.bottom)
			continue;
		if(p->shape)
			if(p->shape->m_name == "MILLING_BOARD_OUTLINE")
				continue;
		if (LegalBoard->TestPointInside(p->x, p->y))
			p->utility = 1; // Legal part
	}
	for (cnet* n = doc->m_nlist->GetFirstNet(); n; n = doc->m_nlist->GetNextNet())
	{
		for (int i = 0; i < n->nconnects; i++)
		{
			if (n->pin[n->connect[i].start_pin].part->utility)
				n->connect[i].utility = 1; // Legal connect
		}
		for (int i = 0; i < n->nareas; i++)
		{
			CPolyLine* po = n->area[i].poly;
			RECT aR = po->GetCornerBounds(0);
			if (RectsIntersection(LegalRect, aR) < 0)
				continue;
			if (LegalBoard->TestPointInside(po->GetX(0), po->GetY(0)))
				n->area[i].utility = 1; // Legal area
			else
			{
				int d = Distance(po->GetX(0), po->GetY(0), LegalBoard->GetX(0), LegalBoard->GetY(0));
				if(d < _2540)
					n->area[i].utility = 1; // Legal area
				else for (int icor = 1; icor < po->GetNumCorners(); icor++)
				{
					if (LegalBoard->TestPointInside(po->GetX(icor), po->GetY(icor)))
					{
						n->area[i].utility = 1; // Legal area
						break;
					}
				}
			}
		}
	}
	int it = 0;
	for (CText* t = doc->m_tlist->GetFirstText(); t; t = doc->m_tlist->GetNextText(&it))
	{
		if (t->m_x > LegalRect.right)
			continue;
		if (t->m_x < LegalRect.left)
			continue;
		if (t->m_y > LegalRect.top)
			continue;
		if (t->m_y < LegalRect.bottom)
			continue;
		if (LegalBoard->TestPointInside(t->m_x, t->m_y))
			t->m_utility = 1; // Legal text
	}
	for (int i = 0; i < doc->m_outline_poly.GetSize(); i++)
	{
		if (i == iLegal)
			continue;
		CPolyLine* po = &doc->m_outline_poly.GetAt(i);
		RECT pR = po->GetCornerBounds(0);
		if (RectsIntersection(LegalRect, pR) <= 0)
			continue;
		int nc = po->GetNumCorners();
		if(nc > 0)
			if (LegalBoard->TestPointInside(po->GetX(0), po->GetY(0)))
				if (LegalBoard->TestPointInside(po->GetX(nc-1), po->GetY(nc-1)))
					po->SetUtility(1); // Legal polyline
	}
	LegalBoard->SetUtility(1);
	return iLegal;
}

void SelectLegalElements(CFreePcbDoc* doc)
{
	id sid(ID_PART, ID_SEL_RECT, 0, 0, 0);
	for (cpart* p = doc->m_plist->GetFirstPart(); p; p = doc->m_plist->GetNextPart(p))
	{
		if (p->utility)
			doc->m_view->NewSelect(p, &sid, 0, 0, 0);
	}
	for (cnet* n = doc->m_nlist->GetFirstNet(); n; n = doc->m_nlist->GetNextNet())
	{
		for (int i = 0; i < n->nconnects; i++)
		{
			if (n->connect[i].utility)
				for (int ii = 0; ii < n->connect[i].nsegs; ii++)
				{
					sid.Set(ID_NET, ID_CONNECT, i, ID_SEG, ii);
					doc->m_view->NewSelect(n, &sid, 0, 0, 0);
				}		
		}
		for (int i = 0; i < n->nareas; i++)
		{
			sid.Set(ID_NET, ID_AREA, i, ID_SIDE, 0);
			if(n->area[i].utility)
				doc->m_view->NewSelect(n, &sid, 0, 0, 0);
		}
	}
	int it = 0;
	sid.Set(ID_TEXT_DEF);
	for (CText* t = doc->m_tlist->GetFirstText(); t; t = doc->m_tlist->GetNextText(&it))
	{
		if (t->m_utility)
			doc->m_view->NewSelect(t, &sid, 0, 0, 0);
	}
	for (int i = 0; i < doc->m_outline_poly.GetSize(); i++)
	{
		CPolyLine* po = &doc->m_outline_poly.GetAt(i);
		if (po->GetUtility())
		{
			sid.Set(ID_POLYLINE, ID_GRAPHIC, i, ID_SIDE, 0);
			if (po->GetLayer() == LAY_BOARD_OUTLINE)
				sid.st = ID_BOARD;
			else if (po->GetLayer() == LAY_SM_TOP || po->GetLayer() == LAY_SM_BOTTOM)
				sid.st = ID_SM_CUTOUT;
			doc->m_view->NewSelect(NULL, &sid, 0, 0, 0);
		}
	}
	doc->m_view->SelectContour();
}




void CreateClearancesForCopperArea(	CFreePcbDoc * doc,
									CString * crop_net_name,
									cnet* area_net,
									int iar,
									int pad_cl,
									int seg_cl,
									int area_cl,
									int hole_cl,
									int text_cl,
									int board_cl,
									int default_cl,
									int thrml_cl,
									int area_width,
									BOOL gHost)
{
	CPolyLine* oP = area_net->area[iar].poly;
	int oP_L = oP->GetLayer();
	int oP_H = oP->GetHatch();
	int oP_W = oP->GetW();
	int oP_M = oP->GetMerge();
	cnet* cropNet = doc->m_nlist->GetNetPtrByName(crop_net_name);
	if (gHost)
	{
		if (getbit(doc->m_crop_flags, MC_REMOVE_PREV))
		{
			for (int isc = area_net->nareas - 1; isc >= 0; isc--)
			{
				if (isc == iar)
					continue;
				if (oP_L == area_net->area[isc].poly->GetLayer())
					if (area_net->area[isc].poly->GetHatch() == CPolyLine::DIAGONAL_FULL)
					{
						int mid_p = area_net->area[isc].poly->GetNumCorners() / 2;
						if (oP->TestPointInside(area_net->area[isc].poly->GetX(0), area_net->area[isc].poly->GetY(0)))
						{
							doc->m_nlist->RemoveArea(area_net, isc);
						}
						else if (oP->TestPointInside(area_net->area[isc].poly->GetX(mid_p), area_net->area[isc].poly->GetY(mid_p)))
						{
							doc->m_nlist->RemoveArea(area_net, isc);
						}
					}
			}
			doc->m_view->SetDrawLayer(DISABLE_CHANGE_DRAW_LAYER);
			doc->m_view->UpdateWindow();
		}
		iar = doc->m_nlist->AddArea(area_net, oP_L, oP->GetX(0), oP->GetY(0), CPolyLine::NO_HATCH);
		for (int icc = 0; icc < oP->GetNumContours(); icc++)
		{
			int end = oP->GetContourEnd(icc);
			for (int iop = max(1, oP->GetContourStart(icc)); iop <= end; iop++)
			{
				doc->m_nlist->AppendAreaCorner(area_net, iar, oP->GetX(iop), oP->GetY(iop), oP->GetSideStyle(iop - 1), FALSE);
			}
			doc->m_nlist->CompleteArea(area_net, iar, oP->GetSideStyle(end));
		}
		area_net->area[iar].poly->SetMerge(oP_M);
	}
	else
	{
		int new_sel_ia = doc->m_nlist->AddArea(area_net, oP_L, oP->GetX(0), oP->GetY(0), oP->GetHatch());
		for (int icc = 0; icc < oP->GetNumContours(); icc++)
		{
			int end = oP->GetContourEnd(icc);
			for (int iop = max(1, oP->GetContourStart(icc)); iop <= end; iop++)
			{
				doc->m_nlist->AppendAreaCorner(area_net, new_sel_ia, oP->GetX(iop), oP->GetY(iop), oP->GetSideStyle(iop - 1), FALSE);
			}
			if (icc == oP->GetNumContours() - 1)
				doc->m_nlist->CompleteArea(area_net, new_sel_ia, oP->GetSideStyle(end));
			else
				area_net->area[new_sel_ia].poly->Close(0, 0);
		}
		doc->m_nlist->RemoveArea(area_net, iar);
		iar = new_sel_ia - 1;
	}
	int areaW = oP_W;
	if (getbit(doc->m_crop_flags, MC_WIDTH))
	{
		area_net->area[iar].poly->SetW(area_width);
		areaW = area_net->area[iar].poly->GetW();
		if (oP_H != CPolyLine::DIAGONAL_FULL)
			doc->m_nlist->SetAreaHatch(area_net, iar, CPolyLine::NO_HATCH); // m_sel_net->area[m_sel_ia].poly->SetHatch( CPolyLine::NO_HATCH );
		doc->m_nlist->SetAreaConnections(area_net, iar);
	}
	int mem_n_areas = area_net->nareas - 1;
	doc->AddBoardHoles(); // valid
	doc->m_nlist->AddCutoutsForArea(area_net,
									iar,
									cropNet,
									pad_cl,
									seg_cl,			
									area_cl,			
									hole_cl,			
									text_cl,			
									board_cl,			
									default_cl,		
									thrml_cl,			
									doc->m_thermal_width,		
									TRUE,
									doc->m_mlist,
									doc->m_cam_flags,
									doc->m_crop_flags);
	CPolyLine* Apo = area_net->area[iar].poly;
	if (Apo->GetNumContours() > 1)
	{
		int nAreas = 0;
		doc->m_nlist->ClipAreaPolygon(area_net, iar, -1, FALSE, FALSE, TRUE, &nAreas);
		doc->ProjectModified(TRUE);
	}
	// delete new areas
	// if it's outside board outline 
	MarkLegalElementsForExport(doc);
	if (getbit(doc->m_crop_flags, MC_BOARD) || getbit(doc->m_crop_flags, MC_POLYLINES))
	{
		for (int i_a = area_net->nareas - 1; i_a >= mem_n_areas; i_a--)
		{
			int cur_x = area_net->area[i_a].poly->GetX(0);
			int cur_y = area_net->area[i_a].poly->GetY(0);
			BOOL remove = 1;
			for (int sc_p = 0; sc_p < doc->m_outline_poly.GetSize(); sc_p++)
			{
				if (doc->m_outline_poly[sc_p].GetUtility() || area_net->name.Compare("LASER__NET"))
				if (doc->m_outline_poly[sc_p].GetLayer() == LAY_BOARD_OUTLINE && getbit(doc->m_crop_flags, MC_BOARD))
				{
					if (doc->m_outline_poly[sc_p].TestPointInside(cur_x, cur_y))
					{
						remove = 0;
						break;
					}
				}
			}
			if (remove == 0) for (int sc_p = 0; sc_p < doc->m_outline_poly.GetSize(); sc_p++)
			{
				if (doc->m_outline_poly[sc_p].GetLayer() == LAY_SCRIBING && getbit(doc->m_crop_flags, MC_POLYLINES))
				{
					if (doc->m_outline_poly[sc_p].TestPointInside(cur_x, cur_y) &&
						doc->m_outline_poly[sc_p].GetHatch() == CPolyLine::DIAGONAL_FULL)
					{
						remove = 1;
						break;
					}
				}
			}
			if (remove)
			{
				doc->m_nlist->RemoveArea(area_net, i_a);
			}
		}
	}
	// delete unconnected areas
	if (getbit(doc->m_crop_flags, MC_NO_ISLANDS))
	{
		doc->m_nlist->SetAreaConnections(area_net);
		for (int i_a = area_net->nareas - 1; i_a >= mem_n_areas; i_a--)
		{
			int npins = area_net->area[i_a].npins;
			int nvias = area_net->area[i_a].nvias;
			if (npins == 0 && nvias == 0)
			{
				doc->m_nlist->RemoveArea(area_net, i_a);
			}
		}
	}
	// delete new areas
	// if it's inside main
	// contour of any area
	if (getbit(doc->m_crop_flags, MC_AREAS))
	{
		doc->m_nlist->SetAreaConnections(area_net);
		for (int i_a = area_net->nareas - 1; i_a >= mem_n_areas; i_a--)
		{
			int cur_x = area_net->area[i_a].poly->GetX(0);
			int cur_y = area_net->area[i_a].poly->GetY(0);
			BOOL rem = 0;
			for (cnet* getn = doc->m_nlist->GetFirstNet(); getn; getn = doc->m_nlist->GetNextNet())
			{
				for (int i_2 = getn->nareas - 1; i_2 >= 0; i_2--)
				{
					if (getn->area[i_2].poly->GetHatch() != CPolyLine::DIAGONAL_FULL)
						continue;
					if (getn == area_net && i_a == i_2)
						continue;
					if (getn->area[i_2].poly->GetLayer() != oP_L)
						continue;
					if (getn->area[i_2].poly->TestPointInside(cur_x, cur_y))
					{
						rem = TRUE;
						break;
					}
				}
				if (rem)
				{
					doc->m_nlist->CancelNextNet();
					break;
				}
			}
			if (rem)
			{
				doc->m_nlist->RemoveArea(area_net, i_a);
			}
		}
	}
	// delete contour
	// if it's inside different 
	// contour of same area
	// or/and when the contour is 
	// outside this area
	{
		for (int i_a = area_net->nareas - 1; i_a >= mem_n_areas; i_a--)
		{
			///m_sel_net->area[i_a].poly->RecalcRectC(0);
			RECT rect_A = area_net->area[i_a].poly->GetCornerBounds(0);
			int g_nc = area_net->area[i_a].poly->GetNumContours();
			for (int i_c = g_nc - 1; i_c > 0; i_c--)
			{
				///m_sel_net->area[i_a].poly->RecalcRectC(i_c);
				RECT rect_c = area_net->area[i_a].poly->GetCornerBounds(i_c);
				if ((rect_A.right - rect_A.left) < (rect_c.right - rect_c.left))
				{
					area_net->area[i_a].poly->RemoveContour(i_c, FALSE);
					continue;
				}
				//
				int i_st = area_net->area[i_a].poly->GetContourStart(i_c);
				int cur_x = area_net->area[i_a].poly->GetX(i_st);
				int cur_y = area_net->area[i_a].poly->GetY(i_st);
				//
				// contour is outside this area
				if (area_net->area[i_a].poly->TestPointInside(cur_x, cur_y, 0) == 0)
				{
					area_net->area[i_a].poly->RemoveContour(i_c, FALSE);
					continue;
				}
				//
				// inside different contour
				for (int n_c = area_net->area[i_a].poly->GetNumContours() - 1; n_c > 0; n_c--)
				{
					if (n_c == i_c)
						continue;
					//
					if (area_net->area[i_a].poly->TestPointInside(cur_x, cur_y, n_c))
					{
						int i_e = area_net->area[i_a].poly->GetContourEnd(i_c);
						cur_x = area_net->area[i_a].poly->GetX(i_e);
						cur_y = area_net->area[i_a].poly->GetY(i_e);
						if (area_net->area[i_a].poly->TestPointInside(cur_x, cur_y, n_c))
						{
							area_net->area[i_a].poly->RemoveContour(i_c, FALSE);
							break;
						}
					}
				}
			}
			if (g_nc != area_net->area[i_a].poly->GetNumContours())
				doc->m_nlist->SetAreaHatch(area_net, i_a); // m_sel_net->area[i_a].poly->Draw();
		}
	}
	// remove thermal stubs
	// (bad thermal relief)
	if (getbit(doc->m_crop_flags, MC_NO_THERMAL) == 0) for (int i_a = area_net->nareas - 1; i_a >= mem_n_areas; i_a--)
	{
		doc->m_nlist->SetAreaConnections(area_net, i_a);
		int bCornerDeleted = 0;
		for (int pin = 0; pin < area_net->area[i_a].npins; pin++)
		{
			int pin_index = area_net->area[i_a].pin[pin];
			cpart* pP = area_net->pin[pin_index].part;
			if (pP)
				if (pP->shape)
				{
					CString pName = area_net->pin[pin_index].pin_name;
					int ip = -1;
					for (ip = pP->shape->GetPinIndexByName(pName, ip);
						ip >= 0;
						ip = pP->shape->GetPinIndexByName(pName, ip))
					{
						dl_element* sel_el = pP->pin[ip].dl_sel;
						if (sel_el)
						{
							CPoint PTS[4];
							int np = 4;
							doc->m_view->m_dlist->Get_Points(sel_el, PTS, &np);
							if (np == 4)
							{
								for (int cr = 0; cr < area_net->area[i_a].poly->GetNumCorners(); cr++)
								{
									// test:
									int numcont = area_net->area[i_a].poly->GetNumContour(cr);
									int cstart = area_net->area[i_a].poly->GetContourStart(numcont);
									int cend = area_net->area[i_a].poly->GetContourEnd(numcont);
									if (cend - cstart < 8)
									{
										cr = cend;
										continue; // fail
									}

									int curx = area_net->area[i_a].poly->GetX(cr);
									int cury = area_net->area[i_a].poly->GetY(cr);
									if (TestPolygon(curx, cury, PTS, np))
									{
										int mx = curx;
										int my = cury;
										int ne = area_net->area[i_a].poly->GetIndexCornerNext(cr);
										int nne = area_net->area[i_a].poly->GetIndexCornerNext(ne);
										int cnt_del = -1;
										int dist;
										do
										{
											nne = area_net->area[i_a].poly->GetIndexCornerNext(nne);
											curx = area_net->area[i_a].poly->GetX(nne);
											cury = area_net->area[i_a].poly->GetY(nne);
											cnt_del++;
											//
											dist = Distance(curx, cury, mx, my);
											dist += areaW;
										} while ((dist > abs(doc->m_thermal_width) + _2540 || dist < abs(doc->m_thermal_width) - _2540) && cnt_del < 3);
										if (TestPolygon(curx, cury, PTS, np))
										{
											dist = Distance(curx, cury, mx, my);
											dist += areaW;
											if (dist > (doc->m_thermal_width + _2540))
												continue;
											if (dist < (doc->m_thermal_width - _2540))
												continue;
											area_net->area[i_a].poly->DeleteCorner(ne, 2 + cnt_del, 0, 0);
											bCornerDeleted = 1;
										}
									}
								}
							}
						}
					}
				}
		}
		for (int via = 0; via < area_net->area[i_a].nvias; via++)
		{
			int iconn = area_net->area[i_a].vcon[via];
			int iver = area_net->area[i_a].vtx[via];
			if (iconn >= area_net->nconnects)
				continue;
			if (iver > area_net->connect[iconn].nsegs)
				continue;
			int via_wid = area_net->connect[iconn].vtx[iver].via_w;
			int vx = area_net->connect[iconn].vtx[iver].x;
			int vy = area_net->connect[iconn].vtx[iver].y;
			for (int cr = 0; cr < area_net->area[i_a].poly->GetNumCorners(); cr++)
			{
				// test:
				int numcont = area_net->area[i_a].poly->GetNumContour(cr);
				int cstart = area_net->area[i_a].poly->GetContourStart(numcont);
				int cend = area_net->area[i_a].poly->GetContourEnd(numcont);
				if (cend - cstart < 8)
				{
					cr = cend;
					continue; // fail
				}

				int curx = area_net->area[i_a].poly->GetX(cr);
				int cury = area_net->area[i_a].poly->GetY(cr);
				int dist = Distance(curx, cury, vx, vy);
				if (dist < via_wid/2)
				{
					int mx = curx;
					int my = cury;
					int ne = area_net->area[i_a].poly->GetIndexCornerNext(cr);
					int nne = area_net->area[i_a].poly->GetIndexCornerNext(ne);
					int cnt_del = -1;
					do
					{
						nne = area_net->area[i_a].poly->GetIndexCornerNext(nne);
						curx = area_net->area[i_a].poly->GetX(nne);
						cury = area_net->area[i_a].poly->GetY(nne);
						cnt_del++;
						//
						dist = Distance(curx, cury, mx, my);
						dist += areaW;
					} while ((dist > abs(doc->m_thermal_width) + _2540 || dist < abs(doc->m_thermal_width) - _2540) && cnt_del < 3);
					dist = Distance(curx, cury, vx, vy);
					if (dist < via_wid / 2)
					{
						dist = Distance(curx, cury, mx, my);
						dist += areaW;
						if (dist > (doc->m_thermal_width + _2540))
							continue;
						if (dist < (doc->m_thermal_width - _2540))
							continue;
						area_net->area[i_a].poly->DeleteCorner(ne, 2 + cnt_del, 0, 0);
						bCornerDeleted = 1;
					}
				}
			}
		}
		if (bCornerDeleted)
		{
			if(area_net->area[i_a].poly->GetNumCorners() < 12)
				doc->m_nlist->RemoveArea(area_net, i_a);
			else
				area_net->area[i_a].poly->Draw();
		}
	}

	if (gHost)
	{
		for (int i_a = area_net->nareas - 1; i_a >= mem_n_areas; i_a--)
			doc->m_nlist->SetAreaHatch(area_net, i_a, CPolyLine::DIAGONAL_FULL); // m_sel_net->area[i_a].poly->SetHatch( CPolyLine::DIAGONAL_FULL );
	}
	//
	if (area_net->nareas <= mem_n_areas)
	{
		AfxMessageBox(G_LANGUAGE == 0 ?
			"There are no contours that would fully meet all the given criteria" :
			"Не существует контуров, которые бы полностью соответствовали всем заданным критериям", MB_ICONWARNING);
		doc->m_view->CancelSelection();
		doc->CancelBoardHoles();
		doc->OnEditUndo(); // undo fill copper
	}
	else
	{
		cnet* mem_n = area_net;
		doc->m_view->CancelSelection();
		doc->CancelBoardHoles();
		area_net = mem_n;
		for (int i_ar = area_net->nareas - 1; i_ar >= mem_n_areas; i_ar--)
		{
			id sel_id = area_net->area[i_ar].poly->GetId();
			sel_id.sst = ID_SIDE;
			for (int i_side = 0; i_side < area_net->area[i_ar].poly->GetNumSides(); i_side++)
			{
				sel_id.ii = i_side;
				doc->m_view->NewSelect(area_net, &sel_id, FALSE, 0, 0);
			}
		}
		doc->m_view->SetCursorMode(CUR_GROUP_SELECTED);
		doc->m_view->HighlightGroup();
	}
}