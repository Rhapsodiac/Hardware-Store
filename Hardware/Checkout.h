#pragma once
#include "LinkedList.h"
#include "Product.h"

// Checkout dialog

class Checkout : public CDialogEx
{
	DECLARE_DYNAMIC(Checkout)

public:
	Checkout(CWnd* pParent = NULL);// standard constructor
	Checkout(LinkedList<Product> *pList, CWnd* pParent = NULL);
	virtual ~Checkout();

	CEdit ce_cart;
	CEdit ce_tax;
	CEdit ce_shipping;
	CEdit ce_total;
	CEdit ce_name;
	CEdit ce_address;
	CEdit ce_city;
	CEdit ce_state;

	LinkedList<Product> *pList;

	double tax, shipping, total;
	CString name, address, city, state;

	CStringW getWCHAR(const char* myStr);
	CStringW getShippingDisplay();
	CStringW getTaxDisplay(LinkedList<Product>*);
	CStringW getTotalDisplay(LinkedList<Product>*);

// Dialog Data
	enum { IDD = IDD_CHECKOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
};
