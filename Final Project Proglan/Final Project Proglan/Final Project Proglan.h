#pragma once

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <strsafe.h>
#include "CommCtrl.h"
#include "resource.h"

#define ADD_MATKUL 101
#define REMOVE_MATKUL 102
#define MODIFY_MATKUL 103

#define LIST_VIEW 200

#define MAX_MATKUL 16
#define MAX 256

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

FILE* fp, * fq;
struct Tanggal {
	int tanggal;
	int bulan;
	int tahun;
} waktu_kuliah[MAX];
struct Jam {
	int jam;
	int menit;
};
struct Periode {
	struct Tanggal mulai;
	struct Tanggal selesai;
};
struct Waktu {
	int hari;
	struct Jam mulai;
	struct Jam selesai;
};
struct Mahasiswa {
	WCHAR nama[MAX];
	WCHAR npm[MAX];
	int kehadiran[MAX];
	struct Mahasiswa* berikut;
} *pertama, *sekarang;

HWND mainhwnd, addmkbtnhwnd, removemkbtnhwnd, modifymkbtnhwnd, mainlisthwnd,
addmatkulhwnd, tabhwnd, infohwnd, mhshwnd,
namamkhwnd, sksmkhwnd, sdatemkhwnd, edatemkhwnd,
daymkhwnd, stmmkhwnd, etmmkhwnd,
modifymatkulhwnd, mhslisthwnd;

int nSesi;

PWSTR dayList[] = {
	L"Minggu",L"Senin",L"Selasa",L"Rabu",L"Kamis",L"Jumat",L"Sabtu"
};

PWSTR monthList[] = {
	L"Januari",L"Februari",L"Maret",L"April",L"Mei",L"Juni",
	L"Juli",L"Agustus",L"September",L"Oktober",L"November",L"Desember"
};

void createMainWindow(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR lpCmdLine,
	int nShowCmd
);
void createButtonAddMatkul(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance
);
void createButtonRemoveMatkul(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance
);
void createButtonModifyMatkul(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance
);
void createListMatkul(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance
);

LRESULT CALLBACK MainWindowProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
BOOL CALLBACK addMatkulProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
BOOL CALLBACK addMatkulInfoProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
BOOL CALLBACK addMatkulMhsProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
BOOL CALLBACK addMatkulInputMhsProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
BOOL CALLBACK modifyMatkulProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
BOOL CALLBACK editMatkulProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
BOOL CALLBACK viewPresenceProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);
BOOL CALLBACK startPresenceProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);


void onSelChanged();

void addMatkul();
void deleteMatkul();
void modifyMatkul();
void daftarMhs(PWSTR mk);
int daftarPresensi(PWSTR mk);
void resetMhs();

void mainButtonOnOff();

int compareTime(SYSTEMTIME time1, SYSTEMTIME time2);
PWSTR parseMonth(int x);
PWSTR parseDay(int x);