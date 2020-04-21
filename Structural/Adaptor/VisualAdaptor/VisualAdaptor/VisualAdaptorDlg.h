
// VisualAdaptorDlg.h : header file
//

#pragma once

#include "Geometry.h"
#include <memory>

const std::vector<std::shared_ptr<VectorObject>> vectorObjects{
	std::make_shared<VectorRectangle>(10, 10, 100, 100),
	std::make_shared<VectorRectangle>(30, 30, 60, 60)
};

struct LineToPointAdaptor
{
	typedef std::vector<Point> Points;

	LineToPointAdaptor(Line& line);

	virtual Points::iterator begin()
	{
		return points.begin();
	}

	virtual Points::iterator end()
	{
		return points.end();
	}

private:
	Points points;
};

// CVisualAdaptorDlg dialog
class CVisualAdaptorDlg : public CDialogEx
{
// Construction
public:
	CVisualAdaptorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISUALADAPTOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	void DrawPoints(CPaintDC& dc, 
					std::vector<Point>::iterator begin,
					std::vector<Point>::iterator end);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
