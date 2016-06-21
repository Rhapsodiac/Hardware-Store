// AddToCart.cpp : implementation file
//

#include "stdafx.h"
#include "Hardware.h"
#include "AddToCart.h"
#include "afxdialogex.h"


// AddToCart dialog

IMPLEMENT_DYNAMIC(AddToCart, CDialogEx)

AddToCart::AddToCart(CWnd* pParent /*=NULL*/)
: CDialogEx(AddToCart::IDD, pParent)
{

}

AddToCart::AddToCart(LinkedList<Product> *iListMain, LinkedList<Product> *pListMain, CWnd* pParent)
: CDialogEx(AddToCart::IDD, pParent)
{
	iList = iListMain;
	pList = pListMain;
	purIndex = 0;
	purQuant = 0;
}

AddToCart::~AddToCart()
{
}

void AddToCart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_STOCK, cb_stockCombo);
	DDX_Control(pDX, IDC_EDIT_QUANT, ce_quantity);
	DDX_Control(pDX, IDC_EDIT_NAME, ce_name);
	DDX_Control(pDX, IDC_EDIT_PRICE, ce_price);

	Product* temp = nullptr;

	//TRACE(iList->elementAt(0).getStockNumDisplay());

	//displays stockNums in combo box
	for (int i = 0; i < iList->size(); i++){
		temp = iList->elementAt(i);
		cb_stockCombo.AddString(temp->getStockNumDisplay());
	}
}

BEGIN_MESSAGE_MAP(AddToCart, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_STOCK, &AddToCart::OnCbnSelchangeComboStock)
	ON_BN_CLICKED(IDOK, &AddToCart::OnBnClickedOk)
END_MESSAGE_MAP()


// AddToCart message handlers


void AddToCart::OnCbnSelchangeComboStock()
{
	// TODO: Add your control notification handler code here
	int index;
	Product *temp = nullptr;
	CStringW temp1 = NULL, temp2 = NULL;

	index = cb_stockCombo.GetCurSel();
	temp = iList->elementAt(index);


	if (temp->quant > 0){
		temp1 = temp->getNameDisplay();
		temp2 = temp->getPriceDisplay();
		//TRACE("\nTEST VALUES: \n");
		//TRACE(temp1);
		//TRACE("\n");
		//TRACE(temp2);

		//name.SetWindowText(LPCTSTR("a"));
		ce_name.SetWindowText(LPCTSTR(temp1));
		ce_price.SetWindowText(LPCTSTR(temp2));
	}
	else{
		ce_name.SetWindowText(temp->getOutOfStock());
		ce_price.SetWindowText(temp->getOutOfStock());
	}

	//cb_stockCombo.ResetContent();

}


void AddToCart::OnBnClickedOk()
{
	//CDialogEx::OnOK();
	// TODO: Add your control notification handler code here

	if (cb_stockCombo.GetCurSel() == CB_ERR || ce_quantity.GetWindowTextLength() == 0){ //missing fields
		AfxMessageBox(_T("Select an item and set quantity desired."), MB_OK | MB_ICONSTOP);
	}
	else{
		Product *temp = nullptr;
		int index = cb_stockCombo.GetCurSel();
		temp = iList->elementAt(index);

		CString s_quant = NULL;
		ce_quantity.GetWindowText(s_quant);
		int quant = _ttoi(s_quant);

		if (temp->getQuant() - quant < 0){ //not enough stock
		//if (iList->elementAt(index)->getQuant() < 0){
			AfxMessageBox(_T("Insufficient Quantity in Stock."), MB_OK | MB_ICONSTOP);
		}		
		else{		
			//fields good, quantity good			
			purIndex = index;
			purQuant = quant;
			EndDialog(IDOK);
		}
	}

}

int AddToCart::getPurchaseIndex(){
	return purIndex;
}

int AddToCart::getPurchaseQuant(){
	return purQuant;
}


//pList->insertLast(Product(*temp, quant));
//pList.insertLast(Product(iList.elementAt(index), quant));
//iList->elementAt(index).quant = 1;
//iList.elementAt(index).setQuant(1);
//temp->setQuant(temp->getQuant() - quant);
//TRACE(iList->elementAt(index).getQuantDisplay());
////TRACE(temp->getQuantDisplay());

