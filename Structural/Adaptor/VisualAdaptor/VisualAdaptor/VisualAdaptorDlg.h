
// VisualAdaptorDlg.h : header file
//

#pragma once

#include "Geometry.h"
#include <memory>
#include <map>

#include <boost\accumulators\accumulators.hpp>
#include <boost\accumulators\statistics.hpp>

const std::vector<std::shared_ptr<VectorObject>> vectorObjects{
	std::make_shared<VectorRectangle>(10, 10, 100, 100),
	std::make_shared<VectorRectangle>(30, 30, 60, 60)
};

struct LineToPointCachingAdaptor
{
	typedef std::vector<Point> Points;

	LineToPointCachingAdaptor(Line& line)
	{
		boost::hash<Line> hash;
		line_hash = hash(line);

		if (cache.find(line_hash) != cache.end())
		{
			return;
		}

		static int count = 0;
		TRACE("%d: Generating points for line\n", count++);

		std::vector<double> values{ 0,1,2,3,4,5,6 };
		boost::accumulators::accumulator_set<double,
			boost::accumulators::stats<boost::accumulators::tag::mean>> acc;
		for (auto x : values)
			acc(x);

		TRACE("test %f test", boost::accumulators::mean(acc));

		Points points;

		int left = min(line.start.x, line.end.x);
		int right = max(line.start.x, line.end.x);
		int top = min(line.start.y, line.end.y);
		int bottom = max(line.start.y, line.end.y);
		int dx = right - left;
		int dy = line.end.y - line.start.y;

		if (dx == 0)
		{
			//vertical
			for (int y = top; y <= bottom; ++y)
			{
				points.emplace_back(Point{ left, y });
			}
		}
		else if (dy == 0)
		{
			for (int x = left; x <= right; ++x)
			{
				points.emplace_back(Point{ x, top });
			}
		}

		cache[line_hash] = points;
	}

	virtual Points::iterator begin()
	{
		return cache[line_hash].begin();
	}

	virtual Points::iterator end()
	{
		return cache[line_hash].end();
	}

private:
	size_t line_hash;
	static std::map<size_t, std::vector<Point>> cache;
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
