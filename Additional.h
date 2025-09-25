#pragma once

void AlignGroupByRatline( CFreePcbDoc * doc );
void SavePcbView(CFreePcbDoc* doc);
void SavePcbViewWriteRndRect(CStdioFile* f, int x, int y, int w, int h, int r, int a, int L);
void SavePcbViewWriteSegment(CStdioFile* f, int x, int y, int x2, int y2, int w, int L);
void SavePcbViewWritePolyline(CStdioFile* f, CPolyLine* p, int L);
void MarkLegalElementsForExport( CFreePcbDoc* doc );
void SelectLegalElements( CFreePcbDoc* doc );
void CreateClearancesForCopperArea(	CFreePcbDoc* doc,
									CString* crop_net_name,
									cnet* area_net,
									int ia,
									int pad_cl,
									int seg_cl,
									int area_cl,
									int hole_cl,
									int text_cl,
									int board_cl,
									int default_cl,
									int thrml_cl,
									int area_width,
									BOOL gHost);