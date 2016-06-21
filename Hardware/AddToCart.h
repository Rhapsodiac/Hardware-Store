#pragma once

#include "LinkedList.h"
#include "Product.h"


// AddToCart dialog

class AddToCart : public CDialogEx
{
	DECLARE_DYNAMIC(AddToCart)

public:
	AddToCart(CWnd* pParent = NULL); // standard constructor
	AddToCart(LinkedList<Product> *iList, LinkedList<Product> *pList, CWnd* pParent = NULL);
	virtual ~AddToCart();

	CComboBox cb_stockCombo;
	CEdit ce_quantity;
	CEdit ce_price;
	CEdit ce_name;

// Dialog Data
	enum { IDD = IDD_ADDTOCART };

	//int index;
	LinkedList<Product> *iList;
	LinkedList<Product> *pList;

	int purIndex;
	int purQuant;

	int getPurchaseIndex();
	int getPurchaseQuant();
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboStock();
	afx_msg void OnBnClickedOk();
};
