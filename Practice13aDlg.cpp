
// Practice13aDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Practice13a.h"
#include "Practice13aDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPractice13aDlg 대화 상자



CPractice13aDlg::CPractice13aDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PRACTICE13A_DIALOG, pParent)
	, m_nChatMode(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPractice13aDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_SERVER, m_IPAddress);
	DDX_Radio(pDX, IDC_RADIO_SERVER, m_nChatMode);
	DDX_Control(pDX, IDC_LIST_CHAT, m_listChat);
}

BEGIN_MESSAGE_MAP(CPractice13aDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_SERVER, &CPractice13aDlg::OnClickedRadioServer)
	ON_COMMAND(IDC_RADIO_CLIENT, &CPractice13aDlg::OnRadioClient)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CPractice13aDlg::OnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CPractice13aDlg::OnClickedButtonSend)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CPractice13aDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_WHOSBLACK, &CPractice13aDlg::OnBnClickedButtonWhosblack)
END_MESSAGE_MAP()


// CPractice13aDlg 메시지 처리기

BOOL CPractice13aDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//IP 주소 가져오기
	char name[255];
	PHOSTENT hostinfo;
	if (gethostname(name, sizeof(name)) == 0)
	{
		if ((hostinfo = gethostbyname(name)) != NULL)
		{
			m_strMyIP = inet_ntoa(*(struct in_addr*) * hostinfo->h_addr_list);

		}
	}

	//컨트롤 초기화
	m_IPAddress.SetWindowTextW(m_strMyIP);
	m_IPAddress.EnableWindow(FALSE);
	SetDlgItemText(IDC_BUTTON_CONNECT, _T("OPEN"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPractice13aDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPractice13aDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // Device context for painting
		// Drawing code here

		// Draw the board
		for (int y = 1; y <= 15; ++y)
		{
			for (int x = 1; x <= 15; ++x)
			{
				dc.Rectangle(x * 30, y * 30, x * 30 + 30, y * 30 + 30);
			}
		}

		// Draw the stones
		for (int y = 0; y < 15; ++y)
		{
			for (int x = 0; x < 15; ++x)
			{
				int posX = (x + 1) * 30;
				int posY = (y + 1) * 30;

				if (m_dol[y][x] == 2) // If black stone
				{
					CBrush blackBrush(RGB(0, 0, 0));
					dc.SelectObject(&blackBrush);
					dc.Ellipse(posX - 15, posY - 15, posX + 15, posY + 15);
				}
				else if (m_dol[y][x] == 3) // If white stone
				{
					CBrush whiteBrush(RGB(255, 255, 255));
					dc.SelectObject(&whiteBrush);
					dc.Ellipse(posX - 15, posY - 15, posX + 15, posY + 15);
				}

			}
		}
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPractice13aDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPractice13aDlg::OnClickedRadioServer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_IPAddress.SetWindowTextW(m_strMyIP);
	m_IPAddress.EnableWindow(FALSE);
	SetDlgItemText(IDC_BUTTON_CONNECT, _T("Open"));
}


void CPractice13aDlg::OnRadioClient()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_IPAddress.SetWindowTextW(m_strMyIP);
	m_IPAddress.EnableWindow(TRUE);
	SetDlgItemText(IDC_BUTTON_CONNECT, _T("Connect"));
}


void CPractice13aDlg::OnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	if (!m_nChatMode)
	{
		((CPractice13aApp*)AfxGetApp())->InitServer();
		GetDlgItem(IDC_RADIO_SERVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	}
	else
	{
		CString strIP;
		GetDlgItemText(IDC_IPADDRESS_SERVER, strIP);
		if (strIP != _T("0.0.0.0"))
		{

			GetDlgItem(IDC_RADIO_SERVER)->EnableWindow(FALSE);
			GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
			((CPractice13aApp*)AfxGetApp())->Connect(strIP);
			m_strOtherIP = strIP;
		}
		else
		{
			AfxMessageBox(_T("접속할 서버의 IP 주소를 입력하세요."));
		}
	}
}


void CPractice13aDlg::Accept(CString strSock)
{
	// TODO: 여기에 구현 코드 추가.
	m_strOtherIP = strSock;
}




/// <summary>
/// 채팅창관련 함수
/// </summary>
void CPractice13aDlg::OnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strSend, strInsert;

	GetDlgItemText(IDC_EDIT_SEND, strSend);  // strSend에 채팅창에 입력한 내용을 저장

	strInsert.Format(_T("[%s]:%s"), m_strMyIP, strSend);// strInsert에 IP주소와 strSend를 저장.
	theApp.SendData(strSend);     // App클래스의 SendData를 호출하여 strSend 전송.

	int sel = m_listChat.InsertString(-1, strInsert);
	m_listChat.SetCurSel(sel);    // 채팅창에 strInsert를 표기

	SetDlgItemText(IDC_EDIT_SEND, _T(""));
}


void CPractice13aDlg::ReceiveData(CString strReceive)
{
	// TODO: 여기에 구현 코드 추가.
	CString strInsert;

	strInsert.Format(_T("[%s]:%s"), m_strOtherIP, strReceive);// strInsert에 IP주소와 strReceive를 저장.
	
	int sel = m_listChat.InsertString(-1, strInsert);
	m_listChat.SetCurSel(sel); // 채팅창에 strInsert를 표기

}



/// <summary>
/// 오목관련 함수
/// </summary>

void CPractice13aDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC dc(this);
	CBrush black_brush(RGB(0, 0, 0));
	CBrush* p_old_brush = nullptr; // NULL 또는 nullptr로 초기화

	int x = (point.x + 15) / 30, y = (point.y + 15) / 30;

	if (x > 0 && y > 0 && x <= 16 && y <= 16 && m_dol[y - 1][x - 1] == 0)
	{
		m_dol[y - 1][x - 1] = m_is_white;                 //돌이 놓아진 자리 값: 흰돌은3, 검은돌은 2이 됨.

		x *= 30;
		y *= 30;
		if (m_is_white == 2)                              //흑돌인 경우
			p_old_brush = dc.SelectObject(&black_brush);  //검은색 브러쉬 선택

		dc.Ellipse(x - 15, y - 15, x + 15, y + 15);       //돌 그리기
		dc.SelectObject(p_old_brush);                     //다시 흰색으로 초기화


	}

	//상대방에게 데이터 보내기
	CString strData;
	int x_send, y_send;
	//원 그리기 용으로 값을 변환 시킨 것을 다시 되돌리기
	x_send = (x + 1)/30;  
	y_send = (y + 1)/30;
	strData.Format(_T("GAME: %d,%d"), x_send - 1, y_send - 1);
	theApp.SendData(strData);

	//5개 돌 검사하기
	fivedolcheck(m_dol, m_SumX);


	UpdateData(FALSE);//Edit_box에 출력하기

	if (m_SumX == 3333) {
		if (m_TestV == 32) {
			MessageBox(_T("흑이 이겼습니다!"), _T("게임 종료"), MB_OK | MB_ICONINFORMATION);
		}
		else if (m_TestV == 243) {
			MessageBox(_T("백이 이겼습니다!"), _T("게임 종료"), MB_OK | MB_ICONINFORMATION);
		}
	}


}



void CPractice13aDlg::PlaceOpponentStone(CString strPosition) //상대방의 돌을 표시 -> OnPaint에서 그림.
{
	// TODO: 여기에 구현 코드 추가.
	int x, y;
	// 문자열에서 x, y 좌표를 파싱
	if (_stscanf_s(strPosition, _T("%d,%d"), &x, &y) == 2)  //성공적으로 문자를 읽어들였는지 확인하는 조건
	{
		if (x >= 0 && y >= 0 && x < 16 && y < 16 && m_dol[y][x] == 0)
		{
			// 상대방의 돌을 놓습니다. 여기서는 상대방 돌의 색상을 설정해야 합니다.
			// 예를 들어, 상대방이 흑돌이라면 m_dol[y][x] = 2; 흰돌이라면 m_dol[y][x] = 3;
			m_dol[y][x] = m_is_white == 2 ? 3 : 2; // 현재 플레이어와 반대 색상을 설정

			// GUI를 갱신하여 돌을 그립니다.
			Invalidate(FALSE); // 돌이 추가된 부분만 다시 그리기 위해 FALSE 사용
		}
	}

}




void CPractice13aDlg::fivedolcheck(char(&m_dol)[16][16], int& m_SumX)
{
	// TODO: 여기에 구현 코드 추가.
		// TODO: 여기에 구현 코드 추가.
	for (int j = 0; j < 16; j++) {//기준 줄 수
		for (int k = 0; k < 16 - 5; k++) {//5개씩 그룹의 시작점

			//행 
			if (checkCondition(j, k, m_dol)) {
				m_SumX = 3333;
				return; // 조건을 만족하면 함수에서 즉시 반환
			}

			//열 
			if (checkConditionver(j, k, m_dol)) {
				m_SumX = 3333;
				return; // 조건을 만족하면 함수에서 즉시 반환
			}
		}
	}

	//오른쪽 위에서 왼쪽 아래방향 
	for (int j = 0; j < 16 - 5; j++) {//기준 줄 수
		for (int k = 4; k < 16; k++) {//5개씩 그룹의 시작점

			//오른쪽 위에서 왼쪽 아래방향
			if (checkConditiondia(j, k, m_dol)) {
				m_SumX = 3333;
				return; // 조건을 만족하면 함수에서 즉시 반환
			}
		}
	}

	//왼쪽 위에서 오른쪽 아래방향 
	for (int j = 0; j < 16 - 5; j++) {//기준 줄 수
		for (int k = 0; k < 16 - 5; k++) {//5개씩 그룹의 시작점

			//왼쪽 위에서 오른쪽 아래방향
			if (checkConditiondia2(j, k, m_dol)) {
				m_SumX = 3333;
				return; // 조건을 만족하면 함수에서 즉시 반환
			}
		}
	}
}


bool CPractice13aDlg::checkCondition(int j, int k, char(&m_dol)[16][16])   //가로 방향 계산하기
{
	// TODO: 여기에 구현 코드 추가.
	int any2 = 1; // 초기값을 1로 설정
	for (int i = 0; i < 5; i++) {

		if (m_dol[j][k + i] != 0) {
			//any += m_dol[j][k + i];
			any2 *= m_dol[j][k + i];

			if (any2 == 32 || any2 == 243) { // any2가 0이 아닌 경우에만 조건 검사
				m_TestV = any2;
				return true;
			}
		}
		else {
			return false; // 값이 비어있으면 함수 빠져나가기
		}
	}
	return false; // 조건을 만족하지 않는 경우
}


bool CPractice13aDlg::checkConditionver(int j, int k, char(&m_dol)[16][16])   //세로 계산하기
{
	// TODO: 여기에 구현 코드 추가.
	int any2 = 1; // 초기값을 1로 설정
	for (int i = 0; i < 5; i++) {//5개씩 곱하기
		if (m_dol[k + i][j] != 0) {//값이 비어있으면 더하지 않고 함수 빠져나가기
			any2 *= m_dol[k + i][j];
			if (any2 == 32 || any2 == 243) {
				m_TestV = any2;
				return true; // 조건을 만족하는 경우
			}
		}
		else

			return false;
	}
	return false;
}


bool CPractice13aDlg::checkConditiondia(int j, int k, char(&m_dol)[16][16])  //오른쪽 위에서 왼쪽 아래방향 계산하기
{
	// TODO: 여기에 구현 코드 추가.
	int any2 = 1; // 초기값을 1로 설정
	for (int i = 0; i < 5; i++) {//5개씩 곱하기
		if (m_dol[k - i][j + i] != 0) {//값이 비어있으면 더하지 않고 함수 빠져나가기
			any2 *= m_dol[k - i][j + i];
			if (any2 == 32 || any2 == 243) {
				m_TestV = any2;
				return true; // 조건을 만족하는 경우
			}
		}
		else

			return false;
	}
	return false;
}


bool CPractice13aDlg::checkConditiondia2(int j, int k, char(&m_dol)[16][16]) //왼쪽 위에서 오른쪽 아래방향 더하기
{
	// TODO: 여기에 구현 코드 추가.
	int any2 = 1; // 초기값을 1로 설정
	for (int i = 0; i < 5; i++) {//5개씩 곱하기
		if (m_dol[k + i][j + i] != 0) {//값이 비어있으면 더하지 않고 함수 빠져나가기
			any2 *= m_dol[k + i][j + i];
			if (any2 == 32 || any2 == 243) {
				m_TestV = any2;
				return true; // 조건을 만족하는 경우
			}
		}
		else

			return false;
	}
	return false;
}

void CPractice13aDlg::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int i = 0; i < 16; i++) {
		for (int k = 0; k < 16; k++) {
			m_dol[i][k] = 0;
		}

	}
	m_SumX = 0;
	m_TestV = 0;
	m_is_white = 0;
	UpdateData(FALSE);//Edit_box에 출력하기
	// 화면을 다시 그리도록 요청
	Invalidate();  // 클라이언트 영역 전체를 무효화하고 다시 그리도록 함
	UpdateWindow();  // 무효화된 영역을 즉시 다시 그림
	GetDlgItem(IDC_BUTTON_WHOSBLACK)->EnableWindow(true);

}



/// <summary>
/// 흑돌 선점하기
/// </summary>

void CPractice13aDlg::OnBnClickedButtonWhosblack() //선점 하는 쪽
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 흑돌을 선점하고 상태를 알립니다.
	m_is_white = 2;
	UpdateData(FALSE); // 이 부분은 대화 상자에 바인딩된 변수를 업데이트하는 MFC 함수입니다.

	// 다른 클라이언트에 흑돌이 선점되었다는 메시지를 전송합니다.
	theApp.SendData(_T("BLACK_PREEMPTED"));
	GetDlgItem(IDC_BUTTON_WHOSBLACK)->EnableWindow(false);
}


void CPractice13aDlg::SetWhite() //선점에 실패한 쪽이 받는 메시지
{
	// TODO: 여기에 구현 코드 추가.
		// 백돌로 설정합니다.
	m_is_white = 3;
	UpdateData(FALSE); // UI 업데이트
	GetDlgItem(IDC_BUTTON_WHOSBLACK)->EnableWindow(false);
}
