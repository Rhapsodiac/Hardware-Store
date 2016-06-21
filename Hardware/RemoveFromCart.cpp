// RemoveFromCart.cpp : implementation file
//

#include "stdafx.h"
#include "Hardware.h"
#include "RemoveFromCart.h"
#include "afxdialogex.h"


// RemoveFromCart dialog

IMPLEMENT_DYNAMIC(RemoveFromCart, CDialogEx)

RemoveFromCart::RemoveFromCart(CWnd* pParent /*=NULL*/)
: CDialogEx(RemoveFromCart::IDD, pParent)
{

}

RemoveFromCart::RemoveFromCart(LinkedList<Product> *iListMain, LinkedList<Product> *pListMain, CWnd* pParent)
: CDialogEx(RemoveFromCart::IDD, pParent)
{
	iList = iListMain;
	pList = pListMain;
	purIndex = 0;
	purQuant = 0;
}

RemoveFromCart::~RemoveFromCart()
{
}

void RemoveFromCart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_INVEN, cb_invenCombo);
	DDX_Control(pDX, IDC_EDIT_QUANT2, ce_quantRemove);
	DDX_Control(pDX, IDC_EDIT_NAME2, ce_name);
	DDX_Control(pDX, IDC_EDIT_PRICE2, ce_price);
	DDX_Control(pDX, IDC_QUANT_HAVE, ce_quantHave);

	Product* temp = nullptr;

	for (int i = 0; i < pList->size(); i++){
		temp = pList->elementAt(i);
		cb_invenCombo.AddString(temp->getStockNumDisplay());
	}


}


BEGIN_MESSAGE_MAP(RemoveFromCart, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_INVEN, &RemoveFromCart::OnCbnSelchangeComboStock)
	ON_BN_CLICKED(IDOK, &RemoveFromCart::OnBnClickedOk)
END_MESSAGE_MAP()


// RemoveFromCart message handlers
void RemoveFromCart::OnCbnSelchangeComboStock()
{
	// TODO: Add your control notification handler code here
	int index;
	Product *temp = nullptr;
	CStringW temp1 = NULL, temp2 = NULL, temp3 = NULL;

	index = cb_invenCombo.GetCurSel();
	temp = pList->elementAt(index);

	if (temp->quant > 0){
		temp1 = temp->getNameDisplay();
		temp2 = temp->getPriceDisplay();
		temp3 = temp->getQuantDisplay();
		ce_name.SetWindowText(LPCTSTR(temp1));
		ce_price.SetWindowText(LPCTSTR(temp2));
		ce_quantHave.SetWindowText(LPCTSTR(temp3));
	}
	else{
		ce_name.SetWindowText(temp->getOutOfStock());
		ce_price.SetWindowText(temp->getOutOfStock());
		ce_quantHave.SetWindowText(temp->getOutOfStock());
	}
	//cb_stockCombo.ResetContent();
}

void RemoveFromCart::OnBnClickedOk()
{
	//CDialogEx::OnOK();
	// TODO: Add your control notification handler code here

	if (cb_invenCombo.GetCurSel() == CB_ERR || ce_quantRemove.GetWindowTextLength() == 0){ //missing fields
		AfxMessageBox(_T("Select an item and set quantity to remove."), MB_OK | MB_ICONSTOP);
	}
	else{
		Product *temp = nullptr;
		int indexP = cb_invenCombo.GetCurSel();
		temp = pList->elementAt(indexP);

		CString s_quant = NULL;
		ce_quantRemove.GetWindowText(s_quant);
		int quantRem = _ttoi(s_quant);

		if (temp->getQuant() - quantRem < 0){
			//not enough stock
			AfxMessageBox(_T("Insufficient Quantity in Cart."), MB_OK | MB_ICONSTOP);
		}
		else{
			//fields good, quantity good			
			purIndex = indexP;
			purQuant = quantRem;
			EndDialog(IDOK);
		}
	}
}

int RemoveFromCart::getPurchaseIndex(){
	return purIndex;
}

int RemoveFromCart::getPurchaseQuant(){
	return purQuant;
}