#pragma once

void AlignGroupByRatline( CFreePcbDoc * doc );
void SavePcbView(CFreePcbDoc* doc);
void SavePcbViewWriteRndRect(CStdioFile* f, int x, int y, int w, int h, int r, int a, int L);
void SavePcbViewWriteSegment(CStdioFile* f, int x, int y, int x2, int y2, int w, int L);
void SavePcbViewWritePolyline(CStdioFile* f, CPolyLine* p, int L);
void MarkLegalElementsForExport( CFreePcbDoc* doc );