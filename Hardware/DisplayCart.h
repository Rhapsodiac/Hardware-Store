#pragma once

#include "LinkedList.h"
#include "Product.h"

// DisplayCart dialog

class DisplayCart : public CDialogEx
{
	DECLARE_DYNAMIC(DisplayCart)

public:
	DisplayCart(CWnd* pParent = NULL);// standard constructor
	DisplayCart(LinkedList<Product> *pList, CWnd* pParent = NULL);
	virtual ~DisplayCart();

	CEdit ce_cart;

// Dialog Data
	enum { IDD = IDD_DISPLAY_CART1 };

	LinkedList<Product> *pList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
