#pragma once
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <math.h>

INT* ByteToBit(byte src);
BYTE BitToByte(INT* src);
VOID CreateHandleFile(HANDLE* hFile, CHAR* FileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition);
BOOL CheckEncr(BYTE ColorR, BYTE ColorG, BYTE ColorB);
INT EncryptionSym(BYTE EncrSym, BYTE* TxBits, INT offSetTxBits);
INT EncryptionSizeTxt(INT szFile, BYTE* TxBits, INT offSetTxBits);
INT EncryptionAllTxt(BYTE* TxBits, BYTE* txtBuf, INT offSetTxBits, INT sizeColor, INT szFile);
INT* DecryptionSizeTxt(BYTE* TxBits, INT offSetTxBits);
BYTE* DecryptionAllTxt(BYTE* TxBits, INT offSetTxBits, INT sizeColor, INT szFile);
INT CreateTestBMP(CHAR* szFileName, BYTE* TxBits, INT width, INT height);
INT embed(CHAR* main_file, CHAR* emded_file);
INT retrieve(CHAR* embed_file, CHAR* retrieve_file);
INT Check(CHAR* checkFile);