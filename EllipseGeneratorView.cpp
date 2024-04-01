// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface
// (the "Fluent UI") and is provided only as referential material to supplement the
// Microsoft Foundation Classes Reference and related electronic documentation
// included with the MFC C++ library software.
// License terms to copy, use or distribute the Fluent UI are available separately.
// To learn more about our Fluent UI licensing program, please visit
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// EllipseGeneratorView.cpp : implementation of the CEllipseGeneratorView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "EllipseGenerator.h"
#endif

#include "EllipseGeneratorDoc.h"
#include "EllipseGeneratorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEllipseGeneratorView

IMPLEMENT_DYNCREATE(CEllipseGeneratorView, CView)

BEGIN_MESSAGE_MAP(CEllipseGeneratorView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEllipseGeneratorView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_START, &CEllipseGeneratorView::OnButtonStart)
	ON_COMMAND(ID_BUTTON_SUSPEND, &CEllipseGeneratorView::OnButtonSuspend)
	ON_COMMAND(ID_BUTTON_RESUME, &CEllipseGeneratorView::OnButtonResume)
END_MESSAGE_MAP()

// CEllipseGeneratorView construction/destruction

CEllipseGeneratorView::CEllipseGeneratorView() noexcept
{
	// TODO: add construction code here
	m_pCurrentThread = NULL;
	m_iCounter = 0;

	x = 300 + 150 * cos(8);
	y = 300 + 150 * sin(8);

	x1 = 300 + 200 * cos(4);
	y1 = 300 + 200 * sin(4);

}

CEllipseGeneratorView::~CEllipseGeneratorView()
{
}

BOOL CEllipseGeneratorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEllipseGeneratorView drawing

void CEllipseGeneratorView::OnDraw(CDC* pDC)
{
	CEllipseGeneratorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	
	CPen blackPen, redPen, pinkPen, bluePen;
	blackPen.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	redPen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	pinkPen.CreatePen(PS_SOLID, 3, RGB(235, 52, 229));
	
	CBrush yellowBrush, greenBrush, blueBrush;
	yellowBrush.CreateSolidBrush(RGB(255, 255, 0));
	greenBrush.CreateSolidBrush(RGB(89, 235, 52));
	blueBrush.CreateSolidBrush(RGB(52, 235, 220));

	CPen* pOldPen = pDC->SelectObject(&blackPen);
	
	pDC->Ellipse(100, 100, 500, 500);
	pDC->Ellipse(150, 150, 450, 450);

	pDC->SelectObject(&redPen);
	
	CBrush* oldBrush = pDC->SelectObject(&yellowBrush);
	
	pDC->Ellipse(275, 275, 325, 325);

	pDC->SelectObject(&pinkPen);
	pDC->SelectObject(&greenBrush);
	pDC->Ellipse(x + 15, y + 15, x - 15, y - 15);
	
	pDC->SelectObject(&blueBrush);
	pDC->Ellipse(x1 + 15, y1 + 15, x1 - 15, y1 - 15);
	
}


// CEllipseGeneratorView printing


void CEllipseGeneratorView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEllipseGeneratorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEllipseGeneratorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEllipseGeneratorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CEllipseGeneratorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEllipseGeneratorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEllipseGeneratorView diagnostics

#ifdef _DEBUG
void CEllipseGeneratorView::AssertValid() const
{
	CView::AssertValid();
}

void CEllipseGeneratorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEllipseGeneratorDoc* CEllipseGeneratorView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEllipseGeneratorDoc)));
	return (CEllipseGeneratorDoc*)m_pDocument;
}
#endif //_DEBUG


// CEllipseGeneratorView message handlers


void CEllipseGeneratorView::OnButtonStart()
{
	// TODO: Add your command handler code here
	m_pCurrentThread=AfxBeginThread(CEllipseGeneratorView::StartThread,this);
}


void CEllipseGeneratorView::OnButtonSuspend()
{
	// TODO: Add your command handler code here
	// AfxMessageBox(_T("Suspend"));
	m_pCurrentThread->SuspendThread();
}


void CEllipseGeneratorView::OnButtonResume()
{
	// TODO: Add your command handler code here
	m_pCurrentThread->ResumeThread();
}


UINT CEllipseGeneratorView::StartThread(LPVOID Param)
{
	// TODO: Add your implementation code here.
	CEllipseGeneratorView* pView = (CEllipseGeneratorView*)Param;
	//CPoint MyPoint(0, 0);
	int i = 8;
	int j = 4;
	while (1)
	{
		i += 6;
		j += 6;
		pView->x = 300 + 150 * cos(i);
		pView->y = 300 + 150 * sin(i);

		pView->x1 = 300 + 200 * cos(j);
		pView->y1 = 300 + 200 * sin(j);

		pView->Invalidate();
		Sleep(300);
}
	return 0;
}
