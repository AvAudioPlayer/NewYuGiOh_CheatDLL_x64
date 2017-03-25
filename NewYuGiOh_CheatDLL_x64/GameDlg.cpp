// GameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NewYuGiOh_CheatDLL_x64.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "CardExtend.h"
#include <algorithm>

// CGameDlg dialog

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGameDlg::IDD, pParent)
{

}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_GETALLCARD, &CGameDlg::OnBnClickedBtnGetallcard)
	ON_BN_CLICKED(IDC_SETNEXTCARD, &CGameDlg::OnBnClickedSetnextcard)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CGameDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON1, &CGameDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CGameDlg::OnNMClickList1)
END_MESSAGE_MAP()

BOOL CGameDlg::OnInitDialog()
{
	CListCtrl * m_List = ((CListCtrl *)GetDlgItem(IDC_LIST1));
	if (m_List != NULL)
		m_List->SetExtendedStyle(m_List->GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	CComboBox* pCCB_NextCard = static_cast<CComboBox *>(GetDlgItem(IDC_CCB_NextCard));
	pCCB_NextCard->InsertString(0, L"Ӱ��Ů������ëɨ");
	pCCB_NextCard->InsertString(1, L"�׻�");

	CComboBox* pCCB_DeskCard = static_cast<CComboBox *>(GetDlgItem(IDC_CCB_DeskCard));
	pCCB_DeskCard->InsertString(0, L"�Ƽ��� �����(1�غ��ƻ�һ���ٻ�)");
	pCCB_DeskCard->InsertString(1, L"ʥ������ �ǳ�����(1�غ�һ�����ӹ���Ч��)");
	pCCB_DeskCard->InsertString(2, L"����������(ħ�������ƻ���Ч)");
	pCCB_DeskCard->InsertString(3, L"��������(���Է�Ҳ�ٻ�������)");
	pCCB_DeskCard->InsertString(4, L"������(����5000)");
	pCCB_DeskCard->InsertString(5, L"��ս���� ս�����");
	pCCB_DeskCard->InsertString(6, L"�����ħ(�Լ��غϹ���+1W)");
	pCCB_DeskCard->InsertString(7, L"���ȱ��˵�ħ��(�ƻ����ﲢ�ҵ�Ѫ)");
	pCCB_DeskCard->InsertString(8, L"��̬��");
	pCCB_DeskCard->InsertString(9, L"������ ������˹");
	pCCB_DeskCard->InsertString(10, L"а�� Ĩ����");
	pCCB_DeskCard->InsertString(11, L"а�� �־�֮Դ");
	pCCB_DeskCard->InsertString(12, L"����̫��");
	pCCB_DeskCard->InsertString(13, L"��ħ��");
	pCCB_DeskCard->InsertString(14, L"���صĻ���ɱ�� ��������");
	pCCB_DeskCard->InsertString(15, L"������� -���ɵ�ʹ��-");
	pCCB_DeskCard->InsertString(16, L"����������");
	pCCB_DeskCard->InsertString(17, L"����ʿ ��ħ����Ů");
	pCCB_DeskCard->InsertString(18, L"Ů���ʥ��");
	pCCB_DeskCard->InsertString(19, L"���侵����");

	return TRUE;
}


// CGameDlg message handlers
LPCWSTR ConvertNumber(__in LPCWSTR pwszFormat, ...)
{
	va_list		args;
	static wchar_t		szBuff[1024] = { 0 };

	va_start(args, pwszFormat);
	_vsnwprintf_s(szBuff, _countof(szBuff) - 1, _TRUNCATE, pwszFormat, args);
	va_end(args);

	return szBuff;
}

void CGameDlg::OnBnClickedBtnGetallcard()
{
	CListCtrl * m_List = (CListCtrl *)GetDlgItem(IDC_LIST1);
	m_List->DeleteAllItems();
	int nColumnCount = m_List->GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
	{
		m_List->DeleteColumn(0);
	}

	m_List->InsertColumn(0, L"ID", LVCFMT_LEFT, 80);
	m_List->InsertColumn(1, L"Name", LVCFMT_LEFT, 150);
	m_List->InsertColumn(2, L"Star", LVCFMT_LEFT, 30);
	m_List->InsertColumn(3, L"Power/Defence", LVCFMT_LEFT, 100);
	m_List->InsertColumn(4, L"Attribute", LVCFMT_LEFT, 50);
	m_List->InsertColumn(5, L"Detail", LVCFMT_LEFT, 400);
	
	std::vector<CCard> VecCard;
	CCardExtend::GetInstance().GetALLCard(VecCard);

	CEdit* pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT_CARDNAME));
	CString strText;
	pEdit->GetWindowTextW(strText);

	if (strText.Trim() != L"")
	{
		VecCard.erase(std::remove_if(VecCard.begin(), VecCard.end(), [&strText](CONST CCard& Card){ return Card.GetCardName().find(strText.GetBuffer()) == -1 && Card.GetCardAttributeText().find(strText.GetBuffer()) == -1; }), VecCard.end());
	}

	for (CONST auto& itm : VecCard)
	{
		int nRow = m_List->InsertItem(m_List->GetItemCount(), ConvertNumber(L"%X", itm.GetCardID()));

		m_List->SetItemText(nRow, 1, itm.GetCardName().c_str());
		m_List->SetItemText(nRow, 2, ConvertNumber(L"%d", itm.GetStarCount()));
		m_List->SetItemText(nRow, 3, ConvertNumber(L"%d/%d", itm.GetPower(), itm.GetDefence()));
		m_List->SetItemText(nRow, 4, itm.GetCardAttributeText().c_str());
		m_List->SetItemText(nRow, 5, itm.GetCardDetail().c_str());
	}
}

struct DeskCardContent
{
	int nIndex;
	DWORD dwCardId;
	std::wstring wsCardName;
};

void CGameDlg::OnBnClickedSetnextcard()
{
	/*CListCtrl * m_List = (CListCtrl *)GetDlgItem(IDC_LIST1);
	m_List->DeleteAllItems();
	int nColumnCount = m_List->GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
	{
		m_List->DeleteColumn(0);
	}

	m_List->InsertColumn(0, L"ID", LVCFMT_LEFT, 80);
	m_List->InsertColumn(1, L"Name", LVCFMT_LEFT, 150);
	m_List->InsertColumn(2, L"Star", LVCFMT_LEFT, 30);
	m_List->InsertColumn(3, L"Power/Defence", LVCFMT_LEFT, 100);
	m_List->InsertColumn(4, L"Attribute", LVCFMT_LEFT, 50);
	m_List->InsertColumn(5, L"Detail", LVCFMT_LEFT, 400);

	std::vector<CCard> VecCard;
	CCardExtend::GetInstance().GetCurrentCardGroup(VecCard);*/

	/*CEdit* pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT_CARDNAME));
	CString strText;
	pEdit->GetWindowTextW(strText);

	if (strText.Trim() != L"")
	{
		VecCard.erase(std::remove_if(VecCard.begin(), VecCard.end(), [&strText](CONST CCard& Card){ return Card.GetCardName().find(strText.GetBuffer()) == -1; }), VecCard.end());
	}

	for (CONST auto& itm : VecCard)
	{
		int nRow = m_List->InsertItem(m_List->GetItemCount(), ConvertNumber(L"%X", itm.GetFullID()));

		m_List->SetItemText(nRow, 1, itm.GetCardName().c_str());
		m_List->SetItemText(nRow, 2, ConvertNumber(L"%d", itm.GetStarCount()));
		m_List->SetItemText(nRow, 3, ConvertNumber(L"%d/%d", itm.GetPower(), itm.GetDefence()));
		m_List->SetItemText(nRow, 4, itm.GetCardAttributeText().c_str());
		m_List->SetItemText(nRow, 5, itm.GetCardDetail().c_str());
	}*/

	CONST static std::vector<DeskCardContent> VecDeskCardContent =
	{
		{ 0, 0x1246, L"Ӱ��Ů������ëɨ" },
		{ 1, 0x10F7, L"�׻�" },
	};

	CComboBox* pCCB_NextCard = static_cast<CComboBox*>(GetDlgItem(IDC_CCB_NextCard));
	int nIndex = pCCB_NextCard->GetCurSel();
	if (nIndex == -1)
		return;

	if (nIndex >= VecDeskCardContent.size())
		return;

	CCardExtend::GetInstance().SetNextCard(VecDeskCardContent.at(nIndex).dwCardId);
}


void CGameDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	*pResult = 0;
}


void CGameDlg::OnBnClickedButton1()
{
	CONST static std::vector<DeskCardContent> VecDeskCardContent = 
	{
		{ 0, 0x252A, L"�Ƽ��� �����" },
		{ 1, 0x2E9B, L"ʥ������ �ǳ�����" },
		{ 2, 0x239F, L"����������" },
		{ 3, 0x2FE2, L"�������� �������ض�����ϣ�Ͷ���" },
		{ 4, 0x157E, L"������" },
		{ 5, 0x24BA, L"��ս���� ս�����" },
		{ 6, 0x1CAE, L"�����ħ ����̩��" },
		{ 7, 0x1CF3, L"�ڱ���-���ȱ��˵�ħ��" },
		{ 8, 0x199A, L"��̬��" },
		{ 9, 0x2E68, L"������ ������˹" },
		{ 10, 0x1BB4, L"а�� Ĩ����" },
		{ 11, 0x1905, L"а�� �־�֮Դ" },
		{ 12, 0x255A, L"����̫��" },
		{ 13, 0x19A5, L"��ħ��" },
		{ 14, 0x2C5E, L"���صĻ���ɱ�� ��������" },
		{ 15, 0x16E4, L"������� -���ɵ�ʹ��-" },
		{ 16, 0x2E6B, L"����������" },
		{ 17, 0x1B8F, L"����ʿ ��ħ����Ů" },
		{ 18, 0x2E72, L"Ů���ʥ��" },
		{ 19, 0x2E6C, L"���侵����" },
	};


	CComboBox* pCCB_DeskCard = static_cast<CComboBox*>(GetDlgItem(IDC_CCB_DeskCard));
	int nIndex = pCCB_DeskCard->GetCurSel();
	if (nIndex == -1)
		return;

	if (nIndex >= VecDeskCardContent.size())
		return;

	CCardExtend::GetInstance().SetCardToDesk(VecDeskCardContent.at(nIndex).dwCardId);
}


void CGameDlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1 && pNMListView->iSubItem != -1)
	{
		CListCtrl * m_list = (CListCtrl *)GetDlgItem(IDC_LIST1);
		CString str = m_list->GetItemText(pNMListView->iItem, pNMListView->iSubItem);
		MsgBoxLog(L"str=%s, Item=%d, iSub=%d", str.GetBuffer(), pNMListView->iItem, pNMListView->iSubItem);
		CEdit* pEdit = reinterpret_cast<CEdit*>(GetDlgItem(IDC_EDIT_CARDNAME));
		pEdit->SetWindowTextW(str.GetBuffer());
	}
	*pResult = 0;
}
