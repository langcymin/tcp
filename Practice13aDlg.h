
// Practice13aDlg.h: 헤더 파일
//

#pragma once


// CPractice13aDlg 대화 상자
class CPractice13aDlg : public CDialogEx
{
// 생성입니다.
public:
	CPractice13aDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PRACTICE13A_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CIPAddressCtrl m_IPAddress;
	int m_nChatMode;
	CListBox m_listChat;
	CString m_strMyIP;
	CString m_strOtherIP;
	afx_msg void OnClickedRadioServer();
	afx_msg void OnRadioClient();
	afx_msg void OnClickedButtonConnect();
	afx_msg void OnClickedButtonSend();
	void ReceiveData(CString strReceive);
	void Accept(CString strSock);

	//오목 게임 함수
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	char m_is_white=2;
	char m_dol[16][16] = { {0,}, };
	int m_SumX;
	int m_TestV;
	void fivedolcheck(char(&m_dol)[16][16], int& m_SumX);
	bool checkCondition(int j, int k, char(&m_dol)[16][16]);
	bool checkConditionver(int j, int k, char(&m_dol)[16][16]);
	bool checkConditiondia(int j, int k, char(&m_dol)[16][16]);
	bool checkConditiondia2(int j, int k, char(&m_dol)[16][16]);
	afx_msg void OnBnClickedButtonReset();

	//오목 돌 데이터를 주고받기 위한 함수
	void PlaceOpponentStone(CString strPosition);
	afx_msg void OnBnClickedButtonWhosblack();
	void SetWhite();
};
