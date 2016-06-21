
// HardwareDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Hardware.h"
#include "HardwareDlg.h"
#include "AddToCart.h"
#include "RemoveFromCart.h"
#include "DisplayCart.h"
#include "afxdialogex.h"
#include "Checkout.h"
#include <iomanip>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()


};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHardwareDlg dialog

CHardwareDlg::CHardwareDlg(CWnd* pParent): CDialogEx(CHardwareDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CHardwareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, ce2);
}

BEGIN_MESSAGE_MAP(CHardwareDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	/*
	ON_COMMAND(cmViewInventory, &CHardwareDlg::OnViewInventory)
	ON_COMMAND(cmAddToCart, &CHardwareDlg::OnAddToCart)
	ON_COMMAND(cmRemoveFromCart, &CHardwareDlg::OnRemoveFromCart)
	ON_COMMAND(cmDisplayCart, &CHardwareDlg::OnDisplayCart)
	ON_COMMAND(cmCheckout, &CHardwareDlg::OnCheckout)
	ON_COMMAND(cmQuit, &CHardwareDlg::OnQuit)
	*/
	ON_COMMAND(ID_VIEWINVENTORY_VIEW, &CHardwareDlg::OnViewinventoryView)
	ON_COMMAND(ID_CART_ADDTOCART, &CHardwareDlg::OnCartAddtocart)
	ON_COMMAND(ID_CART_REMOVEFROMCART, &CHardwareDlg::OnCartRemovefromcart)
	ON_COMMAND(ID_CART_DISPLAYCONTENTSOFCART, &CHardwareDlg::OnCartDisplayContents)
	ON_COMMAND(ID_CHECKOUT_CHECKOUT, &CHardwareDlg::OnCheckoutCheckout)
	ON_COMMAND(ID_QUIT_QUIT, &CHardwareDlg::OnQuitQuit)
END_MESSAGE_MAP()


// CHardwareDlg message handlers

//static LinkedList<Product> iList;
//static LinkedList<Product> pList;




BOOL CHardwareDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	pCurrMenu = new CMenu;
	pCurrMenu->LoadMenuW(MAKEINTRESOURCE(IDR_MENU1));
	SetMenu(pCurrMenu);
	DrawMenuBar();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	initIList(iList);
	iList.sort();
	displayList(iList);


	//delete pCurrMenu;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHardwareDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHardwareDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHardwareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHardwareDlg::initIList(LinkedList<Product> &list){
	list.insertFirst(new Product( "A100", 20, "Hammer", 9.95 ));	
	list.insertLast(new Product("A250", 25, "Saw", 13.95));
	list.insertLast(new Product("B400", 50, "Flat-Head Nails", 11.99));
	list.insertLast(new Product("C888", 50, "Flat-Head Screwdriver", 6.59));
	list.insertLast(new Product("A499", 75, "Pliers", 4.95));
	list.insertLast(new Product("C667", 50, "Drill", 22.95));
	list.insertLast(new Product("B875", 70, "Plumber's Wrench", 11.90));
	list.insertLast(new Product("D547", 60, "Ladder 10 ft", 70.44));
	list.insertLast(new Product("A910", 85, "Flashlight 10 in", 9.99));
	list.insertLast(new Product("B123", 90, "Assorted Buss Fuses", 4.99));	
	
}

void CHardwareDlg::displayList(LinkedList<Product> &list){
	CStringW s = NULL;
	Product *temp;
	for (int c = 0; c < list.size(); c++){
		temp = list.elementAt(c);
		s += temp->getFullDisplay() + _T("\r\n");

		/*
		s += (list.elementAt(c).getNameDisplay() + _T("\t\t")
		+ list.elementAt(c).getStockNumDisplay() + _T("\t")
		+ list.elementAt(c).getQuantDisplay() + _T("\t")
		+ list.elementAt(c).getPriceDisplay() + _T("\r\n"));
		*/
		//TRACE(s);
		//CStringW s = list.peek().getText('n');
		//s.Format((_T("\r\n%s"), list.elementAt(c).getText('n')));
		
		//appendToCE(ce2, s);
		
	}
	ce2.SetWindowText(LPCTSTR(s));

}

void CHardwareDlg::appendToCE(CEdit &edit, LPCTSTR text){
	int len = edit.GetWindowTextLengthW();
	edit.SetSel(len, len);
	edit.ReplaceSel(text);
}



void CHardwareDlg::OnViewinventoryView()
{
	//TRACE("TEST");
	// TODO: Add your command handler code here
	//AddToCart add(iList, pList);

	//INT_PTR var = -1;

	//var = add.DoModal();

	//if (var == IDOK){
		//do stuff
	//}
	//displayList(iList);
}


void CHardwareDlg::OnCartAddtocart()
{
	// TODO: Add your command handler code here

	AddToCart addDlg(&iList, &pList);
	INT_PTR nRet = -1;
	nRet = addDlg.DoModal();

	if (nRet == IDOK){
		//purchase item
		int index = addDlg.getPurchaseIndex();
		int quant = addDlg.getPurchaseQuant();
		purchaseItem(index, quant);
	}
	displayList(iList);
}


void CHardwareDlg::OnCartRemovefromcart()
{
	// TODO: Add your command handler code here
	if (pList.isEmpty()){
		AfxMessageBox(_T("Shopping cart is empty!"), MB_OK | MB_ICONSTOP);
	}
	else{
		RemoveFromCart remDlg(&iList, &pList);
		INT_PTR nRet = -1;
		nRet = remDlg.DoModal();

		if (nRet == IDOK){
			int indexP = remDlg.getPurchaseIndex();
			int quantRem = remDlg.getPurchaseQuant();
			refundItem(indexP, quantRem);
		}
	}
	displayList(iList);
}


void CHardwareDlg::OnCartDisplayContents()
{
	if (pList.isEmpty()){
		AfxMessageBox(_T("Shopping cart is empty!"), MB_OK | MB_ICONSTOP);
	}
	else{
		DisplayCart crtDlg(&pList);
		INT_PTR nRet = -1;
		nRet = crtDlg.DoModal();
	}
}


void CHardwareDlg::OnCheckoutCheckout()
{
	// TODO: Add your command handler code here
	if (pList.isEmpty()){
		AfxMessageBox(_T("Shopping cart is empty!"), MB_OK | MB_ICONSTOP);
	}
	else{
		Checkout crtDlg(&pList);
		INT_PTR nRet = -1;
		nRet = crtDlg.DoModal();
		if (nRet == IDOK){
			AfxMessageBox(_T("Order successfully placed!"), MB_OK | MB_ICONINFORMATION);
			Product* temp = nullptr;
			for (int i = 0; i < pList.size(); i++){
				temp = pList.elementAt(i);
				temp->setQuant(0);
			}
		}
	}
}


void CHardwareDlg::OnQuitQuit()
{
	// TODO: Add your command handler code here
}

void CHardwareDlg::purchaseItem(int indexI, int quantP){
	Product *tempI = nullptr;
	int indexP;
	int newQuant;

	TRACE("WE'RE PURCHASING!");

	tempI = iList.elementAt(indexI);
	newQuant = (tempI->getQuant() - quantP);
	tempI->setQuant(newQuant);

	if (pList.contains(*tempI, indexP)){
		Product *tempP = nullptr;
		tempP = pList.elementAt(indexP);
		tempI->setQuant(tempP->getQuant() + quantP);
	}
	else{
		pList.insertLast(new Product(tempI->getStockNum(), quantP, tempI->getName(), tempI->getPrice()));
	}
}

void CHardwareDlg::refundItem(int indexP, int quantRem){
	Product *tempI = nullptr;
	Product *tempP = nullptr;
	int indexI;
	int newQuantP;

	tempP = pList.elementAt(indexP);
	newQuantP = tempP->getQuant() - quantRem;
	tempP->setQuant(newQuantP);

	iList.contains(*tempP, indexI);
	tempI = iList.elementAt(indexI);
	tempI->setQuant(tempP->getQuant() + quantRem);
}
