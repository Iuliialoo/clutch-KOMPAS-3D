
// clutchDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "clutch.h"
#include "clutchDlg.h"
#include "afxdialogex.h"

#include "math.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\ksConstants.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\Include\ksConstants3D.h"

#include <atlsafe.h>

#include <comutil.h>


#include <string>
using namespace std;

#define PI 4*atan(1)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#import "C:\Program Files\ASCON\KOMPAS-3D v21 Study\SDK\lib\kAPI5.tlb"

using namespace Kompas6API5;

KompasObjectPtr pKompasApp5;

ksPartPtr pPart;
ksDocument3DPtr pDoc;

// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CclutchDlg



CclutchDlg::CclutchDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLUTCH_DIALOG, pParent)
	, D(80)
	, d(11)
	, d1(18)
	, d2(25)
	, d3(8.4)
	, d4(9)
	, l(25)
	, l1(8)
	, l2(2)
	, b1(1)
	, b2(0.5)
	, h(12.8)
	, B(4)
	, D1(55)
	, R(0.2)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CclutchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, D);
	DDX_Text(pDX, IDC_EDIT12, d);
	DDX_Text(pDX, IDC_EDIT2, d1);
	DDX_Text(pDX, IDC_EDIT3, d2);
	DDX_Text(pDX, IDC_EDIT4, d3);
	DDX_Text(pDX, IDC_EDIT5, d4);
	DDX_Text(pDX, IDC_EDIT6, l);
	DDX_Text(pDX, IDC_EDIT7, l1);
	DDX_Text(pDX, IDC_EDIT8, l2);
	DDX_Text(pDX, IDC_EDIT9, b1);
	DDX_Text(pDX, IDC_EDIT10, b2);
	DDX_Text(pDX, IDC_EDIT11, h);
	DDX_Text(pDX, IDC_EDIT13, B);
	DDX_Text(pDX, IDC_EDIT14, D1);
	DDX_Text(pDX, IDC_EDIT15, R);
}

BEGIN_MESSAGE_MAP(CclutchDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CclutchDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Обработчики сообщений CclutchDlg

BOOL CclutchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CclutchDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CclutchDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CclutchDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CclutchDlg::OnBnClickedButton1()
{
	// TODO: добавьте свой код обработчика уведомлений
	BeginWaitCursor();
	UpdateData(TRUE);


	CComPtr<IUnknown> pKompasAppUnk = nullptr;
	if (!pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	// делаем Компас видимым
	pKompasApp5->Visible = true;

	pDoc = pKompasApp5->Document3D();

	pDoc->Create(false, true);

	pPart = pDoc->GetPart(pTop_Part);



	//Контур общий

	ksEntityPtr pSketch = pPart->NewEntity(o3d_sketch);

	ksSketchDefinitionPtr pSketchDef = pSketch->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));

	pSketch->Create();

	ksDocument2DPtr p2DDoc = pSketchDef->BeginEdit();

	double point[8][2];
	point[0][0] = 0;
	point[0][1] = D / 2.f;
	point[1][0] = l1;
	point[1][1] = D / 2.f;
	point[2][0] = l1;
	point[2][1] = d1 / 2.f;
	point[3][0] = l;
	point[3][1] = d1 / 2.f;
	point[4][0] = l;
	point[4][1] = d / 2.f;
	point[5][0] = l2;
	point[5][1] = d / 2.f;
	point[6][0] = l2;
	point[6][1] = d2 / 2.f;
	point[7][0] = 0;
	point[7][1] = d2 / 2.f;

	p2DDoc->ksLineSeg(point[0][0], point[0][1], point[1][0], point[1][1], 1);
	p2DDoc->ksLineSeg(point[1][0], point[1][1], point[2][0], point[2][1], 1);
	p2DDoc->ksLineSeg(point[2][0], point[2][1], point[3][0], point[3][1], 1);
	p2DDoc->ksLineSeg(point[3][0], point[3][1], point[4][0], point[4][1], 1);
	p2DDoc->ksLineSeg(point[4][0], point[4][1], point[5][0], point[5][1], 1);
	p2DDoc->ksLineSeg(point[5][0], point[5][1], point[6][0], point[6][1], 1);
	p2DDoc->ksLineSeg(point[6][0], point[6][1], point[7][0], point[7][1], 1);
	p2DDoc->ksLineSeg(point[7][0], point[7][1], point[0][0], point[0][1], 1);

	p2DDoc->ksLineSeg(-10, 0, 10, 0, 3);


	pSketchDef->EndEdit();

	ksEntityPtr pRotate = pPart->NewEntity(o3d_bossRotated);

	ksBossRotatedDefinitionPtr pRotDef = pRotate->GetDefinition();
	pRotDef->SetSketch(pSketch);
	pRotDef->SetSideParam(TRUE, 360);


	pRotate->Create();


	//Отверстия два

	ksEntityPtr pSketch1 = pPart->NewEntity(o3d_sketch);

	pSketchDef = pSketch1->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));

	pSketch1->Create();

	p2DDoc = pSketchDef->BeginEdit();

	p2DDoc->ksCircle(D1 / 2.f, 0, d4 / 2.f, 1);

	p2DDoc->ksCircle(-D1 / 2.f, 0, d3 / 2.f, 1);

	pSketchDef->EndEdit();

	ksEntityPtr pExtrude = pPart->NewEntity(o3d_cutExtrusion);

	ksCutExtrusionDefinitionPtr pExDef = pExtrude->GetDefinition();
	pExDef->directionType = dtNormal;

	pExDef->SetSketch(pSketch1);
	pExDef->SetSideParam(true, etThroughAll, 0, 0, false);

	pExtrude->Create();


	//Фаска на отверсии сверху и снизу
	ksEntityCollectionPtr fledges = pPart->EntityCollection(o3d_edge);
	ksEntityPtr pFillet = pPart->NewEntity(o3d_fillet);

	ksFilletDefinitionPtr pFilletDef = pFillet->GetDefinition();
	ksEntityCollectionPtr fl = pFilletDef->array();
	fl->Clear();
	ksEntityPtr pChamfer = pPart->NewEntity(o3d_chamfer);

	ksChamferDefinitionPtr pChamferDef = pChamfer->GetDefinition();
	pChamferDef->SetChamferParam(true, b2, b2);

	fl = pChamferDef->array();
	fl->Clear();


	for (int i = 0; i < fledges->GetCount(); i++) {
		ksEntityPtr ed = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();
		if (def->GetOwnerEntity() == pExtrude) {
			if (def->IsCircle()) {
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);
				double x1, y1, z1;

				p1->GetPoint(&x1, &y1, &z1);

				if (x1 > 0) fl->Add(ed);

				if (x1 == 0 && z1 > 0) {
					ksFaceDefinitionPtr f =
						def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("face");
					face->Update();

				}
			}
			ksVertexDefinitionPtr p1 = def->GetVertex(true);
			ksVertexDefinitionPtr p2 = def->GetVertex(false);
			double x1, y1, z1;

			p1->GetPoint(&x1, &y1, &z1);
			if (x1 == 8) {
				ksFaceDefinitionPtr f =
					def->GetAdjacentFace(true);
				ksEntityPtr face = f->GetEntity();
				face->Putname("faceP");
				face->Update();
			}
		}
	}
	pChamfer->Create();

	ksEntityCollectionPtr flFaces = pPart->EntityCollection(o3d_face);
	for (int i = 0; i < flFaces->GetCount(); i++) {
		ksEntityPtr face = flFaces->GetByIndex(i);
		ksFaceDefinitionPtr def = face->GetDefinition();

		if (def->GetOwnerEntity() == pExtrude) {
			if (def->IsCylinder()) {
				double h, r;
				def->GetCylinderParam(&h, &r);
				if (r == d3 / 2.f) {

					face->Putname("topHole");
					face->Update();
				}
				if (r == d4 / 2.f) {
					face->Putname("bottomHole");
					face->Update();
				}
			}
		}
	}




	//Фаски в больших круглых штуках

	ksEntityPtr pChamfer1 = pPart->NewEntity(o3d_chamfer);

	pChamferDef = pChamfer1->GetDefinition();
	pChamferDef->SetChamferParam(true, b1, b1);

	fl = pChamferDef->array();
	fl->Clear();

	for (int i = 0; i < fledges->GetCount(); i++) {
		ksEntityPtr ed = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();

		if (def->GetOwnerEntity() == pRotate) {
			if (def->IsCircle()) {
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);
				double x1, y1, z1;

				p1->GetPoint(&x1, &y1, &z1);
				if (y1 == D / 2.f || x1 == l) {
					fl->Add(ed);
				}
			}
		}
	}
	pChamfer1->Create();

	//Паз

	ksEntityPtr pSketch2 = pPart->NewEntity(o3d_sketch);

	pSketchDef = pSketch2->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));

	pSketch2->Create();

	p2DDoc = pSketchDef->BeginEdit();

	double point2[4][2];
	point2[0][0] = -h + d / 2.f;
	point2[0][1] = -B / 2.f;
	point2[1][0] = -h + d / 2.f;
	point2[1][1] = B / 2.f;
	point2[2][0] = 0;
	point2[2][1] = B / 2.f;
	point2[3][0] = 0;
	point2[3][1] = -B / 2.f;

	p2DDoc->ksLineSeg(point2[0][0], point2[0][1], point2[1][0], point2[1][1], 1);
	p2DDoc->ksLineSeg(point2[1][0], point2[1][1], point2[2][0], point2[2][1], 1);
	p2DDoc->ksLineSeg(point2[2][0], point2[2][1], point2[3][0], point2[3][1], 1);
	p2DDoc->ksLineSeg(point2[3][0], point2[3][1], point2[0][0], point2[0][1], 1);

	pSketchDef->EndEdit();
	
	//выдавить
	
	ksEntityPtr pExtrude2 = pPart->NewEntity(o3d_cutExtrusion);

	pExDef = pExtrude2->GetDefinition();

	pExDef->directionType = dtNormal;

	pExDef->SetSketch(pSketch2);
	pExDef->SetSideParam(true, etThroughAll, 0, 0, false);

	pExtrude2->Create();


	//Скругления в пазе
	fledges = pPart->EntityCollection(o3d_edge);
	pFilletDef->radius = R;
	fl->Clear();

	pDoc->SaveAs("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Detail_.m3d");


	//БОЛТ - d3	
	
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);

	double lenghtFoot = l1 * 3, lenghtHat = l1 / 2.f, r_blt = d3 / 2.f, R_blt = l1 * 1.25, lenghtNut = l1 / 2.f, r_nut = d3 / 2.f, R_nut = R_blt / 1.5;
	
	
	ksEntityPtr pSketch3 = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch3->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pSketch3->Create();
	p2DDoc = pSketchDef->BeginEdit();

	double point3[4][2];
	point3[0][0] = 0;
	point3[0][1] = 0;
	point3[1][0] = lenghtFoot;
	point3[1][1] = 0;
	point3[2][0] = lenghtFoot;
	point3[2][1] = r_blt;
	point3[3][0] = 0;
	point3[3][1] = r_blt;

	p2DDoc->ksLineSeg(point3[0][0], point3[0][1], point3[1][0], point3[1][1], 1);
	p2DDoc->ksLineSeg(point3[1][0], point3[1][1], point3[2][0], point3[2][1], 1);
	p2DDoc->ksLineSeg(point3[2][0], point3[2][1], point3[3][0], point3[3][1], 1);
	p2DDoc->ksLineSeg(point3[3][0], point3[3][1], point3[0][0], point3[0][1], 1);

	p2DDoc->ksLineSeg(-10, 0, 10, 0, 3);

	pSketchDef->EndEdit();

	ksEntityPtr pRotate2 = pPart->NewEntity(o3d_bossRotated);

	pRotDef = pRotate2->GetDefinition();
	pRotDef->SetSketch(pSketch3);
	pRotDef->SetSideParam(TRUE, 360);

	pRotate2->Create();

	fledges = pPart->EntityCollection(o3d_edge);

	for (int i = 0; i < fledges->GetCount(); i++) {
		ksEntityPtr ed = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();
		if (def->GetOwnerEntity() == pRotate2) {
			if (def->IsCircle()) {
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);
				double x1, y1, z1, x2, y2, z2;
				p1->GetPoint(&x1, &y1, &z1);
				p2->GetPoint(&x2, &y2, &z2);
				if (x1 == 0) {
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("cylinderBoltd3");
					face->Update();
				}
				if (x1 == lenghtFoot) {
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("faceBoltd3");
					face->Update();
				}
			}
		}
	}
	

	ksEntityPtr pSketch4 = pPart->NewEntity(o3d_sketch);

	pSketchDef = pSketch4->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));

	pSketch4->Create();

	p2DDoc = pSketchDef->BeginEdit();

	double point4[6][2];
	point4[0][0] = R_blt;
	point4[0][1] = R_blt / sqrt(3);
	point4[1][0] = 0;
	point4[1][1] = R_blt * 2 / sqrt(3);
	point4[2][0] = - R_blt;
	point4[2][1] = R_blt * sqrt(3) / 3.f;
	point4[3][0] = -R_blt;
	point4[3][1] = - R_blt * sqrt(3) / 3.f;
	point4[4][0] = 0;
	point4[4][1] = -R_blt * 2 / sqrt(3);
	point4[5][0] = R_blt;
	point4[5][1] = -R_blt / sqrt(3);

	p2DDoc->ksLineSeg(point4[0][0], point4[0][1], point4[1][0], point4[1][1], 1);
	p2DDoc->ksLineSeg(point4[1][0], point4[1][1], point4[2][0], point4[2][1], 1);
	p2DDoc->ksLineSeg(point4[2][0], point4[2][1], point4[3][0], point4[3][1], 1);
	p2DDoc->ksLineSeg(point4[3][0], point4[3][1], point4[4][0], point4[4][1], 1);
	p2DDoc->ksLineSeg(point4[4][0], point4[4][1], point4[5][0], point4[5][1], 1);
	p2DDoc->ksLineSeg(point4[5][0], point4[5][1], point4[0][0], point4[0][1], 1);

	pSketchDef->EndEdit();

	ksEntityPtr pExtrude4 = pPart->NewEntity(o3d_baseExtrusion);

	ksBaseExtrusionDefinitionPtr pExDefJoin = pExtrude4->GetDefinition();

	pExDefJoin->directionType = dtNormal;

	pExDefJoin->SetSketch(pSketch4);
	pExDefJoin->SetSideParam(true, etBlind, lenghtHat, 0, true);

	pExtrude4->Create();

	pDoc->SaveAs("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Pin_d3.m3d");


	//ГАЙКА d3
	
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);

	ksEntityPtr pSketch5 = pPart->NewEntity(o3d_sketch);
	
	pSketchDef = pSketch5->GetDefinition();
	
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));

	pSketch5->Create();
	
	p2DDoc = pSketchDef->BeginEdit();
	
	double point5[6][2];
	point5[0][0] = R_nut;
	point5[0][1] = R_nut / sqrt(3);
	point5[1][0] = 0;
	point5[1][1] = R_nut * 2 / sqrt(3);
	point5[2][0] = -R_nut;
	point5[2][1] = R_nut * sqrt(3) / 3.f;
	point5[3][0] = -R_nut;
	point5[3][1] = -R_nut * sqrt(3) / 3.f;
	point5[4][0] = 0;
	point5[4][1] = -R_nut * 2 / sqrt(3);
	point5[5][0] = R_nut;
	point5[5][1] = -R_nut / sqrt(3);

	p2DDoc->ksLineSeg(point5[0][0], point5[0][1], point5[1][0], point5[1][1], 1);
	p2DDoc->ksLineSeg(point5[1][0], point5[1][1], point5[2][0], point5[2][1], 1);
	p2DDoc->ksLineSeg(point5[2][0], point5[2][1], point5[3][0], point5[3][1], 1);
	p2DDoc->ksLineSeg(point5[3][0], point5[3][1], point5[4][0], point5[4][1], 1);
	p2DDoc->ksLineSeg(point5[4][0], point5[4][1], point5[5][0], point5[5][1], 1);
	p2DDoc->ksLineSeg(point5[5][0], point5[5][1], point5[0][0], point5[0][1], 1);
	
	pSketchDef->EndEdit();
	
	ksEntityPtr pExtrude5 = pPart->NewEntity(o3d_baseExtrusion);
	
	pExDefJoin = pExtrude5->GetDefinition();
	
	pExDefJoin->directionType = dtNormal;
	
	pExDefJoin->SetSketch(pSketch5);
	pExDefJoin->SetSideParam(true, etBlind, lenghtNut, 0, true);
	
	pExtrude5->Create();

	
	ksEntityPtr pSketch6 = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch6->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pSketch6->Create();

	p2DDoc = pSketchDef->BeginEdit();

	p2DDoc->ksCircle(0, 0, r_nut, 1);

	pSketchDef->EndEdit();

	ksEntityPtr pExtrude6 = pPart->NewEntity(o3d_cutExtrusion);

	pExDef = pExtrude6->GetDefinition();
	pExDef->directionType = dtReverse;

	pExDef->SetSketch(pSketch6);
	pExDef->SetSideParam(true, etThroughAll, 0, 0, false);

	pExtrude6->Create();

	fledges = pPart->EntityCollection(o3d_edge);
	for (int i = 0; i < fledges->GetCount(); i++) {
		ksEntityPtr ed = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();
		if (def->GetOwnerEntity() == pExtrude6) {
			if (def->IsCircle()) {
				ksFaceDefinitionPtr f = def->GetAdjacentFace(false);
				ksEntityPtr face = f->GetEntity();
				face->Putname("CylinderNutd3");
				face->Update();

				f = def->GetAdjacentFace(true);
				face = f->GetEntity();
				face->Putname("FaceNutd3");
				face->Update();
			}
		}
	}

	pDoc->SaveAs("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Nut_d3.m3d");
	
	
	//БОЛТ d4
	
	lenghtFoot = l1 * 3, lenghtHat = l1 / 2.f, r_blt = d4 / 2.f, R_blt = l1 * 1.25, lenghtNut = l1 / 1.5, r_nut = d4 / 2.f, R_nut = R_blt / 1.5;
	
	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);


	ksEntityPtr pSketch7 = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch7->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pSketch7->Create();
	p2DDoc = pSketchDef->BeginEdit();

	double point7[4][2];
	point7[0][0] = 0;
	point7[0][1] = 0;
	point7[1][0] = lenghtFoot;
	point7[1][1] = 0;
	point7[2][0] = lenghtFoot;
	point7[2][1] = r_blt;
	point7[3][0] = 0;
	point7[3][1] = r_blt;

	p2DDoc->ksLineSeg(point7[0][0], point7[0][1], point7[1][0], point7[1][1], 1);
	p2DDoc->ksLineSeg(point7[1][0], point7[1][1], point7[2][0], point7[2][1], 1);
	p2DDoc->ksLineSeg(point7[2][0], point7[2][1], point7[3][0], point7[3][1], 1);
	p2DDoc->ksLineSeg(point7[3][0], point7[3][1], point7[0][0], point7[0][1], 1);

	p2DDoc->ksLineSeg(-10, 0, 10, 0, 3);

	pSketchDef->EndEdit();
	
	ksEntityPtr pRotate7 = pPart->NewEntity(o3d_bossRotated);

	pRotDef = pRotate7->GetDefinition();
	pRotDef->SetSketch(pSketch7);
	pRotDef->SetSideParam(TRUE, 360);

	pRotate7->Create();

	fledges = pPart->EntityCollection(o3d_edge);

	fledges = pPart->EntityCollection(o3d_edge);

	for (int i = 0; i < fledges->GetCount(); i++) {
		ksEntityPtr ed = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();
		if (def->GetOwnerEntity() == pRotate7) {
			if (def->IsCircle()) {
				ksVertexDefinitionPtr p1 = def->GetVertex(true);
				ksVertexDefinitionPtr p2 = def->GetVertex(false);
				double x1, y1, z1, x2, y2, z2;
				p1->GetPoint(&x1, &y1, &z1);
				p2->GetPoint(&x2, &y2, &z2);
				if (x1 == 0) {
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("cylinderBoltd4");
					face->Update();
				}
				if (x1 == lenghtFoot) {
					ksFaceDefinitionPtr f = def->GetAdjacentFace(true);
					ksEntityPtr face = f->GetEntity();
					face->Putname("faceBoltd4");
					face->Update();
				}
			}
		}
	}
	

	ksEntityPtr pSketch8 = pPart->NewEntity(o3d_sketch);

	pSketchDef = pSketch8->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));

	pSketch8->Create();

	p2DDoc = pSketchDef->BeginEdit();

	double point8[6][2];
	point8[0][0] = R_blt;
	point8[0][1] = R_blt / sqrt(3);
	point8[1][0] = 0;
	point8[1][1] = R_blt * 2 / sqrt(3);
	point8[2][0] = -R_blt;
	point8[2][1] = R_blt * sqrt(3) / 3.f;
	point8[3][0] = -R_blt;
	point8[3][1] = -R_blt * sqrt(3) / 3.f;
	point8[4][0] = 0;
	point8[4][1] = -R_blt * 2 / sqrt(3);
	point8[5][0] = R_blt;
	point8[5][1] = -R_blt / sqrt(3);

	p2DDoc->ksLineSeg(point8[0][0], point8[0][1], point8[1][0], point8[1][1], 1);
	p2DDoc->ksLineSeg(point8[1][0], point8[1][1], point8[2][0], point8[2][1], 1);
	p2DDoc->ksLineSeg(point8[2][0], point8[2][1], point8[3][0], point8[3][1], 1);
	p2DDoc->ksLineSeg(point8[3][0], point8[3][1], point8[4][0], point8[4][1], 1);
	p2DDoc->ksLineSeg(point8[4][0], point8[4][1], point8[5][0], point8[5][1], 1);
	p2DDoc->ksLineSeg(point8[5][0], point8[5][1], point8[0][0], point8[0][1], 1);

	pSketchDef->EndEdit();

	ksEntityPtr pExtrude8 = pPart->NewEntity(o3d_baseExtrusion);

	pExDefJoin = pExtrude8->GetDefinition();

	pExDefJoin->directionType = dtNormal;

	pExDefJoin->SetSketch(pSketch8);
	pExDefJoin->SetSideParam(true, etBlind, lenghtHat, 0, true);

	pExtrude8->Create();
	//for (int i = 0; i < fledges->GetCount(); i++) {
	//	ksEntityPtr ed = fledges->GetByIndex(i);
	//	ksEdgeDefinitionPtr def = ed->GetDefinition();
	//	if (def->GetOwnerEntity() == pRotate7) {
	//		if (def->IsCircle()) {
	//			ksVertexDefinitionPtr p1 = def->GetVertex(true);
	//			ksVertexDefinitionPtr p2 = def->GetVertex(false);
	//			double x1, y1, z1, x2, y2, z2;
	//			p1->GetPoint(&x1, &y1, &z1);
	//			p2->GetPoint(&x2, &y2, &z2);
	//			if (x1 == 0) {
	//				ksFaceDefinitionPtr f = def->GetAdjacentFace(false);
	//				ksEntityPtr face = f->GetEntity();
	//				
	//				ed->Putname("faceBoltd4");
	//				/*ed->Update();*/
	//				
	//				f = def->GetAdjacentFace(true);
	//				face = f->GetEntity();
	//				face->Putname("cylinderBoltd4");
	//				face->Update();
	//			}
	//		}
	//	}
	//}

	pDoc->SaveAs("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Pin_d4.m3d");
	



	//ГАЙКА - d4

	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pPart = pDoc->GetPart(pTop_Part);

	ksEntityPtr pSketch9 = pPart->NewEntity(o3d_sketch);

	pSketchDef = pSketch9->GetDefinition();

	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));

	pSketch9->Create();

	p2DDoc = pSketchDef->BeginEdit();

	double point9[6][2];
	point9[0][0] = R_nut;
	point9[0][1] = R_nut / sqrt(3);
	point9[1][0] = 0;
	point9[1][1] = R_nut * 2 / sqrt(3);
	point9[2][0] = -R_nut;
	point9[2][1] = R_nut * sqrt(3) / 3.f;
	point9[3][0] = -R_nut;
	point9[3][1] = -R_nut * sqrt(3) / 3.f;
	point9[4][0] = 0;
	point9[4][1] = -R_nut * 2 / sqrt(3);
	point9[5][0] = R_nut;
	point9[5][1] = -R_nut / sqrt(3);

	p2DDoc->ksLineSeg(point9[0][0], point9[0][1], point9[1][0], point9[1][1], 1);
	p2DDoc->ksLineSeg(point9[1][0], point9[1][1], point9[2][0], point9[2][1], 1);
	p2DDoc->ksLineSeg(point9[2][0], point9[2][1], point9[3][0], point9[3][1], 1);
	p2DDoc->ksLineSeg(point9[3][0], point9[3][1], point9[4][0], point9[4][1], 1);
	p2DDoc->ksLineSeg(point9[4][0], point9[4][1], point9[5][0], point9[5][1], 1);
	p2DDoc->ksLineSeg(point9[5][0], point9[5][1], point9[0][0], point9[0][1], 1);

	pSketchDef->EndEdit();

	ksEntityPtr pExtrude9 = pPart->NewEntity(o3d_baseExtrusion);

	pExDefJoin = pExtrude9->GetDefinition();

	pExDefJoin->directionType = dtNormal;

	pExDefJoin->SetSketch(pSketch9);
	pExDefJoin->SetSideParam(true, etBlind, lenghtNut, 0, false);

	pExtrude9->Create();


	ksEntityPtr pSketch10 = pPart->NewEntity(o3d_sketch);
	pSketchDef = pSketch10->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pSketch10->Create();

	p2DDoc = pSketchDef->BeginEdit();

	p2DDoc->ksCircle(0, 0, r_nut, 1);

	pSketchDef->EndEdit();

	ksEntityPtr pExtrude10 = pPart->NewEntity(o3d_cutExtrusion);

	pExDef = pExtrude10->GetDefinition();
	pExDef->directionType = dtReverse;

	pExDef->SetSketch(pSketch10);
	pExDef->SetSideParam(true, etThroughAll, 0, 0, false);

	pExtrude10->Create();

	fledges = pPart->EntityCollection(o3d_edge);
	for (int i = 0; i < fledges->GetCount(); i++) {
		ksEntityPtr ed = fledges->GetByIndex(i);
		ksEdgeDefinitionPtr def = ed->GetDefinition();
		if (def->GetOwnerEntity() == pExtrude10) {
			if (def->IsCircle()) {
				ksFaceDefinitionPtr f = def->GetAdjacentFace(false);
				ksEntityPtr face = f->GetEntity();
				face->Putname("CylinderNutd4");
				face->Update();

				f = def->GetAdjacentFace(true);
				face = f->GetEntity();
				face->Putname("FaceNutd4");
				face->Update();
			}
		}
	}
	
	pDoc->SaveAs("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Nut_d4.m3d");


	pDoc = pKompasApp5->Document3D();
	
	pDoc->Create(false, false);

	pPart = pDoc->GetPart(pTop_Part);

	ksPartPtr pDetail1, pDetail2, pPinD3, pPinD4, pNutD3, pNutD4;
	pDoc->SetPartFromFile("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Detail_.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Detail_.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Pin_d3.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Nut_d3.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Pin_d4.m3d", pPart, true);
	pDoc->SetPartFromFile("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Nut_d4.m3d", pPart, true);

	pDetail1 = pDoc->GetPart(0);
	pDetail2 = pDoc->GetPart(1);
	pPinD3 = pDoc->GetPart(2);
	pNutD3 = pDoc->GetPart(3);
	pPinD4 = pDoc->GetPart(4);
	pNutD4 = pDoc->GetPart(5);


	ksEntityCollectionPtr col = pDetail1->EntityCollection(o3d_face);

	ksEntityPtr Detail1TopHole = col->GetByName("topHole", true, true);
	ksEntityPtr Detail1BottomHole = col->GetByName("bottomHole", true, true);
	ksEntityPtr face1 = col->GetByName("face", true, true);
	ksEntityPtr faceP1 = col->GetByName("faceP", true, true);


	col = pDetail2->EntityCollection(o3d_face);

	ksEntityPtr Detail2TopHole = col->GetByName("topHole", true, true);
	ksEntityPtr Detail2BottomHole = col->GetByName("bottomHole", true, true);
	ksEntityPtr face2 = col->GetByName("face", true, true);
	ksEntityPtr faceP2 = col->GetByName("faceP", true, true);

	col = pPinD3->EntityCollection(o3d_face);
	ksEntityPtr cylinderBoltd3 = col->GetByName("cylinderBoltd3", true, true);
	ksEntityPtr faceBoltd3 = col->GetByName("faceBoltd3", true, true);

	col = pNutD3->EntityCollection(o3d_face);
	ksEntityPtr cylinderNutd3 = col->GetByName("cylinderNutd3", true, true);
	ksEntityPtr faceNutd3 = col->GetByName("faceNutd3", true, true);
	

	col = pPinD4->EntityCollection(o3d_face);
	ksEntityPtr cylinderBoltd4 = col->GetByName("cylinderBoltd4", true, true);
	ksEntityPtr faceBoltd4 = col->GetByName("faceBoltd4", true, true);

	col = pNutD4->EntityCollection(o3d_face);
	ksEntityPtr cylinderNutd4 = col->GetByName("cylinderNutd4", true, true);
	ksEntityPtr faceNutd4 = col->GetByName("faceNutd4", true, true);
	


	pDoc->AddMateConstraint(mc_Concentric, Detail1TopHole, Detail2TopHole, -1, 1, 0);
	pDoc->AddMateConstraint(mc_Concentric, Detail1BottomHole, Detail2BottomHole, -1, 1, 0);

	pDoc->AddMateConstraint(mc_Concentric, Detail1TopHole, cylinderBoltd3, -1, 1, 0);
	pDoc->AddMateConstraint(mc_Concentric, Detail1BottomHole, cylinderBoltd4, -1, 1, 0);

	pDoc->AddMateConstraint(mc_Concentric, Detail1TopHole, cylinderNutd3, 1, 1, 0);
	pDoc->AddMateConstraint(mc_Concentric, Detail1BottomHole, cylinderNutd4, 1, 1, 0);

	pDoc->AddMateConstraint(mc_Coincidence, face1, face2, -1, -1, 0);

	pDoc->AddMateConstraint(mc_Coincidence, faceP1, faceNutd3, -1, -1, 0);
	pDoc->AddMateConstraint(mc_Coincidence, faceP1, faceNutd4, -1, -1, 0);

	pDoc->AddMateConstraint(mc_Distance, faceP2, faceBoltd3, -1, -1, -lenghtFoot);
	pDoc->AddMateConstraint(mc_Distance, faceP2, faceBoltd4, -1, -1, -lenghtFoot);

	pDoc->RebuildDocument();

	pDoc->SaveAs("D:\\МОЕ\\Учеба\\3 семестр\\Прога\\clutch\\Assembly.3d");
}
