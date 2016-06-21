
// HardwareDlg.h : header file
//

#pragma once

#include "LinkedList.h"
#include "Product.h"
#include "afxwin.h"


// CHardwareDlg dialog
class CHardwareDlg : public CDialogEx
{
// Construction
public:
	CHardwareDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_HARDWARE_DIALOG };

	LinkedList<Product> iList;
	LinkedList<Product> pList;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void initIList(LinkedList<Product>&);
	void initPList(LinkedList<Product>&);
	void displayList(LinkedList<Product>&);
	void appendToCE(CEdit&, LPCTSTR);
	void purchaseItem(int, int);
	void refundItem(int, int);

//Menu items
private:
	CMenu *pCurrMenu;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	/*
	afx_msg void OnViewInventory();
	afx_msg void OnAddToCart();
	afx_msg void OnRemoveFromCart();
	afx_msg void OnDisplayCart();
	afx_msg void OnCheckout();
	afx_msg void OnQuit();
	*/
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewinventoryView();
	afx_msg void OnCartAddtocart();
	afx_msg void OnCartRemovefromcart();
	afx_msg void OnCartDisplayContents();
	afx_msg void OnCheckoutCheckout();
	afx_msg void OnQuitQuit();
	CEdit ce2;
};
