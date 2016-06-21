#pragma once

#include "LinkedList.h"
#include "Product.h"


// RemoveFromCart dialog

class RemoveFromCart : public CDialogEx
{
	DECLARE_DYNAMIC(RemoveFromCart)

public:
	RemoveFromCart(CWnd* pParent = NULL);   // standard constructor
	RemoveFromCart(LinkedList<Product> *iList, LinkedList<Product> *pList, CWnd* pParent = NULL);
	virtual ~RemoveFromCart();

	CComboBox cb_invenCombo;
	CEdit ce_quantHave;
	CEdit ce_quantRemove;
	CEdit ce_price;
	CEdit ce_name;

	LinkedList<Product> *iList;
	LinkedList<Product> *pList;

	int purIndex;
	int purQuant;

	int getPurchaseIndex();
	int getPurchaseQuant();

// Dialog Data
	enum { IDD = IDD_REMOVE_FROM_CART };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeComboStock();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditQuant2();
};
