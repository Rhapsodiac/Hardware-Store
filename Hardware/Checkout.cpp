// Checkout.cpp : implementation file
//

#include "stdafx.h"
#include "Hardware.h"
#include "Checkout.h"
#include "afxdialogex.h"

using std::stringstream;
using std::string;


// Checkout dialog

IMPLEMENT_DYNAMIC(Checkout, CDialogEx)

Checkout::Checkout(CWnd* pParent /*=NULL*/)
	: CDialogEx(Checkout::IDD, pParent)
{

}

Checkout::Checkout(LinkedList<Product> *pListMain, CWnd* pParent)
: CDialogEx(Checkout::IDD, pParent){
	pList = pListMain;
}

Checkout::~Checkout()
{
}

void Checkout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_CART, ce_cart);
	DDX_Control(pDX, IDC_EDIT_TAX, ce_tax);
	DDX_Control(pDX, IDC_EDIT_SHIPPING, ce_shipping);
	DDX_Control(pDX, IDC_EDIT_TOTAL, ce_total);
	DDX_Control(pDX, IDC_EDIT_NAME, ce_name);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, ce_address);
	DDX_Control(pDX, IDC_EDIT_CITY, ce_city);
	DDX_Control(pDX, IDC_EDIT_STATE, ce_state);

	Product *temp = nullptr;
	CStringW s = NULL;
	CString shipping = getShippingDisplay();
	CString tax = getTaxDisplay(pList);
	CString total = getTotalDisplay(pList);

	for (int i = 0; i < pList->size(); i++){
		temp = pList->elementAt(i);
		s += temp->getFullDisplay() + _T("\r\n");
	}

	ce_cart.SetWindowText(LPCTSTR(s));
	ce_shipping.SetWindowTextW(LPCTSTR(shipping));
	ce_tax.SetWindowTextW(LPCTSTR(tax));
	ce_total.SetWindowTextW(LPCTSTR(total));
}

CStringW Checkout::getShippingDisplay(){
	const char* myStr = NULL;
	stringstream ss("");
	ss << "$";
	ss << std::fixed << std::setprecision(2);
	ss << 9.95;
	string s2 = ss.str();
	myStr = s2.c_str();
	return getWCHAR(myStr);
}

CStringW Checkout::getWCHAR(const char* myStr){
	size_t s = strlen(myStr) + 1;
	const size_t s2 = 200;
	size_t converted = 0;
	wchar_t wcstring[s2];
	mbstowcs_s(&converted, wcstring, s, myStr, _TRUNCATE);
	return wcstring;
}

CStringW Checkout::getTaxDisplay(LinkedList<Product>* pList){
	double tax = 0, sum = 0;
	Product* temp;
	for (int i = 0; i < pList->size(); i++){
		temp = pList->elementAt(i);
		sum += (temp->getQuant() * temp->getPrice());
	}
	tax = (sum * 0.0625);

	const char* myStr = NULL;
	stringstream ss("");
	ss << "$";
	ss << std::fixed << std::setprecision(2);
	ss << tax;
	string s2 = ss.str();
	myStr = s2.c_str();
	return getWCHAR(myStr);
}

CStringW Checkout::getTotalDisplay(LinkedList<Product>* pList){
	double tax = 0, sum = 0;
	Product* temp;
	for (int i = 0; i < pList->size(); i++){
		temp = pList->elementAt(i);
		sum += (temp->getQuant() * temp->getPrice());
	}
	tax = (sum * 0.0625);

	const char* myStr = NULL;
	stringstream ss("");
	ss << "$";
	ss << std::fixed << std::setprecision(2);
	ss << sum;
	string s2 = ss.str();
	myStr = s2.c_str();
	return getWCHAR(myStr);
}


BEGIN_MESSAGE_MAP(Checkout, CDialogEx)
	ON_BN_CLICKED(IDOK, &Checkout::OnBnClickedOk)
END_MESSAGE_MAP()

void Checkout::OnBnClickedOk(){

	if (ce_name.GetWindowTextLength() == 0 || ce_address.GetWindowTextLengthW() == 0
		|| ce_city.GetWindowTextLengthW() == 0 || ce_state.GetWindowTextLengthW() == 0){
		AfxMessageBox(_T("Fill out all address fields."), MB_OK | MB_ICONSTOP);
	}
	else{
		AfxMessageBox(_T("Your order is on its way!"), MB_OK | MB_ICONEXCLAMATION);
		EndDialog(IDOK);
	}
}


// Checkout message handlers
