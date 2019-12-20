#include "Final Project Proglan.h"

int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR lpCmdLine,
	int nShowCmd
) {

	createMainWindow(hInstance, hPrevInstance, lpCmdLine, nShowCmd);
	createButtonAddMatkul(hInstance, hPrevInstance);
	createButtonRemoveMatkul(hInstance, hPrevInstance);
	createButtonModifyMatkul(hInstance, hPrevInstance);
	createListMatkul(hInstance, hPrevInstance);

	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return 0;
}

void createMainWindow(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR lpCmdLine,
	int nShowCmd
) {

	WNDCLASS wc;

	wc.style = 0;
	wc.lpfnWndProc = MainWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"Kelas utama";
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	RegisterClass(&wc);

	mainhwnd = CreateWindowEx(
		0,
		wc.lpszClassName,
		L"Program Presensi Dosen",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 940, 500,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (mainhwnd == NULL) return;

	ShowWindow(mainhwnd, nShowCmd);

	return;
}

void createButtonAddMatkul(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance
) {

	addmkbtnhwnd = CreateWindowEx(
		0,
		WC_BUTTON,
		L"Tambah",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		820, 10, 100, 30,
		mainhwnd,
		(HMENU)ADD_MATKUL,
		hInstance,
		NULL
	);

	return;
}

void createButtonRemoveMatkul(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance
) {

	removemkbtnhwnd = CreateWindowEx(
		0,
		WC_BUTTON,
		L"Hapus",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		820, 50, 100, 30,
		mainhwnd,
		(HMENU)REMOVE_MATKUL,
		hInstance,
		NULL
	);

	Button_Enable(removemkbtnhwnd, FALSE);

	return;
}

void createButtonModifyMatkul(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance
) {

	modifymkbtnhwnd = CreateWindowEx(
		0,
		WC_BUTTON,
		L"Ubah",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		820, 90, 100, 30,
		mainhwnd,
		(HMENU)MODIFY_MATKUL,
		hInstance,
		NULL
	);

	Button_Enable(modifymkbtnhwnd, FALSE);

	return;
}

void createListMatkul(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance
) {

	int _sks[MAX_MATKUL];
	WCHAR _mk[MAX_MATKUL][MAX];
	struct Periode _periode[MAX_MATKUL];
	struct Waktu _waktu[MAX_MATKUL];

	mainlisthwnd = CreateWindowEx(
		0,
		WC_LISTVIEW,
		L"",
		WS_TABSTOP | WS_VISIBLE | WS_BORDER | WS_CHILD | LVS_REPORT | LVS_SHOWSELALWAYS,
		10, 10, 800, 300,
		mainhwnd,
		(HMENU)LIST_VIEW,
		hInstance,
		NULL
	);

	SendMessage(mainlisthwnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
		LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	PWSTR kolom[4] = { L"Nama matkul",L"SKS",L"Periode",L"Waktu" };
	int ukuran[4] = { 150,50,350,250 };
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	int banyak_kolom = sizeof(kolom) / sizeof(char*);
	for (int i = 0; i < banyak_kolom; i++) {
		lvc.pszText = kolom[i];
		lvc.cx = ukuran[i];
		SendMessage(mainlisthwnd, LVM_INSERTCOLUMN, i, (LPARAM)&lvc);
	}

	fopen_s(&fp, "Matkul.txt", "r");
	int cnt;
	for (cnt = 0;; cnt++) {
		if (fwscanf_s(fp, L"%[^;];%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
			_mk[cnt], (unsigned)sizeof(_mk[cnt]),
			&_sks[cnt],
			&_periode[cnt].mulai.tanggal,
			&_periode[cnt].mulai.bulan,
			&_periode[cnt].mulai.tahun,
			&_periode[cnt].selesai.tanggal,
			&_periode[cnt].selesai.bulan,
			&_periode[cnt].selesai.tahun,
			&_waktu[cnt].hari,
			&_waktu[cnt].mulai.jam,
			&_waktu[cnt].mulai.menit,
			&_waktu[cnt].selesai.jam,
			&_waktu[cnt].selesai.menit
		) == EOF) break;
	}
	fclose(fp);

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.cchTextMax = MAX;
	lvi.pszText = (PWSTR)malloc(MAX);

	lvi.iSubItem = 0;
	for (int i = 0; i < cnt; i++) {
		lvi.iItem = i;
		lvi.pszText = _mk[i];
		SendMessage(mainlisthwnd, LVM_INSERTITEM, 0, (LPARAM)&lvi);
	}

	lvi.iSubItem = 1;
	for (int i = 0; i < cnt; i++) {
		lvi.iItem = i;
		StringCchPrintf(lvi.pszText, MAX, L"%d", _sks[i]);
		SendMessage(mainlisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);
	}

	lvi.iSubItem = 2;
	for (int i = 0; i < cnt; i++) {
		lvi.iItem = i;
		StringCchPrintf(lvi.pszText, MAX, L"%.2d %s %d - %.2d %s %d",
			_periode[i].mulai.tanggal,
			parseMonth(_periode[i].mulai.bulan),
			_periode[i].mulai.tahun,
			_periode[i].selesai.tanggal,
			parseMonth(_periode[i].selesai.bulan),
			_periode[i].selesai.tahun
		);
		SendMessage(mainlisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);
	}

	lvi.iSubItem = 3;
	for (int i = 0; i < cnt; i++) {
		lvi.iItem = i;
		StringCchPrintf(lvi.pszText, MAX, L"%s %.2d:%.2d - %.2d:%.2d",
			parseDay(_waktu[i].hari),
			_waktu[i].mulai.jam,
			_waktu[i].mulai.menit,
			_waktu[i].selesai.jam,
			_waktu[i].selesai.menit
		);
		SendMessage(mainlisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);
	}

	return;
}

LRESULT CALLBACK MainWindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
			switch (LOWORD(wParam))
			{
			case ADD_MATKUL:
				addMatkul();
				break;
			case REMOVE_MATKUL:
				deleteMatkul();
				break;
			case MODIFY_MATKUL:
				modifyMatkul();
				break;
			}
		}
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case LIST_VIEW:
			mainButtonOnOff();
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

BOOL CALLBACK addMatkulProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		addmatkulhwnd = hwnd;
		tabhwnd = GetDlgItem(hwnd, IDC_TAB1);

		TCITEM tab_item;
		tab_item.mask = TCIF_TEXT;
		tab_item.cchTextMax = MAX;
		tab_item.pszText = L"Informasi umum";
		SendMessage(tabhwnd, TCM_INSERTITEM, 0, (LPARAM)&tab_item);
		tab_item.pszText = L"Mahasiswa";
		SendMessage(tabhwnd, TCM_INSERTITEM, 1, (LPARAM)&tab_item);

		infohwnd = CreateDialog(
			NULL, MAKEINTRESOURCE(IDD_ADDMATKUL_INFO),
			hwnd, (DLGPROC)addMatkulInfoProc
		);

		mhshwnd = CreateDialog(
			NULL, MAKEINTRESOURCE(IDD_ADDMATKUL_MHS),
			hwnd, (DLGPROC)addMatkulMhsProc
		);

		RECT rc;
		GetWindowRect(tabhwnd, &rc);
		rc.top += 20;
		SetWindowPos(
			infohwnd, 0,
			rc.left, rc.top,
			rc.right - rc.left, rc.bottom - rc.top,
			SWP_SHOWWINDOW
		);
		SetWindowPos(
			mhshwnd, 0,
			rc.left, rc.top,
			rc.right - rc.left, rc.bottom - rc.top,
			SWP_HIDEWINDOW
		);

	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK: {
			WCHAR nama[MAX], sks[MAX], hari_txt[7];
			struct Periode periode;
			struct Waktu waktu;
			SYSTEMTIME time;

			GetDlgItemText(infohwnd, IDC_NAMAMATKUL, nama, MAX);
			GetDlgItemText(infohwnd, IDC_SKSFIELD, sks, MAX);
			SendDlgItemMessage(
				infohwnd, IDC_STARTPERIOD, DTM_GETSYSTEMTIME, 0, (LPARAM)&time
			);
			periode.mulai.tanggal = (int)time.wDay;
			periode.mulai.bulan = (int)time.wMonth;
			periode.mulai.tahun = (int)time.wYear;
			SendDlgItemMessage(
				infohwnd, IDC_ENDPERIOD, DTM_GETSYSTEMTIME, 0, (LPARAM)&time
			);
			periode.selesai.tanggal = (int)time.wDay;
			periode.selesai.bulan = (int)time.wMonth;
			periode.selesai.tahun = (int)time.wYear;
			waktu.hari = (int)SendDlgItemMessage(
				infohwnd, IDC_DAYMATKUL, CB_GETCURSEL, 0, 0
			);
			StringCchCopy(hari_txt, 7, (STRSAFE_LPCWSTR)parseDay(waktu.hari));
			SendDlgItemMessage(
				infohwnd, IDC_STIMEMATKUL, DTM_GETSYSTEMTIME, 0, (LPARAM)&time
			);
			waktu.mulai.jam = (int)time.wHour;
			waktu.mulai.menit = (int)time.wMinute;
			SendDlgItemMessage(
				infohwnd, IDC_ETIMEMATKUL, DTM_GETSYSTEMTIME, 0, (LPARAM)&time
			);
			waktu.selesai.jam = (int)time.wHour;
			waktu.selesai.menit = (int)time.wMinute;

			_wfopen_s(&fp, L"Matkul.txt", L"a");
			fwprintf_s(fp, L"%s;%s;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d\n",
				nama, sks,
				periode.mulai.tanggal, periode.mulai.bulan, periode.mulai.tahun,
				periode.selesai.tanggal, periode.selesai.bulan,
				periode.selesai.tahun, waktu.hari,
				waktu.mulai.jam, waktu.mulai.menit,
				waktu.selesai.jam, waktu.selesai.menit
			);

			LVITEM lvi;
			lvi.mask = LVIF_TEXT;
			lvi.cchTextMax = MAX;
			lvi.pszText = (PWSTR)malloc(MAX);
			lvi.iItem = (int)SendMessage(mainlisthwnd, LVM_GETITEMCOUNT, 0, 0);

			lvi.iSubItem = 0;
			StringCchCopy(lvi.pszText, MAX, nama);
			SendMessage(mainlisthwnd, LVM_INSERTITEM, 0, (LPARAM)&lvi);

			lvi.iSubItem = 1;
			StringCchCopy(lvi.pszText, MAX, sks);
			SendMessage(mainlisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);

			lvi.iSubItem = 2;
			StringCchPrintf(lvi.pszText, MAX, L"%.2d %s %d - %.2d %s %d",
				periode.mulai.tanggal, parseMonth(periode.mulai.bulan),
				periode.mulai.tahun, periode.selesai.tanggal,
				parseMonth(periode.selesai.bulan), periode.selesai.tahun
			);
			SendMessage(mainlisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);

			lvi.iSubItem = 3;
			StringCchPrintf(lvi.pszText, MAX, L"%s %.2d:%.2d - %.2d:%.2d",
				hari_txt,
				waktu.mulai.jam, waktu.mulai.menit,
				waktu.selesai.jam, waktu.selesai.menit
			);
			SendMessage(mainlisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);

			WCHAR fname[2 * MAX];
			StringCchPrintf(fname, 2 * MAX, L"%s (Mahasiswa).txt", nama);
			_wfreopen_s(&fp, fname, L"a", fp);
			int nMhs = (int)SendMessage(mhslisthwnd, LVM_GETITEMCOUNT, 0, 0);
			for (int i = 0; i < nMhs; i++) {
				lvi.iSubItem = 0;
				SendMessage(mhslisthwnd, LVM_GETITEMTEXT, i, (LPARAM)&lvi);
				fwprintf_s(fp, L"%s;", lvi.pszText);
				lvi.iSubItem = 1;
				SendMessage(mhslisthwnd, LVM_GETITEMTEXT, i, (LPARAM)&lvi);
				fwprintf_s(fp, L"%s\n", lvi.pszText);
			}

			StringCchPrintf(fname, 2 * MAX, L"%s (Presensi).txt", nama);
			_wfreopen_s(&fp, fname, L"a", fp);

			fclose(fp);
			free(lvi.pszText);
			EndDialog(hwnd, wParam);
			return 1;
		}
		case IDCANCEL:
			EndDialog(hwnd, wParam);
			return 1;
		}
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->code) {
		case TCN_SELCHANGE:
			onSelChanged();
			break;
		}
	}

	return 0;
}

BOOL CALLBACK addMatkulInfoProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {

	switch (uMsg)
	{
	case WM_INITDIALOG:
		namamkhwnd = GetDlgItem(hwnd, IDC_NAMAMATKUL);
		sksmkhwnd = GetDlgItem(hwnd, IDC_SKSFIELD);
		sdatemkhwnd = GetDlgItem(hwnd, IDC_STARTPERIOD);
		edatemkhwnd = GetDlgItem(hwnd, IDC_ENDPERIOD);
		daymkhwnd = GetDlgItem(hwnd, IDC_DAYMATKUL);
		stmmkhwnd = GetDlgItem(hwnd, IDC_STIMEMATKUL);
		etmmkhwnd = GetDlgItem(hwnd, IDC_ETIMEMATKUL);

		for (int i = 0; i < sizeof(dayList) / sizeof(PWSTR); i++) {
			SendMessage(daymkhwnd, CB_ADDSTRING, 0, (LPARAM)dayList[i]);
		}

		SendDlgItemMessage(hwnd, IDC_STIMEMATKUL, DTM_SETFORMAT, 0,
			(LPARAM)L"HH':'mm");
		SendDlgItemMessage(hwnd, IDC_ETIMEMATKUL, DTM_SETFORMAT, 0,
			(LPARAM)L"HH':'mm");
		break;
	}

	return 0;
}

BOOL CALLBACK addMatkulMhsProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (uMsg)
	{
	case WM_INITDIALOG: {
		mhslisthwnd = GetDlgItem(hwnd, IDC_MHSLIST);

		SendMessage(mhslisthwnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
			LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

		LVCOLUMN lvc;
		lvc.mask = LVCF_TEXT | LVCF_WIDTH;
		lvc.cchTextMax = MAX;

		lvc.pszText = L"Nama Mahasiswa";
		lvc.cx = 200;
		SendMessage(mhslisthwnd, LVM_INSERTCOLUMN, 0, (LPARAM)&lvc);

		lvc.pszText = L"NPM";
		lvc.cx = 150;
		SendMessage(mhslisthwnd, LVM_INSERTCOLUMN, 1, (LPARAM)&lvc);
	}
					  break;
	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
			switch (LOWORD(wParam))
			{
			case IDC_ADDMHS:
				DialogBox(
					NULL, MAKEINTRESOURCE(IDD_ADDMATKUL_INPUTMHS),
					addmatkulhwnd, (DLGPROC)addMatkulInputMhsProc
				);
				break;
			case IDC_DELMHS: {
				int sel = (int)SendMessage(
					mhslisthwnd, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
				SendMessage(mhslisthwnd, LVM_DELETEITEM, (WPARAM)sel, 0);
			}
						   break;
			}
			break;
		}
		break;
	}

	return 0;
}

BOOL CALLBACK addMatkulInputMhsProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK: {
			WCHAR buffer[MAX];

			LVITEM lvi;
			lvi.mask = LVIF_TEXT;
			lvi.cchTextMax = MAX;
			lvi.pszText = (PWSTR)malloc(2 * MAX);
			lvi.iItem = (int)SendMessage(
				mhslisthwnd, LVM_GETITEMCOUNT, 0, 0
			);

			lvi.iSubItem = 0;
			GetDlgItemText(hwnd, IDC_ADDMATKUL_INPUTNAMAMHS, buffer, MAX);
			StringCchCopy(lvi.pszText, MAX, buffer);
			SendMessage(mhslisthwnd, LVM_INSERTITEM, 0, (LPARAM)&lvi);

			lvi.iSubItem = 1;
			GetDlgItemText(hwnd, IDC_ADDMATKUL_INPUTNPMMHS, buffer, MAX);
			StringCchCopy(lvi.pszText, MAX, buffer);
			SendMessage(mhslisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);

			free(lvi.pszText);
			EndDialog(hwnd, wParam);
			return 1;
		}
		case IDCANCEL:
			EndDialog(hwnd, wParam);
			return 1;
		}
		break;
	}
	return 0;
}

BOOL CALLBACK modifyMatkulProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {

	switch (uMsg)
	{
	case WM_INITDIALOG: {
		TCHAR mk[MAX];
		HWND spresencebtnhwnd = GetDlgItem(hwnd, IDC_STARTPRESENCEBTN);
		int ID[4] = {
			IDC_MODIFYMATKUL_NAMAMK,IDC_MODIFYMATKUL_SKS,
			IDC_MODIFYMATKUL_PERIOD,IDC_MODIFYMATKUL_TIME
		};

		modifymatkulhwnd = hwnd;
		mhslisthwnd = GetDlgItem(hwnd, IDC_MODIFYMATKUL_MHSLIST);

		LVITEM lvi;
		lvi.mask = LVIF_TEXT;
		lvi.cchTextMax = MAX;
		lvi.iItem = (int)SendMessage(
			mainlisthwnd, LVM_GETNEXTITEM, -1, LVNI_SELECTED
		);

		for (int i = 0; i < 4; i++) {
			lvi.iSubItem = i;
			lvi.pszText = (PWSTR)malloc(2 * MAX);
			SendMessage(
				mainlisthwnd, LVM_GETITEMTEXT, lvi.iItem, (LPARAM)&lvi
			);
			SetDlgItemText(hwnd, ID[i], lvi.pszText);
		}

		SendMessage(mhslisthwnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
			LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
		LVCOLUMN lvc;
		lvc.mask = LVCF_TEXT | LVCF_WIDTH;
		lvc.cchTextMax = MAX;

		lvc.pszText = L"Nama Mahasiswa";
		lvc.cx = 200;
		SendMessage(mhslisthwnd, LVM_INSERTCOLUMN, 0, (LPARAM)&lvc);
		lvc.pszText = L"NPM";
		lvc.cx = 150;
		SendMessage(mhslisthwnd, LVM_INSERTCOLUMN, 1, (LPARAM)&lvc);

		SendDlgItemMessage(
			hwnd, IDC_MODIFYMATKUL_NAMAMK, WM_GETTEXT, MAX, (LPARAM)mk
		);

		daftarMhs(mk);
		nSesi = daftarPresensi(mk);

		struct Mahasiswa* entry = pertama;
		for (int i = 0;; i++) {
			if (entry == NULL) break;
			lvi.iItem = i;
			lvi.iSubItem = 0;
			lvi.pszText = entry->nama;
			SendMessage(mhslisthwnd, LVM_INSERTITEM, 0, (LPARAM)&lvi);
			lvi.iSubItem = 1;
			lvi.pszText = entry->npm;
			SendMessage(mhslisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);
			entry = entry->berikut;
		}

		SYSTEMTIME sPeriod, ePeriod, sTime, eTime, curr;
		int mkSelect = (int)SendMessage(
			mainlisthwnd, LVM_GETNEXTITEM, -1, LVNI_FOCUSED
		);

		GetLocalTime(&curr);
		_wfreopen_s(&fp, L"Matkul.txt", L"r", fp);
		for (int i = 0;; i++) {
			if (i != mkSelect) {
				fwscanf_s(fp, L"%*[^\n]\n");
				continue;
			}
			break;
		}
		fwscanf_s(fp,
			L"%*[^;];%*[^;];%hd;%hd;%hd;%hd;%hd;%hd;%hd;%hd;%hd;%hd;%hd\n",
			&sPeriod.wDay, &sPeriod.wMonth, &sPeriod.wYear,
			&ePeriod.wDay, &ePeriod.wMonth, &ePeriod.wYear,
			&sTime.wDayOfWeek,
			&sTime.wHour, &sTime.wMinute,
			&eTime.wHour, &eTime.wMinute
		);
		fclose(fp);

		sPeriod.wHour = 0;
		sPeriod.wMinute = 0;
		sPeriod.wSecond = 0;
		sPeriod.wMilliseconds = 0;
		ePeriod.wHour = 23;
		ePeriod.wMinute = 59;
		ePeriod.wSecond = 59;
		ePeriod.wMilliseconds = 999;
		sTime.wDay = curr.wDay;
		sTime.wMonth = curr.wMonth;
		sTime.wYear = curr.wYear;
		sTime.wSecond = 0;
		sTime.wMilliseconds = 0;
		eTime.wDay = curr.wDay;
		eTime.wMonth = curr.wMonth;
		eTime.wYear = curr.wYear;
		eTime.wSecond = 0;
		eTime.wMilliseconds = 0;

		if (compareTime(curr, sPeriod) == -1 ||
			compareTime(curr, ePeriod) == 1 ||
			curr.wDayOfWeek != sTime.wDayOfWeek ||
			compareTime(curr, sTime) == -1 ||
			compareTime(curr, eTime) == 1) {
			Button_Enable(spresencebtnhwnd, FALSE);
		}
	}
					  break;
	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
			switch (LOWORD(wParam))
			{
			case IDC_EDITMKBTN:
				DialogBox(
					NULL, MAKEINTRESOURCE(IDD_EDITMATKUL),
					hwnd, (DLGPROC)editMatkulProc
				);
				break;
			case IDC_VIEWPRESENCEBTN:
				DialogBox(
					NULL, MAKEINTRESOURCE(IDD_VIEWPRESENCE),
					hwnd, (DLGPROC)viewPresenceProc
				);
				break;
			case IDC_STARTPRESENCEBTN:
				DialogBox(
					NULL, MAKEINTRESOURCE(IDD_STARTPRESENCE),
					hwnd, (DLGPROC)startPresenceProc
				);
				break;
			case IDOK:
				resetMhs();
				EndDialog(hwnd, wParam);
				return 1;
			}
			break;
		}
	}

	return 0;
}

BOOL CALLBACK editMatkulProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {

	WCHAR nama[MAX], sks[MAX];
	SYSTEMTIME speriod, eperiod,
		stime = { 2000,1,0,1,0,0,0,0 },
		etime = { 2000,1,0,1,0,0,0,0 };
	int cursel, day;

	cursel = (int)SendMessage(mainlisthwnd, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		for (int i = 0;; i++) {
			_wfopen_s(&fp, L"Matkul.txt", L"r");
			if (i == cursel) {
				fwscanf_s(fp,
					L"%[^;];%[^;];%hd;%hd;%hd;%hd;%hd;%hd;%d;%hd;%hd;%hd;%hd",
					nama, MAX, sks, MAX,
					&speriod.wDay, &speriod.wMonth, &speriod.wYear,
					&eperiod.wDay, &eperiod.wMonth, &eperiod.wYear,
					&day,
					&stime.wHour, &stime.wMinute,
					&etime.wHour, &etime.wMinute
				);
				break;
			}
			fwscanf_s(fp, L"%*[^\n]\n");
		}
		fclose(fp);

		SetDlgItemText(hwnd, IDC_NEWNAMAMK, nama);
		SetDlgItemText(hwnd, IDC_NEWSKS, sks);
		SendDlgItemMessage(hwnd, IDC_NEWSPERIOD, DTM_SETSYSTEMTIME, GDT_VALID,
			(LPARAM)&speriod);
		SendDlgItemMessage(hwnd, IDC_NEWEPERIOD, DTM_SETSYSTEMTIME, GDT_VALID,
			(LPARAM)&eperiod);
		for (int i = 0; i < sizeof(dayList) / sizeof(PWSTR); i++) {
			SendDlgItemMessage(hwnd, IDC_NEWDAYMK, CB_ADDSTRING, 0,
				(LPARAM)dayList[i]);
		}
		SendDlgItemMessage(hwnd, IDC_NEWDAYMK, CB_SETCURSEL, (WPARAM)day, 0);
		SendDlgItemMessage(hwnd, IDC_NEWSTIME, DTM_SETFORMAT, 0,
			(LPARAM)L"HH':'mm");
		SendDlgItemMessage(hwnd, IDC_NEWETIME, DTM_SETFORMAT, 0,
			(LPARAM)L"HH':'mm");
		SendDlgItemMessage(hwnd, IDC_NEWSTIME, DTM_SETSYSTEMTIME, GDT_VALID,
			(LPARAM)&stime);
		SendDlgItemMessage(hwnd, IDC_NEWETIME, DTM_SETSYSTEMTIME, GDT_VALID,
			(LPARAM)&etime);
	}
	break;
	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
			switch (LOWORD(wParam))
			{
			case IDOK:
			{
				GetDlgItemText(hwnd, IDC_NEWNAMAMK, nama, MAX);
				GetDlgItemText(hwnd, IDC_NEWSKS, sks, MAX);
				SendDlgItemMessage(hwnd, IDC_NEWSPERIOD, DTM_GETSYSTEMTIME, 0,
					(LPARAM)&speriod);
				SendDlgItemMessage(hwnd, IDC_NEWEPERIOD, DTM_GETSYSTEMTIME, 0,
					(LPARAM)&eperiod);
				day = (int)SendDlgItemMessage(
					hwnd, IDC_NEWDAYMK, CB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hwnd, IDC_NEWSTIME, DTM_GETSYSTEMTIME, 0,
					(LPARAM)&stime);
				SendDlgItemMessage(hwnd, IDC_NEWETIME, DTM_GETSYSTEMTIME, 0,
					(LPARAM)&etime);

				WCHAR temp[2 * MAX];
				_wfopen_s(&fp, L"Matkul.txt", L"r");
				_wfopen_s(&fq, L"t", L"w+");
				for (int i = 0;; i++) {
					if (fwscanf_s(fp, L"%[^\n]\n", temp, 2 * MAX) == EOF) break;
					if (i == cursel) {
						fwprintf_s(fq,
							L"%s;%s;%hd;%hd;%hd;%hd;%hd;%hd;%d;%hd;%hd;%hd;%hd\n",
							nama, sks,
							speriod.wDay, speriod.wMonth, speriod.wYear,
							eperiod.wDay, eperiod.wMonth, eperiod.wYear,
							day,
							stime.wHour, stime.wMinute,
							etime.wHour, etime.wMinute
						);
					}
					else fwprintf_s(fq, L"%s\n", temp);
				}
				fclose(fq);
				fclose(fp);
				_wremove(L"Matkul.txt");
				rename("t", "Matkul.txt");

				WCHAR periodtxt[MAX], timetxt[MAX];
				LVITEM lvi;
				lvi.mask = LVIF_TEXT;
				lvi.cchTextMax = MAX;
				lvi.iItem = cursel;
				lvi.pszText = (PWSTR)malloc(MAX);

				lvi.iSubItem = 0;
				StringCchCopy(lvi.pszText, MAX, nama);
				SendMessage(mainlisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);

				lvi.iSubItem = 1;
				StringCchCopy(lvi.pszText, MAX, sks);
				SendMessage(mainlisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);

				lvi.iSubItem = 2;
				StringCchPrintf(periodtxt, MAX, L"%.2hd %s %hd - %.2hd %s %hd",
					speriod.wDay, parseMonth((int)speriod.wMonth),
					speriod.wYear, eperiod.wDay,
					parseMonth(eperiod.wMonth), eperiod.wYear
				);
				StringCchCopy(lvi.pszText, MAX, periodtxt);
				SendMessage(mainlisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);

				lvi.iSubItem = 3;
				StringCchPrintf(timetxt, MAX, L"%s %.2hd:%.2hd - %.2hd:%.2hd",
					parseDay(day),
					stime.wHour, stime.wMinute,
					etime.wHour, etime.wMinute
				);
				StringCchCopy(lvi.pszText, MAX, timetxt);
				SendMessage(mainlisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);
				free(lvi.pszText);

				int ID[4] = {
					IDC_MODIFYMATKUL_NAMAMK,IDC_MODIFYMATKUL_SKS,
					IDC_MODIFYMATKUL_PERIOD,IDC_MODIFYMATKUL_TIME
				};
				PWSTR txt[4] = { nama,sks,periodtxt,timetxt };
				for (int i = 0; i < 4; i++) {
					SetDlgItemText(modifymatkulhwnd, ID[i], txt[i]);
				}

				EndDialog(hwnd, wParam);
				return 1;
			}
			case IDCANCEL:
				EndDialog(hwnd, wParam);
				return 1;
			}
			break;
		}
		break;
	}
	return 0;
}

BOOL CALLBACK viewPresenceProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	HWND presencelisthwnd = GetDlgItem(hwnd, IDC_VIEWPRESENCE_MHSLIST);

	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SendMessage(presencelisthwnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
			LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

		LVCOLUMN lvc;
		lvc.mask = LVCF_TEXT | LVCF_WIDTH;
		lvc.cchTextMax = MAX;
		lvc.pszText = (PWSTR)malloc(MAX);

		lvc.cx = 250;
		lvc.pszText = L"Nama Mahasiswa";
		SendMessage(presencelisthwnd, LVM_INSERTCOLUMN, 0, (LPARAM)&lvc);
		lvc.cx = 150;
		lvc.pszText = L"NPM";
		SendMessage(presencelisthwnd, LVM_INSERTCOLUMN, 1, (LPARAM)&lvc);
		lvc.pszText = (PWSTR)malloc(MAX);
		for (int i = 0; i < nSesi; i++) {
			lvc.cx = 75;
			wsprintf(lvc.pszText, L"%d/%d/%d",
				waktu_kuliah[i].tanggal,
				waktu_kuliah[i].bulan,
				waktu_kuliah[i].tahun
			);
			SendMessage(
				presencelisthwnd, LVM_INSERTCOLUMN, i + 2, (LPARAM)&lvc);
		}
		free(lvc.pszText);

		struct Mahasiswa* entry = pertama;
		LVITEM lvi;
		lvi.cchTextMax = MAX;
		lvi.pszText = (PWSTR)malloc(MAX);
		lvi.mask = LVIF_TEXT;
		for (int i = 0;; i++) {
			if (entry == NULL) break;
			lvi.iItem = i;
			lvi.iSubItem = 0;
			lvi.pszText = entry->nama;
			SendMessage(presencelisthwnd, LVM_INSERTITEM, 0, (LPARAM)&lvi);
			lvi.iSubItem = 1;
			lvi.pszText = entry->npm;
			SendMessage(presencelisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);

			for (int j = 0; j < nSesi; j++) {
				lvi.iSubItem = j + 2;
				if (entry->kehadiran[j] == 0) lvi.pszText = L"Absen";
				else if (entry->kehadiran[j] == 1) lvi.pszText = L"Hadir";
				SendMessage(presencelisthwnd, LVM_SETITEM, 0, (LPARAM)&lvi);
			}

			entry = entry->berikut;
		}
	}
		break;
	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
			switch (LOWORD(wParam))
			{
			case IDOK:
				EndDialog(hwnd, wParam);
				return 1;
			}
			break;
		}
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR)lParam)->idFrom)
		{
		case IDC_VIEWPRESENCE_MHSLIST:
			switch (((LPNMHDR)lParam)->code)
			{
			case NM_CLICK: {
				int selected = (int)SendMessage(
					presencelisthwnd, LVM_GETSELECTEDCOUNT, 0, 0);
				if (selected == 0) {
					SetDlgItemText(hwnd, IDC_MHSINFO, L"");
					SetDlgItemText(hwnd, IDC_NPMMHS, L"");
					SetDlgItemText(hwnd, IDC_PRESENCEMHS, L"");
					SetDlgItemText(hwnd, IDC_EXAMSTATUSMHS,
						L"Pilih salah satu mahasiswa untuk mulai melihat rekap"
					);
				}
				else if (selected == 1) {
					int iSelected = (int)SendMessage(
						presencelisthwnd, LVM_GETNEXTITEM, -1, LVNI_SELECTED),
						presence_cnt = 0;
					float persen;
					WCHAR text[32];
					struct Mahasiswa* entry = pertama;
					for (int i = 0; i < iSelected; i++) entry = entry->berikut;

					SetDlgItemText(hwnd, IDC_MHSINFO, entry->nama);
					SetDlgItemText(hwnd, IDC_NPMMHS, entry->npm);

					for (int i = 0; i < nSesi; i++) {
						if (entry->kehadiran[i] == 1) presence_cnt++;
					}
					persen = (float)(presence_cnt * 100);
					persen /= (float)nSesi;

					StringCchPrintf(text, 32, L"%d dari %d pertemuan (%.2f%%)",
						presence_cnt, nSesi, persen);
					SetDlgItemText(hwnd, IDC_PRESENCEMHS, text);

					if (persen < 75) SetDlgItemText(hwnd, IDC_EXAMSTATUSMHS,
						L"Mahasiswa ini tidak diperbolehkan mengikuti UAS");
					else SetDlgItemText(hwnd, IDC_EXAMSTATUSMHS,
						L"Mahasiswa ini diperbolehkan mengikuti UAS");
				}
			}
				break;
			}
			break;
		}
		break;
	}

	return 0;
}

BOOL CALLBACK startPresenceProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {

	HWND presencefieldhwnd = GetDlgItem(hwnd, IDC_PRESENCEFIELD);
	SYSTEMTIME curr;
	int nMhs = (int)SendMessage(mhslisthwnd, LVM_GETITEMCOUNT, 0, 0);

	GetLocalTime(&curr);

	switch (uMsg)
	{
	case WM_INITDIALOG: {
		WCHAR dateText[32];
		PWSTR headers[3] = { L"Hadir?",L"Nama Mahasiswa",L"NPM" };
		int width[3] = { 50,150,100 };

		StringCchPrintf(dateText, 32, L"%s, %d %s %d",
			parseDay(curr.wDayOfWeek), curr.wDay,
			parseMonth(curr.wMonth), curr.wYear
		);

		SendDlgItemMessage(
			hwnd, IDC_CURRDATE, WM_SETTEXT, 0, (LPARAM)&dateText
		);

		SendMessage(presencefieldhwnd, LVM_SETEXTENDEDLISTVIEWSTYLE,
			LVS_EX_CHECKBOXES, LVS_EX_CHECKBOXES);

		LVCOLUMN lvc;
		lvc.mask = LVCF_TEXT | LVCF_WIDTH;
		lvc.cchTextMax = MAX;
		lvc.pszText = (PWSTR)malloc(2 * MAX);
		for (int i = 0; i < 3; i++) {
			lvc.cx = width[i];
			StringCchCopy(lvc.pszText, MAX, headers[i]);
			SendMessage(presencefieldhwnd, LVM_INSERTCOLUMN, i, (LPARAM)&lvc);
		}
		free(lvc.pszText);

		struct Mahasiswa* entry = pertama;
		LVITEM lvi;
		lvi.cchTextMax = MAX;
		lvi.pszText = (PWSTR)malloc(MAX);

		for (int i = 0;; i++) {
			if (entry == NULL) break;
			lvi.iItem = i;
			lvi.iSubItem = 0;
			lvi.mask = LVIF_STATE;
			lvi.stateMask = LVIS_STATEIMAGEMASK;
			lvi.state = 2;
			SendMessage(presencefieldhwnd, LVM_INSERTITEM, 0, (LPARAM)&lvi);

			lvi.mask = LVIF_TEXT;
			lvi.iSubItem = 1;
			lvi.pszText = entry->nama;
			SendMessage(presencefieldhwnd, LVM_SETITEM, 0, (LPARAM)&lvi);
			lvi.iSubItem = 2;
			lvi.pszText = entry->npm;
			SendMessage(presencefieldhwnd, LVM_SETITEM, 0, (LPARAM)&lvi);

			entry = entry->berikut;
		}
	}
					  break;
	case WM_COMMAND:
		switch (HIWORD(wParam))
		{
		case BN_CLICKED:
			switch (LOWORD(wParam))
			{
			case IDOK: {
				WCHAR fname[2 * MAX];
				GetDlgItemText(
					GetParent(hwnd), IDC_MODIFYMATKUL_NAMAMK, fname, MAX);
				StringCchCat(fname, 2 * MAX, L" (Presensi).txt");
				_wfopen_s(&fp, fname, L"a");
				fwprintf_s(fp, L"%hd;%hd;%hd",
					curr.wDay, curr.wMonth, curr.wYear);
				for (int i = 0; i < nMhs; i++) {
					fwprintf_s(fp, L";%d",
						(int)ListView_GetCheckState(presencefieldhwnd, i)
					);
				}
				fwprintf_s(fp, L"\n");
				fclose(fp);
				EndDialog(hwnd, wParam);
				return 1;
			}
			case IDCANCEL:
				EndDialog(hwnd, wParam);
				return 1;
			}
			break;
		}
		break;
	}
	return 0;
}

void onSelChanged() {
	int sel = (int)SendMessage(tabhwnd, TCM_GETCURSEL, 0, 0);
	switch (sel)
	{
	case 0:
		ShowWindow(infohwnd, SW_SHOW);
		ShowWindow(mhshwnd, SW_HIDE);
		break;
	case 1:
		ShowWindow(infohwnd, SW_HIDE);
		ShowWindow(mhshwnd, SW_SHOW);
		break;
	}
	return;
}

void addMatkul() {
	DialogBox(
		NULL, MAKEINTRESOURCE(IDD_ADDMATKUL),
		mainhwnd, (DLGPROC)addMatkulProc
	);
	return;
}

void deleteMatkul() {
	TCHAR title[MAX], temp[2 * MAX];
	int idx = (int)SendMessage(mainlisthwnd, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);

	title[0] = '\0';
	temp[0] = '\0';

	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iSubItem = 0;
	lvi.pszText = title;
	lvi.cchTextMax = MAX;

	SendMessage(mainlisthwnd, LVM_GETITEMTEXT, idx, (LPARAM)&lvi);

	int resp = MessageBox(
		mainhwnd,
		L"Yakin ingin menghapus mata kuliah ini?",
		L"Konfirmasi penghapusan",
		MB_YESNO | MB_ICONEXCLAMATION
	);
	if (resp == IDNO) return;

	SendMessage(mainlisthwnd, LVM_DELETEITEM, idx, 0);

	fopen_s(&fp, "Matkul.txt", "r");
	fopen_s(&fq, "t", "w+");

	while (fwscanf_s(fp, L"%[^;];", temp, MAX) != EOF) {
		if (wcscmp(temp, title) == 0) {
			fwscanf_s(fp, L"%*[^\n]\n");
			continue;
		}
		fwprintf_s(fq, L"%s;", temp);
		fwscanf_s(fp, L"%[^\n]\n", temp, MAX);
		fwprintf_s(fq, L"%s\n", temp);
	}

	fclose(fq);
	fclose(fp);

	_wremove(L"Matkul.txt");
	rename("t", "Matkul.txt");
	StringCchPrintf(temp, 2 * MAX, L"%s (Mahasiswa).txt", title);
	_wremove(temp);
	StringCchPrintf(temp, 2 * MAX, L"%s (Presensi).txt", title);
	_wremove(temp);

	return;
}

void modifyMatkul() {
	DialogBox(
		NULL, MAKEINTRESOURCE(IDD_MODIFYMATKUL),
		mainhwnd, (DLGPROC)modifyMatkulProc
	);
	return;
}

void daftarMhs(PWSTR mk) {
	WCHAR fname[2 * MAX];

	StringCchPrintf(fname, 2 * MAX, L"%s (Mahasiswa).txt", mk);
	_wfopen_s(&fp, fname, L"r");

	while (TRUE) {
		struct Mahasiswa* newEntry =
			(struct Mahasiswa*) malloc(sizeof(struct Mahasiswa));

		if (fwscanf_s(fp, L"%[^;];%[^\n]\n",
			newEntry->nama, MAX, newEntry->npm, MAX) == EOF) {
			free(newEntry);
			break;
		}

		newEntry->berikut = NULL;
		if (pertama == NULL) pertama = newEntry;
		else sekarang->berikut = newEntry;
		sekarang = newEntry;
	}
	return;
}

int daftarPresensi(PWSTR mk) {
	WCHAR fname[2 * MAX];
	int i;

	StringCchPrintf(fname, 2 * MAX, L"%s (Presensi).txt", mk);
	_wfreopen_s(&fp, fname, L"r", fp);

	struct Mahasiswa* entry;

	for (i = 0;; i++) {
		if (fwscanf_s(fp, L"%d;%d;%d",
			&waktu_kuliah[i].tanggal, &waktu_kuliah[i].bulan,
			&waktu_kuliah[i].tahun) == EOF) break;
		entry = pertama;
		while (entry != NULL) {
			fwscanf_s(fp, L";%d", &entry->kehadiran[i]);
			entry = entry->berikut;
		}
		fwscanf_s(fp, L"\n");
	}
	return i;
}

void resetMhs() {
	struct Mahasiswa* entry = pertama, * temp;
	while (entry != NULL) {
		temp = entry->berikut;
		free(entry);
		entry = temp;
	}
	pertama = NULL;
	sekarang = NULL;
	return;
}

void mainButtonOnOff() {
	LRESULT num = SendMessage(mainlisthwnd, LVM_GETSELECTEDCOUNT, 0, 0);
	if (num == 0) {
		Button_Enable(removemkbtnhwnd, FALSE);
		Button_Enable(modifymkbtnhwnd, FALSE);
	}
	else {
		Button_Enable(removemkbtnhwnd, TRUE);
		Button_Enable(modifymkbtnhwnd, TRUE);
	}
}

int compareTime(SYSTEMTIME time1, SYSTEMTIME time2) {
	FILETIME first, second;
	SystemTimeToFileTime(&time1, &first);
	SystemTimeToFileTime(&time2, &second);

	return (int)CompareFileTime(&first, &second);
}

PWSTR parseMonth(int x) {
	return monthList[x - 1];
}

PWSTR parseDay(int x) {
	return dayList[x];
}