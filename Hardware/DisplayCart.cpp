// DisplayCart.cpp : implementation file
//

#include "stdafx.h"
#include "Hardware.h"
#include "DisplayCart.h"
#include "afxdialogex.h"


// DisplayCart dialog

IMPLEMENT_DYNAMIC(DisplayCart, CDialogEx)

DisplayCart::DisplayCart(CWnd* pParent /*=NULL*/)
	: CDialogEx(DisplayCart::IDD, pParent)
{

}

DisplayCart::DisplayCart(LinkedList<Product> *pListMain, CWnd* pParent)
: CDialogEx(DisplayCart::IDD, pParent){
	pList = pListMain;
}

DisplayCart::~DisplayCart()
{
}

void DisplayCart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CUST_CART, ce_cart);

	Product *temp = nullptr;
	CStringW s = NULL;

	for (int i = 0; i < pList->size(); i++){
		temp = pList->elementAt(i);
		s += temp->getFullDisplay() + _T("\r\n");
	}
	ce_cart.SetWindowText(LPCTSTR(s));
	
}


BEGIN_MESSAGE_MAP(DisplayCart, CDialogEx)
	ON_BN_CLICKED(IDOK, &DisplayCart::OnBnClickedOk)
END_MESSAGE_MAP()


// DisplayCart message handlers


void DisplayCart::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	DisplayCart::OnOK();
}
