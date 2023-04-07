#include "Header.h"

INT* ByteToBit(byte src) {

	INT* bitarr = new INT[8];
	for (INT i = 0; i < 8; ++i) {
		if ((src >> i & 1) == 1)
			bitarr[i] = 1;
		else
			bitarr[i] = 0;
	}
	return bitarr;
}

BYTE BitToByte(INT* src) {

	BYTE sym = 0;
	for (INT i = 0; i < 8; ++i) { //сделать проверку на длинну массива
		if (src[i] == 1)
			sym += (BYTE)pow(2, i);
	}
	return sym;
}

VOID CreateHandleFile(HANDLE* hFile, CHAR* FileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition)
{
	*hFile = CreateFileA(
		FileName,
		dwDesiredAccess,
		0,
		NULL,
		dwCreationDisposition,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
}

BOOL CheckEncr(BYTE ColorR, BYTE ColorG, BYTE ColorB) {

	BYTE EncSym;

	INT resMsg[8] = { 0 };

	INT* colorR = ByteToBit(ColorR);
	resMsg[0] = colorR[0];
	resMsg[1] = colorR[1];

	INT* colorG = ByteToBit(ColorG);
	resMsg[2] = colorG[0];
	resMsg[3] = colorG[1];
	resMsg[4] = colorG[2];


	INT* colorB = ByteToBit(ColorB);
	resMsg[5] = colorB[0];
	resMsg[6] = colorB[1];
	resMsg[7] = colorB[2];

	EncSym = BitToByte(resMsg);
	delete[] colorR;
	delete[] colorG;
	delete[] colorB;
	if (EncSym == '?')
		return 1;
	else
		return 0;
}

INT EncryptionSym(BYTE EncrSym, BYTE* TxBits, INT offSetTxBits) {

	INT* BitArrEncrSym = ByteToBit(EncrSym); 
	INT* BitArrR = ByteToBit(TxBits[offSetTxBits]); 
	BitArrR[0] = BitArrEncrSym[0];
	BitArrR[1] = BitArrEncrSym[1];
	BYTE nR = BitToByte(BitArrR);
	TxBits[offSetTxBits] = nR;
	offSetTxBits++;

	INT* BitArrG = ByteToBit(TxBits[offSetTxBits]);
	BitArrG[0] = BitArrEncrSym[2];
	BitArrG[1] = BitArrEncrSym[3];
	BitArrG[2] = BitArrEncrSym[4];
	BYTE nG = BitToByte(BitArrG);
	TxBits[offSetTxBits] = nG;
	offSetTxBits++;

	INT* BitArrB = ByteToBit(TxBits[offSetTxBits]);
	BitArrB[0] = BitArrEncrSym[5];
	BitArrB[1] = BitArrEncrSym[6];
	BitArrB[2] = BitArrEncrSym[7];
	BYTE nB = BitToByte(BitArrB);
	TxBits[offSetTxBits] = nB;
	offSetTxBits++;

	delete[] BitArrEncrSym;
	delete[] BitArrR;
	delete[] BitArrG;
	delete[] BitArrB;

	return offSetTxBits;
}

INT EncryptionSizeTxt(INT szFile, BYTE* TxBits, INT offSetTxBits) {

	INT SzTxt[3] = { 0 }, i = 2;
	
	while (szFile > 0) {
		SzTxt[i] = szFile % 10;
		szFile /= 10;
		--i;
	}

	for (int i = 0; i < 3; ++i) {
		INT* BitSzTxt = ByteToBit(SzTxt[i]);
		INT* BitArrR = ByteToBit(TxBits[offSetTxBits]);
		BitArrR[0] = BitSzTxt[0];
		BitArrR[1] = BitSzTxt[1];
		BYTE nR = BitToByte(BitArrR);
		TxBits[offSetTxBits] = nR;
		offSetTxBits++;

		INT* BitArrG = ByteToBit(TxBits[offSetTxBits]);
		BitArrG[0] = BitSzTxt[2];
		BitArrG[1] = BitSzTxt[3];
		BitArrG[2] = BitSzTxt[4];
		BYTE nG = BitToByte(BitArrG);
		TxBits[offSetTxBits] = nG;
		offSetTxBits++;

		INT* BitArrB = ByteToBit(TxBits[offSetTxBits]);
		BitArrB[0] = BitSzTxt[5];
		BitArrB[1] = BitSzTxt[6];
		BitArrB[2] = BitSzTxt[7];
		BYTE nB = BitToByte(BitArrB);
		TxBits[offSetTxBits] = nB;
		offSetTxBits++;

		delete[] BitSzTxt;
		delete[] BitArrR;
		delete[] BitArrG;
		delete[] BitArrB;
	}

	return offSetTxBits;
}

INT EncryptionAllTxt(BYTE* TxBits, BYTE* txtBuf ,INT offSetTxBits, INT sizeColor, INT szFile){

	INT index = 0, offSetI = offSetTxBits;
	for (INT i = offSetI; i < sizeColor; i++) {
		if (index == szFile)
			break;
		INT* EncrText = ByteToBit(txtBuf[index]);
		INT* BitArrR = ByteToBit(TxBits[offSetTxBits]);
		BitArrR[0] = EncrText[0];
		BitArrR[1] = EncrText[1];
		BYTE nR = BitToByte(BitArrR);
		TxBits[offSetTxBits] = nR;
		offSetTxBits++;

		INT* BitArrG = ByteToBit(TxBits[offSetTxBits]);
		BitArrG[0] = EncrText[2];
		BitArrG[1] = EncrText[3];
		BitArrG[2] = EncrText[4];
		BYTE nG = BitToByte(BitArrG);
		TxBits[offSetTxBits] = nG;
		offSetTxBits++;

		INT* BitArrB = ByteToBit(TxBits[offSetTxBits]);
		BitArrB[0] = EncrText[5];
		BitArrB[1] = EncrText[6];
		BitArrB[2] = EncrText[7];
		BYTE nB = BitToByte(BitArrB);
		TxBits[offSetTxBits] = nB;
		offSetTxBits++;

		index++;
		delete[] EncrText;
		delete[] BitArrR;
		delete[] BitArrG;
		delete[] BitArrB;
	}
	return offSetTxBits;
}

INT* DecryptionSizeTxt(BYTE* TxBits, INT offSetTxBits) {
	
	INT* SzTxt = new INT[3];
	INT resSzTxt[8] = { 0 };
	for (INT i = 0; i < 3; ++i) {
		INT* BitArrR = ByteToBit(TxBits[offSetTxBits]);
		resSzTxt[0] = BitArrR[0];
		resSzTxt[1] = BitArrR[1];
		offSetTxBits++;

		INT* BitArrG = ByteToBit(TxBits[offSetTxBits]);
		resSzTxt[2] = BitArrG[0];
		resSzTxt[3] = BitArrG[1];
		resSzTxt[4] = BitArrG[2];
		offSetTxBits++;

		INT* BitArrB = ByteToBit(TxBits[offSetTxBits]);
		resSzTxt[5] = BitArrB[0];
		resSzTxt[6] = BitArrB[1];
		resSzTxt[7] = BitArrB[2];
		offSetTxBits++;

		SzTxt[i] = BitToByte(resSzTxt);
		delete[] BitArrR;
		delete[] BitArrG;
		delete[] BitArrB;
	}
	return SzTxt;
}

BYTE* DecryptionAllTxt(BYTE* TxBits, INT offSetTxBits, INT sizeColor, INT szFile){

	INT index = 0, offSetI = offSetTxBits;
	BYTE* resAllText = new BYTE[szFile];
	for (INT i = offSetI; i < sizeColor; i++) {
		if (index == szFile)
			break;
		INT* resText = new INT[8];
		INT* BitArrR = ByteToBit(TxBits[offSetTxBits]);
		resText[0] = BitArrR[0];
		resText[1] = BitArrR[1];
		offSetTxBits++;

		INT* BitArrG = ByteToBit(TxBits[offSetTxBits]);
		resText[2] = BitArrG[0];
		resText[3] = BitArrG[1];
		resText[4] = BitArrG[2];
		offSetTxBits++;

		INT* BitArrB = ByteToBit(TxBits[offSetTxBits]);
		resText[5] = BitArrB[0];
		resText[6] = BitArrB[1];
		resText[7] = BitArrB[2];
		offSetTxBits++;

		resAllText[index] = BitToByte(resText);
		delete[] resText;
		delete[] BitArrR;
		delete[] BitArrG;
		delete[] BitArrB;
		index++;
	}
	return resAllText;
}

INT CreateTestBMP(CHAR* szFileName, BYTE* TxBits, INT width, INT height) { //первые 54 бита это структура BMP по этому 0

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	RGBTRIPLE colorRGB;

	memset(&bfh, 0, sizeof(bfh));

	INT Width = width;
	INT Height = height;

	bfh.bfType = 0x4D42;
	bfh.bfOffBits = sizeof(bfh) + sizeof(bih);
	bfh.bfSize = bfh.bfOffBits + sizeof(colorRGB) * Width * Height + Height * ((sizeof(colorRGB) * Width) % 4);

	memset(&bih, 0, sizeof(bih));

	bih.biSize = sizeof(bih);
	bih.biBitCount = 24;
	bih.biClrUsed = 0;
	bih.biCompression = BI_RGB;
	bih.biHeight = Height;
	bih.biWidth = Width;
	bih.biPlanes = 1;

	HANDLE hFile = CreateFileA(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return 0;
	DWORD RW;

	WriteFile(hFile, &bfh, sizeof(bfh), &RW, NULL);
	WriteFile(hFile, &bih, sizeof(bih), &RW, NULL);

	int offsetBMP = 0;

	for (int i = 0; i < Height; ++i)
	{
		for (int j = 0; j < Width; ++j)
		{
			colorRGB.rgbtRed = TxBits[offsetBMP];
			colorRGB.rgbtGreen = TxBits[offsetBMP + 1];
			colorRGB.rgbtBlue = TxBits[offsetBMP + 2];
			WriteFile(hFile, &colorRGB, sizeof(colorRGB), &RW, NULL);
			offsetBMP += 3;
		}
	}
	CloseHandle(hFile);
	return true;
}

INT embed(CHAR* main_file, CHAR* emded_file) {

	BITMAPFILEHEADER bfh = { 0 };	//Заголовок BMP файла
	BITMAPINFOHEADER bih = { 0 };	//Заголовок BMP файла
	BYTE *TxBits, *buf;				// массивы для цветов 
	DWORD nBytesRead;				// сколько данных прочтено с файла  
	HANDLE FileHandle;				// хендл, открываемого для чтения, файла 
	INT width, height;				// ширина и высота файла
	BOOL rBfh, rBih, rPix;			// чтение заголовков и пикселей
	INT sizeColor;					// Размер исходного рисунка
	INT offSetTxBits = 0;			// Смещение по массиву RGB
	BYTE EncrSym = '?';				// Символ закодированного файла
	
	BYTE* txtBuf;					// Буфер данных с текствого файла
	LARGE_INTEGER szTxtFile;		// Размер файла
	BOOL rBfhTxt;					// чтение текствого файла
	HANDLE hFileTxtE;				// хендл txt файла Encode

	CreateHandleFile(&FileHandle, main_file, GENERIC_READ, OPEN_EXISTING);
	if (FileHandle == INVALID_HANDLE_VALUE)
	{
		printf("Error LoadImage file! GetLastError - %d", GetLastError());
		return false;
	}

	rBfh = ReadFile(FileHandle, &bfh, sizeof(bfh), &nBytesRead, NULL); // Чтение первого заголовков
	if (rBfh && nBytesRead == 0) {
		printf("Ошибка чтения первого заголовка GetLastError = %d", GetLastError());
		return false;
	}
		
	rBih = ReadFile(FileHandle, &bih, sizeof(bih), &nBytesRead, NULL); // Чтение втрого заголовка
	if (rBih && nBytesRead == 0) {
		printf("Ошибка чтения второго заголовка GetLastError = %d", GetLastError());
		return false;
	}
		
	width = bih.biWidth;
	height = bih.biHeight;
	sizeColor = width * height * 3;

	buf = new BYTE[sizeColor];
	TxBits = new BYTE[sizeColor];
	rPix = ReadFile(FileHandle, buf, sizeColor, &nBytesRead, NULL);
	if (rPix && nBytesRead == 0) {
		printf("Ошибка чтения пикселей GetLastError = %d", GetLastError());
		return false;
	}

	for (INT i = 0; i < sizeColor; i += 3) // переписали с BGR в RGB { [R], [G], [B], [R], [G] ... }
	{
		TxBits[i] = buf[i + 2];
		TxBits[i + 1] = buf[i + 1];
		TxBits[i + 2] = buf[i];
	}

	offSetTxBits = EncryptionSym(EncrSym, TxBits, offSetTxBits);

	CreateHandleFile(&hFileTxtE, emded_file, GENERIC_READ, OPEN_EXISTING);
	if (hFileTxtE == INVALID_HANDLE_VALUE)
		{
			printf("Error Load TxtFile file! GetLastError - %d", GetLastError());
			return false;
		}

	GetFileSizeEx(hFileTxtE, &szTxtFile);
	INT szFile = szTxtFile.QuadPart;

	txtBuf = new BYTE[szFile];
	rBfhTxt = ReadFile(hFileTxtE, txtBuf, szFile, &nBytesRead, NULL);
	if (rBfhTxt && nBytesRead == 0) {
			printf("Ошибка чтения пикселей GetLastError = %d", GetLastError());
			return false;
		}

	offSetTxBits = EncryptionSizeTxt(szFile, TxBits, offSetTxBits);
	offSetTxBits = EncryptionAllTxt(TxBits, txtBuf, offSetTxBits, sizeColor, szFile);

	CreateTestBMP((CHAR*)"Embed.bmp", TxBits, width, height);

	CloseHandle(FileHandle);
	CloseHandle(hFileTxtE);
	delete[] txtBuf;
	delete[] TxBits;
	delete[] buf;
	return true;
}

INT retrieve(CHAR* embed_file, CHAR* retrieve_file) {

	BITMAPFILEHEADER bfh = { 0 };	//Заголовок BMP файла
	BITMAPINFOHEADER bih = { 0 };	//Заголовок BMP файла
	BYTE* TxBits, * buf;				// массивы для цветов 
	DWORD nBytesRead;				// сколько данных прочтено с файла  
	HANDLE FileHandle;				// хендл, открываемого для чтения, файла 
	INT width, height;				// ширина и высота файла
	BOOL rBfh, rBih, rPix;			// чтение заголовков и пикселей
	INT sizeColor;					// Размер исходного рисунка
	INT offSetTxBits = 0;			// Смещение по массиву RGB
	HANDLE hFileTxtD;				// хендл txt файла Decode
	BYTE* resText;					// Буфер данных для Decode

	CreateHandleFile(&FileHandle, embed_file, GENERIC_READ, OPEN_EXISTING);
	if (FileHandle == INVALID_HANDLE_VALUE)
	{
		printf("Error LoadImage file! GetLastError - %d", GetLastError());
		return false;
	}

	rBfh = ReadFile(FileHandle, &bfh, sizeof(bfh), &nBytesRead, NULL); // Чтение первого заголовков
	if (rBfh && nBytesRead == 0) {
		printf("Ошибка чтения первого заголовка GetLastError = %d", GetLastError());
		return false;
	}

	rBih = ReadFile(FileHandle, &bih, sizeof(bih), &nBytesRead, NULL); // Чтение втрого заголовка
	if (rBih && nBytesRead == 0) {
		printf("Ошибка чтения второго заголовка GetLastError = %d", GetLastError());
		return false;
	}

	width = bih.biWidth;
	height = bih.biHeight;
	sizeColor = width * height * 3;

	buf = new BYTE[sizeColor];
	TxBits = new BYTE[sizeColor];
	rPix = ReadFile(FileHandle, buf, sizeColor, &nBytesRead, NULL);
	if (rPix && nBytesRead == 0) {
		printf("Ошибка чтения пикселей GetLastError = %d", GetLastError());
		return false;
	}

	for (INT i = 0; i < sizeColor; i += 3) // переписали с BGR в RGB { [R], [G], [B], [R], [G] ... }
	{
		TxBits[i] = buf[i + 2];
		TxBits[i + 1] = buf[i + 1];
		TxBits[i + 2] = buf[i];
	}
	
	offSetTxBits = 3;
	INT* szFileArr = DecryptionSizeTxt(TxBits, offSetTxBits);
	offSetTxBits += 9;
	INT szFile = 0;
	if (szFileArr[0] != 0)
		szFile = szFileArr[0] * 100 + szFileArr[1] * 10 + szFileArr[2];
	else if (szFileArr[1] != 0)
		szFile = szFileArr[1] * 10 + szFileArr[2];
	else if (szFileArr[2] != 0)
		szFile = szFileArr[2];

	resText = DecryptionAllTxt(TxBits, offSetTxBits, sizeColor, szFile);

	CreateHandleFile(&hFileTxtD, retrieve_file, GENERIC_WRITE, CREATE_ALWAYS);
	if (hFileTxtD == INVALID_HANDLE_VALUE)
	{
		printf("Error Load TxtFile file! GetLastError - %d", GetLastError());
		return false;
	}

	DWORD r;
	BOOL da = WriteFile(hFileTxtD, resText, szFile, &r, NULL);
	if (da == 0)
		printf("GetLastError %d", GetLastError());

	CloseHandle(hFileTxtD);
	CloseHandle(FileHandle);
	delete[] buf;
	delete[] TxBits;
	delete[] resText;
	delete[] szFileArr;
	return true;
}

INT Check(CHAR* checkFile) {

	BITMAPFILEHEADER bfh = { 0 };	//Заголовок BMP файла
	BITMAPINFOHEADER bih = { 0 };	//Заголовок BMP файла
	BYTE* TxBits, * buf;			// массивы для цветов 
	DWORD nBytesRead;				// сколько данных прочтено с файла  
	HANDLE FileHandle;				// хендл, открываемого для чтения, файла 
	INT width, height;				// ширина и высота файла
	BOOL rBfh, rBih, rPix;			// чтение заголовков и пикселей
	INT sizeColor;					// Размер исходного рисунка
	INT offSetTxBits = 0;			// Смещение по массиву RGB
	BYTE EncrSym = '?';				// Символ закодированного файла

	CreateHandleFile(&FileHandle, checkFile, GENERIC_READ, OPEN_EXISTING);
	if (FileHandle == INVALID_HANDLE_VALUE)
	{
		printf("Error LoadImage file! GetLastError - %d", GetLastError());
		return false;
	}

	rBfh = ReadFile(FileHandle, &bfh, sizeof(bfh), &nBytesRead, NULL); // Чтение первого заголовков
	if (rBfh && nBytesRead == 0) {
		printf("Ошибка чтения первого заголовка GetLastError = %d", GetLastError());
		return false;
	}

	rBih = ReadFile(FileHandle, &bih, sizeof(bih), &nBytesRead, NULL); // Чтение втрого заголовка
	if (rBih && nBytesRead == 0) {
		printf("Ошибка чтения второго заголовка GetLastError = %d", GetLastError());
		return false;
	}

	width = bih.biWidth;
	height = bih.biHeight;
	sizeColor = width * height * 3;

	buf = new BYTE[sizeColor];
	TxBits = new BYTE[sizeColor];
	rPix = ReadFile(FileHandle, buf, sizeColor, &nBytesRead, NULL);
	if (rPix && nBytesRead == 0) {
		printf("Ошибка чтения пикселей GetLastError = %d", GetLastError());
		return false;
	}

	for (INT i = 0; i < sizeColor; i += 3) // переписали с BGR в RGB { [R], [G], [B], [R], [G] ... }
	{
		TxBits[i] = buf[i + 2];
		TxBits[i + 1] = buf[i + 1];
		TxBits[i + 2] = buf[i];
	}


	BOOL Check = CheckEncr(TxBits[0], TxBits[1], TxBits[2]);
	if (Check == 1)
		printf("Зашифрован\n");
	else
		printf("Не зашифрован\n");

	CloseHandle(FileHandle);
	delete[] buf;
	delete[] TxBits;
	return true;
}

INT main() {

	SetConsoleOutputCP(1251);
	embed((CHAR*)"test2.bmp", (CHAR*)"Entext.txt");
	Check((CHAR*)"Embed.bmp");
	retrieve((CHAR*)"Embed.bmp", (CHAR*)"Rtest.txt");
	return 1;
}

//INT main(INT argc, CHAR* argv[])
//{
//	if (argv[1] == "-embed")
//		embed(argv[2], argv[3]);
//	else if (argv[1] == "-retrive")
//		retrieve(argv[2], argv[3]);
//	else if (argv[1] == "-check")
//		Check(argv[1]);
//	else
//		printf("Invalid_File_Name!");
//	return 0;
//}